#!/usr/bin/env sh

set -e

VAULT_ADDR="https://localhost:8200"

# Detect repository layout for secrets: prefer ./secrets at root, fallback to ./srcs/secrets
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
if [ -n "${SECRETS_ROOT:-}" ]; then
  SECRETS_ROOT="$SECRETS_ROOT"
elif [ -d "$REPO_ROOT/secrets" ] || [ ! -d "$REPO_ROOT/srcs/secrets" ]; then
  SECRETS_ROOT="$REPO_ROOT/secrets"
else
  SECRETS_ROOT="$REPO_ROOT/srcs/secrets"
fi

# Local paths
ROLE_FILE="$SECRETS_ROOT/api-approle/role_id"
SECRET_FILE="$SECRETS_ROOT/api-approle/secret_id"
UNSEAL_KEY_FILE="$SECRETS_ROOT/vault/unseal_key"
ROOT_TOKEN_FILE="$SECRETS_ROOT/vault/root_token"
CERT_DIR="$SECRETS_ROOT/certs"

# Verify that root_token exists for bootstrap
if [ ! -f "$ROOT_TOKEN_FILE" ]; then
  echo "❌ Missing $ROOT_TOKEN_FILE for bootstrap."
  exit 1
fi
ROOT_TOKEN="$(cat "$ROOT_TOKEN_FILE")"

# Check if Vault is sealed using curl
echo "==> Checking seal status..."
SEALED=$(curl -sk "$VAULT_ADDR/v1/sys/seal-status" | grep '"sealed":true' || echo "")
if [ -n "$SEALED" ]; then
  echo "==> Unsealing Vault..."
  # Read unseal_key from file (keep for bootstrap)
  UNSEAL_KEY=$(cat "$UNSEAL_KEY_FILE")
  curl -sk -X POST -d "{\"key\":\"$UNSEAL_KEY\"}" "$VAULT_ADDR/v1/sys/unseal" >/dev/null
fi

# Authentication with AppRole using curl
echo "==> Logging in to Vault with AppRole..."
# Read role_id and secret_id from Vault
ROLE_ID=$(curl -sk -H "X-Vault-Token: $ROOT_TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/secrets" | grep -o '"role_id":"[^"]*"' | cut -d'"' -f4)
SECRET_ID=$(curl -sk -H "X-Vault-Token: $ROOT_TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/secrets" | grep -o '"secret_id":"[^"]*"' | cut -d'"' -f4)

TOKEN=$(curl -sk -X POST "$VAULT_ADDR/v1/auth/approle/login" \
  -d "{\"role_id\":\"$ROLE_ID\",\"secret_id\":\"$SECRET_ID\"}" | \
  grep -o '"client_token":"[^"]*"' | cut -d'"' -f4)

if [ -z "$TOKEN" ]; then
  echo "❌ Couldn't get token. Is Vault running and unsealed?"
  exit 1
fi

# Reading secrets from Vault KV using curl
echo "==> Reading secrets from kv/transcendence/api ..."
JSON=$(curl -sk -H "X-Vault-Token: $TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/api")

# Extracting values using grep and cut (without jq)
JWT_SECRET=$(echo "$JSON" | grep -o '"JWT_SECRET":"[^"]*"' | cut -d'"' -f4 || echo "empty")
DB_PASSWORD=$(echo "$JSON" | grep -o '"DB_PASSWORD":"[^"]*"' | cut -d'"' -f4 || echo "empty")
OAUTH_SECRET=$(echo "$JSON" | grep -o '"OAUTH_CLIENT_SECRET":"[^"]*"' | cut -d'"' -f4 || echo "empty")

# Read certificates from filesystem (or from Vault if preferred)
if [ -r "$CERT_DIR/fullchain.pem" ]; then
  FULLCHAIN="$(cat "$CERT_DIR/fullchain.pem")"
else
  # Fallback to Vault
  FULLCHAIN=$(curl -sk -H "X-Vault-Token: $TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/certs" | grep -o '"fullchain":"[^"]*"' | cut -d'"' -f4 | sed 's/\\n/\n/g')
fi
if [ -r "$CERT_DIR/privkey.pem" ]; then
  PRIVKEY="$(cat "$CERT_DIR/privkey.pem")"
else
  # Fallback to Vault
  PRIVKEY=$(curl -sk -H "X-Vault-Token: $TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/certs" | grep -o '"privkey":"[^"]*"' | cut -d'"' -f4 | sed 's/\\n/\n/g')
fi

echo
echo "✅ Secrets from Vault (AppRole from Vault):"
echo "JWT_SECRET=$JWT_SECRET"
echo "DB_PASSWORD=$DB_PASSWORD"
echo "OAUTH_CLIENT_SECRET=$OAUTH_SECRET"
echo "FULLCHAIN:"
echo "$FULLCHAIN"
echo "PRIVKEY:"
echo "$PRIVKEY"

# Seal Vault using root_token if available
if [ -f "$ROOT_TOKEN_FILE" ]; then
  echo "==> Sealing Vault..."
  ROOT_TOKEN="$(cat "$ROOT_TOKEN_FILE")"
  HTTP_CODE=$(curl -sk -w '%{http_code}' -o /dev/null -X PUT \
    -H "X-Vault-Token: $ROOT_TOKEN" "$VAULT_ADDR/v1/sys/seal")
  if [ "$HTTP_CODE" = "204" ]; then
    echo "✅ Vault has been sealed successfully."
  else
    echo "⚠️  Could not seal Vault (HTTP $HTTP_CODE)."
  fi
else
  echo "⚠️  root_token not found; skipping seal."
fi