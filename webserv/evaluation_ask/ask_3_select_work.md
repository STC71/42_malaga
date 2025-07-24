# ⚙️ HOW DOES SELECT() WORK

## 📋 **OBJETIVO DE ESTE DOCUMENTO**

Este documento responde específicamente a la pregunta **"Ask for an explanation of how does select() (or equivalent) work"** de la hoja de evaluación oficial. Se centra exclusivamente en explicar el funcionamiento interno de select() y su uso práctico.

### **📂 Ubicación en el Código**
- **Archivo principal**: `srcs/Server.cpp`
- **Función clave**: `Server::run()`
- **Uso específico**: Main loop del servidor
- **Headers incluidos**: `<sys/select.h>`, `<sys/time.h>`, `<unistd.h>`

---

## 🔍 **¿CÓMO FUNCIONA SELECT()?**

### **Concepto Fundamental**
select() es una **llamada al sistema** que permite a un programa **monitorear múltiples file descriptors** simultáneamente y **bloquear hasta que al menos uno esté listo** para realizar I/O sin bloquear.

### **Declaración de la Función**
```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

---

## 🧠 **FUNCIONAMIENTO INTERNO**

### **1. Preparación de los Sets**
```c
fd_set read_fds, write_fds;
FD_ZERO(&read_fds);     // Limpiar el set
FD_ZERO(&write_fds);    // Limpiar el set
FD_SET(socket_fd, &read_fds);   // Añadir FD al set de lectura
```

### **2. Llamada a select()**
```c
int ready = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
```
**¿Qué hace el kernel?**
- Examina todos los file descriptors en los sets
- Verifica si alguno está listo para I/O
- Si ninguno está listo: **bloquea el proceso**
- Si alguno está listo: **retorna inmediatamente**

### **3. Verificación de Resultados**
```c
if (FD_ISSET(socket_fd, &read_fds)) {
    // Este FD está listo para lectura
    read(socket_fd, buffer, size);
}
```

---

## ⏱️ **ESTADOS DE FILE DESCRIPTORS**

### **Listo para Lectura**
Un FD está listo para lectura cuando:
- ✅ Hay datos disponibles en el buffer de recepción
- ✅ La conexión ha sido cerrada por el peer (EOF)
- ✅ Es un listening socket con conexiones pendientes
- ✅ Ha ocurrido un error en el socket

### **Listo para Escritura**
Un FD está listo para escritura cuando:
- ✅ Hay espacio disponible en el buffer de envío
- ✅ La conexión está establecida (para sockets)
- ✅ Ha ocurrido un error en el socket

### **Excepciones**
Un FD tiene una excepción cuando:
- ⚠️ Datos out-of-band (TCP urgent data)
- ⚠️ Condiciones excepcionales específicas del socket

---

## 🔄 **CICLO DE TRABAJO DE SELECT()**

### **Paso a Paso**
```
1. LIMPIAR → FD_ZERO() en todos los sets
2. CONFIGURAR → FD_SET() para cada FD de interés
3. CALCULAR → Determinar max_fd + 1
4. LLAMAR → select() bloquea hasta que hay eventos
5. VERIFICAR → FD_ISSET() para cada FD
6. PROCESAR → Realizar I/O en FDs listos
7. REPETIR → Volver al paso 1
```

### **Ejemplo Práctico en Nuestro Servidor**
```c
while (true) {
    // 1. LIMPIAR
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    max_fd = 0;
    
    // 2. CONFIGURAR server sockets (siempre listen)
    for (int server_fd : server_sockets) {
        FD_SET(server_fd, &read_fds);
        max_fd = max(max_fd, server_fd);
    }
    
    // 3. CONFIGURAR client sockets
    for (Client& client : clients) {
        FD_SET(client.fd, &read_fds);  // Siempre leer
        if (client.has_response_ready) {
            FD_SET(client.fd, &write_fds);  // Solo escribir si hay datos
        }
        max_fd = max(max_fd, client.fd);
    }
    
    // 4. LLAMAR select()
    int ready = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
    
    // 5-6. VERIFICAR y PROCESAR
    if (ready > 0) {
        handle_ready_fds(&read_fds, &write_fds);
    }
}
```

---

## 📊 **PARÁMETROS DE SELECT()**

### **1. nfds (int)**
- **Propósito**: Número del FD más alto + 1
- **Razón**: Optimización - el kernel solo verifica FDs 0 hasta nfds-1
- **Cálculo**: `max_fd + 1` donde max_fd es el FD más grande en uso

### **2. readfds (fd_set*)**
- **Propósito**: Set de FDs a monitorear para lectura
- **Modificado**: select() modifica este set (marca solo FDs listos)
- **Uso**: FD_SET() para añadir, FD_ISSET() para verificar

### **3. writefds (fd_set*)**
- **Propósito**: Set de FDs a monitorear para escritura
- **Uso típico**: Sockets con datos pendientes de envío
- **Optimización**: Solo añadir FDs cuando realmente hay datos que enviar

### **4. exceptfds (fd_set*)**
- **Propósito**: Set de FDs a monitorear para excepciones
- **Uso común**: NULL (no usado en la mayoría de casos)
- **Aplicaciones**: Datos out-of-band, condiciones especiales

### **5. timeout (struct timeval*)**
- **NULL**: Bloqueo indefinido hasta que hay eventos
- **{0, 0}**: No bloquear (polling)
- **{sec, usec}**: Bloquear máximo ese tiempo

---

## ⚡ **VALORES DE RETORNO**

### **Casos de Retorno**
```c
int result = select(...);

if (result > 0) {
    // Número de FDs listos
    // Procesar FDs con FD_ISSET()
}
else if (result == 0) {
    // Timeout (si se especificó)
    // Ningún FD está listo
}
else { // result < 0
    // Error (verificar errno)
    // Typical: EINTR (signal received)
}
```

### **Manejo de Errores Común**
```c
if (select(...) < 0) {
    if (errno == EINTR) {
        continue;  // Signal recibido, reintentar
    } else {
        perror("select failed");
        exit(1);
    }
}
```

---

## 🔧 **MACROS DE MANIPULACIÓN DE FD_SET**

### **Funciones Básicas**
```c
FD_ZERO(&set);          // Limpiar todos los bits
FD_SET(fd, &set);       // Añadir fd al set
FD_CLR(fd, &set);       // Remover fd del set
FD_ISSET(fd, &set);     // Verificar si fd está en el set
```

### **Implementación Conceptual**
```c
// fd_set es esencialmente un array de bits
typedef struct {
    long bits[FD_SETSIZE/sizeof(long)];
} fd_set;

// FD_SET(fd, &set) hace algo como:
set.bits[fd / BITS_PER_LONG] |= (1 << (fd % BITS_PER_LONG));

// FD_ISSET(fd, &set) hace algo como:
return set.bits[fd / BITS_PER_LONG] & (1 << (fd % BITS_PER_LONG));
```

---

## ⚠️ **CONSIDERACIONES IMPORTANTES**

### **1. Modificación de Sets**
- select() **modifica** los sets de entrada
- Solo quedan marcados los FDs que están listos
- **Hay que reconstruir los sets** en cada iteración

### **2. Límite de FD_SETSIZE**
- Típicamente 1024 en sistemas modernos
- Es un límite **compile-time**, no runtime
- Para más FDs, usar poll() o epoll()

### **3. Rendimiento O(n)**
- select() debe escanear todos los FDs hasta max_fd
- Para muchos FDs, alternativas como epoll() son más eficientes
- Para nuestro proyecto, select() es perfectamente adecuado

### **4. Interrupciones por Señales**
- select() puede ser interrumpido por señales (EINTR)
- Importante manejar este caso y reintentar

---

## ✅ **RESUMEN**

**Cómo funciona select()**:
1. **Entrada**: Sets de FDs a monitorear + timeout opcional
2. **Kernel**: Examina todos los FDs, bloquea si ninguno está listo
3. **Retorno**: Número de FDs listos + sets modificados con solo FDs listos
4. **Aplicación**: Verifica con FD_ISSET() y procesa FDs listos

**Ventajas**:
- ✅ Manejo de múltiples FDs con un solo thread
- ✅ Eficiente para cantidades moderadas de conexiones
- ✅ Estándar POSIX, muy portable
- ✅ API simple y bien documentada

**En nuestro servidor**: Permite manejar múltiples clientes HTTP simultáneamente sin bloqueos, procesando solo los eventos que están realmente listos.
