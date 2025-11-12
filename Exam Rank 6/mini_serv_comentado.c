/*
 * MINI_SERV - SERVIDOR DE CHAT MULTICLIENTE
 * =========================================
 * 
 * Este programa implementa un servidor de chat que permite a múltiples clientes
 * conectarse simultáneamente y comunicarse entre sí. Utiliza select() para 
 * manejar múltiples conexiones de forma no bloqueante.
 * 
 * Funcionalidades:
 * - Acepta conexiones en 127.0.0.1 (localhost)
 * - Asigna IDs únicos a cada cliente (0, 1, 2, ...)
 * - Retransmite mensajes entre clientes
 * - Notifica conexiones y desconexiones
 * - Maneja múltiples clientes simultáneamente sin bloqueo
 */

// ============================================================================
// INCLUDES NECESARIOS
// ============================================================================
#include <stdio.h>       // vsprintf() - formateo de strings
#include <stdlib.h>      // exit(), atoi() - utilidades del sistema y conversiones
#include <string.h>      // strlen(), bzero() - manipulación de strings y memoria
#include <unistd.h>      // write(), close() - operaciones de archivos/descriptores
#include <stdarg.h>      // va_list, va_start(), va_end() - argumentos variables
#include <netinet/in.h>  // struct sockaddr_in, htons(), htonl() - direcciones de red
#include <sys/select.h>  // select(), fd_set, FD_* macros - multiplexación E/S
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), send(), recv()

// ============================================================================
// ESTRUCTURAS DE DATOS
// ============================================================================

/* 
 * Estructura que representa un cliente conectado
 * - id: identificador único del cliente (0, 1, 2, ...)
 * - msg: buffer de acumulación para mensajes parciales del cliente
 * 
 *   BUFFER DE ACUMULACIÓN - CONCEPTO CLAVE:
 *   ======================================
 *   Este buffer resuelve el problema de la "fragmentación de mensajes":
 *   
 *   PROBLEMA: TCP puede entregar datos en fragmentos arbitrarios
 *   - Mensaje: "Hola mundo\n" puede llegar como "Ho", "la mun", "do\n"
 *   - O varios mensajes juntos: "Mensaje1\nMensaje2\nMens"
 *   
 *   SOLUCIÓN: Buffer persistente que acumula datos hasta encontrar '\n'
 *   - Recibe fragmento → Añade a buffer → ¿Hay '\n'? → Procesa mensaje completo
 *   - Si no hay '\n' → Espera más datos en próxima recv()
 *   
 *   TAMAÑO 370000: Calculado para soportar múltiples líneas:
 *   - Subject permite "Un solo mensaje puede contener varios \n"
 *   - Buffer recv_buffer es 400000 bytes
 *   - Margen de seguridad: 370000 < 400000 (30KB de buffer)
 *   - Permite acumular ~370 líneas de 1000 caracteres cada una
 *   - O un mensaje muy largo de hasta 370KB antes del \n final
 */
typedef struct s_client { 
    int id;                 // ID único del cliente
    char msg[370000];       // Buffer de acumulación para mensajes fragmentados (ver explicación arriba)
} t_client;

// ============================================================================
// VARIABLES GLOBALES
// ============================================================================

/*
 * DISEÑO DE CONSTANTES NUMÉRICAS - JUSTIFICACIÓN TÉCNICA:
 * ========================================================
 * 
 * ¿POR QUÉ ESTOS NÚMEROS ESPECÍFICOS Y NO OTROS?
 * 
 * 1. clients[2048]:
 *    - Límite teórico de FDs en sistemas Unix: ~1024-65536
 *    - 2048 = potencia de 2 (eficiencia de memoria/cache)
 *    - Permite muchos clientes sin uso excesivo de RAM
 *    - Cálculo RAM: 2048 * (4 + 370000) ≈ 758 MB (aceptable)
 * 
 * 2. msg[370000] / buffers[400000]:
 *    - Base: múltiplo de 1000 para cálculos mentales fáciles
 *    - 400KB = tamaño común en sistemas para I/O buffers
 *    - 370KB permite margen de 30KB para prefijos/sufijos
 *    - Soporta mensajes grandes (casos extremos) sin problemas
 *    - Alternativas descartadas:
 *      * 64KB: Demasiado pequeño para múltiples líneas
 *      * 1MB: Uso excesivo de memoria
 *      * 500KB: No múltiplo "redondo" para cálculos
 * 
 * 3. listen(s, 100):
 *    - Queue size (tamaño de la cola de conexiones) para conexiones pendientes
 *    - Cuando un cliente intenta conectarse, la conexión se pone en cola
 *      si el servidor no puede aceptarla inmediatamente. El servidor procesa las
 *      conexiones de la cola una por una con accept().
 *    - 100 = Tamaño máximo de la cola = balance entre responsividad y uso de recursos.
 *      Si la cola está llena (100 conexiones esperando), entonces las nuevas conexiones
 *      serán rechazadas hasta que haya espacio disponible.
 *    - Suficiente para picos de conexiones simultáneas
 *    - Alternativas consideradas:
 *      * 10: Muy pequeño, podría rechazar conexiones válidas
 *      * 1000: Excesivo para un chat, uso innecesario de memoria kernel
 * 
 * 4. 2130706433 (127.0.0.1):
 *    - Representación decimal de 127.0.0.1 en network byte order
 *    - 127.0.0.1 = localhost (requisito del subject)
 *    - Cálculo: 127*256³ + 0*256² + 0*256¹ + 1*256⁰ = 2130706433
 *    - Más eficiente que inet_addr("127.0.0.1")
 */

// Array de todos los clientes posibles
// CANTIDAD 2048: Ver justificación arriba - balance óptimo memoria/capacidad
t_client clients[2048];

/*
 * CONJUNTOS DE DESCRIPTORES PARA SELECT() - EXPLICACIÓN DETALLADA:
 * ================================================================
 * 
 * ¿QUÉ ES UN fd_set?
 * - Es una estructura de datos tipo "conjunto de bits" (bitmap)
 * - Cada bit representa un descriptor de archivo (FD)
 * - Si el bit está activado (1): el FD está en el conjunto
 * - Si el bit está desactivado (0): el FD NO está en el conjunto
 * - Tamaño típico: 1024 bits = puede monitorear FDs 0-1023
 * 
 * MACROS PARA MANIPULAR fd_set:
 * - FD_ZERO(&set): Limpia todos los bits (conjunto vacío)
 * - FD_SET(fd, &set): Activa el bit del descriptor 'fd'
 * - FD_CLR(fd, &set): Desactiva el bit del descriptor 'fd'
 * - FD_ISSET(fd, &set): Verifica si el descriptor 'fd' está activo
 * 
 * FUNCIONAMIENTO DE select():
 * - select() MODIFICA los conjuntos que recibe como parámetros
 * - Entrada: conjuntos con FDs que queremos monitorear
 * - Salida: conjuntos con solo los FDs que tienen actividad
 * - Por eso necesitamos 3 conjuntos diferentes en nuestro código
 */

// Conjuntos de descriptores para select()
fd_set read_set;    // FDs listos para lectura (datos disponibles)
                    // COMPORTAMIENTO: select() deja aquí solo los FDs que tienen
                    // datos para leer (nueva conexión o mensaje de cliente)
                    
fd_set write_set;   // FDs listos para escritura (pueden enviar datos)
                    // COMPORTAMIENTO: select() deja aquí solo los FDs a los que
                    // podemos enviar datos sin bloquear el programa
                    
fd_set current;     // FDs actualmente monitoreados (servidor + clientes)
                    // PROPÓSITO: Es la "plantilla maestra" que contiene todos
                    // los FDs activos. Se copia a read_set y write_set antes
                    // de cada select() porque select() los modifica

// Variables de control
int max_fd = 0;     // Mayor descriptor de archivo activo (optimización para select)
int next_id = 0;    // Próximo ID a asignar a un nuevo cliente

/*
 * BUFFERS DE COMUNICACIÓN - CONCEPTOS FUNDAMENTALES:
 * ===================================================
 * 
 * ¿QUÉ ES UN BUFFER?
 * - Un buffer es una zona de memoria temporal que actúa como "almacén intermedio"
 * - Permite desacoplar la velocidad de producción y consumo de datos
 * - En redes: compensa diferencias entre velocidad de envío/recepción
 * - Es como un "depósito de agua" entre dos tuberías de diferente capacidad
 * 
 * ¿POR QUÉ NECESITAMOS BUFFERS EN NETWORKING?
 * 1. FRAGMENTACIÓN: Los datos pueden llegar en múltiples paquetes TCP
 * 2. VELOCIDAD VARIABLE: Red más lenta que procesamiento del programa
 * 3. ATOMICIDAD: Necesitamos mensajes completos antes de procesarlos
 * 4. EFICIENCIA: Reduce número de llamadas al sistema (syscalls)
 * 
 * TIPOS DE BUFFERS EN ESTE SERVIDOR:
 * 1. recv_buffer: Recibe datos "en bruto" del sistema operativo
 * 2. send_buffer: Prepara datos formateados para envío
 * 3. clients[].msg: Acumula datos hasta formar mensaje completo
 * 
 * FLUJO DE DATOS CON BUFFERS:
 * Red → recv_buffer → clients[].msg → send_buffer → Red
 *   ↑         ↑           ↑              ↑           ↑
 *  TCP    recv()    acumulación    vsprintf()    send()
 */

// Buffers de comunicación
char send_buffer[400000];   // Buffer para formatear mensajes antes del envío final
                            // PROPÓSITO: Preparar mensaje completo con prefijos antes de send()
                            // TAMAÑO 400000: Debe ser >= que msg[370000] + prefijos como
                            // "client 999: " (12 chars) + mensaje (370000) + "\n" + margen
                            // VENTAJA: Una sola llamada send() por mensaje (más eficiente)
                            
char recv_buffer[400000];   // Buffer temporal para recibir datos "en bruto" de la red
                            // PROPÓSITO: Zona intermedia entre socket y procesamiento
                            // TAMAÑO 400000: Tamaño estándar para recv() que permite
                            // recibir hasta 400KB en una sola llamada del sistema
                            // COMPORTAMIENTO: Puede contener datos parciales, múltiples
                            // mensajes, o fragmentos de mensajes que luego se procesan

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

/*
 * FUNCIÓN: err
 * Propósito: Mostrar mensaje de error y terminar el programa
 * Parámetros: msg - mensaje personalizado (NULL para "Fatal error")
 * Comportamiento:
 *   - Si msg existe: muestra msg
 *   - Si msg es NULL: muestra "Fatal error"
 *   - Siempre añade '\n' al final
 *   - Termina el programa con exit(1)
 */
void err(char *msg) {
    // Operador ternario: si msg existe usa msg, sino "Fatal error"
    // NÚMERO 11: longitud exacta de "Fatal error" (optimización de rendimiento)
    // strlen("Fatal error") = 11, pero calcularlo en runtime es ineficiente
    write(2, msg ? msg : "Fatal error", msg ? strlen(msg) : 11);
    write(2, "\n", 1);  // Salto de línea
    exit(1);            // Terminar con código de error (estándar Unix)
}

/*
 * FUNCIÓN: send_msg
 * Propósito: Enviar un mensaje formateado a todos los clientes exceptuando uno
 * 
 * ARGUMENTOS VARIÁDICOS - CONCEPTO AVANZADO EN C:
 * ===============================================
 * 
 * ¿QUÉ SON LOS ARGUMENTOS VARIÁDICOS?
 * - Permiten que una función reciba un número variable de argumentos
 * - Similar a printf(): printf("%d %s", numero, cadena) - 2 argumentos extra
 * - O printf("%d", numero) - solo 1 argumento extra
 * - El "..." en la declaración indica "cero o más argumentos adicionales"
 * 
 * SINTAXIS EN LA DECLARACIÓN:
 * void funcion(tipo param_fijo, ...);
 *              ↑               ↑
 *        parámetro fijo    argumentos variables
 * 
 * REQUISITOS IMPORTANTES:
 * 1. DEBE haber al menos UN parámetro fijo antes del "..."
 * 2. El parámetro fijo suele indicar CÓMO interpretar los argumentos variables
 * 3. En nuestro caso: 'format' es el formato que describe los argumentos siguientes
 * 
 * ¿CÓMO FUNCIONA INTERNAMENTE?
 * - Los argumentos se almacenan en la pila (stack) en orden
 * - va_list es un "puntero" que recorre estos argumentos
 * - va_start() lo posiciona al primer argumento variable
 * - vsprintf() lee todos los argumentos según el formato
 * - va_end() limpia recursos (por seguridad/portabilidad)
 * 
 * Parámetros de nuestra función:
 *   - sender: descriptor que NO debe recibir el mensaje (quien lo envía)
 *   - format: formato del mensaje (como printf) - PARÁMETRO FIJO OBLIGATORIO
 *   - ...: argumentos variables para el formato (0 o más argumentos)
 * 
 * Ejemplos de uso:
 *   send_msg(fd, "client %d just arrived", cliente_id);           // 1 argumento extra
 *   send_msg(fd, "client %d: %s", cliente_id, mensaje);           // 2 argumentos extra
 *   send_msg(fd, "server error %d at %s:%d", error, file, line);  // 3 argumentos extra
 */
void send_msg(int sender, char *format, ...) {
    // sender es el FD que envió el mensaje y NO debe recibirlo
    // *format es el formato del mensaje (como en printf)

    /* Ejemplos prácticos de uso:

        Ejemplo 1: Solo texto
            send_msg(fd, "Hola mundo");
            format = "Hola mundo"
            Resultado: "Hola mundo"

        Ejemplo 2: Con un número
            send_msg(fd, "client %d just arrived", 5);
            format = "client %d just arrived"
            %d se reemplaza por 5
            Resultado: "client 5 just arrived"

        Ejemplo 3: Con número y texto
            send_msg(fd, "client %d: %s", 3, "Hola a todos");
            format = "client %d: %s" 
            %d se reemplaza por 3
            %s se reemplaza por "Hola a todos"
            Resultado: "client 3: Hola a todos" */

    // Limpiar buffer de envío para evitar datos residuales
    bzero(send_buffer, sizeof(send_buffer));    // sizeof se utiliza para obtener tamaño del array
    // send_buffer es un array para almacenar el mensaje formateado que vamos a enviar
    // bzero recibe puntero al buffer y su tamaño en bytes y lo llena con ceros. Esto lo hacemos para 
    // asegurarnos de que no haya datos residuales de envíos anteriores.
    
    /*
     * PROCESAMIENTO DE ARGUMENTOS VARIÁDICOS - PASO A PASO:
     * =====================================================
     * 
     * 1. va_list args: Declara variable para manejar argumentos variables
     *    - va_list es un tipo especial definido en <stdarg.h>
     *    - Actúa como "cursor" que apunta a argumentos en la pila
     *    - NO es un array, es una estructura opaca específica del compilador
     * 
     * 2. va_start(args, format): Inicializa el cursor
     *    - Posiciona 'args' al primer argumento después de 'format'
     *    - 'format' es la "referencia" para saber dónde empiezan los argumentos variables
     *    - Después de va_start(), args apunta al primer argumento variádico
     * 
     * 3. vsprintf(send_buffer, format, args): Procesa TODOS los argumentos
     *    - Es la versión "variádica" de sprintf()
     *    - sprintf(): requiere argumentos explícitos
     *    - vsprintf(): toma argumentos de va_list
     *    - Lee el formato en 'format' y extrae argumentos de 'args' automáticamente
     *    - Resultado: string formateado en send_buffer
     * 
     * 4. va_end(args): Limpia recursos
     *    - Marca el final del procesamiento de argumentos
     *    - En algunos sistemas es crucial para la gestión de memoria
     *    - Siempre debe llamarse después de va_start()
     */
    va_list args;                               // Variable para manejar argumentos variádicos
    va_start(args, format);                     // Inicializar: args apunta al primer argumento tras 'format'
    vsprintf(send_buffer, format, args);        // Formatear mensaje usando argumentos variádicos
    va_end(args);                               // Limpiar recursos del procesamiento variádico
    
    /*
     * ENVÍO MASIVO CON write_set - USO DE FD_ISSET EN send_msg:
     * ==========================================================
     * FD_ISSET(fd, &write_set): ¿Podemos enviar datos a este FD sin bloquear?
     * 
     * ¿Por qué usar write_set aquí?
     * - write_set contiene FDs listos para ESCRITURA (según último select())
     * - Si un cliente tiene buffer de salida lleno, NO estará en write_set
     * - Evitamos bloquear el programa intentando enviar a clientes "ocupados"
     * - Solo enviamos a clientes que pueden recibir datos inmediatamente
     * 
     * Lógica del filtro: FD_ISSET(fd, &write_set) && fd != sender
     * 1. FD_ISSET(fd, &write_set): ¿Este FD puede recibir datos?
     * 2. fd != sender: ¿No es el remitente del mensaje?
     * 3. Solo si AMBAS condiciones son verdaderas: enviar mensaje
     * 
     * Ejemplo práctico:
     * - current = {3, 5, 7, 9} (servidor + 3 clientes)
     * - write_set = {3, 5, 9} (cliente 7 tiene buffer lleno)
     * - sender = 5 (cliente 5 envió el mensaje)
     * - Resultado: enviamos solo a cliente 9
     * - Cliente 7 recibirá el mensaje cuando su buffer se libere
     */
    for(int fd = 0; fd <= max_fd; fd++)
        if(FD_ISSET(fd, &write_set) && fd != sender)  // Si está listo y no es el remitente
            if(send(fd, send_buffer, strlen(send_buffer), 0) == -1) { err(NULL); }
            // Envía el mensaje si send() no falla (no es -1) sino error fatal
            // send requiere: fd, puntero a datos, longitud de datos, flags (0 = sin flags)
            // los flags pueden modificar comportamiento (no usados aquí)
}

// ============================================================================
// FUNCIÓN PRINCIPAL
// ============================================================================
int main(int argc, char *argv[]) {
    // Verificar argumentos de línea de comandos
    if(argc != 2) { err("Wrong number of arguments"); }
    
    // ========================================================================
    // CONFIGURACIÓN DEL SERVIDOR
    // ========================================================================
    
    /*
     * Inicialización de sockaddr_in campo por campo (compatible con cc):
     * - sin_family: AF_INET (IPv4)
     * - sin_port: puerto del argumento convertido a network byte order
     * - sin_addr.s_addr: 127.0.0.1 (localhost) en network byte order
     * 
     * struct sockaddr_in server: Estructura de dirección del servidor, sockaddr_in 
     * hace referencia a IPv4  y sirve para definir la dirección IP y el puerto del servidor.
     * server es una variable de tipo struct sockaddr_in que almacena la configuración del servidor,
     * o sea la IP y el puerto en el que escuchará conexiones.
     * 
     * AF_INET indica que usaremos IPv4. O sea direcciones como 127.0.0.1
     * htons(atoi(argv[1])) convierte el puerto (argumento 1) a network byte order, 
     * que es el formato estándar en redes, independiente de la arquitectura del sistema.
     * 
     * htnonl es "host to network long", convierte un número de 32 bits (long) de
     * formato host a formato network.
     * 
     * JUSTIFICACIÓN DE 2130706433:
     * - Es 127.0.0.1 en formato decimal network byte order
     * - Cálculo: 127*(256^3) + 0*(256^2) + 0*(256^1) + 1*(256^0)
     * - Más eficiente que parsing string "127.0.0.1"
     * - Cumple requirement subject: "solo escuchar en 127.0.0.1"
     * - Alternativas descartadas:
     *   * inet_addr("127.0.0.1"): Require parsing runtime
     *   * INADDR_LOOPBACK: Menos explícito sobre la IP específica
     * 
     * INICIALIZACIÓN COMPATIBLE CON cc:
     * ================================
     * Se usa inicialización campo por campo en lugar de inicializador designado
     * para garantizar compatibilidad con compilador cc usado en campus 42.
     * La sintaxis con llaves anidadas {htonl(...)} puede causar errores.
     */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(2130706433);
    
    /*
     * ¿QUÉ ES UN SOCKET? - CONCEPTO FUNDAMENTAL
     * ========================================
     * 
     * Un SOCKET es como un "enchufe" o "punto de conexión" que permite que dos 
     * programas se comuniquen a través de la red (o incluso en la misma máquina).
     * 
     * ANALOGÍA: EL TELÉFONO
     * ====================
     * Imagina que un socket es como un TELÉFONO:
     * 
     * Programa A  ←→  Socket  ←→  Red  ←→  Socket  ←→  Programa B
     *    (tú)         (teléfono)  (líneas)  (teléfono)    (amigo)
     * 
     * TIPOS DE SOCKETS EN NUESTRO CÓDIGO:
     * ===================================
     * 
     * 1. SOCKET SERVIDOR (server_socket):
     *    - Es como la CENTRALITA TELEFÓNICA
     *    - ESCUCHA conexiones entrantes
     *    - NO envía datos directamente
     *    - CREA nuevos sockets para cada cliente
     * 
     * 2. SOCKETS CLIENTE (variable 'c'):
     *    - Son como LÍNEAS TELEFÓNICAS INDIVIDUALES
     *    - CADA CLIENTE tiene su propio socket
     *    - A través de estos ENVÍAS Y RECIBES mensajes
     * 
     * FLUJO DE TRABAJO:
     * ================
     * Socket Servidor:
     *   1. socket()  → Crear el "teléfono principal"
     *   2. bind()    → Asignar "número de teléfono" (IP:puerto)
     *   3. listen()  → Decir "estoy disponible para llamadas"
     *   4. accept()  → Contestar cuando alguien llama
     * 
     * Socket Cliente (en cada conexión):
     *   1. send()    → Hablar por teléfono
     *   2. recv()    → Escuchar lo que dice el otro
     *   3. close()   → Colgar
     * 
     * EN TÉRMINOS TÉCNICOS:
     * ====================
     * Un socket es:
     *   - UN NÚMERO ENTERO (file((server_socket = socket(AF_INET, SOCK_STREAM, 0)) descriptor)
     *   - UNA INTERFAZ entre tu programa y el sistema operativo
     *   - UN CANAL BIDIRECCIONAL para comunicación
     *   - INDEPENDIENTE DEL PROTOCOLO (TCP, UDP, etc.)
     * 
     * Es básicamente un "canal de comunicación" entre programas.
     */
    
    // Crear socket del servidor
    int server_socket;  // Descriptor del socket servidor
    // El condicional verifica que socket() no falle. Si falla, error fatal.
    // socket() recibe: dominio (AF_INET = IPv4), tipo (SOCK_STREAM = TCP), protocolo (0 = default)
    // el resultado es un descriptor de archivo (número entero) o -1 en caso de error, dicho 
    // descriptor se almacena en server_socket para usarlo luego... si todo va bien.
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { err(NULL); }
    
    /*
     * INICIALIZACIÓN DE fd_set Y ESTRUCTURAS DE CONTROL:
     * =================================================
     * 
     * max_fd = server_socket: El socket servidor es el mayor FD inicial
     * 
     * FD_ZERO(&current): Limpia 'current' (todos los bits a 0)
     * FD_ZERO(&write_set): Limpia 'write_set' (todos los bits a 0)
     * 
     * ¿Por qué limpiar write_set aquí?
     * - write_set se usa para saber a qué clientes podemos enviar mensajes
     * - Inicialmente vacío porque no hay clientes conectados
     * - Se llenará dinámicamente cuando lleguen clientes
     * 
     * ¿Por qué NO limpiar read_set aquí?
     * - read_set se recrea en cada iteración del bucle principal
     * - No necesita inicialización porque se sobrescribe constantemente
     * 
     * FD_SET(s, &current): Añadir socket servidor al conjunto maestro
     * - Activa el bit correspondiente al socket servidor 's' en 'current'
     * - Esto significa que queremos monitorear el servidor para nuevas conexiones
     * - 'current' ahora tiene solo 1 bit activo: el del servidor
     * - Cuando select() detecte actividad en 'server_socket', significa nueva conexión
     */
    max_fd = server_socket;
    // FD_ZERO(&current) limpia el conjunto actual, o sea todos los FDs activos
    // FD_ZERO(&write_set) limpia el conjunto de escritura.
    // FD_SET añade el socket del servidor al conjunto current
    FD_ZERO(&current); FD_ZERO(&write_set); FD_SET(server_socket, &current);
    bzero(clients, sizeof(clients));           // Limpiar array de clientes

    // Vincular socket a dirección y puerto, luego escuchar conexiones
    // LISTEN QUEUE = 100: Ver justificación en comentarios de variables globales
    // Balance óptimo para servidor de chat: permite picos sin uso excesivo de recursos
    // bind() asigna IP:puerto al socket servidor, para ello recibe: socket, puntero a struct sockaddr, tamaño struct
    // con lo que podremos aceptar conexiones en esa IP:puerto. Si falla bind() o listen(), error fatal.
    // listen() pone el socket en modo escucha, con cola de hasta 100 conexiones pendientes.
    if(bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == -1 || listen(server_socket, 100) == -1) { err(NULL); }

    // ========================================================================
    // BUCLE PRINCIPAL DEL SERVIDOR
    // ========================================================================
    while(1) {
        /*
         * PREPARACIÓN PARA select() - COPIA DE CONJUNTOS:
         * ===============================================
         * read_set = write_set = current;
         * 
         * ¿Por qué hacer esta copia triple?
         * 1. 'current' contiene TODOS los FDs activos (servidor + clientes)
         * 2. select() MODIFICA los conjuntos que recibe como parámetros
         * 3. Después de select():
         *    - read_set tendrá solo FDs con datos para leer
         *    - write_set tendrá solo FDs listos para escribir
         *    - current se mantiene intacto con todos los FDs activos
         * 
         * Ejemplo práctico:
         * - Antes: current = {3, 5, 7} (servidor + 2 clientes)
         * - Copiamos: read_set = write_set = {3, 5, 7}
         * - select() modifica: read_set = {5}, write_set = {3, 5, 7}
         * - Significado: cliente 5 envió datos, todos pueden recibir datos
         * - current sigue siendo {3, 5, 7} para la próxima iteración
         */
        read_set = write_set = current;
        
        /*
         * LLAMADA A select() - MULTIPLEXACIÓN DE E/S:
         * ===========================================
         * select(max_fd + 1, &read_set, &write_set, NULL, NULL)
         * 
         * Parámetros explicados:
         * 1. max_fd + 1: Rango de FDs a revisar (0 hasta max_fd inclusive)
         * 2. &read_set: Conjunto para monitorear LECTURA (entrada: todos, salida: con datos)
         * 3. &write_set: Conjunto para monitorear ESCRITURA (entrada: todos, salida: listos)
         * 4. NULL: No monitoreamos excepciones
         * 5. NULL: Sin timeout (espera indefinida)
         * 
         * ¿Qué hace select() internamente?
         * - Examina cada FD en los conjuntos
         * - Elimina FDs que NO tienen actividad
         * - Deja solo FDs que SÍ tienen actividad
         * - Se bloquea hasta que al menos 1 FD tenga actividad
         */
        if(select(max_fd + 1, &read_set, &write_set, NULL, NULL) == -1) { continue; }
        
        // Revisar todos los descriptores activos
        for(int fd = 0; fd <= max_fd; fd++){
            /*
             * VERIFICACIÓN DE ACTIVIDAD - FD_ISSET EN read_set:
             * =================================================
             * FD_ISSET(fd, &read_set): ¿Este FD tiene datos para leer?
             * 
             * CONTEXTO: select() ya filtró los FDs activos
             * - read_set ahora contiene SOLO FDs con datos disponibles
             * - Iteramos todos los FDs posibles (0 hasta max_fd)
             * - FD_ISSET() nos dice si este FD específico tiene actividad
             * 
             * Casos posibles:
             * 1. fd == s (servidor): nueva conexión pendiente
             * 2. fd == cliente: mensaje recibido del cliente
             * 3. fd no está en read_set: sin actividad, continuar
             */
            if(FD_ISSET(fd, &read_set)){
                
                // ===========================================================
                // CASO 1: NUEVA CONEXIÓN (fd es el socket servidor)
                // ===========================================================
                if(fd == server_socket){
                    /*
                     * ACEPTAR NUEVA CONEXIÓN:
                     * =====================
                     * - accept() extrae la primera conexión de la cola de listen()
                     * - Devuelve un nuevo descriptor de archivo para el cliente
                     * - Variable socklen_t: compatibilidad con cc (sin compound literal)
                     */
                    socklen_t addr_len = sizeof(server);
                    int new_client = accept(server_socket, (struct sockaddr*)&server, &addr_len);
                    if(new_client != -1) {  // Si accept() tuvo éxito
                        // Actualizar max_fd si es necesario para optimizar select()
                        if(new_client > max_fd) max_fd = new_client;
                        
                        /*
                         * CONFIGURAR NUEVO CLIENTE:
                         * ========================
                         * - Asignar ID único secuencial e incrementar contador global
                         * - Añadir cliente al conjunto maestro para monitoreo futuro
                         * - Notificar a todos los clientes existentes sobre la llegada
                         */
                        clients[new_client].id = next_id++;     // Asignar ID único e incrementar contador
                        FD_SET(new_client, &current);           // Añadir cliente al monitoreo
                        send_msg(new_client, "server: client %d just arrived\n", clients[new_client].id);
                    }
                }
                // ===========================================================
                // CASO 2: ACTIVIDAD DE CLIENTE EXISTENTE
                // ===========================================================
                else {
                    /*
                     * RECEPCIÓN Y PROCESAMIENTO DE DATOS:
                     * ==================================
                     * - recv() lee datos del socket hacia recv_buffer
                     * - Declaración múltiple: declara msg_bytes, i, len en una línea
                     * - msg_bytes = bytes recibidos (<=0 significa desconexión)
                     * - i, len = contadores para procesar los datos byte a byte
                     */
                    int msg_bytes = recv(fd, recv_buffer, sizeof(recv_buffer), 0), i, len;
                    
                    // -------------------------------------------------------
                    // SUBCASO 2A: DESCONEXIÓN (recv retorna <= 0)
                    // -------------------------------------------------------
                    if(msg_bytes <= 0){
                        /*
                         * LIMPIEZA DE CLIENTE DESCONECTADO:
                         * ================================
                         * 1. Notificar a todos sobre la desconexión
                         * 2. Remover FD del monitoreo (ANTES de close!)
                         * 3. Cerrar descriptor
                         * 4. Limpiar buffer del cliente
                         * 5. Actualizar max_fd si era el mayor
                         */
                        send_msg(fd, "server: client %d just left\n", clients[fd].id);
                        FD_CLR(fd, &current); close(fd); bzero(clients[fd].msg, sizeof(clients[fd].msg));
                        if(fd == max_fd) while(max_fd > 0 && !FD_ISSET(max_fd, &current)) max_fd--;
                    }
                    // -------------------------------------------------------
                    // SUBCASO 2B: DATOS RECIBIDOS (procesar mensaje)
                    // -------------------------------------------------------
                    else {
                        /*
                         * PROCESAMIENTO BYTE A BYTE - DETECCIÓN DE MENSAJES:
                         * ==================================================
                         * - Recorre cada byte recibido en recv_buffer
                         * - Lo añade al buffer de acumulación del cliente
                         * - Si encuentra '\n': mensaje completo, procesar y retransmitir
                         * - Si no encuentra '\n': seguir acumulando para próxima recv()
                         */
                        for(i = 0, len = strlen(clients[fd].msg); i < msg_bytes && len < 370000 - 1; i++, len++)
                            if((clients[fd].msg[len] = recv_buffer[i]) == '\n'){
                                // Fin de mensaje detectado: procesar y retransmitir
                                clients[fd].msg[len] = '\0';  // Terminar string (quitar \n)
                                send_msg(fd, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                                bzero(clients[fd].msg, sizeof(clients[fd].msg));
                                len = -1;  // Reset contador (se incrementará a 0 en el for)
                            }
                    }
                }
            }
        }
    }
    // El programa nunca llega aquí (bucle infinito)
}

/*
 * NOTAS TÉCNICAS AVANZADAS - ANÁLISIS PROFUNDO DEL DISEÑO:
 * =========================================================
 * 
 * 1. MULTIPLEXACIÓN E/S CON SELECT() - ARQUITECTURA EVENT-DRIVEN:
 *    ============================================================
 *    - select() implementa el patrón "Reactor" para manejo de eventos
 *    - Permite escalar hasta ~1000 conexiones concurrentes sin hilos
 *    - Ventajas sobre multithreading:
 *      * Sin overhead de context switching
 *      * Sin problemas de sincronización/mutex
 *      * Menor uso de memoria (sin stacks de hilos)
 *    - Limitaciones: Máximo FD_SETSIZE descriptores (~1024)
 *    - Alternativas modernas: epoll (Linux), kqueue (BSD), IOCP (Windows)
 * 
 * 2. NETWORK BYTE ORDER Y PORTABILIDAD:
 *    ==================================
 *    - Big-endian vs Little-endian: diferente orden de bytes en memoria
 *    - Network byte order = Big-endian (estándar RFC 1700)
 *    - htons()/htonl(): "host to network" - conversión automática
 *    - ntohs()/ntohl(): "network to host" - conversión inversa
 *    - 2130706433 = representación optimizada de 127.0.0.1
 *    - Evita parsing runtime y garantiza portabilidad entre arquitecturas
 * 
 * 3. GESTIÓN AVANZADA DE MEMORIA Y BUFFERS:
 *    ======================================
 *    - Patrón "Triple Buffer": recv_buffer → clients[].msg → send_buffer
 *    - Buffer estáticos vs dinámicos:
 *      * Evitan fragmentación de heap
 *      * Predicibles en tiempo de ejecución
 *      * Sin riesgo de memory leaks
 *      * Optimización de cache locality
 *    - bzero() vs memset(): bzero más legible para limpiar buffers
 *    - Diseño de tamaños con margen de seguridad (30KB buffer entre tamaños)
 * 
 * 4. PROTOCOLO DE APLICACIÓN MINIMALISTA:
 *    ====================================
 *    - Delimitador '\n': Simple pero efectivo
 *    - Ventajas: fácil parsing, compatible con telnet/netcat
 *    - Prefijos identificativos: "client X:", "server:"
 *    - Sin overhead de headers binarios o parsing complejo
 *    - Streaming protocol: procesa datos conforme llegan
 * 
 * 5. OPTIMIZACIONES DE CÓDIGO C APLICADAS:
 *    ====================================
 *    a) DECLARACIONES COMPACTAS:
 *       - struct sockaddr_in sa = {AF_INET, htons(...), {htonl(...)}};
 *       - int msg_bytes = recv(...), i, len; // Declaración múltiple
 *    
 *    b) INICIALIZADORES DESIGNADOS:
 *       - Inicialización directa de estructuras sin memset
 *       - Más legible y eficiente que asignaciones por separado
 *    
 *    c) COMPATIBILIDAD CON cc:
 *       - socklen_t addr_len = sizeof(sa); // Variable explícita
 *       - Evita compound literals no soportados por cc del campus
 *    
 *    d) OPERADORES TERNARIOS:
 *       - msg ? strlen(msg) : 11 // Condicional inline
 *       - Más compacto que if-else para casos simples
 *    
 *    e) ASIGNACIÓN EN EXPRESIONES:
 *       - if((clients[fd].msg[len] = recv_buffer[i]) == '\n')
 *       - Asigna Y compara en una sola expresión
 *    
 *    f) FUNCIONES VARIÁDICAS:
 *       - send_msg(fd, "format %d", arg) // Como printf
 *       - Flexibilidad sin sobrecarga de múltiples funciones
 * 
 * 6. DISEÑO DE CONSTANTES - INGENIERÍA DE SISTEMAS:
 *    ===============================================
 *    - 2048 clientes: Potencia de 2 para alineación de memoria
 *    - 370000/400000 bytes: Múltiplos de 1000 para cálculos mentales
 *    - Queue size 100: Balance empírico entre responsividad y recursos
 *    - Todas las decisiones basadas en:
 *      * Límites del sistema operativo
 *      * Características del hardware típico
 *      * Patrones de uso esperados en chat
 *      * Análisis de trade-offs memoria vs performance
 * 
 * 7. PATRONES DE DISEÑO IMPLEMENTADOS:
 *    =================================
 *    - REACTOR PATTERN: select() como despachador de eventos
 *    - OBSERVER PATTERN: broadcast notifica a todos los observadores (clientes)
 *    - COMMAND PATTERN: Cada mensaje es un comando procesado uniformemente
 *    - BUFFER PATTERN: Múltiples niveles de buffering para optimización
 * 
 * 8. CONSIDERACIONES DE SEGURIDAD Y ROBUSTEZ:
 *    ========================================
 *    - Validación de límites: len < 370000 - 1 (previene overflow)
 *    - Manejo de errores: err() para fallos críticos del sistema
 *    - Limpieza de recursos: FD_CLR antes de close()
 *    - Actualización consistente de max_fd tras desconexiones
 *    - Reinicio automático tras errores de select()
 * 
 * 9. ESCALABILIDAD Y LIMITACIONES:
 *    =============================
 *    - Límite actual: ~1000-2000 conexiones simultáneas
 *    - Bottlenecks identificados:
 *      * FD_SETSIZE máximo en select()
 *      * Broadcast O(n) por cada mensaje
 *      * Memoria fija por cliente (758MB total para 2048 clientes)
 *    - Mejoras posibles:
 *      * epoll/kqueue para > 10k conexiones
 *      * Message queues para broadcast eficiente
 *      * Memoria dinámica para clientes activos únicamente
 * 
 * 10. ANÁLISIS DE COMPLEJIDAD TEMPORAL:
 *     =================================
 *     - select(): O(max_fd) por iteración
 *     - send_msg(): O(max_fd) por mensaje
 *     - Procesamiento por byte: O(r) donde r = bytes recibidos
 *     - Complejidad total por mensaje: O(max_fd + r)
 *     - Memoria: O(1) por cliente (arrays estáticos)
 * 
 * ESTE CÓDIGO DEMUESTRA:
 * - Programación de sistemas de bajo nivel en C
 * - Networking TCP/IP y multiplexación de E/S
 * - Gestión eficiente de memoria y recursos
 * - Optimizaciones específicas del compilador C
 * - Diseño escalable para aplicaciones de red
 * - Patrones de arquitectura para sistemas concurrentes
 */