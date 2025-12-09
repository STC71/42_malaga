#!/usr/bin/env bash
# filepath: /home/robi/Escritorio/Transcendence/srcs/scripts/01.init_waf_and_vault.sh
# Prepares logs, certificates, Vault and AppRole for the Transcendence stack (HTTPS only).
#
# Note: This script does not use mandatory bind-mounts. It saves the keys to
# srcs/secrets/vault on the host and also attempts to write them inside the
# Vault container (/srcs/secrets/vault) for compatibility with
# named volumes. If you use named volumes, the secrets will be persisted to
# the Docker volumes; otherwise, they are saved on the host.
set -euo pipefail

# ---------- Paths ----------
BASE_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
SRC_DIR="$BASE_DIR/srcs"

# Vault address for API calls
VAULT_ADDR="https://127.0.0.1:8200"

# Allow new layout where `secrets/` lives at repo root (preferred) or fall back to
# legacy `srcs/secrets/`. This mirrors the logic in 00.gen_selfsigned_cert.sh so
# both scripts behave consistently after the redesign.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

if [ -n "${SECRETS_ROOT:-}" ]; then
  SECRETS_ROOT="$SECRETS_ROOT"
elif [ -d "$REPO_ROOT/secrets" ] || [ ! -d "$REPO_ROOT/srcs/secrets" ]; then
  SECRETS_ROOT="$REPO_ROOT/secrets"
else
  SECRETS_ROOT="$SRC_DIR/secrets"
fi

LOGS_NGX_DIR="$SRC_DIR/logs/nginx"
LOGS_MODSEC_DIR="$SRC_DIR/logs/modsec"
SECRETS_VAULT_DIR="$SECRETS_ROOT/vault"
SECRETS_APPROLE_DIR="$SECRETS_ROOT/api-approle"
CERTS_DIR="$SECRETS_ROOT/certs"

# Vault config/data still live under srcs/data by default. If you have a different
# layout you can set VAULT_CFG_DIR/VAULT_DATA_DIR env vars before running the script.
VAULT_CFG_DIR="${VAULT_CFG_DIR:-$SRC_DIR/data/vault/config}"
VAULT_DATA_DIR="${VAULT_DATA_DIR:-$SRC_DIR/data/vault/file}"
VAULT_HCL="$VAULT_CFG_DIR/vault.hcl"

# ---------- Helpers ----------
# Detect compose command available: prefer `docker compose` then fallback to `docker-compose`
if command -v docker >/dev/null 2>&1; then
  if docker compose version >/dev/null 2>&1; then
    DC="docker compose"
  elif command -v docker-compose >/dev/null 2>&1; then
    DC="docker-compose"
  else
    echo "Error: neither 'docker compose' nor 'docker-compose' is available in PATH" >&2
    exit 1
  fi
else
  echo "Error: docker command not found in PATH" >&2
  exit 1
fi

v() {
  # Execute Vault CLI inside the vault container using the detected compose tool.
  # shellcheck disable=SC2086
  if [ -t 1 ]; then
    $DC exec -it vault sh -c "export VAULT_ADDR=https://127.0.0.1:8200; export VAULT_SKIP_VERIFY=true; $*"
  else
    $DC exec -T vault sh -c "export VAULT_ADDR=https://127.0.0.1:8200; export VAULT_SKIP_VERIFY=true; $*"
  fi
}

ensure_line_in_file() {
  local line="$1" file="$2"
  grep -qxF "$line" "$file" 2>/dev/null || echo "$line" >> "$file"
}

wait_for_vault() {
  echo "==> Waiting for Vault to respond ..."
  for i in {1..30}; do
    out=$(v "vault status" 2>&1 || true)
    if echo "$out" | grep -qE 'Initialized|Sealed|Unsealed'; then
      echo "   Vault is responding."
      return 0
    fi
    sleep 1
  done
  echo "⚠️  Vault did not respond in time. This is normal with self-signed certificates in localhost."
  echo "   You can continue; scripts will work with VAULT_SKIP_VERIFY=true."
  return 0
}

# ---------- Prepare local folders ----------
echo "==> Preparing local folders under srcs/ ..."

mkdir -p "$LOGS_NGX_DIR" "$LOGS_MODSEC_DIR" "$SECRETS_VAULT_DIR" "$SECRETS_APPROLE_DIR" \
         "$VAULT_CFG_DIR" "$VAULT_DATA_DIR" "$CERTS_DIR"

# Create frontend/dist only in the real frontend folder. Some setups put the
# frontend at repo root (`$BASE_DIR/frontend`) while others may have it under
# `srcs/frontend`. Create `dist` only where a `frontend` directory exists to
# avoid creating an unwanted `srcs/frontend` folder.
if [ -d "$BASE_DIR/frontend" ]; then
  mkdir -p "$BASE_DIR/frontend/dist"
elif [ -d "$SRC_DIR/frontend" ]; then
  mkdir -p "$SRC_DIR/frontend/dist"
fi

chmod -R 775 "$SRC_DIR/logs" || true

# ---------- Ensure ModSecurity log files exist ----------
touch "$LOGS_MODSEC_DIR/modsec_audit.log" "$LOGS_MODSEC_DIR/modsec_debug.log"
chmod 666 "$LOGS_MODSEC_DIR/modsec_audit.log" "$LOGS_MODSEC_DIR/modsec_debug.log"

# ---------- Ensure Nginx log files exist ----------
touch "$LOGS_NGX_DIR/access.log" "$LOGS_NGX_DIR/error.log"
chmod 666 "$LOGS_NGX_DIR/access.log" "$LOGS_NGX_DIR/error.log"

# ---------- Ensure test certificates (self-signed) ----------
if [ ! -f "$CERTS_DIR/fullchain.pem" ] || [ ! -f "$CERTS_DIR/privkey.pem" ]; then
  echo "==> Generating self-signed TLS certificates for localhost ..."
  cat > "$CERTS_DIR/cert.conf" <<EOF
[req]
default_bits = 2048
prompt = no
default_md = sha256
distinguished_name = dn
x509_extensions = v3_req

[dn]
CN = localhost

[v3_req]
subjectAltName = @alt_names

[alt_names]
DNS.1 = localhost
IP.1 = 127.0.0.1
EOF

  openssl req -x509 -nodes -days 365 \
    -newkey rsa:2048 \
    -keyout "$CERTS_DIR/privkey.pem" \
    -out "$CERTS_DIR/fullchain.pem" \
    -config "$CERTS_DIR/cert.conf" \
    -extensions v3_req

  chmod 600 "$CERTS_DIR/privkey.pem"
  chmod 644 "$CERTS_DIR/fullchain.pem"
fi

# ---------- Minimal vault.hcl if missing ----------
if [ ! -f "$VAULT_HCL" ]; then
  cat > "$VAULT_HCL" <<'HCL'
ui = true
disable_mlock = true
listener "tcp" {
  address = "0.0.0.0:8200"
  tls_disable = 0
  tls_cert_file = "/vault/certs/fullchain.pem"
  tls_key_file  = "/vault/certs/privkey.pem"
}
storage  "file" { path = "/vault/file" }
log_level = "info"
HCL
  echo "   Created $VAULT_HCL"
fi

# ---------- .gitignore safety ----------
#ensure_line_in_file "srcs/secrets/" "$BASE_DIR/.gitignore"
#ensure_line_in_file "*.pem"         "$BASE_DIR/.gitignore"
#ensure_line_in_file "*.key"         "$BASE_DIR/.gitignore"
#ensure_line_in_file "srcs/.env"     "$BASE_DIR/.gitignore"

# ---------- Bring up Vault ----------
echo "==> Bringing up Vault ..."
# Use the detected compose command
# shellcheck disable=SC2086
$DC up -d vault || true

sleep 1
# shellcheck disable=SC2086
if ! $DC ps vault | grep -q "Up"; then
  echo "Vault is not Up. Showing last logs:"
  # shellcheck disable=SC2086
  $DC logs --tail=50 vault || true
  echo "Fix: ensure docker-compose.yml mounts ./srcs/data/vault/config:/vault/config, ./srcs/data/vault/file:/vault/file, and ./srcs/secrets/certs:/vault/certs"
  exit 1
fi

wait_for_vault

# ---------- (3) INIT + UNSEAL + LOGIN ----------
ROOT_TOKEN_FILE="$SECRETS_VAULT_DIR/root_token"
UNSEAL_KEY_FILE="$SECRETS_VAULT_DIR/unseal_key"

echo "==> Checking if Vault is initialized ..."
# Check Vault's actual initialization status via API
VAULT_INITIALIZED=$(curl -sk "$VAULT_ADDR/v1/sys/seal-status" 2>/dev/null | jq -r '.initialized // "false"' || echo "false")
if [ "$VAULT_INITIALIZED" = "true" ]; then
  echo "   Vault is already initialized."
  # Ensure we have the token files; if not, try to recover or warn
  if [ ! -f "$ROOT_TOKEN_FILE" ] || [ ! -f "$UNSEAL_KEY_FILE" ]; then
    echo "⚠️  Warning: Vault is initialized but token files are missing. Intentando resetear Vault automáticamente..."
    if command -v make >/dev/null 2>&1; then
      make vault-reset
      echo "Vault reseteado. Reiniciando inicialización..."
      chmod +x "$0"
      exec "$0"
    else
      echo "Error: 'make' no está disponible. Por favor, resetea Vault manualmente con 'make vault-reset' y vuelve a ejecutar este script."
      exit 1
    fi
  fi
else
  echo "==> Initializing Vault ..."
  # Limpiar archivos previos para evitar inconsistencias.
  rm -f "$UNSEAL_KEY_FILE" "$ROOT_TOKEN_FILE" "$SECRETS_VAULT_DIR/init.txt"
  # Inicializar Vault en el contenedor principal usando exec -T (no requiere TTY).
  if [ -t 1 ]; then
    INIT_OUT=$($DC exec -it vault vault operator init -key-shares=1 -key-threshold=1)
  else
    echo "❌ Error: No hay TTY disponible para inicializar Vault. Ejecuta manualmente:"
    echo "$DC exec -it vault vault operator init -key-shares=1 -key-threshold=1"
    echo "Luego vuelve a ejecutar este script."
    # Limpiar archivos huérfanos si existen y la inicialización manual se realizó fuera del script
    if [ -f "$UNSEAL_KEY_FILE" ] && [ -f "$ROOT_TOKEN_FILE" ] && [ -f "$SECRETS_VAULT_DIR/init.txt" ]; then
      echo "Detectados archivos de inicialización manual. Limpiando y regenerando..."
      rm -f "$UNSEAL_KEY_FILE" "$ROOT_TOKEN_FILE" "$SECRETS_VAULT_DIR/init.txt"
    fi
    exit 1
  fi
  # El resto del proceso regenera los archivos correctamente.
  UNSEAL_KEY="$(echo "$INIT_OUT" | awk -F': ' '/Unseal Key 1/ {print $2; exit}')"
  ROOT_TOKEN="$(echo "$INIT_OUT" | awk -F': ' '/Initial Root Token/ {print $2; exit}')"
  if [ -z "$UNSEAL_KEY" ] || [ -z "$ROOT_TOKEN" ]; then
    echo "Error: could not parse init output:"
    echo "$INIT_OUT"
    exit 1
  fi

  # Save into the Vault container's persistent named volume
  printf '%s\n' "$INIT_OUT" | $DC exec -i vault sh -c "mkdir -p /srcs/secrets/vault && cat > /srcs/secrets/vault/init.txt"
  printf '%s' "$UNSEAL_KEY" | $DC exec -i vault sh -c "cat > /srcs/secrets/vault/unseal_key"
  printf '%s' "$ROOT_TOKEN" | $DC exec -i vault sh -c "cat > /srcs/secrets/vault/root_token"
  
  # If host secrets dir exists and is writable (only when bind-mounted), save there too.
  if [ -d "$SECRETS_VAULT_DIR" ] && [ -w "$SECRETS_VAULT_DIR" ]; then
    printf "%s" "$UNSEAL_KEY" > "$UNSEAL_KEY_FILE"
    printf "%s" "$ROOT_TOKEN" > "$ROOT_TOKEN_FILE"
    printf '%s\n' "$INIT_OUT" > "$SECRETS_VAULT_DIR/init.txt"
    echo "   Saved unseal key and root token under $SECRETS_VAULT_DIR/ (host)"
  else
    echo "   Saved unseal key and root token inside the Vault container at /srcs/secrets/vault/"
    echo "   Attempting to copy generated keys from the container to the host repo path (no bind-mount required)."
    # Ensure host dir exists and try to copy files out of the container. If docker cp fails
    # we continue without error so the script remains idempotent.
    mkdir -p "$SECRETS_VAULT_DIR" || true
    docker cp vault:/srcs/secrets/vault/. "$SECRETS_VAULT_DIR" 2>/dev/null || true
    # Fix permissions if files were copied
    chmod 600 "$SECRETS_VAULT_DIR/unseal_key" 2>/dev/null || true
    chmod 600 "$SECRETS_VAULT_DIR/root_token" 2>/dev/null || true
    echo "   If the copy succeeded, files are now under $SECRETS_VAULT_DIR/ on the host."
  fi
fi

# Ensure init.txt exists under host secrets when possible. If the host secrets
# directory exists but init.txt is missing, try to create it from the existing
# token files or copy it from the container. This keeps a human-readable init
# output in `SECRETS_VAULT_DIR/init.txt` for convenience.
if [ -d "$SECRETS_VAULT_DIR" ]; then
  if [ ! -f "$SECRETS_VAULT_DIR/init.txt" ]; then
    echo "==> Creating missing $SECRETS_VAULT_DIR/init.txt from available keys..."
    if [ -f "$UNSEAL_KEY_FILE" ] && [ -f "$ROOT_TOKEN_FILE" ]; then
      UNSEAL_KEY_EXISTING="$(cat "$UNSEAL_KEY_FILE")"
      ROOT_TOKEN_EXISTING="$(cat "$ROOT_TOKEN_FILE")"
      {
        printf 'Unseal Key 1: %s\n\n' "$UNSEAL_KEY_EXISTING"
        printf 'Initial Root Token: %s\n' "$ROOT_TOKEN_EXISTING"
      } > "$SECRETS_VAULT_DIR/init.txt" || true
      echo "   Wrote $SECRETS_VAULT_DIR/init.txt from host token files."
    else
      # Try to copy from container if present
      if command -v docker >/dev/null 2>&1; then
        docker cp vault:/srcs/secrets/vault/init.txt "$SECRETS_VAULT_DIR/" 2>/dev/null || true
        if [ -f "$SECRETS_VAULT_DIR/init.txt" ]; then
          echo "   Copied init.txt from container to $SECRETS_VAULT_DIR/."
        else
          echo "   Could not create init.txt: no token files and no container copy available."
        fi
      else
        echo "   Docker not available; cannot copy init.txt from container."
      fi
    fi
    chmod 600 "$SECRETS_VAULT_DIR/init.txt" 2>/dev/null || true
  fi
fi

echo "==> Checking sealed state ..."
VAULT_STATUS=$(v "vault status" 2>&1 || true)
if echo "$VAULT_STATUS" | grep -q "Sealed.*true"; then
  echo "==> Unsealing ..."
  UNSEAL_KEY="$(cat "$UNSEAL_KEY_FILE")"
  v "vault operator unseal '$UNSEAL_KEY'"
else
  echo "   Already unsealed."
fi

echo "==> Login with root token ..."
ROOT_TOKEN="$(cat "$ROOT_TOKEN_FILE")"
v "vault login '$ROOT_TOKEN'"

# ---------- (4) KV v2 + demo data ----------
echo "==> Enabling KV v2 at 'kv' ..."
# idempotent: ignore if already enabled
v "vault secrets enable -path=kv kv-v2 >/dev/null 2>&1 || true"

JWT_SECRET_VAL="superjwt"
DB_PASSWORD_VAL="sup3r_pwd"
OAUTH_SECRET_VAL="foo_bar_baz"

# Load variables from .env if it exists and is valid
if [ -f "$SRC_DIR/secrets/.env" ]; then
  # Check if .env file has valid syntax before sourcing
  if bash -n "$SRC_DIR/secrets/.env" 2>/dev/null; then
    . "$SRC_DIR/secrets/.env"
    JWT_SECRET_VAL="${JWT_SECRET:-$JWT_SECRET_VAL}"
    DB_PASSWORD_VAL="${DB_PASSWORD:-$DB_PASSWORD_VAL}"
    OAUTH_SECRET_VAL="${OAUTH_CLIENT_SECRET:-$OAUTH_SECRET_VAL}"
  else
    echo "⚠️  Warning: .env file has syntax errors, using default values"
  fi
fi

echo "==> Writing sample secrets at kv/transcendence/api ..."
v "vault kv put kv/transcendence/api JWT_SECRET='$JWT_SECRET_VAL' DB_PASSWORD='$DB_PASSWORD_VAL' OAUTH_CLIENT_SECRET='$OAUTH_SECRET_VAL'"

# Store certificates in Vault
if [ -f "$SRC_DIR/secrets/certs/fullchain.pem" ] && [ -f "$SRC_DIR/secrets/certs/privkey.pem" ]; then
  FULLCHAIN=$(cat "$SRC_DIR/secrets/certs/fullchain.pem")
  PRIVKEY=$(cat "$SRC_DIR/secrets/certs/privkey.pem")
  v "vault kv put kv/transcendence/certs fullchain='$FULLCHAIN' privkey='$PRIVKEY'"
  echo "   Certificates stored in Vault."
fi

# ---------- (5) Least-privilege policy ----------
echo "==> Writing policy 'transcendence-api' ..."
v "sh -lc 'cat >/tmp/transcendence-api.hcl <<\"HCL\"
path \"kv/data/transcendence/*\" {
  capabilities = [\"read\", \"list\"]
}
path \"kv/metadata/transcendence/*\" {
  capabilities = [\"list\"]
}
HCL
vault policy write transcendence-api /tmp/transcendence-api.hcl >/dev/null
rm -f /tmp/transcendence-api.hcl'"

# ---------- (6) AppRole ----------
echo "==> Enabling AppRole and creating role ..."
# idempotent: ignore if approle already enabled
v "vault auth enable approle >/dev/null 2>&1 || true"

# Create/Update role
v "vault write auth/approle/role/transcendence-api \
  token_policies=transcendence-api \
  token_ttl=1h token_max_ttl=24h" >/dev/null

echo "==> Fetching RoleID and generating SecretID ..."
ROLE_ID="$(v 'vault read -field=role_id auth/approle/role/transcendence-api/role-id' | tr -d '\r')"
SECRET_ID="$(v 'vault write -f -field=secret_id auth/approle/role/transcendence-api/secret-id' | tr -d '\r')"

# Store role_id and secret_id in Vault KV instead of files
v "vault kv put kv/transcendence/secrets role_id='$ROLE_ID' secret_id='$SECRET_ID'"

# Do NOT create files
# mkdir -p "$SECRETS_APPROLE_DIR"
# printf "%s" "$ROLE_ID"   > "$SECRETS_APPROLE_DIR/role_id"
# printf "%s" "$SECRET_ID" > "$SECRETS_APPROLE_DIR/secret_id"
# chmod 600 "$SECRETS_APPROLE_DIR/role_id" "$SECRETS_APPROLE_DIR/secret_id"

echo
echo "===================================================================="
echo "✅ Done."
echo "  Logs (Nginx):       $LOGS_NGX_DIR"
echo "  Logs (ModSec):      $LOGS_MODSEC_DIR"
echo "  Vault root token:   $ROOT_TOKEN_FILE"
echo "  Vault unseal key:   $UNSEAL_KEY_FILE"
echo "  AppRole credentials stored securely in Vault."
echo
echo "Next: run 'bash srcs/scripts/02.read_vault_from_host.sh' to read secrets."
echo "===================================================================="