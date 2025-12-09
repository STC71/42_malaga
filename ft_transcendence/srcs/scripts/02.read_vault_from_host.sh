#!/usr/bin/env bash
# filepath: /mnt/c/users/usuario/desktop/Transcendence/srcs/scripts/02.read_vault_from_host.sh

set -euo pipefail

VAULT_ADDR="https://127.0.0.1:8200"

# Detect repository layout for secrets (prefer repo-root ./secrets, fallback to ./srcs/secrets)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
if [ -n "${SECRETS_ROOT:-}" ]; then
  SECRETS_ROOT="$SECRETS_ROOT"
elif [ -d "$REPO_ROOT/secrets" ] || [ ! -d "$REPO_ROOT/srcs/secrets" ]; then
  SECRETS_ROOT="$REPO_ROOT/secrets"
else
  SECRETS_ROOT="$REPO_ROOT/srcs/secrets"
fi

ROOT_TOKEN_FILE="$SECRETS_ROOT/vault/root_token"
UNSEAL_KEY_FILE="$SECRETS_ROOT/vault/unseal_key"

if ! command -v jq >/dev/null 2>&1; then
  echo "❌ jq is required but not installed."
  exit 1
fi

if [ ! -f "$ROOT_TOKEN_FILE" ]; then
  echo "❌ Missing $ROOT_TOKEN_FILE. Please run the init script first."
  exit 1
fi
ROOT_TOKEN="$(cat "$ROOT_TOKEN_FILE")"

if [ ! -f "$UNSEAL_KEY_FILE" ]; then
  echo "❌ Missing $UNSEAL_KEY_FILE. Cannot unseal Vault."
  exit 1
fi

echo "==> Checking seal status ..."
SEALED="$(curl -sk "$VAULT_ADDR/v1/sys/seal-status" | jq -r '.sealed')"
if [ "$SEALED" = "true" ]; then
  echo "==> Unsealing Vault..."
  UNSEAL_KEY="$(cat "$UNSEAL_KEY_FILE")"
  # It may require more than one call if there are multiple shares; in your case, one is sufficient.
  curl -sk -X POST -d "{\"key\":\"$UNSEAL_KEY\"}" "$VAULT_ADDR/v1/sys/unseal" >/dev/null
  SEALED_AFTER="$(curl -sk "$VAULT_ADDR/v1/sys/seal-status" | jq -r '.sealed')"
  if [ "$SEALED_AFTER" != "false" ]; then
    echo "❌ Vault is still sealed after unseal attempt."
    exit 1
  fi
else
  echo "   Vault already unsealed."
fi

echo "==> Reading secrets from kv/transcendence/api ..."
JSON="$(curl -sk -H "X-Vault-Token: $ROOT_TOKEN" "$VAULT_ADDR/v1/kv/data/transcendence/api")"

JWT_SECRET="$(echo "$JSON" | jq -r '.data.data.JWT_SECRET // empty')"
DB_PASSWORD="$(echo "$JSON" | jq -r '.data.data.DB_PASSWORD // empty')"
OAUTH_SECRET="$(echo "$JSON" | jq -r '.data.data.OAUTH_CLIENT_SECRET // empty')"

if [ -z "$JWT_SECRET$DB_PASSWORD$OAUTH_SECRET" ]; then
  echo "❌ No secrets found at kv/transcendence/api."
  exit 1
fi

echo
echo "✅ Secrets from Vault:"
echo "JWT_SECRET=$JWT_SECRET"
echo "DB_PASSWORD=$DB_PASSWORD"
echo "OAUTH_CLIENT_SECRET=$OAUTH_SECRET"
echo

echo "==> Sealing Vault..."
# sys/seal is a PUT and returns 204 No Content on success
HTTP_CODE="$(curl -sk -w '%{http_code}' -o /dev/null -X PUT -H "X-Vault-Token: $ROOT_TOKEN" "$VAULT_ADDR/v1/sys/seal")"
if [ "$HTTP_CODE" = "204" ]; then
  echo "✅ Vault has been sealed successfully."
else
  echo "❌ Failed to seal Vault (HTTP $HTTP_CODE)."
fi