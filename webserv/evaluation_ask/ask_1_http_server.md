# 🌐 BASICS OF AN HTTP SERVER

## 📋 **OBJETIVO DE ESTE DOCUMENTO**

Este documento responde específicamente a la pregunta **"Explain the basics of an HTTP server"** de la hoja de evaluación oficial. Se centra exclusivamente en los conceptos fundamentales de un servidor HTTP y cómo están implementados en nuestro proyecto.

---

## 🔍 **¿QUÉ ES UN SERVIDOR HTTP?**

### **Definición Fundamental**
Un servidor HTTP es un programa que implementa el protocolo HTTP (HyperText Transfer Protocol) para servir contenido web. Su función esencial es actuar como intermediario entre clientes (navegadores, aplicaciones) y recursos web.

### **Ciclo Básico de Funcionamiento**
```
1. ESCUCHAR → El servidor espera conexiones en un puerto
2. ACEPTAR   → Acepta nuevas conexiones de clientes
3. RECIBIR   → Lee el request HTTP del cliente
4. PROCESAR  → Interpreta la solicitud y busca el recurso
5. GENERAR   → Crea una respuesta HTTP apropiada
6. ENVIAR    → Transmite la respuesta al cliente
7. MANTENER  → Optionalmente mantiene la conexión (keep-alive)
```

## ⚙️ **CONFIGURACIÓN DEL SERVIDOR**

### **Elementos Básicos de Configuración**
Un servidor HTTP necesita configuración para:
- **Puertos de escucha**: Donde el servidor acepta conexiones
- **Nombres de servidor**: Hostnames que el servidor reconoce
- **Directorio raíz**: Ubicación de los archivos web
- **Métodos permitidos**: Qué operaciones HTTP están habilitadas
- **Límites**: Tamaño máximo de requests, timeouts, etc.

### **Ejemplo de Configuración**
```nginx
server {
    listen 9000;              # Puerto de escucha
    server_name localhost;    # Nombre del servidor
    root www;                 # Directorio raíz
    index index.html;         # Archivo por defecto
    
    location / {
        methods GET POST;     # Métodos permitidos
    }
}
```

## 🎯 **REGLAS CRÍTICAS DE IMPLEMENTACIÓN**

### **1. Manejo Correcto de recv/send**
- **Nunca usar errno** después de recv/send
- Solo verificar el **valor de retorno** de la función
- Si retorna < 0: error, si retorna 0: conexión cerrada

### **2. Una Operación por select()**
- Solo **un recv/send** por cliente por iteración de select()
- Evita bloqueos y garantiza fairness entre clientes

### **3. Monitoreo Simultáneo**
- select() debe monitorear **read Y write** file descriptors simultáneamente
- Permite responder a eventos de lectura y escritura eficientemente

---

## 📊 **STATUS CODES PRINCIPALES**

Los códigos de estado HTTP informan al cliente sobre el resultado de su request:

- **2xx Success**: 200 OK, 201 Created, 204 No Content
- **4xx Client Error**: 400 Bad Request, 403 Forbidden, 404 Not Found, 405 Method Not Allowed, 413 Payload Too Large
- **5xx Server Error**: 500 Internal Server Error


## ✅ **RESUMEN DE CONCEPTOS BÁSICOS**

Un servidor HTTP básico debe implementar:

1. **Socket Programming**: Escuchar en puertos, aceptar conexiones
2. **Protocol Parsing**: Interpretar requests HTTP correctamente
3. **Response Generation**: Crear responses HTTP válidas
4. **Connection Management**: Manejar múltiples clientes eficientemente
5. **Error Handling**: Gestionar errores sin crashear
6. **Resource Serving**: Servir archivos estáticos
7. **Method Support**: Implementar GET, POST, DELETE mínimo
8. **Configuration**: Sistema configurable para diferentes setups

**Nuestro servidor implementa todos estos conceptos siguiendo estrictamente las especificaciones HTTP/1.1 y las reglas del subject de 42.**

---

## 🌐 **COMPORTAMIENTO EN EL NAVEGADOR**

### **¿Qué verás al acceder a `localhost:9000`?**

**RESULTADO: Directory Listing en AMBOS casos**

#### **Caso 1: `localhost:9000` (sin barra final)**
```html
Directory Listing for /
├── cgi-bin        (Scripts CGI - PHP y Python)
├── errors         (Páginas de error personalizadas)  
├── index.html     (Página principal)
├── 404.html       (Página de error 404)
├── files          (Archivos estáticos de prueba)
└── Uploads        (Directorio para subir archivos)
```

#### **Caso 2: `localhost:9000/` (con barra final)**
```html
Directory Listing for /
├── cgi-bin        (Scripts CGI - PHP y Python)
├── errors         (Páginas de error personalizadas)  
├── index.html     (Página principal)
├── 404.html       (Página de error 404)
├── files          (Archivos estáticos de prueba)
└── Uploads        (Directorio para subir archivos)
```

### **¿Por qué ambos muestran lo mismo?**

1. **Normalización de URI**: El servidor normaliza ambas URLs a la ruta `/`
2. **Configuración**: `directory_listing on` está habilitado para la ubicación `/`
3. **Prioridad**: Directory listing tiene prioridad sobre archivo index cuando está habilitado
4. **Estándar HTTP**: Ambas formas son equivalentes para el directorio raíz

### **Para acceder al archivo index.html directamente:**
- `localhost:9000/index.html` → Muestra: `<h1>Welcome to localhost</h1>`

### **Comportamiento Técnico:**
```cpp
// En Response.cpp - línea 138
if (uri[uri.length() - 1] != '/') listing << "/";  // Normaliza URI
```

El servidor maneja ambas formas correctamente y las trata como acceso al directorio raíz.

---
