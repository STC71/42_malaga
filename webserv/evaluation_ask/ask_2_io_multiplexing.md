# 🔀 I/O MULTIPLEXING

## 📋 **OBJETIVO DE ESTE DOCUMENTO**

Este documento responde específicamente a la pregunta **"Ask what function the group used for I/O Multiplexing"** de la hoja de evaluación oficial. Se centra exclusivamente en la función utilizada y los conceptos fundamentales del I/O multiplexing.

### **📂 Ubicación en el Código**
- **Archivo principal**: `srcs/Server.cpp`
- **Función clave**: `Server::run()`
- **Líneas relevantes**: Main loop con select()
- **Headers incluidos**: `<sys/select.h>`, `<unistd.h>`

---

## 🔍 **¿QUÉ FUNCIÓN UTILIZAMOS PARA I/O MULTIPLEXING?**

### **Respuesta Directa**
**Utilizamos la función `select()`** para implementar I/O multiplexing en nuestro servidor HTTP.

### **Declaración de la Función**
```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

---

## 🔧 **¿POR QUÉ SELECT()?**

### **Ventajas de select()**
- ✅ **Estándar POSIX**: Compatible con todos los sistemas Unix/Linux
- ✅ **Multiplataforma**: Funciona en Linux, macOS, BSD
- ✅ **Simplicidad**: API clara y bien documentada
- ✅ **Adecuado para el proyecto**: Maneja eficientemente el número de conexiones esperado

### **Alternativas Consideradas**
- **poll()**: Similar a select() pero con interfaz diferente
- **epoll()**: Específico de Linux, más eficiente para muchas conexiones
- **kqueue()**: Específico de BSD/macOS, equivalente a epoll

**Razón de la elección**: select() cumple perfectamente los requisitos del proyecto y es el más compatible.

---

## ⚙️ **¿CÓMO FUNCIONA SELECT()?**

### **Concepto Fundamental**
select() permite que un programa monitoree múltiples file descriptors simultáneamente y se "despierte" cuando alguno está listo para:
- **Lectura**: Hay datos disponibles para leer
- **Escritura**: Se puede escribir sin bloquear
- **Excepción**: Ocurrió una condición excepcional

### **Parámetros de select()**
1. **nfds**: Número del file descriptor más alto + 1
2. **readfds**: Set de FDs a monitorear para lectura
3. **writefds**: Set de FDs a monitorear para escritura
4. **exceptfds**: Set de FDs a monitorear para excepciones (no usado)
5. **timeout**: Tiempo máximo de espera (NULL = bloqueo indefinido)

### **Ciclo Básico de Uso**
```
1. PREPARAR → Limpiar y configurar los fd_sets
2. AÑADIR   → Agregar file descriptors a los sets apropiados
3. LLAMAR   → Ejecutar select() y esperar eventos
4. VERIFICAR → Comprobar qué FDs están listos
5. PROCESAR → Manejar cada FD listo
6. REPETIR  → Volver al paso 1
```

---

## 🎯 **IMPLEMENTACIÓN EN NUESTRO SERVIDOR**

### **Estructura Principal**
```
MAIN LOOP:
  ├── FD_ZERO() - Limpiar sets
  ├── FD_SET() - Añadir server sockets (lectura)
  ├── FD_SET() - Añadir client sockets (lectura/escritura)
  ├── select() - Esperar eventos
  ├── Procesar nuevas conexiones
  ├── Procesar lecturas de clientes
  └── Procesar escrituras a clientes
```

### **File Descriptors Monitoreados**
- **Server sockets** (read): Para aceptar nuevas conexiones
- **Client sockets** (read): Para recibir requests HTTP
- **Client sockets** (write): Para enviar responses HTTP (solo cuando hay datos listos)

### **Ventajas de Nuestro Enfoque**
- ✅ **No blocking**: Nunca se bloquea esperando I/O
- ✅ **Escalable**: Maneja múltiples clientes con un solo thread/hilo
- ✅ **Eficiente**: Solo procesa FDs que están realmente listos
- ✅ **Determinista**: Comportamiento predecible y controlado

### **Verificación en el Código**
Para revisar la implementación, buscar en:
1. **`srcs/Server.cpp`** - Función `Server::run()`: Bucle principal con select()
2. **`srcs/Server.cpp`** - Funciones `handleNewConnections()`, `handleClientReads()`, `handleClientWrites()`
3. **`include/Server.hpp`** - Declaraciones de fd_set y variables relacionadas

---

## 📊 **COMPARACIÓN CON OTRAS OPCIONES**

### **select() vs poll()**
- **select()**: Usa bitmasks (fd_set), límite de FD_SETSIZE
- **poll()**: Usa array de estructuras, sin límite fijo
- **Para nuestro caso**: select() es suficiente y más simple

### **select() vs epoll() (Linux)**
- **select()**: O(n) para revisar FDs, reescribe sets cada vez
- **epoll()**: O(1) para eventos listos, mantiene estado
- **Para nuestro caso**: select() es adecuado para el volumen esperado

### **select() vs kqueue() (BSD/macOS)**
- **select()**: Estándar POSIX, disponible en todas partes
- **kqueue()**: Más eficiente pero específico de BSD
- **Para nuestro caso**: select() ofrece mejor portabilidad

---

## ⚠️ **LIMITACIONES Y CONSIDERACIONES**

### **Limitaciones de select()**
- **FD_SETSIZE**: Límite máximo de file descriptors (típicamente 1024)
- **Rendimiento**: O(n) para escanear todos los FDs
- **Modificación de sets**: Los fd_sets se modifican en cada llamada

### **¿Por qué no afectan nuestro proyecto?**
- **Escala apropiada**: Un servidor web típico no necesita miles de conexiones simultáneas
- **Simplicidad**: El código es más fácil de entender y mantener
- **Portabilidad**: Funciona en cualquier sistema Unix/Linux sin modificaciones

---

## ✅ **RESUMEN**

**Función utilizada**: `select()`

**Razones de la elección**:
1. **Cumple los requisitos**: Maneja múltiples conexiones eficientemente
2. **Estándar**: Disponible en todos los sistemas Unix/Linux
3. **Simplicidad**: API clara y bien documentada
4. **Adecuado**: Perfecto para la escala del proyecto webserv

**Resultado**: Un servidor que maneja múltiples clientes simultáneamente sin bloqueos, usando un solo thread y siguiendo las mejores prácticas de programación de red.
