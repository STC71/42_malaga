# 📦 Static Assets - Archivos Estáticos del Frontend

## 📋 Descripción General

Este directorio contiene **archivos estáticos** del frontend que se sirven directamente sin procesamiento por Vite. Son recursos que necesitan estar disponibles en rutas específicas para testing, health checks o compatibilidad.

## 📄 Archivo Principal

```
static/
└── app.js    # Placeholder JavaScript (3 líneas)
```

## 🎯 Propósito

### app.js

**Contenido:**
```javascript
// Minimal placeholder app.js so /static/app.js returns 200 for test harness
console.log('static app.js placeholder');
```

**Razón de existencia:**
- ✅ El script de testing (`test_auto.sh`) verifica que `/static/app.js` retorne HTTP 200
- ✅ Cumple requisitos de la subject de tener archivos JS estáticos disponibles
- ✅ Placeholder para futuras expansiones

**Acceso:**
```bash
curl http://localhost:2323/static/app.js
# Output: console.log('static app.js placeholder');
```

## 🌐 Configuración de Nginx

Los archivos en `/static/` son servidos por Nginx:

**Ubicación:** `srcs/conf/nginx/nginx.conf`

```nginx
location /static/ {
    alias /app/frontend/static/;
    try_files $uri $uri/ =404;
    
    # Headers de cache para archivos estáticos
    add_header Cache-Control "public, max-age=31536000, immutable";
}
```

## 📂 Posibles Expansiones

Este directorio puede contener en el futuro:

### 1. JavaScript Estático
```
static/
├── app.js              # Actual placeholder
├── analytics.js        # Tracking de métricas
├── error-handler.js    # Manejador global de errores
└── polyfills.js        # Polyfills para navegadores antiguos
```

### 2. CSS Estático
```
static/
├── legacy.css          # Estilos legacy
├── print.css           # Estilos de impresión
└── themes/
    ├── dark.css
    └── light.css
```

### 3. Assets Estáticos
```
static/
├── fonts/              # Fuentes web
│   ├── roboto.woff2
│   └── opensans.woff2
├── icons/              # Iconos SVG
│   ├── favicon.ico
│   └── logo.svg
└── docs/               # Documentación estática
    ├── api.html
    └── terms.html
```

### 4. Manifests & Workers
```
static/
├── manifest.json       # PWA manifest
├── robots.txt          # SEO robots
├── sitemap.xml         # Sitemap
└── service-worker.js   # Service worker PWA
```

## 🔄 Diferencia con /public/

### `/static/` (este directorio)
- ✅ Servido directamente por **Nginx**
- ✅ No procesado por Vite
- ✅ Acceso directo: `/static/file.js`
- ✅ Para archivos que DEBEN estar en ruta específica
- ✅ Cache agresivo (immutable)

### `/public/` (directorio de Vite)
- ✅ Procesado por **Vite** en desarrollo
- ✅ Copiado a `/dist/` en build
- ✅ Acceso directo: `/file.js` (raíz)
- ✅ Para assets que Vite debe copiar
- ✅ Cache configurable

**Ejemplo:**
```
/public/logo.png        → http://localhost:2323/logo.png
/static/app.js          → http://localhost:2323/static/app.js
```

## 🧪 Testing

### Verificar Accesibilidad

```bash
# Desarrollo (puerto 2323)
curl -I http://localhost:2323/static/app.js
# Debería retornar: HTTP/1.1 200 OK

# Producción (puerto 443 con Nginx)
curl -I https://localhost/static/app.js
```

### Test Automático

El script `test_auto.sh` valida este archivo:

```bash
# En test_auto.sh
curl -s -o /dev/null -w "%{http_code}" http://localhost:2323/static/app.js
# Debe retornar: 200
```

## 📝 Convenciones

### Añadir Nuevos Archivos

1. **Crear archivo en `/static/`**
   ```bash
   touch frontend/static/analytics.js
   ```

2. **Añadir contenido**
   ```javascript
   // analytics.js
   (function() {
       console.log('Analytics initialized');
   })();
   ```

3. **Verificar acceso**
   ```bash
   curl http://localhost:2323/static/analytics.js
   ```

4. **Actualizar documentación** (este README)

### Naming Conventions

- ✅ Usar **kebab-case**: `error-handler.js`, `theme-dark.css`
- ✅ Archivos JavaScript: extensión `.js`
- ✅ Archivos CSS: extensión `.css`
- ✅ Subdirectorios: minúsculas sin espacios

## 🔐 Seguridad

### Headers de Seguridad (Nginx)

```nginx
location /static/ {
    # ...
    
    # Prevenir ejecución de scripts en subdirectorios
    add_header X-Content-Type-Options "nosniff";
    
    # CSP para archivos estáticos
    add_header Content-Security-Policy "default-src 'self'";
}
```

### Consideraciones

- ❌ **NO** almacenar archivos sensibles (.env, keys, passwords)
- ❌ **NO** hacer commit de archivos temporales o logs
- ✅ **SÍ** usar archivos minificados en producción
- ✅ **SÍ** validar tamaño de archivos antes de añadir

## 🚀 Despliegue

### Desarrollo

Los archivos se sirven directamente desde el directorio:

```yaml
# docker-compose.yml
volumes:
  - ./frontend/static:/app/frontend/static:ro
```

### Producción

Los archivos se copian al contenedor:

```dockerfile
# Dockerfile
COPY static /app/frontend/static
```

## 📊 Estructura Recomendada (Futuro)

```
static/
├── README.md                 # Este archivo
├── app.js                    # Placeholder actual
├── js/
│   ├── analytics.js
│   ├── error-handler.js
│   └── polyfills.js
├── css/
│   ├── legacy.css
│   └── print.css
├── fonts/
│   ├── roboto.woff2
│   └── opensans.woff2
├── icons/
│   ├── favicon.ico
│   └── logo.svg
├── docs/
│   ├── api.html
│   └── terms.html
└── manifests/
    ├── manifest.json
    ├── robots.txt
    └── sitemap.xml
```

## 📚 Documentación Relacionada

- [Frontend README](../README.md) - Documentación general del frontend
- [Public Directory](../public/README.md) - Assets procesados por Vite
- [Nginx Configuration](../../srcs/conf/nginx/nginx.conf) - Configuración del servidor

## 🔗 Enlaces Útiles

- [Vite Static Assets](https://vitejs.dev/guide/assets.html)
- [Nginx Static Files](https://docs.nginx.com/nginx/admin-guide/web-server/serving-static-content/)
- [Web Performance](https://web.dev/fast/)

## 🤝 Equipo de Desarrollo

- **rdel-olm** - Static assets management
- **nporras-** - Frontend infrastructure
- **davigome** - Nginx configuration
- **sternero** - Testing automation
- **jesopan-** - DevOps integration

---

**📦 Static Assets** - Frontend Static Files  
*Última actualización: Diciembre 2025*
