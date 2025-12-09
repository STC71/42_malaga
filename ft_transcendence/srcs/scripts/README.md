# 🔧 Scripts - Automatización de Inicialización y Mantenimiento

## 📋 Descripción General

Este directorio contiene **scripts de shell (bash)** para automatizar tareas críticas de inicialización, configuración y mantenimiento del proyecto Transcendence. Los scripts gestionan certificados SSL, inicialización de Vault, logs de ModSecurity, y testing de reglas WAF.

## 🗂️ Estructura de Scripts

```
scripts/
├── 00.gen_selfsigned_cert.sh           # Generar certificados SSL autofirmados
├── 01.init_waf_and_vault.sh            # Inicializar WAF y HashiCorp Vault
├── 02.read_vault_from_host.sh          # Leer secretos de Vault desde host
├── 03.test_vault_secrets_from_container.sh  # Test de Vault en container
└── 99.test_modsec_rules.sh             # Testing de reglas ModSecurity
```

---

## 🔐 `00.gen_selfsigned_cert.sh` - Generación de Certificados SSL

### Propósito

Generar certificados SSL/TLS **autofirmados** para desarrollo local con HTTPS.

### Funcionamiento

```bash
#!/usr/bin/env bash
set -euo pipefail

# 1. Detectar directorio de certificados
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

if [ -d "$REPO_ROOT/secrets" ]; then
  CERT_DIR="$REPO_ROOT/secrets/certs"
else
  CERT_DIR="$REPO_ROOT/srcs/secrets/certs"
fi

mkdir -p "$CERT_DIR"

# 2. Verificar si ya existen certificados
if [ ! -f "$CERT_DIR/fullchain.pem" ] || [ ! -f "$CERT_DIR/privkey.pem" ]; then
  echo "==> Generating self-signed TLS certificates for localhost ..."
  
  # 3. Crear archivo de configuración OpenSSL
  cat > "$CERT_DIR/cert.conf" <<EOF
[req]
default_bits = 2048
prompt = no
default_md = sha256
distinguished_name = dn
x509_extensions = v3_req

[dn]
C=ES
ST=Madrid
L=Madrid
O=42 School
OU=Transcendence Project
CN=localhost

[v3_req]
subjectAltName = @alt_names

[alt_names]
DNS.1 = localhost
DNS.2 = transcendence.local
IP.1 = 127.0.0.1
IP.2 = ::1
EOF

  # 4. Generar certificado autofirmado (válido 365 días)
  openssl req \
    -x509 \
    -nodes \
    -days 365 \
    -newkey rsa:2048 \
    -keyout "$CERT_DIR/privkey.pem" \
    -out "$CERT_DIR/fullchain.pem" \
    -config "$CERT_DIR/cert.conf"

  echo "✅ Certificates generated at $CERT_DIR"
  echo "   - fullchain.pem (public certificate)"
  echo "   - privkey.pem (private key)"
else
  echo "ℹ️  Certificates already exist at $CERT_DIR"
fi
```

### Uso

```bash
# Ejecutar desde cualquier directorio
./srcs/scripts/00.gen_selfsigned_cert.sh

# O desde raíz del proyecto
make certs  # Si existe target en Makefile
```

### Salida

```
==> Generating self-signed TLS certificates for localhost ...
Generating a RSA private key
..........+++++
..................+++++
writing new private key to '/path/to/secrets/certs/privkey.pem'
-----
✅ Certificates generated at /path/to/secrets/certs
   - fullchain.pem (public certificate)
   - privkey.pem (private key)
```

### Advertencias de Navegador

⚠️ Los certificados autofirmados generarán advertencias en navegadores:

- **Chrome/Edge**: "Your connection is not private" (NET::ERR_CERT_AUTHORITY_INVALID)
- **Firefox**: "Warning: Potential Security Risk Ahead"

**Solución**: Hacer clic en "Advanced" → "Proceed to localhost (unsafe)" durante desarrollo.

---

## 🚀 `01.init_waf_and_vault.sh` - Inicialización Completa

### Propósito

Script maestro que inicializa **todos los componentes de seguridad**:
1. Directorios de logs (Nginx + ModSecurity)
2. Certificados SSL (llama a `00.gen_selfsigned_cert.sh`)
3. HashiCorp Vault (unsealing + configuración)
4. AppRole credentials para autenticación

### Estructura

```bash
#!/usr/bin/env bash
set -euo pipefail

# ========== CONFIGURACIÓN DE PATHS ==========
BASE_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
SRC_DIR="$BASE_DIR/srcs"
SECRETS_ROOT="$BASE_DIR/secrets"  # o $SRC_DIR/secrets (legacy)

LOGS_NGX_DIR="$SRC_DIR/logs/nginx"
LOGS_MODSEC_DIR="$SRC_DIR/logs/modsec"
SECRETS_VAULT_DIR="$SECRETS_ROOT/vault"
SECRETS_APPROLE_DIR="$SECRETS_ROOT/api-approle"
CERTS_DIR="$SECRETS_ROOT/certs"

# ========== PASO 1: DIRECTORIOS DE LOGS ==========
echo "==> Creating log directories..."
mkdir -p "$LOGS_NGX_DIR" "$LOGS_MODSEC_DIR"
chmod 755 "$LOGS_NGX_DIR" "$LOGS_MODSEC_DIR"

# ========== PASO 2: CERTIFICADOS SSL ==========
echo "==> Ensuring TLS certificates exist..."
if [ ! -f "$CERTS_DIR/fullchain.pem" ]; then
  "$BASE_DIR/srcs/scripts/00.gen_selfsigned_cert.sh"
fi

# ========== PASO 3: INICIALIZAR VAULT ==========
echo "==> Initializing HashiCorp Vault..."
docker-compose up -d vault

# Esperar a que Vault esté disponible
echo "Waiting for Vault to be ready..."
until docker-compose exec -T vault vault status 2>/dev/null | grep -q "Sealed"; do
  sleep 2
done

# Inicializar Vault (solo si es primera vez)
if [ ! -f "$SECRETS_VAULT_DIR/init.txt" ]; then
  echo "==> Running vault operator init..."
  docker-compose exec -T vault vault operator init \
    -key-shares=5 \
    -key-threshold=3 \
    > "$SECRETS_VAULT_DIR/init.txt"
  
  # Extraer unseal keys y root token
  grep 'Unseal Key 1:' "$SECRETS_VAULT_DIR/init.txt" | awk '{print $4}' > "$SECRETS_VAULT_DIR/unseal_key"
  grep 'Initial Root Token:' "$SECRETS_VAULT_DIR/init.txt" | awk '{print $4}' > "$SECRETS_VAULT_DIR/root_token"
  
  chmod 600 "$SECRETS_VAULT_DIR"/*
  echo "✅ Vault initialized. Keys saved to $SECRETS_VAULT_DIR"
fi

# ========== PASO 4: UNSEAL VAULT ==========
echo "==> Unsealing Vault..."
UNSEAL_KEY=$(head -n 1 "$SECRETS_VAULT_DIR/unseal_key")
docker-compose exec -T vault vault operator unseal "$UNSEAL_KEY"

# ========== PASO 5: CONFIGURAR APPROLE ==========
ROOT_TOKEN=$(cat "$SECRETS_VAULT_DIR/root_token")
echo "==> Configuring AppRole authentication..."

# Login con root token
docker-compose exec -T vault vault login "$ROOT_TOKEN"

# Habilitar AppRole auth method
docker-compose exec -T vault vault auth enable approle || true

# Crear política para API
cat > /tmp/api-policy.hcl <<EOF
path "secret/data/*" {
  capabilities = ["read"]
}
EOF

docker-compose exec -T vault vault policy write api-policy /tmp/api-policy.hcl

# Crear AppRole
docker-compose exec -T vault vault write auth/approle/role/api-role \
  token_ttl=1h \
  token_max_ttl=4h \
  policies=api-policy

# Obtener role_id y secret_id
ROLE_ID=$(docker-compose exec -T vault vault read -field=role_id auth/approle/role/api-role/role-id)
SECRET_ID=$(docker-compose exec -T vault vault write -f -field=secret_id auth/approle/role/api-role/secret-id)

echo "$ROLE_ID" > "$SECRETS_APPROLE_DIR/role_id"
echo "$SECRET_ID" > "$SECRETS_APPROLE_DIR/secret_id"
chmod 600 "$SECRETS_APPROLE_DIR"/*

echo "✅ AppRole configured. Credentials saved to $SECRETS_APPROLE_DIR"

# ========== PASO 6: GUARDAR SECRETOS EN VAULT ==========
echo "==> Storing application secrets in Vault..."
docker-compose exec -T vault vault kv put secret/database \
  username=transcendence \
  password=supersecret123

docker-compose exec -T vault vault kv put secret/jwt \
  secret=$(openssl rand -base64 32) \
  refresh_secret=$(openssl rand -base64 32)

echo "✅ Secrets stored in Vault"
echo "=================================================="
echo "Initialization complete!"
echo "Nginx logs: $LOGS_NGX_DIR"
echo "ModSecurity logs: $LOGS_MODSEC_DIR"
echo "Vault keys: $SECRETS_VAULT_DIR"
echo "AppRole creds: $SECRETS_APPROLE_DIR"
echo "=================================================="
```

### Uso

```bash
# Primera ejecución (inicializa todo)
./srcs/scripts/01.init_waf_and_vault.sh

# O mediante Makefile
make init
```

### Output Esperado

```
==> Creating log directories...
==> Ensuring TLS certificates exist...
ℹ️  Certificates already exist
==> Initializing HashiCorp Vault...
Creating vault ... done
Waiting for Vault to be ready...
==> Running vault operator init...
✅ Vault initialized. Keys saved to /path/to/secrets/vault
==> Unsealing Vault...
Key                Value
---                -----
Sealed             false
==> Configuring AppRole authentication...
✅ AppRole configured. Credentials saved to /path/to/secrets/api-approle
==> Storing application secrets in Vault...
✅ Secrets stored in Vault
==================================================
Initialization complete!
==================================================
```

---

## 🔍 `02.read_vault_from_host.sh` - Leer Secretos desde Host

### Propósito

Script de utilidad para **leer secretos de Vault desde el host** (fuera de contenedores).

### Implementación

```bash
#!/usr/bin/env bash
set -euo pipefail

SECRETS_ROOT="${SECRETS_ROOT:-./secrets}"
VAULT_ADDR="http://localhost:8200"

# Leer root token
ROOT_TOKEN=$(cat "$SECRETS_ROOT/vault/root_token")

# Login
export VAULT_ADDR
export VAULT_TOKEN="$ROOT_TOKEN"

# Leer secreto específico
echo "==> Reading JWT secret from Vault..."
vault kv get -field=secret secret/jwt

echo "==> Reading database credentials..."
vault kv get secret/database
```

### Uso

```bash
./srcs/scripts/02.read_vault_from_host.sh
```

---

## 🐳 `03.test_vault_secrets_from_container.sh` - Test en Container

### Propósito

Verificar que el **backend puede leer secretos de Vault usando AppRole** desde dentro del contenedor.

### Test

```bash
#!/usr/bin/env bash
set -euo pipefail

echo "==> Testing Vault access from backend container..."

# Ejecutar dentro del container backend
docker-compose exec backend node -e "
const fs = require('fs');
const axios = require('axios');

const roleId = fs.readFileSync('/app/secrets/api-approle/role_id', 'utf8').trim();
const secretId = fs.readFileSync('/app/secrets/api-approle/secret_id', 'utf8').trim();

(async () => {
  // 1. Autenticarse con AppRole
  const authResp = await axios.post('http://vault:8200/v1/auth/approle/login', {
    role_id: roleId,
    secret_id: secretId
  });
  
  const token = authResp.data.auth.client_token;
  console.log('✅ AppRole login successful');
  
  // 2. Leer secreto
  const secretResp = await axios.get('http://vault:8200/v1/secret/data/jwt', {
    headers: { 'X-Vault-Token': token }
  });
  
  console.log('✅ JWT secret retrieved:', secretResp.data.data.data.secret);
})();
"
```

---

## 🛡️ `99.test_modsec_rules.sh` - Testing de WAF

### Propósito

Ejecutar **baterías de tests contra ModSecurity** para validar reglas.

### Tests Implementados

```bash
#!/usr/bin/env bash
set -euo pipefail

BASE_URL="https://localhost"
TESTS_PASSED=0
TESTS_FAILED=0

run_test() {
  local NAME="$1"
  local URL="$2"
  local EXPECTED_CODE="$3"
  
  echo -n "Testing $NAME... "
  RESPONSE_CODE=$(curl -k -s -o /dev/null -w "%{http_code}" "$URL")
  
  if [ "$RESPONSE_CODE" -eq "$EXPECTED_CODE" ]; then
    echo "✅ PASS (got $RESPONSE_CODE)"
    ((TESTS_PASSED++))
  else
    echo "❌ FAIL (expected $EXPECTED_CODE, got $RESPONSE_CODE)"
    ((TESTS_FAILED++))
  fi
}

# ========== TESTS ==========

# 1. XSS Attacks (debe ser bloqueado: 403)
run_test "XSS in query param" \
  "$BASE_URL/api/users?search=<script>alert(1)</script>" \
  403

# 2. SQL Injection (debe ser bloqueado: 403)
run_test "SQLi UNION attack" \
  "$BASE_URL/api/users?id=1' UNION SELECT * FROM passwords--" \
  403

# 3. Path Traversal (debe ser bloqueado: 403)
run_test "LFI attempt" \
  "$BASE_URL/api/files?path=../../../../etc/passwd" \
  403

# 4. Request válido (debe pasar: 200/401)
run_test "Valid API request" \
  "$BASE_URL/api/healthz" \
  200

# 5. Login rate limiting (5to request debe fallar: 429)
for i in {1..6}; do
  curl -k -s -X POST "$BASE_URL/api/auth/login" \
    -H "Content-Type: application/json" \
    -d '{"username":"test","password":"test"}' \
    -o /dev/null
done
run_test "Login rate limit (6th request)" \
  "$BASE_URL/api/auth/login" \
  429

# ========== RESULTADOS ==========
echo ""
echo "=============================="
echo "Tests Passed: $TESTS_PASSED"
echo "Tests Failed: $TESTS_FAILED"
echo "=============================="

[ $TESTS_FAILED -eq 0 ] && exit 0 || exit 1
```

### Ejecutar Tests

```bash
./srcs/scripts/99.test_modsec_rules.sh
```

### Output

```
Testing XSS in query param... ✅ PASS (got 403)
Testing SQLi UNION attack... ✅ PASS (got 403)
Testing LFI attempt... ✅ PASS (got 403)
Testing Valid API request... ✅ PASS (got 200)
Testing Login rate limit (6th request)... ✅ PASS (got 429)

==============================
Tests Passed: 5
Tests Failed: 0
==============================
```

---

## 🔗 Integración con Makefile

```makefile
# Makefile en raíz del proyecto

.PHONY: init certs test-waf

init:
	@echo "Initializing project..."
	./srcs/scripts/01.init_waf_and_vault.sh

certs:
	@echo "Generating SSL certificates..."
	./srcs/scripts/00.gen_selfsigned_cert.sh

test-waf:
	@echo "Testing ModSecurity rules..."
	./srcs/scripts/99.test_modsec_rules.sh

vault-read:
	@echo "Reading Vault secrets..."
	./srcs/scripts/02.read_vault_from_host.sh

vault-test:
	@echo "Testing Vault from container..."
	./srcs/scripts/03.test_vault_secrets_from_container.sh
```

---

**Ubicación**: `/srcs/scripts/`  
**Tecnologías**: Bash, OpenSSL, Docker Compose, HashiCorp Vault CLI, curl  
**Documentación relacionada**: 
- `../secrets/certs/README.md` - Certificados generados
- `../secrets/vault/README.md` - Keys de Vault
- `../conf/modsecurity/README.md` - Reglas WAF testeadas
