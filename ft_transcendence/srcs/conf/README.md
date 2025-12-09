# ⚙️ SRCS/CONF - Configuración de Infraestructura

## 📋 Descripción General

Este directorio contiene los **archivos de configuración** de los servicios de infraestructura que protegen y optimizan la aplicación Transcendence. Incluye configuraciones de **Nginx** (reverse proxy + load balancer) y **ModSecurity** (Web Application Firewall - WAF) con reglas OWASP CRS.

## 🗂️ Estructura de Directorios

```
conf/
├── nginx/                    # Configuración de Nginx
│   ├── nginx.conf           # Archivo principal de configuración
│   ├── entrypoint-empty/    # Scripts de inicialización (vacío actualmente)
│   └── templates-empty/     # Plantillas de configuración (vacío)
│
└── modsecurity/             # Web Application Firewall
    ├── modsecurity.conf     # Configuración principal de ModSecurity
    ├── crs-setup.conf       # Configuración OWASP CRS
    ├── unicode.mapping      # Mapeo de caracteres Unicode
    ├── custom-rules/        # Reglas personalizadas del proyecto
    ├── custom-rules-options/# Opciones de reglas custom
    └── owasp-crs/          # OWASP Core Rule Set completo
```

## 🌐 Nginx - Reverse Proxy y Load Balancer

### `nginx.conf` - Configuración Principal

**Propósito**: Actuar como punto de entrada único para todas las peticiones HTTP/HTTPS hacia la aplicación.

#### Funcionalidades

1. **Reverse Proxy**: Reenvía peticiones a backend/frontend según la ruta
2. **SSL/TLS Termination**: Gestiona certificados HTTPS
3. **Load Balancing**: Distribuye carga entre múltiples instancias (preparado para escalado)
4. **Compresión**: Gzip para reducir tamaño de respuestas
5. **Caching**: Caché de assets estáticos
6. **Security Headers**: Cabeceras de seguridad HTTP

#### Estructura Típica

```nginx
# nginx.conf

user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log warn;
pid /var/run/nginx.pid;

events {
    worker_connections 1024;
    use epoll;  # Optimización para Linux
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    # Logging
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    access_log /var/log/nginx/access.log main;

    # Performance
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    types_hash_max_size 2048;

    # Gzip compression
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;
    gzip_types text/plain text/css text/xml text/javascript 
               application/json application/javascript application/xml+rss;

    # Security headers
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    add_header Referrer-Policy "no-referrer-when-downgrade" always;

    # Rate limiting
    limit_req_zone $binary_remote_addr zone=api:10m rate=10r/s;
    limit_conn_zone $binary_remote_addr zone=addr:10m;

    # Upstream backends
    upstream backend {
        least_conn;  # Algoritmo de balanceo
        server backend:3000 max_fails=3 fail_timeout=30s;
        # server backend2:3000;  # Para escalado horizontal
    }

    upstream frontend {
        server frontend:5173;
    }

    # HTTP → HTTPS redirect
    server {
        listen 80;
        server_name transcendence.local;
        return 301 https://$server_name$request_uri;
    }

    # HTTPS server
    server {
        listen 443 ssl http2;
        server_name transcendence.local;

        # SSL certificates
        ssl_certificate /etc/nginx/certs/fullchain.pem;
        ssl_certificate_key /etc/nginx/certs/privkey.pem;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers on;
        ssl_session_cache shared:SSL:10m;
        ssl_session_timeout 10m;

        # ModSecurity integration
        modsecurity on;
        modsecurity_rules_file /etc/nginx/modsec/modsecurity.conf;

        # API endpoints → Backend
        location /api/ {
            limit_req zone=api burst=20 nodelay;
            proxy_pass http://backend;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection 'upgrade';
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;
            proxy_cache_bypass $http_upgrade;
        }

        # Socket.IO → Backend
        location /socket.io/ {
            proxy_pass http://backend;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
            proxy_set_header Host $host;
            proxy_read_timeout 86400;  # 24 horas para conexiones persistentes
        }

        # Frontend SPA
        location / {
            proxy_pass http://frontend;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            
            # SPA routing: redirigir 404 a index.html
            try_files $uri $uri/ /index.html;
        }

        # Assets estáticos con caché agresivo
        location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2|ttf|eot)$ {
            proxy_pass http://frontend;
            expires 1y;
            add_header Cache-Control "public, immutable";
        }

        # Health check endpoint
        location /healthz {
            access_log off;
            return 200 "OK\n";
            add_header Content-Type text/plain;
        }
    }
}
```

#### Rate Limiting

```nginx
# Limitar login attempts
limit_req_zone $binary_remote_addr zone=login:10m rate=5r/m;

location /api/auth/login {
    limit_req zone=login burst=2 nodelay;
    proxy_pass http://backend;
}

# Limitar creación de salas
limit_req_zone $binary_remote_addr zone=createroom:10m rate=10r/m;

location /api/rooms/create {
    limit_req zone=createroom burst=5;
    proxy_pass http://backend;
}
```

#### Load Balancing Strategies

```nginx
# 1. Round Robin (default)
upstream backend {
    server backend1:3000;
    server backend2:3000;
    server backend3:3000;
}

# 2. Least Connections (mejor para cargas desiguales)
upstream backend {
    least_conn;
    server backend1:3000;
    server backend2:3000;
}

# 3. IP Hash (sticky sessions)
upstream backend {
    ip_hash;
    server backend1:3000;
    server backend2:3000;
}

# 4. Weighted (servidores con capacidades diferentes)
upstream backend {
    server backend1:3000 weight=3;
    server backend2:3000 weight=1;
}
```

---

## 🛡️ ModSecurity - Web Application Firewall

### `modsecurity.conf` - Configuración Principal

**Propósito**: Habilitar y configurar el motor de ModSecurity para inspeccionar tráfico HTTP.

#### Configuración Base

```apache
# modsecurity.conf

# Habilitar ModSecurity
SecRuleEngine On

# Directorios de trabajo
SecDataDir /tmp/
SecTmpDir /tmp/

# Logging
SecAuditEngine RelevantOnly
SecAuditLogRelevantStatus "^(?:5|4(?!04))"
SecAuditLogParts ABIJDEFHZ
SecAuditLogType Serial
SecAuditLog /var/log/modsec/modsec_audit.log

# Request body inspection
SecRequestBodyAccess On
SecRequestBodyLimit 13107200  # 12.5 MB
SecRequestBodyNoFilesLimit 131072  # 128 KB
SecRequestBodyLimitAction Reject

# Response body inspection
SecResponseBodyAccess On
SecResponseBodyMimeType text/plain text/html text/xml application/json
SecResponseBodyLimit 524288  # 512 KB
SecResponseBodyLimitAction ProcessPartial

# Debugging
SecDebugLog /var/log/modsec/modsec_debug.log
SecDebugLogLevel 0  # 0=off, 9=verbose

# Upload restrictions
SecUploadDir /tmp/
SecUploadKeepFiles Off

# Connection limits
SecConnEngine Off  # Deshabilitado por defecto

# Rule engine
SecRuleEngine On
SecRequestBodyAccess On
SecRule REQUEST_HEADERS:Content-Type "text/xml" \
    "id:'200000',phase:1,t:none,t:lowercase,pass,nolog,ctl:requestBodyProcessor=XML"
```

### `crs-setup.conf` - OWASP CRS Setup

**Propósito**: Configurar el OWASP Core Rule Set con políticas de anomaly scoring.

#### Anomaly Scoring

```apache
# crs-setup.conf

# Paranoia level (1-4)
# 1: Básico, 2: Moderado, 3: Estricto, 4: Extremo
SecAction \
  "id:900000,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.paranoia_level=2"

# Anomaly thresholds
SecAction \
  "id:900110,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.inbound_anomaly_score_threshold=5,\
   setvar:tx.outbound_anomaly_score_threshold=4"

# Blocking mode
SecAction \
  "id:900200,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.blocking_paranoia_level=2"
```

#### Whitelisting de Aplicaciones

```apache
# Permitir ciertos endpoints sin inspección (con precaución)
SecRule REQUEST_URI "@beginsWith /api/healthz" \
    "id:900900,\
     phase:1,\
     pass,\
     nolog,\
     ctl:ruleEngine=Off"

# Excluir Socket.IO de body inspection
SecRule REQUEST_URI "@beginsWith /socket.io/" \
    "id:900901,\
     phase:1,\
     pass,\
     nolog,\
     ctl:requestBodyAccess=Off"
```

---

## 📁 Subdirectorios

### `custom-rules/`

**Propósito**: Reglas personalizadas específicas para Transcendence.

**Contenido**: Ver [modsecurity/custom-rules/README.md](./modsecurity/custom-rules/README.md) para detalles de las 18+ reglas custom.

**Ejemplos**:
- `900450-login-ratelimit.conf`: Rate limiting de endpoints de autenticación
- `900300-upload-guard.conf`: Validación de uploads de avatares
- `900100-allow-static-bypass.conf`: Bypass de reglas para assets estáticos

### `custom-rules-options/`

**Propósito**: Opciones y configuraciones auxiliares para reglas custom.

### `owasp-crs/`

**Propósito**: OWASP Core Rule Set completo (3000+ reglas).

**Categorías**:
- **REQUEST-901**: Initialization
- **REQUEST-920**: Protocol Enforcement
- **REQUEST-921**: Protocol Attack
- **REQUEST-930**: Application Attack (LFI)
- **REQUEST-931**: Application Attack (RFI)
- **REQUEST-932**: Application Attack (RCE)
- **REQUEST-933**: Application Attack (PHP)
- **REQUEST-941**: Application Attack (XSS)
- **REQUEST-942**: Application Attack (SQLi)
- **RESPONSE-950**: Data Leakages
- **RESPONSE-980**: Correlation

---

## 🔗 Integración Nginx + ModSecurity

### Flujo de Petición

```
Cliente → HTTPS Request
    ↓
Nginx (puerto 443)
    ↓
ModSecurity WAF (inspección)
    ├─ ¿Amenaza detectada?
    │   ├─ Sí → 403 Forbidden (bloqueado)
    │   └─ No → Continuar
    ↓
Nginx Proxy Pass
    ├─ /api/* → Backend (puerto 3000)
    ├─ /socket.io/* → Backend (WebSocket)
    └─ /* → Frontend (puerto 5173)
    ↓
Respuesta ← Backend/Frontend
    ↓
ModSecurity (inspección de respuesta)
    ↓
Nginx → Cliente
```

### Logging Integrado

```nginx
# nginx.conf - Logs con ModSecurity info
log_format modsec '$remote_addr - $remote_user [$time_local] '
                  '"$request" $status $body_bytes_sent '
                  '"$http_referer" "$http_user_agent" '
                  'modsec_audit_id="$modsec_audit_id" '
                  'modsec_score="$modsec_score"';

access_log /var/log/nginx/access_modsec.log modsec;
```

---

## 🚀 Despliegue y Testing

### Validar Configuración de Nginx

```bash
# Test de sintaxis
nginx -t

# Reload sin downtime
nginx -s reload

# Ver configuración activa
nginx -T
```

### Validar Reglas de ModSecurity

```bash
# Test de reglas individuales
modsec-rules-check /etc/nginx/modsec/modsecurity.conf

# Ver reglas cargadas
grep -r "SecRule" /etc/nginx/modsec/
```

### Testing de WAF

```bash
# Test de XSS (debe ser bloqueado)
curl -k "https://localhost/api/users?search=<script>alert(1)</script>"

# Test de SQLi (debe ser bloqueado)
curl -k "https://localhost/api/users?id=1' OR '1'='1"

# Test de LFI (debe ser bloqueado)
curl -k "https://localhost/api/files?path=../../../../etc/passwd"

# Ver logs de ModSecurity
tail -f /var/log/modsec/modsec_audit.log
```

---

## 📊 Monitoreo

### Métricas de Nginx

```nginx
# Stub status module
location /nginx_status {
    stub_status;
    access_log off;
    allow 127.0.0.1;
    deny all;
}
```

Salida:
```
Active connections: 42
server accepts handled requests
 1234 1234 5678
Reading: 0 Writing: 5 Waiting: 37
```

### Alertas de ModSecurity

```bash
# Script de monitoreo de ataques
#!/bin/bash
tail -f /var/log/modsec/modsec_audit.log | \
grep -E "id \"(942100|941100|930100)\"" | \
while read line; do
    echo "ALERTA: Ataque detectado - $line"
    # Enviar notificación (email, Slack, etc.)
done
```

---

## 🔧 Optimización

### Nginx Performance Tuning

```nginx
# Aumentar worker connections
events {
    worker_connections 4096;
}

# File descriptor limits
worker_rlimit_nofile 8192;

# Caching de proxies
proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=api_cache:10m max_size=1g inactive=60m;

location /api/ {
    proxy_cache api_cache;
    proxy_cache_valid 200 5m;
    proxy_cache_use_stale error timeout updating;
    add_header X-Cache-Status $upstream_cache_status;
}
```

### ModSecurity Performance

```apache
# Reducir paranoia level en producción si hay falsos positivos
setvar:tx.paranoia_level=1

# Deshabilitar inspección de ciertos content-types
SecRule RESPONSE_CONTENT_TYPE "@rx ^image/(jpeg|png|gif)" \
    "id:900950,phase:3,pass,nolog,ctl:responseBodyAccess=Off"
```

---

**Ubicación**: `/srcs/conf/`  
**Tecnologías**: Nginx 1.25, ModSecurity 3, OWASP CRS 4  
**Documentación relacionada**: 
- `modsecurity/custom-rules/README.md` - Reglas personalizadas
- `../secrets/certs/README.md` - Certificados SSL/TLS
- `/docker-compose.yml` - Integración con contenedores
