# 📂 SRCS - Infraestructura y Configuración del Proyecto

## 📋 Descripción General

Este directorio contiene toda la **infraestructura de soporte** del proyecto Transcendence. Incluye configuraciones de servicios (Nginx, ModSecurity WAF, Vault), scripts de automatización, logs de aplicación, datos persistentes y gestión de secretos.

## 🗂️ Estructura Principal

```
srcs/
├── conf/                  # Configuraciones de servicios
│   ├── nginx/            # Reverse proxy y load balancer
│   └── modsecurity/      # Web Application Firewall
│       ├── custom-rules/ # Reglas WAF personalizadas (18 archivos)
│       ├── custom-rules-options/
│       └── owasp-crs/    # OWASP Core Rule Set completo
│
├── secrets/              # Gestión de secretos y credenciales
│   ├── api-approle/     # Vault AppRole (role_id, secret_id)
│   ├── certs/           # Certificados SSL/TLS
│   ├── vault/           # Keys de inicialización de Vault
│   ├── .env             # Variables de entorno
│   └── app.db           # Base de datos SQLite
│
├── data/                 # Datos persistentes
│   └── vault/
│       ├── config/      # Configuración de Vault
│       └── file/        # Almacenamiento backend de Vault
│
├── logs/                 # Logs de aplicación
│   ├── nginx/           # Access y error logs de Nginx
│   └── modsec/          # Audit logs de ModSecurity
│
└── scripts/              # Scripts de automatización
    ├── 00.gen_selfsigned_cert.sh       # Generar certificados SSL
    ├── 01.init_waf_and_vault.sh        # Inicialización completa
    ├── 02.read_vault_from_host.sh      # Leer secretos de Vault
    ├── 03.test_vault_secrets_from_container.sh
    └── 99.test_modsec_rules.sh         # Testing de reglas WAF
```

## 🛡️ Componentes de Seguridad

### 1. **Nginx** (`conf/nginx/`)

**Función**: Reverse proxy, balanceador de carga, terminación SSL/TLS.

**Características**:
- Enrutamiento de peticiones (`/api` → backend, `/` → frontend)
- Compresión Gzip
- Caching de assets estáticos
- Rate limiting por endpoint
- Headers de seguridad HTTP
- HTTP/2 support

**Configuración principal**: `nginx.conf`

**Documentación**: [conf/nginx/README.md](./conf/nginx/README.md) (si existe)

---

### 2. **ModSecurity WAF** (`conf/modsecurity/`)

**Función**: Web Application Firewall para detectar y bloquear ataques web.

**Protecciones**:
- **XSS** (Cross-Site Scripting)
- **SQLi** (SQL Injection)
- **LFI/RFI** (Local/Remote File Inclusion)
- **CSRF** (Cross-Site Request Forgery)
- **Command Injection**
- **Malicious User-Agents**

**Reglas**:
- **OWASP CRS**: 3000+ reglas de la comunidad
- **Custom Rules**: 18+ reglas específicas para Transcendence

**Modos**:
- **Detection Only**: Loguea pero no bloquea (desarrollo)
- **Blocking**: Bloquea peticiones maliciosas (producción)

**Documentación completa**: [conf/modsecurity/README.md](./conf/modsecurity/README.md)

---

### 3. **HashiCorp Vault** (`secrets/vault/`, `data/vault/`)

**Función**: Gestión centralizada de secretos (passwords, API keys, tokens).

**Características**:
- **Encriptación en reposo**: AES-256-GCM
- **Unsealing**: Requiere 3 de 5 keys (Shamir's Secret Sharing)
- **AppRole Auth**: Autenticación para servicios backend
- **Secret Rotation**: Renovación automática de secretos
- **Audit Logging**: Registro completo de accesos

**Secretos almacenados**:
- JWT secrets (access + refresh tokens)
- Database credentials
- OAuth client secrets (Google, 42)
- API keys de terceros

**Documentación**: [secrets/vault/README.md](./secrets/vault/README.md)

---

## 🔐 Gestión de Secretos (`secrets/`)

### Archivos Sensibles

| Archivo | Descripción | Ejemplo |
|---------|-------------|---------|
| `api-approle/role_id` | ID del rol AppRole de Vault | `abc123...` |
| `api-approle/secret_id` | Secret ID para autenticación | `xyz789...` |
| `certs/fullchain.pem` | Certificado SSL público | `-----BEGIN CERTIFICATE-----` |
| `certs/privkey.pem` | Clave privada SSL | `-----BEGIN PRIVATE KEY-----` |
| `vault/init.txt` | Output completo de `vault operator init` | Unseal Keys + Root Token |
| `vault/unseal_key` | Primera unseal key extraída | `Unseal Key 1: ...` |
| `vault/root_token` | Token de root de Vault | `hvs.CAESIAbcDef...` |
| `.env` | Variables de entorno | `JWT_SECRET=...` |
| `app.db` | Base de datos SQLite | Binario |

### Niveles de Seguridad

```
1. Filesystem Permissions
   → chmod 600 secrets/*
   → Solo root/owner puede leer

2. Git Ignore
   → secrets/ en .gitignore
   → Nunca commitear

3. Docker Secrets
   → Montaje seguro en contenedores
   → No en variables de entorno

4. Vault Encryption
   → Secretos encriptados en Vault
   → Desencriptados solo en uso
```

---

## 📊 Logging (`logs/`)

### Nginx Logs (`logs/nginx/`)

```
access.log         → Todas las peticiones HTTP
error.log          → Errores de Nginx
access_modsec.log  → Peticiones con info de ModSecurity
```

**Formato de access.log**:
```
127.0.0.1 - - [01/Jan/2024:12:00:00 +0000] "GET /api/users/1 HTTP/1.1" 200 1234 "-" "Mozilla/5.0"
```

### ModSecurity Logs (`logs/modsec/`)

```
modsec_audit.log   → Peticiones bloqueadas/detectadas
modsec_debug.log   → Debug detallado (solo con SecDebugLogLevel > 0)
```

**Formato de audit.log** (JSON):
```json
{
  "transaction": {
    "client_ip": "192.168.1.100",
    "time": "01/Jan/2024:12:00:00 +0000",
    "request": {
      "method": "GET",
      "uri": "/api/users?search=<script>alert(1)</script>",
      "headers": {...}
    },
    "response": {
      "http_code": 403
    },
    "messages": [
      {
        "message": "XSS Attack Detected",
        "ruleId": "941100",
        "severity": "CRITICAL"
      }
    ]
  }
}
```

### Monitoreo de Logs

```bash
# Tail en tiempo real
tail -f srcs/logs/nginx/access.log
tail -f srcs/logs/modsec/modsec_audit.log

# Buscar ataques XSS
grep "941100" srcs/logs/modsec/modsec_audit.log

# Contar peticiones por IP
awk '{print $1}' srcs/logs/nginx/access.log | sort | uniq -c | sort -nr

# Ver 10 endpoints más accedidos
awk '{print $7}' srcs/logs/nginx/access.log | sort | uniq -c | sort -nr | head -10
```

---

## 💾 Datos Persistentes (`data/`)

### Vault Data (`data/vault/`)

```
config/         → vault.hcl (configuración del servidor)
file/           → Backend de almacenamiento (archivos encriptados)
```

**Backup de Vault**:
```bash
# Backup de datos
tar -czf vault-backup-$(date +%Y%m%d).tar.gz srcs/data/vault/

# Backup de keys
tar -czf vault-keys-$(date +%Y%m%d).tar.gz srcs/secrets/vault/

# Restaurar
tar -xzf vault-backup-20240101.tar.gz -C srcs/data/
```

---

## 🚀 Scripts de Automatización (`scripts/`)

### Inicialización Completa

```bash
# 1. Generar certificados SSL autofirmados
./srcs/scripts/00.gen_selfsigned_cert.sh

# 2. Inicializar WAF, Vault, AppRole, logs
./srcs/scripts/01.init_waf_and_vault.sh

# 3. Verificar acceso a Vault desde host
./srcs/scripts/02.read_vault_from_host.sh

# 4. Test de Vault desde contenedor
./srcs/scripts/03.test_vault_secrets_from_container.sh

# 5. Testing de reglas ModSecurity
./srcs/scripts/99.test_modsec_rules.sh
```

**Documentación completa**: [scripts/README.md](./scripts/README.md)

---

## 🔗 Integración con Docker Compose

```yaml
# docker-compose.yml (ejemplo simplificado)
services:
  vault:
    image: hashicorp/vault:1.15
    volumes:
      - ./srcs/data/vault/file:/vault/file
      - ./srcs/data/vault/config:/vault/config
    environment:
      VAULT_ADDR: http://0.0.0.0:8200
    cap_add:
      - IPC_LOCK

  nginx:
    image: nginx:alpine
    volumes:
      - ./srcs/conf/nginx/nginx.conf:/etc/nginx/nginx.conf:ro
      - ./srcs/secrets/certs:/etc/nginx/certs:ro
      - ./srcs/logs/nginx:/var/log/nginx
      - ./srcs/conf/modsecurity:/etc/nginx/modsec:ro
      - ./srcs/logs/modsec:/var/log/modsec
    ports:
      - "443:443"
      - "80:80"
```

---

## 🧪 Testing de Seguridad

### Validar Configuraciones

```bash
# Test de sintaxis Nginx
docker-compose exec nginx nginx -t

# Reload de Nginx sin downtime
docker-compose exec nginx nginx -s reload

# Verificar reglas ModSecurity cargadas
docker-compose exec nginx grep -r "SecRule" /etc/nginx/modsec/

# Ver status de Vault
docker-compose exec vault vault status
```

### Test de Penetración

```bash
# XSS Attack (debe ser bloqueado: 403)
curl -k "https://localhost/api/users?search=<script>alert(1)</script>"

# SQLi Attack (debe ser bloqueado: 403)
curl -k "https://localhost/api/users?id=1' OR '1'='1"

# LFI Attack (debe ser bloqueado: 403)
curl -k "https://localhost/api/files?path=../../../../etc/passwd"

# Rate Limiting Test
for i in {1..10}; do
  curl -X POST https://localhost/api/auth/login \
    -H "Content-Type: application/json" \
    -d '{"username":"test","password":"test"}'
done
# 6ta petición debe fallar con 429 Too Many Requests
```

### Automated Testing

```bash
# Ejecutar suite completa de tests WAF
./srcs/scripts/99.test_modsec_rules.sh

# Salida esperada:
# Testing XSS in query param... ✅ PASS (got 403)
# Testing SQLi UNION attack... ✅ PASS (got 403)
# Testing LFI attempt... ✅ PASS (got 403)
# Testing Valid API request... ✅ PASS (200)
# Testing Login rate limit (6th request)... ✅ PASS (429)
# ==============================
# Tests Passed: 5
# Tests Failed: 0
# ==============================
```

---

## 📈 Monitoreo y Alertas

### Métricas Nginx

```bash
# Habilitar stub_status en nginx.conf
curl http://localhost/nginx_status

# Salida:
# Active connections: 42
# server accepts handled requests
#  1234 1234 5678
# Reading: 0 Writing: 5 Waiting: 37
```

### Alertas de Ataques

```bash
# Script de monitoreo en tiempo real
tail -f srcs/logs/modsec/modsec_audit.log | \
grep -E "id \"(942100|941100|930100)\"" | \
while read line; do
  echo "🚨 ALERTA: Ataque detectado - $line"
  # Enviar notificación (email, Slack, etc.)
done
```

---

## 🔧 Mantenimiento

### Rotación de Logs

```bash
# logrotate.conf
/path/to/srcs/logs/nginx/*.log {
    daily
    rotate 14
    compress
    delaycompress
    notifempty
    missingok
    sharedscripts
    postrotate
        docker-compose exec nginx nginx -s reload
    endscript
}
```

### Renovación de Certificados

```bash
# Certificados autofirmados: regenerar cada 365 días
rm srcs/secrets/certs/{fullchain,privkey}.pem
./srcs/scripts/00.gen_selfsigned_cert.sh

# Let's Encrypt (producción):
certbot renew --webroot -w /var/www/html
# Copiar nuevos certificados a srcs/secrets/certs/
```

### Backup Automático

```bash
# Cronjob diario
0 2 * * * tar -czf /backups/srcs-$(date +\%Y\%m\%d).tar.gz \
  /path/to/transcendence/srcs/secrets \
  /path/to/transcendence/srcs/data
```

---

## 🚀 Despliegue en Producción

### Checklist de Seguridad

- [ ] Cambiar `JWT_SECRET` en `.env` (usar `openssl rand -base64 32`)
- [ ] Usar certificados SSL de CA válida (Let's Encrypt)
- [ ] ModSecurity en modo `SecRuleEngine On` (blocking)
- [ ] Cambiar root token de Vault después de inicialización
- [ ] Deshabilitar Vault debug logs
- [ ] Configurar backups automáticos de `srcs/data/` y `srcs/secrets/`
- [ ] Establecer firewall (UFW/iptables) para limitar acceso a puertos
- [ ] Habilitar fail2ban para bloquear IPs con intentos de login fallidos
- [ ] Configurar HTTPS Strict Transport Security (HSTS)
- [ ] Implementar Content Security Policy (CSP)

### Variables de Entorno Productivas

```bash
# .env (producción)
JWT_SECRET=$(openssl rand -base64 32)
JWT_REFRESH_SECRET=$(openssl rand -base64 32)
DATABASE_URL=postgresql://user:pass@db:5432/transcendence  # Migrar a PostgreSQL
VAULT_ADDR=https://vault.transcendence.com:8200
NODE_ENV=production
LOG_LEVEL=warn
```

---

**Ubicación**: `/srcs/`  
**Tecnologías**: Nginx, ModSecurity WAF, HashiCorp Vault, OpenSSL, Bash  
**Documentación relacionada**: 
- `conf/README.md` - Configuración de Nginx + ModSecurity
- `secrets/README.md` - Gestión de secretos
- `scripts/README.md` - Automatización
- `/docker-compose.yml` - Orquestación de servicios
- `/backend/` - Integración con backend
- `/frontend/` - Integración con frontend
