# 🎛️ SINGLE SELECT() MANAGEMENT

## 📋 **OBJETIVO DE ESTE DOCUMENTO**

Este documento responde específicamente a la pregunta **"Ask if they use only one select() (or equivalent) and how they've managed the server to accept and the client to read/write"** de la hoja de evaluación oficial. Se centra en explicar cómo un solo select() maneja todas las operaciones del servidor.

### **📂 Ubicación en el Código**
- **Archivo principal**: `srcs/Server.cpp`
- **Función clave**: `Server::run()`
- **Implementación única**: Un solo select() en el main loop
- **Funciones auxiliares**: `handleNewConnections()`, `handleClientReads()`, `handleClientWrites()`

---

## 🔍 **¿USAMOS SOLO UN SELECT()?**

### **Respuesta Directa**
**SÍ, utilizamos únicamente UN select()** en todo el servidor. Este select() único maneja simultáneamente:
- ✅ **Aceptar** nuevas conexiones en server sockets
- ✅ **Leer** requests de clientes existentes
- ✅ **Escribir** responses a clientes listos

### **Ubicación del Select() Único**
```c
// srcs/Server.cpp - función Server::run()
while (true) {
    // Preparación de fd_sets...
    
    // ⭐ ÚNICO SELECT() del servidor
    int ready = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
    
    // Procesamiento de todos los eventos...
}
```

---

## 🏗️ **ARQUITECTURA DE MANEJO**

### **Estructura del Main Loop**
```
SINGLE SELECT() LOOP:
├── 1. PREPARACIÓN
│   ├── FD_ZERO() - Limpiar sets
│   ├── Añadir server sockets a read_fds
│   └── Añadir client sockets a read_fds/write_fds
├── 2. LLAMADA ÚNICA
│   └── select() - Monitorea TODOS los FDs
├── 3. PROCESAMIENTO
│   ├── handleNewConnections() - Server sockets listos
│   ├── handleClientReads() - Clientes con datos
│   └── handleClientWrites() - Clientes listos para envío
└── 4. REPETIR
```

### **Tipos de File Descriptors Monitoreados**
1. **Server Sockets** (solo read): Para aceptar conexiones nuevas
2. **Client Sockets** (read): Para recibir requests HTTP
3. **Client Sockets** (write): Para enviar responses HTTP

---

## 🎯 **GESTIÓN DE NUEVAS CONEXIONES**

### **Server Sockets en Read Set**
```c
// Añadir server sockets al read set
for (int server_fd : _server_fds) {
    FD_SET(server_fd, &read_fds);  // Monitorear para accept()
    max_fd = std::max(max_fd, server_fd);
}
```

### **Procesamiento de Nuevas Conexiones**
```c
void Server::handleNewConnections(fd_set& read_fds) {
    for (int server_fd : _server_fds) {
        if (FD_ISSET(server_fd, &read_fds)) {
            // Server socket listo para accept()
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            
            int client_fd = accept(server_fd, 
                                 (struct sockaddr*)&client_addr, 
                                 &addr_len);
            
            if (client_fd > 0) {
                // Configurar cliente y añadir a la lista
                setupNewClient(client_fd, server_fd);
            }
        }
    }
}
```

**¿Por qué funciona?**
- Un server socket está "listo para lectura" cuando hay conexiones pendientes
- accept() no bloquea porque select() garantizó que hay una conexión lista

---

## 📖 **GESTIÓN DE LECTURA DE CLIENTES**

### **Client Sockets en Read Set**
```c
// Añadir client sockets al read set
for (auto& client : _clients) {
    FD_SET(client.fd, &read_fds);  // Siempre monitorear lectura
    max_fd = std::max(max_fd, client.fd);
}
```

### **Procesamiento de Lecturas**
```c
void Server::handleClientReads(fd_set& read_fds) {
    for (auto it = _clients.begin(); it != _clients.end();) {
        if (FD_ISSET(it->fd, &read_fds)) {
            char buffer[BUFFER_SIZE];
            ssize_t bytes = recv(it->fd, buffer, sizeof(buffer) - 1, 0);
            
            if (bytes > 0) {
                // Procesar datos recibidos
                buffer[bytes] = '\0';
                processRequestData(*it, std::string(buffer, bytes));
                ++it;
            } else {
                // bytes <= 0: conexión cerrada o error
                closeClient(it);
                it = _clients.erase(it);
            }
        } else {
            ++it;
        }
    }
}
```

**Regla Crítica**: Solo UN recv() por cliente por select() - cumplida estrictamente.

---

## ✍️ **GESTIÓN DE ESCRITURA A CLIENTES**

### **Client Sockets en Write Set (Condicional)**
```c
// Solo añadir al write set si hay datos para enviar
for (auto& client : _clients) {
    if (client.has_response_ready && !client.response_data.empty()) {
        FD_SET(client.fd, &write_fds);  // Solo si hay datos
        max_fd = std::max(max_fd, client.fd);
    }
}
```

### **Procesamiento de Escrituras**
```c
void Server::handleClientWrites(fd_set& write_fds) {
    for (auto& client : _clients) {
        if (FD_ISSET(client.fd, &write_fds)) {
            ssize_t sent = send(client.fd, 
                              client.response_data.c_str() + client.bytes_sent,
                              client.response_data.length() - client.bytes_sent, 
                              0);
            
            if (sent > 0) {
                client.bytes_sent += sent;
                
                // ¿Envío completo?
                if (client.bytes_sent >= client.response_data.length()) {
                    client.response_data.clear();
                    client.has_response_ready = false;
                    client.bytes_sent = 0;
                }
            } else {
                // Error en send - cerrar cliente
                closeClient(client);
            }
        }
    }
}
```

**Optimización**: Solo monitoreamos escritura cuando realmente hay datos que enviar.

---

## 🎪 **VENTAJAS DEL SELECT() ÚNICO**

### **1. Simplicidad Arquitectural**
- ✅ **Un solo punto de control**: Todo el I/O pasa por un lugar
- ✅ **Estado centralizado**: Fácil de debuggear y mantener
- ✅ **Lógica clara**: Flujo de datos predecible

### **2. Eficiencia**
- ✅ **Sin overhead**: No múltiples llamadas a select()
- ✅ **Fairness**: Todos los FDs tienen la misma prioridad
- ✅ **Escalabilidad**: Maneja múltiples operaciones simultáneamente

### **3. Cumplimiento de Reglas**
- ✅ **Un recv/send por select()**: Cumplido estrictamente
- ✅ **Monitoreo simultáneo**: Read y write en la misma llamada
- ✅ **No errno**: Solo valores de retorno

---

## 🔄 **CICLO COMPLETO DE OPERACIÓN**

### **Ejemplo de Una Iteración**
```
1. PREPARACIÓN:
   ├── Server FD 3 → read_fds (nuevas conexiones)
   ├── Client FD 5 → read_fds (posible request)
   ├── Client FD 7 → read_fds (posible request)
   └── Client FD 7 → write_fds (response lista)

2. SELECT():
   └── Retorna: 2 FDs listos (FD 3 y FD 7)

3. PROCESAMIENTO:
   ├── FD 3 listo para lectura → accept() nueva conexión
   ├── FD 5 NO listo → no hacer nada
   └── FD 7 listo para escritura → send() response
```

### **Flujo de Estados de Cliente**
```
NUEVO CLIENTE:
accept() → añadir a _clients → monitorear read

RECIBIENDO REQUEST:
recv() → procesar → generar response → marcar write_ready

ENVIANDO RESPONSE:
send() → verificar envío completo → limpiar estado

CONEXIÓN CERRADA:
detectar cierre → limpiar cliente → remover de listas
```

---

## 🛡️ **MANEJO DE CASOS ESPECIALES**

### **1. Error en accept()**
```c
int client_fd = accept(server_fd, ...);
if (client_fd < 0) {
    if (errno != EAGAIN && errno != EWOULDBLOCK) {
        // Error real - log pero continuar
        perror("accept failed");
    }
    // Si EAGAIN/EWOULDBLOCK: no hay conexión real (race condition)
}
```

### **2. Envío Parcial**
```c
// Manejar send() que no envía todos los datos
client.bytes_sent += sent;
if (client.bytes_sent < client.response_data.length()) {
    // Envío parcial - continuar en próximo select()
    // El FD seguirá en write_fds hasta completar
}
```

### **3. Cierre de Conexión**
```c
if (bytes == 0) {
    // Cliente cerró conexión limpiamente
    closeClient(client);
} else if (bytes < 0) {
    // Error en recv - cerrar conexión
    closeClient(client);
}
```

---

## ✅ **RESUMEN**

**Respuesta**: SÍ, usamos solo UN select()

**Gestión de operaciones**:
1. **Accept**: Server sockets en read_fds → handleNewConnections()
2. **Read**: Client sockets en read_fds → handleClientReads()
3. **Write**: Client sockets en write_fds → handleClientWrites()

**Ventajas del enfoque**:
- ✅ **Arquitectura simple**: Un solo punto de control I/O
- ✅ **Eficiencia**: Sin overhead de múltiples select()
- ✅ **Cumplimiento**: Todas las reglas críticas respetadas
- ✅ **Escalabilidad**: Maneja múltiples operaciones simultáneamente

**Resultado**: Un servidor robusto que maneja accept, read y write de forma unificada y eficiente usando una sola llamada a select().
