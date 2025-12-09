# 🔐 Secrets - Gestión Centralizada de Información Sensible

## 📋 Descripción General

Este directorio es el repositorio centralizado de **toda la información sensible** del proyecto: credenciales, tokens, certificados SSL y configuraciones de seguridad. Implementa el principio de "separación de secrets" del código fuente para máxima seguridad.

## 🗂️ Estructura de Subdirectorios

### 📁 `api-approle/`
**Propósito**: Credenciales de autenticación AppRole para HashiCorp Vault.

**Contiene**:
- `role_id`: Identificador del rol de la aplicación
- `secret_id`: Credencial secreta (equivalente a contraseña)

**Uso**: Backend se autentica con Vault usando estas credenciales para acceder a secrets dinámicos.

**Documentación**: Ver [api-approle/README.md](./api-approle/README.md)

---

### 🔒 `certs/`
**Propósito**: Certificados SSL/TLS para comunicaciones HTTPS.

**Contiene**:
- `fullchain.pem`: Cadena completa de certificados
- `privkey.pem`: Clave privada del servidor
- `cert.conf`: Configuración OpenSSL para generación

**Uso**: Nginx y servicios web para habilitar HTTPS seguro.

**Documentación**: Ver [certs/README.md](./certs/README.md)

---

### 🗝️ `vault/`
**Propósito**: Claves maestras de inicialización de Vault.

**Contiene**:
- `init.txt`: Salida completa del `vault operator init`
- `unseal_key`: Una de las claves de desbloqueo
- `root_token`: Token administrativo supremo

**Uso**: Inicialización y unseal de Vault tras reinicios.

**Documentación**: Ver [vault/README.md](./vault/README.md)

---

### 📄 `.env`
**Propósito**: Variables de entorno sensibles cargadas por backend.

**Contiene**:
```env
# Database
DATABASE_URL=sqlite:./database.sqlite

# JWT
JWT_SECRET=supersecretkey_change_in_production

# OAuth (si habilitado)
GOOGLE_CLIENT_ID=your_google_client_id
GOOGLE_CLIENT_SECRET=your_google_client_secret

# Vault (si habilitado)
VAULT_ADDR=http://vault:8200
VAULT_TOKEN=hvs.CAESID...
```

**Carga**: Backend usa `dotenv` para leer al arrancar.

---

### 🗄️ `app.db`
**Propósito**: Base de datos SQLite con información de usuarios (desarrollo).

**Contiene**:
- Tabla `Users`: credenciales hasheadas, perfiles
- Tabla `Friendships`: relaciones entre usuarios
- Tabla `Matches`: historial de partidas
- Tabla `Conversations` y `Messages`: chat
- Tabla `BlockedUsers`: usuarios bloqueados

**Producción**: Migrar a PostgreSQL o MySQL.

---

## 🔄 Flujo de Acceso a Secrets

```
1. Secrets en reposo (este directorio)
   ↓
2. Docker Compose monta volúmenes:
   - ./srcs/secrets:/app/secrets:ro (backend)
   - ./srcs/secrets/certs:/etc/ssl/certs:ro (nginx)
   ↓
3. Aplicaciones leen secrets:
   - Backend: process.env (desde .env)
   - Backend: fs.readFileSync('/app/secrets/...')
   - Nginx: ssl_certificate directivas
   ↓
4. Autenticación con servicios externos:
   - Vault: AppRole login
   - Database: connection string
   - OAuth: client credentials
```

## 🛡️ Seguridad Multinivel

### Nivel 1: Filesystem Protection
```bash
# Permisos restrictivos
chmod 700 srcs/secrets/
chmod 600 srcs/secrets/*/.
chmod 600 srcs/secrets/**/*

# Owner específico
chown -R $(whoami):$(whoami) srcs/secrets/
```

### Nivel 2: Git Exclusion
```gitignore
# .gitignore
srcs/secrets/.env
srcs/secrets/**/*.pem
srcs/secrets/**/secret_id
srcs/secrets/**/root_token
srcs/secrets/**/unseal_key
srcs/secrets/app.db
```

### Nivel 3: Docker Read-Only Mounts
```yaml
volumes:
  - ./srcs/secrets:/app/secrets:ro  # ← :ro = read-only
```

### Nivel 4: Vault Dynamic Secrets
En lugar de secrets estáticos, usar Vault para:
- Credenciales de DB temporales (TTL 1h)
- API keys rotativas
- Certificados generados dinámicamente

## 🔗 Integración con el Proyecto

### Backend (`backend/pon-server.js`)
```javascript
import 'dotenv/config';  // Lee .env automáticamente
import fs from 'fs';

// Acceso a secrets
const jwtSecret = process.env.JWT_SECRET;
const vaultToken = fs.readFileSync('/app/secrets/vault/root_token', 'utf8');
```

### Docker Compose (`docker-compose.yml`)
```yaml
services:
  backend:
    environment:
      - NODE_ENV=production
      - JWT_SECRET=${JWT_SECRET}  # Desde .env del host
    volumes:
      - ./srcs/secrets:/app/secrets:ro
```

### Nginx (`srcs/conf/nginx/nginx.conf`)
```nginx
ssl_certificate /etc/ssl/certs/fullchain.pem;
ssl_certificate_key /etc/ssl/certs/privkey.pem;
```

## 🔄 Gestión de Secrets por Ambiente

### Desarrollo
- Secrets autogenerados (`00.gen_selfsigned_cert.sh`)
- `.env` con valores dummy OK
- SQLite en archivo local
- Vault en modo dev (sin persistencia)

### Staging
- Secrets semi-reales (certificados válidos para `staging.domain.com`)
- `.env` con valores de staging
- PostgreSQL en contenedor Docker
- Vault persistente con backups

### Producción
- Secrets de CA externa (Let's Encrypt)
- `.env` inyectado desde CI/CD (GitHub Secrets, AWS Secrets Manager)
- PostgreSQL/MySQL managed (RDS, Cloud SQL)
- Vault en cluster HA con unseal keys distribuidas

## 🧪 Inicialización Completa

```bash
# 1. Generar certificados SSL
./srcs/scripts/00.gen_selfsigned_cert.sh

# 2. Crear .env base
cp srcs/secrets/.env.example srcs/secrets/.env
nano srcs/secrets/.env  # Editar valores

# 3. Inicializar Vault (si se usa)
docker-compose up -d vault
./srcs/scripts/01.init_waf_and_vault.sh

# 4. Verificar permisos
./srcs/scripts/02.read_vault_from_host.sh

# 5. Levantar stack completo
docker-compose up -d

# 6. Verificar acceso a secrets
docker exec transcendence-backend ls -la /app/secrets
```

## 📊 Inventario de Secrets

| Archivo/Directorio | Tipo | Sensibilidad | Rotación | Backup |
|-------------------|------|--------------|----------|--------|
| `api-approle/secret_id` | Credential | 🔴 Crítica | 30 días | No (regenerable) |
| `certs/privkey.pem` | Private Key | 🔴 Crítica | 90 días | Sí (offline) |
| `vault/root_token` | Token | 🔴 Máxima | Post-setup | Sí (cifrado) |
| `vault/unseal_key` | Key | 🔴 Máxima | 90 días | Sí (distribuido) |
| `.env` | Config | 🟡 Media | Cambio de versión | Sí (versionado) |
| `app.db` | Database | 🟢 Baja (dev) | N/A | Opcional |

## 🚨 Procedimiento de Compromiso

Si se sospecha exposición de secrets:

### Acción Inmediata
```bash
# 1. Revocar todos los tokens de Vault
docker exec vault vault token revoke -mode=path auth/approle

# 2. Regenerar secret_id
docker exec vault vault write -f -field=secret_id auth/approle/role/myapp/secret-id > api-approle/secret_id

# 3. Regenerar certificados SSL
./srcs/scripts/00.gen_selfsigned_cert.sh

# 4. Cambiar JWT_SECRET en .env
openssl rand -base64 32 > .jwt_secret_new

# 5. Reiniciar todos los servicios
docker-compose down
docker-compose up -d

# 6. Invalidar sesiones de usuarios
docker exec transcendence-backend node -e "
const db = require('./db.js');
db.User.update({ sessionVersion: 0 }, { where: {} });
"
```

### Post-Incidente
- Auditoría completa de logs
- Rotación forzada de passwords de usuarios
- Revisión de accesos no autorizados
- Actualización de documentación de incidente

## 📚 Referencias y Buenas Prácticas

### Documentos Internos
- [api-approle/README.md](./api-approle/README.md) - AppRole authentication
- [certs/README.md](./certs/README.md) - TLS/SSL certificates
- [vault/README.md](./vault/README.md) - Vault initialization keys

### Recursos Externos
- [12-Factor App: Config](https://12factor.net/config)
- [OWASP Secrets Management](https://cheatsheetseries.owasp.org/cheatsheets/Secrets_Management_Cheat_Sheet.html)
- [HashiCorp Vault Best Practices](https://learn.hashicorp.com/tutorials/vault/pattern-approle)
- [Mozilla Web Security Guidelines](https://infosec.mozilla.org/guidelines/web_security)

### Scripts Relacionados
- `../scripts/00.gen_selfsigned_cert.sh` - Generación de certificados
- `../scripts/01.init_waf_and_vault.sh` - Inicialización de Vault
- `../scripts/02.read_vault_from_host.sh` - Verificación de acceso
- `../scripts/03.test_vault_secrets_from_container.sh` - Tests de integración

---

**Ubicación**: `/srcs/secrets/`  
**Responsable**: DevOps / Security Team  
**Nivel de acceso**: Restringido (solo desarrolladores senior y CI/CD)  
**Auditoría**: Logs de acceso habilitados en Vault y filesystem
