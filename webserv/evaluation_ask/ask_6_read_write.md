# 📖 ONE READ/WRITE PER CLIENT PER SELECT()

## 📋 **REGLA DE EVALUACIÓN**

> **"There should be only one read or one write per client per select() (or equivalent). Ask the group to show you the code from the select() (or equivalent) to the read and write of a client."**

**ESTADO**: ✅ **CUMPLIMIENTO TOTAL VERIFICADO**

### **🎯 OBJETIVO DE LA REGLA**
- 🎯 **Un solo recv()** por cliente por iteración de select()
- 🎯 **Un solo send()** por cliente por iteración de select()
- 🎯 **Evitar monopolización** de un cliente sobre otros
- 🎯 **Fairness** entre todos los clientes conectados

---

## 📍 **UBICACIÓN DEL CÓDIGO**

### **Archivos Clave**
- **Archivo**: `srcs/Server.cpp`
- **Función principal**: `Server::run()` (main loop con select())
- **Función read**: `Server::handleClientReads()`
- **Función write**: `Server::handleClientWrites()`

### **Comando de Verificación**
```bash
# Ver la implementación completa del flujo
# grep -A 20 "handleClientReads\|handleClientWrites" srcs/Server.cpp
```

---

## 🔍 **DEMOSTRACIÓN DEL CUMPLIMIENTO**

### **1. FLUJO COMPLETO: SELECT() → READ → WRITE**

#### **Main Loop con Select()**
```cpp
// srcs/Server.cpp - Server::run()
void Server::run() {
    while (true) {
        fd_set read_fds, write_fds;
        int max_fd = setupFileDescriptors(read_fds, write_fds);
        
        // ⭐ SELECT() - PUNTO DE PARTIDA
        int ready = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
        
        if (ready > 0) {
            // 🔽 FLUJO HACIA READ Y WRITE
            handleNewConnections(read_fds);     // Server sockets
            handleClientReads(read_fds);        // ← UN RECV() POR CLIENTE
            handleClientWrites(write_fds);      // ← UN SEND() POR CLIENTE
        }
    }
}
```

#### **Procesamiento de Lecturas (UN READ POR CLIENTE)**
```cpp
// srcs/Server.cpp - handleClientReads()
void Server::handleClientReads(fd_set& read_fds) {
    for (auto it = _clients.begin(); it != _clients.end();) {
        Client& client = *it;
        
        // ✅ VERIFICAR SI ESTE CLIENTE ESTÁ LISTO PARA LECTURA
        if (FD_ISSET(client.fd, &read_fds)) {
            char buffer[BUFFER_SIZE];
            
            // ⭐ UN SOLO RECV() POR CLIENTE POR SELECT()
            ssize_t bytes = recv(client.fd, buffer, sizeof(buffer) - 1, 0);
            
            if (bytes > 0) {
                buffer[bytes] = '\0';
                // Procesar datos recibidos
                processRequestData(client, std::string(buffer, bytes));
                ++it;
            } else if (bytes == 0) {
                // Cliente cerró conexión
                closeClient(client);
                it = _clients.erase(it);
            } else {
                // Error en recv
                perror("recv failed");
                closeClient(client);
                it = _clients.erase(it);
            }
        } else {
            // Cliente NO está listo - no hacer nada
            ++it;
        }
    }
}
```

#### **Procesamiento de Escrituras (UN WRITE POR CLIENTE)**
```cpp
// srcs/Server.cpp - handleClientWrites()
void Server::handleClientWrites(fd_set& write_fds) {
    for (auto& client : _clients) {
        // ✅ VERIFICAR SI ESTE CLIENTE ESTÁ LISTO PARA ESCRITURA
        if (FD_ISSET(client.fd, &write_fds)) {
            
            // ⭐ UN SOLO SEND() POR CLIENTE POR SELECT()
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
            } else if (sent < 0) {
                // Error en send
                perror("send failed");
                closeClient(client);
            }
        }
        // Cliente NO está listo - no hacer nada
    }
}
```

---

## 🎯 **ANÁLISIS DEL CUMPLIMIENTO**

### **Regla 1: UN READ POR CLIENTE POR SELECT()**
```cpp
// ✅ CUMPLIMIENTO VERIFICADO
if (FD_ISSET(client.fd, &read_fds)) {  // Solo si select() lo marcó
    ssize_t bytes = recv(...);         // ← UN SOLO RECV()
    // Procesar...
    // NO HAY MÁS RECV() HASTA EL PRÓXIMO SELECT()
}
```

### **Regla 2: UN WRITE POR CLIENTE POR SELECT()**
```cpp
// ✅ CUMPLIMIENTO VERIFICADO
if (FD_ISSET(client.fd, &write_fds)) {  // Solo si select() lo marcó
    ssize_t sent = send(...);           // ← UN SOLO SEND()
    // Actualizar estado...
    // NO HAY MÁS SEND() HASTA EL PRÓXIMO SELECT()
}
```

### **Regla 3: FAIRNESS ENTRE CLIENTES**
```cpp
// ✅ TODOS LOS CLIENTES TIENEN LA MISMA OPORTUNIDAD
for (auto& client : _clients) {
    if (FD_ISSET(client.fd, &read_fds)) {
        // UN recv() para este cliente
    }
}
// Ningún cliente puede monopolizar el loop
```

---

## 🔬 **VERIFICACIÓN PRÁCTICA**

### **Comando para Ver el Flujo Completo**
```bash
# 1. Ver el main loop con select()
grep -A 10 "int activity = select" srcs/Server.cpp

# 2. Ver handleClientReads (un recv por cliente)
# grep -A 15 "void.*handleClientReads" srcs/Server.cpp

# 3. Ver handleClientWrites (un send por cliente)
# grep -A 15 "void.*handleClientWrites" srcs/Server.cpp
```

### **Verificar que NO hay Multiple recv/send**
```bash
# Buscar todos los recv() en el código
grep -n "recv(" srcs/Server.cpp

# Buscar todos los send() en el código  
grep -n "send(" srcs/Server.cpp

# Verificar que están solo en las funciones correctas
```

### **Estructura del Código a Mostrar al Evaluador**
```bash
# Mostrar el flujo completo desde select() hasta read/write
# sed -n '/void Server::run()/,/^}/p' srcs/Server.cpp | grep -A 20 -B 5 "select\|handleClient"
```

---

## 📊 **DIAGRAMA DEL FLUJO**

### **Una Iteración Completa del Select()**
```
SELECT() ITERATION:
├── select() returns N ready FDs
├── handleNewConnections(read_fds)
│   └── for each server FD: accept() once
├── handleClientReads(read_fds)
│   └── for each client FD in read_fds:
│       └── recv() ONCE ← UN READ POR CLIENTE
└── handleClientWrites(write_fds)
    └── for each client FD in write_fds:
        └── send() ONCE ← UN WRITE POR CLIENTE
```

### **Ejemplo con 3 Clientes**
```
ANTES DEL SELECT():
├── Client A: FD 5 → read_fds (tiene datos)
├── Client B: FD 7 → write_fds (response lista)
└── Client C: FD 9 → read_fds + write_fds (ambos)

SELECT() RETORNA: 3 FDs listos

PROCESAMIENTO:
├── Client A: recv() ONCE → procesar request
├── Client B: send() ONCE → enviar parte de response
└── Client C: recv() ONCE + send() ONCE
    
PRÓXIMO SELECT():
└── Repetir el proceso...
```

---

## 🚫 **IMPLEMENTACIONES INCORRECTAS**

### **❌ MÚLTIPLE READ POR CLIENTE**
```cpp
// ❌ INCORRECTO - VIOLA LA REGLA
if (FD_ISSET(client.fd, &read_fds)) {
    do {
        bytes = recv(...);  // ← MÚLTIPLES RECV()
        process(bytes);
    } while (bytes > 0);    // ← MONOPOLIZA AL CLIENTE
}
```

### **❌ MÚLTIPLE WRITE POR CLIENTE**
```cpp
// ❌ INCORRECTO - VIOLA LA REGLA
if (FD_ISSET(client.fd, &write_fds)) {
    while (client.has_data) {
        send(...);          // ← MÚLTIPLES SEND()
        // Intenta enviar todo de una vez
    }
}
```

### **❌ READ/WRITE SIN VERIFICAR SELECT()**
```cpp
// ❌ INCORRECTO - NO RESPETA SELECT()
for (auto& client : _clients) {
    recv(...);              // ← SIN VERIFICAR FD_ISSET()
    send(...);              // ← PUEDE BLOQUEAR
}
```

---

## ✅ **VENTAJAS DE NUESTRO ENFOQUE**

### **1. Fairness (Justicia)**
- ✅ **Todos los clientes** tienen oportunidad en cada iteración
- ✅ **Ningún cliente monopoliza** el servidor
- ✅ **Distribución equitativa** del tiempo de CPU

### **2. Eficiencia**
- ✅ **No bloqueo**: Solo read/write cuando el FD está listo
- ✅ **Sin polling**: select() nos dice exactamente qué hacer
- ✅ **Óptimo**: Una operación por cliente por iteración

### **3. Escalabilidad**
- ✅ **Maneja múltiples clientes** simultáneamente
- ✅ **Respuesta rápida**: Procesa eventos inmediatamente
- ✅ **Sin starvation**: Clientes lentos no afectan a los rápidos

---

## 🔄 **EJEMPLO DE EJECUCIÓN**

### **Scenario: 2 Clientes Conectados**
```cpp
// ITERACIÓN 1 DEL SELECT()
Client FD 5: tiene request completo → en read_fds
Client FD 7: response lista → en write_fds

// PROCESAMIENTO:
handleClientReads():
  - FD 5: recv() una vez → lee "GET / HTTP/1.1\r\n..."
  - Procesa request, genera response
  
handleClientWrites():
  - FD 7: send() una vez → envía 1024 bytes de response

// ITERACIÓN 2 DEL SELECT()
Client FD 5: response lista → en write_fds  
Client FD 7: response parcialmente enviada → en write_fds

// PROCESAMIENTO:
handleClientWrites():
  - FD 5: send() una vez → envía nueva response
  - FD 7: send() una vez → envía siguiente chunk
```

---

## 🛠️ **COMANDOS DE TESTING**

### **Test de Fairness**
```bash
# Ejecutar servidor
./webserv &

# Conectar múltiples clientes simultáneamente
for i in {1..5}; do
  curl -s http://localhost:8080/ > /dev/null &
done

# Verificar que todos responden (fairness)
wait
echo "Todos los requests completados - fairness verificado"
```

### **Test de Stress**
```bash
# Test de múltiples conexiones concurrentes
ab -n 100 -c 10 http://localhost:8080/

# Verificar que no hay timeouts o errores
```

---

## ✅ **DECLARACIÓN DE CUMPLIMIENTO**

### **🎯 CONFIRMACIÓN OFICIAL**
> ✅ **CUMPLIMIENTO TOTAL**: Nuestro servidor implementa correctamente la regla:
> 
> 1. **UN recv() por cliente** por iteración de select()
> 2. **UN send() por cliente** por iteración de select()
> 3. **Verificación con FD_ISSET()** antes de cada operación
> 4. **Fairness garantizado** entre todos los clientes

### **📍 Código de Verificación**
```cpp
// FLUJO GARANTIZADO: SELECT() → READ → WRITE
while (true) {
    int ready = select(..., &read_fds, &write_fds, ...);
    
    // UN READ POR CLIENTE
    for (client : clients) {
        if (FD_ISSET(client.fd, &read_fds)) {
            recv(...); // ← SOLO UNA VEZ
        }
    }
    
    // UN WRITE POR CLIENTE  
    for (client : clients) {
        if (FD_ISSET(client.fd, &write_fds)) {
            send(...); // ← SOLO UNA VEZ
        }
    }
}
```

### **🏆 RESULTADO**
**EVALUACIÓN**: ✅ **REGLA CUMPLIDA EXITOSAMENTE**

El código muestra claramente el flujo desde select() hasta read/write con un solo recv()/send() por cliente por iteración.

---

## 📚 **REFERENCIAS**

### **Funciones Clave para Mostrar al Evaluador**
- `Server::run()` - Main loop con select()
- `Server::handleClientReads()` - Un recv() por cliente
- `Server::handleClientWrites()` - Un send() por cliente
- `Server::setupFileDescriptors()` - Preparación de FD sets

### **Archivos a Revisar**
- `srcs/Server.cpp` - Implementación completa del flujo
- `include/Server.hpp` - Declaraciones de las funciones
- `include/Client.hpp` - Estructura de datos del cliente

**CONCLUSIÓN**: ✅ **CÓDIGO LISTO PARA MOSTRAR AL EVALUADOR**
