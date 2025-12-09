# 🔒 Certificados TLS/SSL

## 📋 Descripción

Este directorio contiene los certificados SSL/TLS utilizados para habilitar comunicaciones HTTPS seguras en la aplicación. Los certificados pueden ser autofirmados (desarrollo) o emitidos por una CA de confianza (producción).

## 📁 Contenido

### `fullchain.pem`
**Propósito**: Cadena completa de certificados en formato PEM.

**Contiene**:
1. Certificado del servidor (dominio específico)
2. Certificados intermedios de la CA
3. Certificado raíz (opcional, según configuración)

**Uso**: Nginx y otros proxies lo usan para presentar identidad al cliente.

**Formato**: Base64 encoded, múltiples bloques `-----BEGIN CERTIFICATE-----`

---

### `privkey.pem`
**Propósito**: Clave privada asociada al certificado del servidor.

**Características**:
- **EXTREMADAMENTE SENSIBLE** - nunca debe exponerse
- Formato PEM sin cifrar (o cifrado con passphrase)
- Usado por Nginx para descifrar conexiones TLS
- Único y específico para el certificado

**Seguridad**: Permisos estrictos `600`, nunca commitear a Git.

---

### `cert.conf`
**Propósito**: Archivo de configuración OpenSSL para generación de certificados.

**Contiene**:
- Distinguished Name (DN): país, organización, CN (Common Name)
- Subject Alternative Names (SANs): dominios adicionales
- Opciones de criptografía (tamaño de clave, algoritmo)
- Extensiones X.509

**Uso**: Input para scripts de generación de certificados autofirmados.

```ini
[req]
default_bits = 2048
distinguished_name = req_distinguished_name
req_extensions = v3_req

[req_distinguished_name]
countryName = ES
organizationName = Transcendence
commonName = localhost

[v3_req]
subjectAltName = @alt_names

[alt_names]
DNS.1 = localhost
DNS.2 = *.localhost
IP.1 = 127.0.0.1
```

---

## 🔄 Flujo de Uso

```
Generación (desarrollo):
  cert.conf → openssl req → fullchain.pem + privkey.pem

Despliegue:
  docker-compose.yml monta:
    - fullchain.pem → /etc/nginx/ssl/cert.pem
    - privkey.pem   → /etc/nginx/ssl/key.pem

Nginx lee:
  ssl_certificate     /etc/nginx/ssl/cert.pem;
  ssl_certificate_key /etc/nginx/ssl/key.pem;

Cliente (navegador):
  HTTPS request → Nginx → Presenta fullchain.pem
  Navegador valida cadena de confianza
  Si autofirmado: warning (aceptar manualmente)
```

## 🔗 Integración con el Proyecto

### Script de Generación (`srcs/scripts/00.gen_selfsigned_cert.sh`)
```bash
#!/bin/bash
# Genera certificado autofirmado válido por 365 días

openssl req -x509 -nodes \
  -days 365 \
  -newkey rsa:2048 \
  -keyout privkey.pem \
  -out fullchain.pem \
  -config cert.conf \
  -extensions v3_req
```

### Nginx Configuration (`srcs/conf/nginx/nginx.conf`)
```nginx
server {
    listen 443 ssl http2;
    server_name localhost;

    ssl_certificate     /etc/ssl/certs/fullchain.pem;
    ssl_certificate_key /etc/ssl/certs/privkey.pem;
    
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;
    ssl_prefer_server_ciphers on;

    location / {
        proxy_pass http://frontend:80;
        # ...
    }
}
```

### Docker Compose (`docker-compose.yml`)
```yaml
services:
  nginx:
    volumes:
      - ./srcs/secrets/certs:/etc/ssl/certs:ro
```

## 🛡️ Consideraciones de Seguridad

### Desarrollo vs Producción

| Aspecto | Desarrollo | Producción |
|---------|------------|------------|
| Tipo | Autofirmado | CA firmado (Let's Encrypt) |
| Validez | 365 días | 90 días (renovación auto) |
| SAN | localhost, 127.0.0.1 | Dominio real (transcendence.com) |
| Permisos | 600 (owner) | 400 (read-only) |
| Warning navegador | Sí (aceptar manualmente) | No (confianza automática) |

### ⚠️ IMPORTANTE: Protección de `privkey.pem`

```bash
# Verificar permisos correctos
ls -la srcs/secrets/certs/privkey.pem
# Debe mostrar: -rw------- (600)

# Si no, corregir:
chmod 600 srcs/secrets/certs/privkey.pem

# Asegurar que está en .gitignore
echo "srcs/secrets/certs/*.pem" >> .gitignore
```

## 🔄 Renovación de Certificados

### Desarrollo (autofirmado)
```bash
# Regenerar certificado
cd srcs/secrets/certs
../../../scripts/00.gen_selfsigned_cert.sh

# Reiniciar Nginx
docker restart nginx-waf
```

### Producción (Let's Encrypt)
```bash
# Usando Certbot
docker run -it --rm \
  -v $(pwd)/srcs/secrets/certs:/etc/letsencrypt \
  certbot/certbot certonly --standalone \
  -d transcendence.yourdomain.com \
  --email admin@yourdomain.com \
  --agree-tos

# Copiar certificados generados
cp /etc/letsencrypt/live/transcendence.yourdomain.com/fullchain.pem .
cp /etc/letsencrypt/live/transcendence.yourdomain.com/privkey.pem .

# Configurar renovación automática (cron)
0 0 1 * * certbot renew && docker restart nginx-waf
```

## 🧪 Validación de Certificados

```bash
# Ver detalles del certificado
openssl x509 -in fullchain.pem -text -noout | less

# Verificar que CN y SANs coinciden
openssl x509 -in fullchain.pem -noout -subject -ext subjectAltName

# Test de conexión SSL
openssl s_client -connect localhost:443 -servername localhost

# Verificar cadena completa
openssl verify -CAfile fullchain.pem fullchain.pem

# Ver fecha de expiración
openssl x509 -in fullchain.pem -noout -enddate
```

## 📊 Tipos de Certificados

### Autofirmado (Self-Signed)
**Pros**:
- Gratis e inmediato
- Control total
- Perfecto para desarrollo local

**Contras**:
- Navegadores muestran warning
- No validado por CA externa
- No apto para producción pública

### CA Firmado (Let's Encrypt, DigiCert, etc.)
**Pros**:
- Confianza automática en navegadores
- Validación externa de identidad
- Requerido para producción

**Contras**:
- Requiere dominio público
- Proceso de validación
- Renovación periódica necesaria

## 🔍 Troubleshooting

### Error: "NET::ERR_CERT_AUTHORITY_INVALID"
**Causa**: Certificado autofirmado no confiable.  
**Solución**: En Chrome/Firefox, aceptar manualmente o importar CA a trust store del SO.

### Error: "SSL handshake failed"
**Causa**: `privkey.pem` no coincide con `fullchain.pem`.  
**Solución**: Regenerar ambos con el mismo comando.

### Error: "Permission denied reading key file"
**Causa**: Nginx no tiene permisos para leer `privkey.pem`.  
**Solución**: 
```bash
chmod 600 privkey.pem
chown nginx:nginx privkey.pem  # Si Nginx corre como usuario nginx
```

## 📚 Referencias Adicionales

- [OpenSSL Cookbook](https://www.feistyduck.com/library/openssl-cookbook/)
- [Mozilla SSL Configuration Generator](https://ssl-config.mozilla.org/)
- [Let's Encrypt Documentation](https://letsencrypt.org/docs/)
- Script relacionado: `../../scripts/00.gen_selfsigned_cert.sh`
- Configuración: `../../conf/nginx/nginx.conf`

---

**Ubicación**: `/srcs/secrets/certs/`  
**Nivel de sensibilidad**: 🔴 **CRÍTICO** - privkey.pem debe protegerse  
**Gestión**: Manual en dev, automatizada (Certbot) en producción  
**Expiración**: Verificar cada 90 días (Let's Encrypt) o 365 días (autofirmado)
