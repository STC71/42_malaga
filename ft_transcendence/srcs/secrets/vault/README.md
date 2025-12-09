# 🔐 Vault - Tokens y Claves de Inicialización

## 📋 Descripción

Este directorio almacena las claves maestras de HashiCorp Vault generadas durante el proceso de inicialización (`vault operator init`). Estos archivos son críticos para el desbloqueo y acceso administrativo a Vault.

## 📁 Contenido

### `init.txt`
**Propósito**: Salida completa del comando `vault operator init`.

**Contiene**:
- Las 5 claves de unseal (por defecto)
- El token root inicial
- Threshold (número mínimo de claves para unseal)
- Instrucciones de uso

**Ejemplo de formato**:
```
Unseal Key 1: AbCdEf1234567890...
Unseal Key 2: GhIjKl0987654321...
Unseal Key 3: MnOpQr1122334455...
Unseal Key 4: StUvWx5544332211...
Unseal Key 5: YzAbCd9988776655...

Initial Root Token: hvs.CAESID...

Vault initialized with 5 key shares and a key threshold of 3.
Please securely distribute the key shares.
```

**Uso**: Respaldo completo; los datos se extraen a archivos individuales.

---

### `unseal_key`
**Propósito**: Almacena UNA de las claves de unseal (típicamente la Key 1).

**Función**:
- Vault arranca en estado "sealed" (cifrado, inaccesible)
- Requiere 3 de 5 claves para "unseal" (desbloquear)
- Este archivo facilita unseal automático en desarrollo

**Seguridad**: En producción, las 5 claves deben distribuirse a personas diferentes.

---

### `root_token`
**Propósito**: Token de acceso administrativo total a Vault.

**Características**:
- Permisos ilimitados sobre todos los secrets
- Sin expiración (a menos que se revoque explícitamente)
- Solo debe usarse para configuración inicial y emergencias
- Después de setup, debe crearse tokens con permisos limitados

**Flujo recomendado**:
1. Usar root token para configurar policies y AppRoles
2. Generar tokens limitados para aplicaciones
3. Revocar root token: `vault token revoke <root_token>`
4. Regenerar root solo en emergencias mediante `vault operator generate-root`

---

## 🔄 Flujo de Inicialización y Unseal

```
1. Primera vez: vault operator init
   → Genera 5 unseal keys + 1 root token
   → Guarda salida en init.txt
   ↓
2. Extracción automática (script):
   grep "Unseal Key 1" init.txt | cut -d: -f2 > unseal_key
   grep "Root Token" init.txt | cut -d: -f2 > root_token
   ↓
3. Cada arranque de Vault:
   - Estado inicial: SEALED (cifrado)
   - vault operator unseal $(cat unseal_key)  # Primera clave
   - vault operator unseal <key2>             # Segunda clave
   - vault operator unseal <key3>             # Tercera clave
   → Estado: UNSEALED (operativo)
   ↓
4. Autenticación administrativa:
   vault login $(cat root_token)
   → Acceso total para configurar
```

## 🔗 Integración con el Proyecto

### Script de Inicialización (`srcs/scripts/01.init_waf_and_vault.sh`)
```bash
#!/bin/bash

# Inicializar Vault (solo primera vez)
if [ ! -f ./srcs/secrets/vault/init.txt ]; then
    docker exec vault vault operator init > ./srcs/secrets/vault/init.txt
    
    # Extraer unseal key y root token
    grep "Unseal Key 1" ./srcs/secrets/vault/init.txt | awk '{print $4}' > ./srcs/secrets/vault/unseal_key
    grep "Root Token" ./srcs/secrets/vault/init.txt | awk '{print $4}' > ./srcs/secrets/vault/root_token
fi

# Unseal Vault con las 3 primeras claves
for i in {1..3}; do
    key=$(grep "Unseal Key $i" ./srcs/secrets/vault/init.txt | awk '{print $4}')
    docker exec vault vault operator unseal "$key"
done

# Login con root token
root_token=$(cat ./srcs/secrets/vault/root_token)
docker exec vault vault login "$root_token"

# Configurar policies, AppRoles, secrets...
```

### Docker Compose (`docker-compose.yml`)
```yaml
services:
  vault:
    image: hashicorp/vault:1.15
    container_name: vault
    cap_add:
      - IPC_LOCK  # Previene swap de memoria
    environment:
      VAULT_ADDR: 'http://0.0.0.0:8200'
      VAULT_DEV_ROOT_TOKEN_ID: 'dev-only-token'  # Solo en modo dev
    volumes:
      - ./srcs/data/vault:/vault/data
      - ./srcs/secrets/vault:/vault/secrets:ro
```

### Backend (`backend/pon-server.js`)
```javascript
// Backend NO debe usar root token
// Usar AppRole authentication en su lugar
const roleId = fs.readFileSync('/app/secrets/api-approle/role_id', 'utf8');
const secretId = fs.readFileSync('/app/secrets/api-approle/secret_id', 'utf8');

const authResponse = await fetch('http://vault:8200/v1/auth/approle/login', {
  method: 'POST',
  body: JSON.stringify({ role_id: roleId, secret_id: secretId })
});
const { auth } = await authResponse.json();
// Usar auth.client_token (limitado) en lugar de root_token
```

## 🛡️ Consideraciones de Seguridad

### ⚠️ EXTREMADAMENTE SENSIBLE

Estos archivos representan **acceso total** a Vault. Si se comprometen:
- Atacante puede leer todos los secrets de la aplicación
- Puede modificar/eliminar secrets
- Puede crear nuevos tokens con permisos ilimitados

### ✅ Mejores Prácticas

#### Desarrollo
- ✅ Un solo unseal key en `unseal_key` está OK
- ✅ Usar root token para configuración rápida
- ✅ Reinicializar Vault frecuentemente para practicar
- ✅ `.gitignore` todos estos archivos

#### Producción
- 🚨 **NUNCA** almacenar las 5 claves juntas
- 🚨 Distribuir claves a 5 personas/sistemas diferentes
- 🚨 Requerir 3 de 5 para unseal (Shamir's Secret Sharing)
- 🚨 Root token solo para emergencias
- 🚨 Revocar root token después de configuración inicial
- 🚨 Rotar unseal keys periódicamente: `vault operator rekey`
- 🚨 Habilitar audit logging: `vault audit enable file`

### Protección de Archivos

```bash
# Permisos correctos
chmod 600 srcs/secrets/vault/*
chown $(whoami):$(whoami) srcs/secrets/vault/*

# Verificar que están en .gitignore
grep -q "srcs/secrets/vault/" .gitignore || echo "srcs/secrets/vault/" >> .gitignore

# Eliminar de historial de Git si se commitearon por error
git filter-branch --tree-filter 'rm -rf srcs/secrets/vault' HEAD
git push --force
```

## 🔄 Escenarios de Uso

### Escenario 1: Primer Despliegue
```bash
# 1. Levantar Vault
docker-compose up -d vault

# 2. Inicializar (genera claves)
docker exec vault vault operator init > srcs/secrets/vault/init.txt

# 3. Extraer claves
grep "Unseal Key 1" srcs/secrets/vault/init.txt | awk '{print $4}' > srcs/secrets/vault/unseal_key
grep "Root Token" srcs/secrets/vault/init.txt | awk '{print $4}' > srcs/secrets/vault/root_token

# 4. Unseal con 3 claves
docker exec vault vault operator unseal $(sed -n '1p' srcs/secrets/vault/unseal_key)
docker exec vault vault operator unseal $(sed -n '2p' srcs/secrets/vault/unseal_key)
docker exec vault vault operator unseal $(sed -n '3p' srcs/secrets/vault/unseal_key)

# 5. Login
docker exec vault vault login $(cat srcs/secrets/vault/root_token)
```

### Escenario 2: Reinicio de Vault Container
```bash
# Vault se seala automáticamente al reiniciar
docker restart vault

# Necesita unseal de nuevo
docker exec vault vault operator unseal $(cat srcs/secrets/vault/unseal_key)
# Repetir 2 veces más con otras claves...
```

### Escenario 3: Pérdida de Root Token
```bash
# Regenerar root token con unseal keys
docker exec -it vault sh
vault operator generate-root -init
# Seguir instrucciones, requiere 3 unseal keys

# Guardar nuevo root token
vault operator generate-root -otp=<OTP> -nonce=<NONCE>
```

## 🧪 Verificación

```bash
# Ver estado de Vault
docker exec vault vault status

# Debe mostrar:
# Sealed: false
# Key Shares: 5
# Key Threshold: 3

# Test de autenticación con root token
docker exec vault vault login $(cat srcs/secrets/vault/root_token)

# Listar secrets engines habilitados
docker exec vault vault secrets list

# Ver políticas activas
docker exec vault vault policy list
```

## 📚 Referencias

- [Vault Initialization](https://www.vaultproject.io/docs/commands/operator/init)
- [Seal/Unseal Concepts](https://www.vaultproject.io/docs/concepts/seal)
- [Shamir's Secret Sharing](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing)
- [Vault Security Model](https://www.vaultproject.io/docs/internals/security)
- Script relacionado: `../../scripts/01.init_waf_and_vault.sh`

---

**Ubicación**: `/srcs/secrets/vault/`  
**Nivel de sensibilidad**: 🔴 **MÁXIMA CRÍTICA**  
**Backup**: Copias físicas offline en ubicaciones seguras separadas  
**Rotación**: Cada 90 días en producción (comando `vault operator rekey`)
