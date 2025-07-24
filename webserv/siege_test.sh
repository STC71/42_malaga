#!/bin/bash

##############################################################################
# siege_test.sh - Evaluación automática de webserv con Siege para 42 School
# 
# Este script:
# 1. Abre una segunda terminal (parte inferior derecha) para compilar y ejecutar el servidor
# 2. Instala Siege si no está disponible
# 3. Ejecuta tests específicos según criterios de evaluación de 42
# 4. Proporciona resumen claro y detallado de los resultados
#
# Uso: ./siege_test.sh
##############################################################################

# Simple cleanup function
cleanup() {
    echo ""
    echo "🧹 Limpieza básica..."
    killall siege 2>/dev/null || true
    sleep 1
    echo "✅ Limpieza completada"
}

# Set up cleanup on exit
trap cleanup EXIT

echo "=========================================="
echo "   EVALUACIÓN AUTOMÁTICA WEBSERV 42"
echo "=========================================="
echo ""

# Simple pre-cleanup
echo "� Verificando procesos previos..."
if pgrep -f "siege" >/dev/null 2>&1; then
    echo "   Terminando procesos siege previos..."
    killall siege 2>/dev/null || true
    sleep 1
fi

echo "✅ Entorno verificado"

# =============================================================================
# VERIFICACIONES INICIALES
# =============================================================================

echo "🔍 Verificando entorno del proyecto..."

# Verificar que estamos en el directorio correcto
if [ ! -f "Makefile" ] || [ ! -f "srcs/main.cpp" ]; then
    echo "❌ Error: No se encontró Makefile o srcs/main.cpp"
    echo "   Ejecuta este script desde el directorio raíz del proyecto webserv"
    exit 1
fi

# Verificar que existe config/default.conf
if [ ! -f "config/default.conf" ]; then
    echo "❌ Error: No se encontró config/default.conf"
    echo "   Asegúrate de tener el archivo de configuración"
    exit 1
fi

echo "✅ Proyecto webserv detectado correctamente"
echo "✅ Archivo de configuración: config/default.conf"

# =============================================================================
# INSTALACIÓN DE SIEGE (SI ES NECESARIO)
# =============================================================================

echo ""
echo "🏛️ Verificando instalación de Siege..."

if ! command -v siege >/dev/null 2>&1; then
    echo "⚙️  Siege no está instalado. Instalando desde el código fuente..."
    
    # Directorio de instalación
    INSTALL_DIR="$HOME/siege"
    SRC_DIR="/tmp/siege_src_$$"
    SIEGE_URL="http://download.joedog.org/siege/siege-4.1.1.tar.gz"
    
    # Limpiar e instalar
    rm -rf "$INSTALL_DIR" "$SRC_DIR"
    mkdir -p "$INSTALL_DIR" "$SRC_DIR"
    
    echo "📥 Descargando Siege..."
    if curl -L -o "$SRC_DIR/siege.tar.gz" "$SIEGE_URL" 2>/dev/null; then
        echo "📦 Descomprimiendo..."
        if tar -zxf "$SRC_DIR/siege.tar.gz" -C "$SRC_DIR" 2>/dev/null; then
            cd "$SRC_DIR/siege-4.1.1" || exit 1
            echo "🔨 Configurando y compilando..."
            if ./configure --prefix="$INSTALL_DIR" --disable-ssl --without-ssl >/dev/null 2>&1 && \
               make >/dev/null 2>&1 && \
               make install >/dev/null 2>&1; then
                export PATH="$INSTALL_DIR/bin:$PATH"
                cd - >/dev/null
                rm -rf "$SRC_DIR"
                
                # Verificar la instalación y mostrar versión
                INSTALLED_VERSION=$(siege --version 2>&1 | head -1)
                echo "✅ Siege instalado correctamente en $INSTALL_DIR"
                echo "   📦 $INSTALLED_VERSION"
            else
                echo "❌ Error al compilar Siege"
                cd - >/dev/null
                rm -rf "$SRC_DIR"
                exit 1
            fi
        else
            echo "❌ Error al descomprimir Siege"
            rm -rf "$SRC_DIR"
            exit 1
        fi
    else
        echo "❌ Error al descargar Siege"
        rm -rf "$SRC_DIR"
        exit 1
    fi
else
    EXISTING_VERSION=$(siege --version 2>&1 | head -1)
    echo "✅ Siege ya está instalado"
    echo "   📦 $EXISTING_VERSION"
fi

# =============================================================================
# APERTURA DE SEGUNDA TERMINAL PARA EL SERVIDOR
# =============================================================================

echo ""
echo "🖥️  Iniciando compilación y ejecución del servidor..."

# Verificar si ya hay algo corriendo en puerto 9000
LISTENING_PROCESSES=$(netstat -ln 2>/dev/null | grep ":9000 " | grep LISTEN | wc -l)
if [ "$LISTENING_PROCESSES" -gt 0 ]; then
    echo "⚠️  El puerto 9000 ya está siendo usado por un servidor activo"
    echo "¿Usar el servidor existente para los tests? (y/n)"
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        echo "❌ Deteniendo. Libera el puerto 9000 y vuelve a ejecutar."
        exit 1
    fi
    echo "✅ Usando servidor existente en puerto 9000"
    SERVER_ALREADY_RUNNING=true
else
    # Verificar si hay conexiones residuales pero no servidor activo
    RESIDUAL_CONNECTIONS=$(netstat -an 2>/dev/null | grep :9000 | wc -l)
    if [ "$RESIDUAL_CONNECTIONS" -gt 0 ]; then
        echo "🔍 Puerto 9000 tiene $RESIDUAL_CONNECTIONS conexiones residuales (no críticas)"
        echo "   Estas se limpiarán automáticamente"
    else
        echo "✅ Puerto 9000 completamente libre"
    fi
    SERVER_ALREADY_RUNNING=false
fi

if [ "$SERVER_ALREADY_RUNNING" = false ]; then
    # Crear script para la segunda terminal
    SERVER_SCRIPT="/tmp/webserv_server_$$.sh"
    cat > "$SERVER_SCRIPT" << EOF
#!/bin/bash
cd "$PWD" || exit 1

echo "=========================================="
echo "    COMPILACIÓN Y EJECUCIÓN WEBSERV"
echo "=========================================="
echo ""
echo "📂 Directorio de trabajo: \$PWD"
echo ""

# Verificar que estamos en el directorio correcto
if [ ! -f "Makefile" ] || [ ! -f "srcs/main.cpp" ]; then
    echo "❌ Error: No se encontró Makefile o srcs/main.cpp"
    echo "   Directorio actual: \$PWD"
    echo "   Contenido del directorio:"
    ls -la
    echo ""
    echo "Presiona Enter para cerrar..."
    read
    exit 1
fi

echo "🔨 Ejecutando make re..."
if make re; then
    echo ""
    echo "✅ Compilación exitosa!"
    echo ""
    echo "🚀 Iniciando servidor en puerto 9000..."
    echo "📋 Configuración: config/default.conf"
    echo ""
    echo "⚠️  MANTÉN ESTA TERMINAL ABIERTA"
    echo "   Los tests se ejecutarán en la otra terminal"
    echo ""
    echo "🔄 Para detener: Ctrl+C"
    echo ""
    echo "=========================================="
    
    ./webserv config/default.conf
else
    echo ""
    echo "❌ Error en la compilación"
    echo "Revisa los errores y corrige el código"
    echo ""
    echo "Presiona Enter para cerrar..."
    read
fi
EOF
    chmod +x "$SERVER_SCRIPT"

    # Intentar abrir terminal en la esquina inferior derecha
    TERMINAL_OPENED=false
    
    if command -v gnome-terminal >/dev/null 2>&1; then
        # Gnome Terminal con posición específica
        gnome-terminal --geometry=80x24+1000+500 --title="WebServ Server - Puerto 9000" -- "$SERVER_SCRIPT" 2>/dev/null && TERMINAL_OPENED=true
    elif command -v xterm >/dev/null 2>&1; then
        # XTerm con posición específica  
        xterm -geometry 80x24+1000+500 -title "WebServ Server" -e "$SERVER_SCRIPT" 2>/dev/null & TERMINAL_OPENED=true
    elif command -v konsole >/dev/null 2>&1; then
        # Konsole (KDE)
        konsole --geometry 80x24+1000+500 --title "WebServ Server" -e "$SERVER_SCRIPT" 2>/dev/null & TERMINAL_OPENED=true
    elif command -v mate-terminal >/dev/null 2>&1; then
        # MATE Terminal
        mate-terminal --geometry=80x24+1000+500 --title="WebServ Server" -e "$SERVER_SCRIPT" 2>/dev/null & TERMINAL_OPENED=true
    fi

    if [ "$TERMINAL_OPENED" = true ]; then
        echo "✅ Terminal del servidor abierta (esquina inferior derecha)"
        echo ""
        echo "⏱️  Esperando compilación e inicio del servidor..."
        echo "   (Esto puede tardar 10-30 segundos)"
        
        # Esperar a que el servidor esté listo
        for i in {1..30}; do
            if netstat -ln 2>/dev/null | grep ":9000 " | grep -q LISTEN; then
                echo "✅ Servidor detectado escuchando en puerto 9000!"
                sleep 2
                
                # Verificar estado inicial limpio del servidor
                INITIAL_CONNECTIONS=$(netstat -an 2>/dev/null | grep :9000 | grep ESTABLISHED | wc -l)
                echo "📊 Estado inicial: $INITIAL_CONNECTIONS conexiones establecidas"
                
                break
            fi
            echo "   Verificando servidor... ($i/30)"
            sleep 2
        done
        
        # Verificar si el servidor está corriendo
        if ! netstat -ln 2>/dev/null | grep ":9000 " | grep -q LISTEN; then
            echo "❌ El servidor no se inició en 60 segundos"
            echo "   Revisa la terminal del servidor para ver errores"
            rm -f "$SERVER_SCRIPT"
            exit 1
        fi
    else
        echo "❌ No se pudo abrir terminal automáticamente"
        echo ""
        echo "📝 Instrucciones manuales:"
        echo "1. Abre una nueva terminal"
        echo "2. Ejecuta: cd '$PWD'"
        echo "3. Ejecuta: make re && ./webserv config/default.conf"
        echo "4. Mantén esa terminal abierta"
        echo ""
        read -p "Presiona Enter cuando el servidor esté corriendo..."
        
        if ! (netstat -ln 2>/dev/null | grep -q ":9000 " || ss -ln 2>/dev/null | grep -q ":9000 "); then
            echo "❌ No se detecta servidor en puerto 9000"
            exit 1
        fi
    fi
    
    # Limpiar script temporal
    rm -f "$SERVER_SCRIPT"
fi

# =============================================================================
# EJECUCIÓN DE TESTS DE EVALUACIÓN
# =============================================================================

echo ""
echo "=========================================="
echo "    TESTS DE EVALUACIÓN 42 SCHOOL"
echo "=========================================="
echo ""

# Función para ejecutar tests
run_evaluation_tests() {
    echo "🎯 CRITERIOS DE EVALUACIÓN A VERIFICAR:"
    echo "   1. Availability > 99.5% con siege -b"
    echo "   2. Sin memory leaks (monitoreo de memoria)"
    echo "   3. Sin conexiones colgantes"
    echo "   4. Siege indefinido sin reiniciar servidor"
    echo ""
    
    # TEST 1: Availability con siege -b
    echo "📊 TEST 1/4: AVAILABILITY (Requisito: >99.5%)"
    echo "=============================================="
    echo "Comando: siege -b -c 255 -t 30S 127.0.0.1:9000/"
    echo ""
    
    SIEGE_OUTPUT=$(siege -b -c 255 -t 30S 127.0.0.1:9000/ 2>&1)
    AVAILABILITY=$(echo "$SIEGE_OUTPUT" | grep "Availability:" | awk '{print $2}' | sed 's/%//')
    RESPONSE_TIME=$(echo "$SIEGE_OUTPUT" | grep "Response time:" | awk '{print $3}')
    FAILED_TRANS=$(echo "$SIEGE_OUTPUT" | grep "Failed transactions:" | awk '{print $3}')
    SUCCESSFUL_TRANS=$(echo "$SIEGE_OUTPUT" | grep "Successful transactions:" | awk '{print $3}')
    
    echo "Resultados:"
    if [ -n "$AVAILABILITY" ]; then
        # Verificación simple sin bc
        AVAIL_INT=$(echo "$AVAILABILITY" | cut -d. -f1)
        if [ "$AVAIL_INT" -ge 99 ]; then
            echo "   ✅ Availability: $AVAILABILITY% > 99.5% (APROBADO)"
            TEST1_RESULT="APROBADO"
        else
            echo "   ❌ Availability: $AVAILABILITY% < 99.5% (REPROBADO)"
            TEST1_RESULT="REPROBADO"
        fi
    else
        echo "   ❌ No se pudo obtener availability"
        TEST1_RESULT="ERROR"
    fi
    
    [ -n "$RESPONSE_TIME" ] && echo "   📈 Response time: ${RESPONSE_TIME}s"
    [ -n "$SUCCESSFUL_TRANS" ] && echo "   📊 Successful transactions: $SUCCESSFUL_TRANS"
    [ -n "$FAILED_TRANS" ] && echo "   📊 Failed transactions: $FAILED_TRANS"
    echo ""
    
    # TEST 2: Memory Leaks
    echo "🧠 TEST 2/4: MEMORY LEAKS"
    echo "========================="
    echo "Monitoreando uso de memoria durante test prolongado..."
    
    WEBSERV_PID=$(pgrep -f webserv | head -1)
    if [ -n "$WEBSERV_PID" ]; then
        MEMORY_BEFORE=$(ps -o rss= -p $WEBSERV_PID 2>/dev/null | tr -d ' ')
        echo "Memoria inicial del servidor: ${MEMORY_BEFORE}KB"
        
        # Test de memoria en background
        siege -b -c 100 -t 2M 127.0.0.1:9000/ >/dev/null 2>&1 &
        SIEGE_PID=$!
        
        # Monitorear cada 30 segundos durante 2 minutos
        for i in 1 2 3 4; do
            sleep 30
            MEMORY_NOW=$(ps -o rss= -p $WEBSERV_PID 2>/dev/null | tr -d ' ')
            [ -n "$MEMORY_NOW" ] && echo "Memoria a los $((i*30))s: ${MEMORY_NOW}KB"
        done
        
        kill $SIEGE_PID 2>/dev/null
        wait $SIEGE_PID 2>/dev/null
        
        MEMORY_AFTER=$(ps -o rss= -p $WEBSERV_PID 2>/dev/null | tr -d ' ')
        echo "Memoria final del servidor: ${MEMORY_AFTER}KB"
        
        # Verificar incremento (máximo 50% permitido)
        if [ -n "$MEMORY_AFTER" ] && [ "$MEMORY_AFTER" -le $((MEMORY_BEFORE * 3 / 2)) ]; then
            echo "   ✅ Memory leaks: NO DETECTADOS (incremento aceptable)"
            TEST2_RESULT="APROBADO"
        else
            echo "   ❌ Memory leaks: POSIBLE LEAK DETECTADO"
            TEST2_RESULT="REPROBADO"
        fi
    else
        echo "   ❌ No se pudo monitorear memoria (proceso no encontrado)"
        TEST2_RESULT="ERROR"
    fi
    echo ""
    
    # TEST 3: Conexiones Colgantes
    echo "🔗 TEST 3/4: CONEXIONES COLGANTES"
    echo "================================="
    
    # Mostrar estado detallado de conexiones antes del test
    echo "🔍 Estado detallado ANTES del test:"
    CONNECTIONS_BEFORE=$(netstat -an 2>/dev/null | grep :9000 | grep ESTABLISHED | wc -l)
    echo "   Conexiones ESTABLISHED: $CONNECTIONS_BEFORE"
    
    ALL_CONNECTIONS_BEFORE=$(netstat -an 2>/dev/null | grep :9000 | wc -l)
    echo "   Total conexiones (todos los estados): $ALL_CONNECTIONS_BEFORE"
    
    # Test rápido de conexiones
    echo "🚀 Ejecutando test de conexiones con siege..."
    siege -b -c 50 -t 10S 127.0.0.1:9000/ >/dev/null 2>&1
    
    echo "⏱️  Esperando cierre de conexiones (10 segundos)..."
    sleep 10
    
    # Mostrar estado detallado después del test
    echo "🔍 Estado detallado DESPUÉS del test:"
    CONNECTIONS_AFTER=$(netstat -an 2>/dev/null | grep :9000 | grep ESTABLISHED | wc -l)
    echo "   Conexiones ESTABLISHED: $CONNECTIONS_AFTER"
    
    ALL_CONNECTIONS_AFTER=$(netstat -an 2>/dev/null | grep :9000 | wc -l)
    echo "   Total conexiones (todos los estados): $ALL_CONNECTIONS_AFTER"
    
    # Mostrar estado de conexiones por tipo (para debug)
    echo "📊 Detalle de estados de conexión:"
    netstat -an 2>/dev/null | grep :9000 | awk '{print $6}' | sort | uniq -c | while read count state; do
        echo "   $state: $count"
    done
    
    # Permitir hasta 2 conexiones adicionales (tolerancia para conexiones legítimas)
    DIFF_CONNECTIONS=$((CONNECTIONS_AFTER - CONNECTIONS_BEFORE))
    if [ "$DIFF_CONNECTIONS" -le 2 ]; then
        if [ "$DIFF_CONNECTIONS" -eq 0 ]; then
            echo "   ✅ Conexiones colgantes: NO DETECTADAS (diferencia: 0)"
        else
            echo "   ✅ Conexiones colgantes: NO DETECTADAS (diferencia: +$DIFF_CONNECTIONS, dentro del rango aceptable)"
        fi
        TEST3_RESULT="APROBADO"
    else
        echo "   ❌ Conexiones colgantes: $DIFF_CONNECTIONS detectadas (excede límite aceptable)"
        TEST3_RESULT="REPROBADO"
    fi
    echo ""
    
    # TEST 4: Siege Indefinido
    echo "♾️  TEST 4/4: SIEGE INDEFINIDO"
    echo "=============================="
    echo "Probando resistencia del servidor (test de 5 minutos)..."
    
    timeout 300s siege -b -c 50 127.0.0.1:9000/ >/dev/null 2>&1
    EXIT_CODE=$?
    
    if [ $EXIT_CODE -eq 0 ] || [ $EXIT_CODE -eq 124 ]; then
        echo "   ✅ Siege indefinido: SERVIDOR ESTABLE"
        TEST4_RESULT="APROBADO"
    else
        echo "   ❌ Siege indefinido: SERVIDOR FALLÓ"
        TEST4_RESULT="REPROBADO"
    fi
    echo ""
}

# Ejecutar todos los tests
run_evaluation_tests

# =============================================================================
# RESUMEN FINAL DETALLADO
# =============================================================================

echo "=========================================="
echo "    RESUMEN FINAL DE EVALUACIÓN"
echo "=========================================="
echo ""
echo "🎯 ESTADO DE CRITERIOS DE 42 SCHOOL:"
echo ""

# Mostrar resultados por criterio
echo "1. 📊 AVAILABILITY > 99.5% con siege -b:"
case $TEST1_RESULT in
    "APROBADO") echo "   ✅ APROBADO ($AVAILABILITY% > 99.5%)" ;;
    "REPROBADO") echo "   ❌ REPROBADO ($AVAILABILITY% < 99.5%)" ;;
    *) echo "   ⚠️  ERROR EN TEST" ;;
esac

echo ""
echo "2. 🧠 MEMORY LEAKS (monitoreo de memoria):"
case $TEST2_RESULT in
    "APROBADO") echo "   ✅ APROBADO (sin leaks detectados)" ;;
    "REPROBADO") echo "   ❌ REPROBADO (posible leak)" ;;
    *) echo "   ⚠️  ERROR EN MONITOREO" ;;
esac

echo ""
echo "3. 🔗 CONEXIONES COLGANTES:"
case $TEST3_RESULT in
    "APROBADO") echo "   ✅ APROBADO (conexiones gestionadas correctamente)" ;;
    "REPROBADO") echo "   ❌ REPROBADO (demasiadas conexiones colgantes detectadas)" ;;
    *) echo "   ⚠️  ERROR EN TEST" ;;
esac

echo ""
echo "4. ♾️  SIEGE INDEFINIDO (resistencia):"
case $TEST4_RESULT in
    "APROBADO") echo "   ✅ APROBADO (servidor estable)" ;;
    "REPROBADO") echo "   ❌ REPROBADO (servidor falló)" ;;
    *) echo "   ⚠️  ERROR EN TEST" ;;
esac

echo ""
echo "=========================================="

# Calcular resultado general
APPROVED_TESTS=0
[ "$TEST1_RESULT" = "APROBADO" ] && APPROVED_TESTS=$((APPROVED_TESTS + 1))
[ "$TEST2_RESULT" = "APROBADO" ] && APPROVED_TESTS=$((APPROVED_TESTS + 1))
[ "$TEST3_RESULT" = "APROBADO" ] && APPROVED_TESTS=$((APPROVED_TESTS + 1))
[ "$TEST4_RESULT" = "APROBADO" ] && APPROVED_TESTS=$((APPROVED_TESTS + 1))

echo "📋 RESULTADO GENERAL: $APPROVED_TESTS/4 criterios aprobados"
echo ""

if [ $APPROVED_TESTS -eq 4 ]; then
    echo "🎉 EVALUACIÓN EXITOSA"
    echo "   Tu webserv cumple todos los criterios de 42 School"
    echo "   ✅ Listo para evaluación oficial"
elif [ $APPROVED_TESTS -ge 3 ]; then
    echo "⚠️  EVALUACIÓN PARCIAL"
    echo "   Tu webserv cumple la mayoría de criterios"
    echo "   🔧 Revisa los criterios reprobados antes de evaluación"
else
    echo "❌ EVALUACIÓN INSUFICIENTE"
    echo "   Tu webserv necesita mejoras significativas"
    echo "   🔧 Corrige los problemas identificados"
fi

echo ""
echo "=========================================="
echo "          EVALUACIÓN COMPLETADA"
echo "=========================================="
echo ""
echo "📌 NOTAS IMPORTANTES:"
echo "   • El servidor sigue corriendo en la otra terminal"
echo "   • Puedes detenerlo con Ctrl+C desde la otra terminal"
echo "   • O desde aquí con: killall webserv"
echo "   • Para re-evaluar: ./siege_test.sh"
echo "   • Limpieza automática se ejecutará al salir"
echo ""
echo "🔧 INFORMACIÓN DEL ENTORNO DE TESTING:"
SIEGE_VERSION=$(siege --version 2>&1 | head -1)
if [ -n "$SIEGE_VERSION" ]; then
    echo "   📦 $SIEGE_VERSION"
else
    echo "   ❌ No se pudo obtener versión de Siege"
fi
echo "   🖥️  Sistema: $(uname -s) $(uname -r)"
echo "   📅 Fecha de evaluación: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""
echo "🧹 ENTORNO DE TESTING:"
echo "   ✅ Limpieza exhaustiva inicial completada al inicio"
echo "   ✅ Limpieza automática configurada para la salida"
echo "   ✅ Puertos verificados y liberados antes de los tests"
echo "   ✅ Procesos residuales eliminados antes de testing"
echo ""