# 🧩 HEADERS C++ - WEBSERV

Esta carpeta contiene los **archivos de cabecera (.hpp)** del proyecto webserv. Implementan las clases principales del servidor HTTP con arquitectura modular.

## 📂 **ARCHIVOS DE CABECERA**

```
include/
├── 🖥️ Server.hpp     # Servidor principal con select() loop
├── 👤 Client.hpp     # Gestión de clientes HTTP
├── 📄 Request.hpp    # Parsing de requests HTTP
├── 📋 Response.hpp   # Generación de responses HTTP
├── ⚙️ Config.hpp     # Parser de configuración
└── 🐍 CGI.hpp        # Ejecución de scripts CGI
```

---

## 🎯 **RESPONSABILIDADES**

### 🖥️ **Server.hpp**
- **I/O Multiplexing**: Un solo `select()` para todos los file descriptors
- **Client Management**: Creación/destrucción de clientes
- **Socket Operations**: Accept, bind, listen
- **Non-blocking I/O**: Todas las operaciones son no bloqueantes

### 👤 **Client.hpp**
- **HTTP State Machine**: Estados de conexión (READING, PROCESSING, WRITING)
- **Request/Response Handling**: Parsing y generación
- **Connection Management**: Keep-alive y timeouts
- **Buffer Management**: Read/write buffers

### � **Request.hpp**
- **HTTP Parsing**: Métodos, URI, headers, body
- **Content Validation**: Límites de tamaño, métodos permitidos
- **URL Decoding**: Manejo de caracteres especiales
- **Query Parameters**: Parsing de parámetros GET

### 📋 **Response.hpp**
- **HTTP Generation**: Status codes, headers, body
- **Content Types**: Auto-detección de MIME types
- **Static Files**: Serving de archivos estáticos
- **Error Pages**: Páginas de error personalizadas

### ⚙️ **Config.hpp**
- **Configuration Parsing**: Sintaxis tipo Nginx
- **Virtual Hosts**: Múltiples servidores
- **Location Blocks**: Configuración por ruta
- **Directive Validation**: Verificación de sintaxis

### � **CGI.hpp**
- **Process Execution**: fork(), execve(), pipes
- **Environment Setup**: Variables CGI estándar
- **I/O Redirection**: stdin, stdout, stderr
- **Timeout Handling**: Prevención de procesos colgados

---

## 🏗️ **ARQUITECTURA**

```
Server (select loop) → Client (HTTP state) → Request (parsing)
                                           → Response (generation)
                                           → CGI (scripts)
Config (parsing) → Server (configuration)
```

### 🎯 **Principios de Diseño**
- **Single Responsibility**: Cada clase una función específica
- **RAII**: Memory management automático
- **Non-blocking I/O**: Sin operaciones bloqueantes
- **Error Handling**: Sin uso de errno

---

## 📊 **RESUMEN**

| Header           | Responsabilidad      | Complejidad | Criticidad |
|------------------|----------------------|-------------|------------|
| **Server.hpp**   | I/O multiplexing     |    Alta     | 🚨 Crítica |
| **Client.hpp**   | Estado HTTP          |    Media    | 🔥 Alta    |
| **Request.hpp**  | Parsing HTTP         |    Media    | 🔥 Alta    |
| **Response.hpp** | Generación HTTP      |    Media    | 🔥 Alta    |
| **Config.hpp**   | Parser configuración |    Baja     | 📍 Media   |
| **CGI.hpp**      | Ejecución scripts    |    Alta     | 📍 Media   |

---

## 🚨 **PUNTOS CRÍTICOS**

- **✅ C++98 Standard**: Sin C++11 o superior
- **✅ Un solo select()**: En Server::run() únicamente
- **✅ Non-blocking I/O**: Todas las operaciones de red
- **✅ Memory Management**: RAII sin memory leaks
- **✅ Error Handling**: Sin errno después de socket ops

**🎯 Arquitectura modular que cumple con todos los requisitos de 42 School.**

### ✅ **Estilo de Código**

- **📝 Naming**: CamelCase para clases, snake_case para variables
- **🔒 Encapsulation**: Private members con getters públicos
- **📋 Const Correctness**: const para métodos que no modifican estado
- **🛡️ Exception Safety**: Strong exception guarantee donde sea posible

### 🚨 **Errores Comunes a Evitar**

- **❌ Memory Leaks**: Usar RAII y smart pointers cuando sea apropiado
- **❌ Blocking Operations**: Todas las I/O operations deben ser no bloqueantes
- **❌ errno Usage**: No usar errno después de socket operations
- **❌ Multiple select()**: Solo un select() en Server::run()

---

## 📚 **REFERENCIAS TÉCNICAS**

### 🔗 **Estándares**

- **HTTP/1.1**: [RFC 7230-7235](https://tools.ietf.org/html/rfc7230)
- **CGI**: [RFC 3875](https://tools.ietf.org/html/rfc3875)
- **C++98**: [ISO/IEC 14882:1998](https://www.iso.org/standard/25845.html)

### 📖 **Documentación**

- **Socket Programming**: [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- **select()**: `man 2 select`
- **HTTP Parsing**: [HTTP Made Really Easy](https://www.jmarshall.com/easy/http/)

---

## 📋 **RESUMEN EJECUTIVO**

| 🧩 Header        | 🎯 Responsabilidad                   | 📊 Complejidad | 🔥 Criticidad |
|------------------|--------------------------------------|----------------|---------------|
| **Server.hpp**   | I/O multiplexing y gestión principal | Alta           | 🚨 Crítica    |
| **Client.hpp**   | Estado de conexiones HTTP            | Media          | 🔥 Alta       |
| **Request.hpp**  | Parsing de HTTP requests             | Media          | 🔥 Alta       |
| **Response.hpp** | Generación de HTTP responses         | Media          | 🔥 Alta       |
| **Config.hpp**   | Parser de configuración              | Baja           | 📍 Media      |
| **CGI.hpp**      | Ejecución de scripts                 | Alta           | 📍 Media      |

**🎯 Arquitectura modular y robusta que cumple con todos los requisitos de 42 School para el proyecto webserv.**