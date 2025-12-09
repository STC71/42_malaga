# 🔐 API AppRole - Credenciales de Vault

## 📋 Descripción

Este directorio contiene las credenciales de autenticación AppRole para HashiCorp Vault. AppRole es un método de autenticación diseñado para aplicaciones y servicios automatizados que necesitan acceder a secretos de forma segura.

## 📁 Contenido

### `role_id`
**Propósito**: Identificador público del rol de la aplicación.

**Características**:
- Similar a un "username" para la aplicación
- Puede compartirse con el equipo de desarrollo
- No es sensible por sí mismo (requiere secret_id para autenticar)
- Se configura una vez durante la inicialización de Vault

**Uso**: El backend lo lee al arrancar para identificarse ante Vault.

---

### `secret_id`
**Propósito**: Credencial secreta equivalente a una contraseña.

**Características**:
- **ALTAMENTE SENSIBLE** - nunca debe commitearse a Git
- Puede tener TTL (tiempo de vida) y número limitado de usos
- Se regenera periódicamente por seguridad
- Se combina con `role_id` para obtener tokens de acceso

**Seguridad**: Debe estar en `.gitignore` y tener permisos `600` (solo lectura para owner).

---

## 🔄 Flujo de Autenticación AppRole

```
1. Backend lee role_id y secret_id del disco
   ↓
2. Backend hace POST a Vault: /v1/auth/approle/login
   Body: { "role_id": "...", "secret_id": "..." }
   ↓
3. Vault valida las credenciales
   ↓
4. Vault devuelve un token temporal (client_token)
   ↓
5. Backend usa ese token para leer secretos:
   GET /v1/secret/data/myapp
   Header: X-Vault-Token: <client_token>
```

## 🔗 Relación con el Proyecto

### Backend (`backend/pon-server.js`)
```javascript
// Lee las credenciales al iniciar
const roleId = fs.readFileSync('/app/secrets/api-approle/role_id', 'utf8');
const secretId = fs.readFileSync('/app/secrets/api-approle/secret_id', 'utf8');

// Autentica con Vault
const response = await fetch('http://vault:8200/v1/auth/approle/login', {
  method: 'POST',
  body: JSON.stringify({ role_id: roleId, secret_id: secretId })
});
const { auth } = await response.json();
const vaultToken = auth.client_token;
```

### Docker Compose (`docker-compose.yml`)
```yaml
services:
  backend:
    volumes:
      - ./srcs/secrets:/app/secrets:ro  # Monta como read-only
```

### Scripts de Inicialización (`srcs/scripts/01.init_waf_and_vault.sh`)
```bash
# Crea el AppRole en Vault
vault write auth/approle/role/myapp \
  secret_id_ttl=720h \
  token_ttl=24h \
  token_max_ttl=72h

# Obtiene el role_id
vault read -field=role_id auth/approle/role/myapp/role-id > role_id

# Genera un secret_id
vault write -field=secret_id -f auth/approle/role/myapp/secret-id > secret_id
```

## 🛡️ Consideraciones de Seguridad

### ✅ Buenas Prácticas Implementadas

1. **Separación de credenciales**: `role_id` y `secret_id` en archivos distintos
2. **Permisos restrictivos**: Solo el usuario owner puede leer
3. **Rotación automática**: Scripts permiten regenerar `secret_id` sin downtime
4. **Montaje read-only**: Docker monta el volumen como `:ro`

### ⚠️ Consideraciones Importantes

- **Nunca comitear `secret_id`**: Debe estar en `.gitignore`
- **Vault debe estar levantado**: Estas credenciales son inútiles sin Vault activo
- **Tokens temporales**: El token obtenido expira; implementar refresh lógico
- **Límite de uso**: `secret_id` puede tener uso único o limitado

## 🔄 Regeneración de Credenciales

Si se compromete el `secret_id`, regenerarlo:

```bash
# Desde el host (requiere acceso a Vault)
./srcs/scripts/01.init_waf_and_vault.sh

# O manualmente
docker exec -it vault sh
vault write -field=secret_id -f auth/approle/role/myapp/secret-id > /tmp/new_secret_id
exit

# Copiar al host
docker cp vault:/tmp/new_secret_id ./srcs/secrets/api-approle/secret_id

# Reiniciar backend para usar nuevo secret
docker restart transcendence-backend
```

## 📊 Ventajas de AppRole vs Otros Métodos

| Método | Pros | Contras | Uso Ideal |
|--------|------|---------|-----------|
| **AppRole** | Diseñado para apps/CI | Requiere gestión de secrets | **Backend services** ✅ |
| Token estático | Simple | Sin rotación, menos seguro | Dev/testing temporal |
| Kubernetes Auth | Integración K8s nativa | Solo para K8s | Producción en K8s |
| AWS IAM | Sin credenciales explícitas | Solo AWS | Apps en AWS |

## 🧪 Verificación de Funcionamiento

```bash
# Test de autenticación desde container
docker exec transcendence-backend node -e "
const fs = require('fs');
const roleId = fs.readFileSync('/app/secrets/api-approle/role_id', 'utf8').trim();
const secretId = fs.readFileSync('/app/secrets/api-approle/secret_id', 'utf8').trim();
console.log('Role ID:', roleId.substring(0, 10) + '...');
console.log('Secret ID:', secretId.substring(0, 10) + '...');
"

# Verificar autenticación con Vault (si está activo)
docker exec vault vault write auth/approle/login \
  role_id=$(cat ./srcs/secrets/api-approle/role_id) \
  secret_id=$(cat ./srcs/secrets/api-approle/secret_id)
```

## 📚 Referencias

- [HashiCorp Vault AppRole Docs](https://www.vaultproject.io/docs/auth/approle)
- [AppRole Best Practices](https://learn.hashicorp.com/tutorials/vault/pattern-approle)
- Script de inicialización: `../../scripts/01.init_waf_and_vault.sh`
- Backend integration: `../../../../backend/pon-server.js`

---

**Ubicación**: `/srcs/secrets/api-approle/`  
**Nivel de sensibilidad**: 🔴 **CRÍTICO** - secret_id debe protegerse  
**Gestión**: Automática mediante scripts de inicialización
