#!/bin/bash

##############################################################################
# 01_only_one_select.sh - Verificación de uso de un solo select() o equivalente
# EVALUACIÓN:
# "Ask if they use only one select() (or equivalent) and how they've 
#  managed the server to accept and the client to read/write"
##############################################################################

# Definir colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

echo -e "${CYAN}=========================================="
echo -e "  USO DE UN SOLO SELECT() - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. BUSCAR FUNCIONES DE MULTIPLEXACIÓN I/O
# =============================================================================

echo -e "${BLUE}🔍 1. Buscando select/poll/epoll en el código:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"select\\|poll\\|epoll\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

GREP_RESULTS=$(grep -rn "select\|poll\|epoll" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)

if [ -z "$GREP_RESULTS" ]; then
    echo -e "${RED}❌ ERROR: No se encontraron funciones de multiplexación I/O${NC}"
    exit 1
fi

echo "$GREP_RESULTS"
echo ""

# Contar llamadas reales (sin comentarios)
SELECT_CALLS=$(echo "$GREP_RESULTS" | grep "select(" | grep -v "//" | grep -v "\*" | wc -l)
TOTAL_CALLS=$(echo "$GREP_RESULTS" | grep -E "select\(|poll\(|epoll_" | grep -v "//" | grep -v "\*" | wc -l)

echo -e "${YELLOW}📊 Análisis: $TOTAL_CALLS llamadas encontradas ($SELECT_CALLS de select)${NC}"

if [ "$TOTAL_CALLS" -eq 1 ]; then
    echo -e "${GREEN}✅ CORRECTO: Solo una función de multiplexación${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Se encontraron $TOTAL_CALLS funciones (debe ser 1)${NC}"
fi

echo ""

# =============================================================================
# 2. VERIFICAR GESTIÓN DE CONEXIONES
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando gestión de conexiones:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"accept\\|recv\\|send\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

CONNECTION_RESULTS=$(grep -rn "accept\|recv\|send" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$CONNECTION_RESULTS" | head -5
TOTAL_CONN=$(echo "$CONNECTION_RESULTS" | wc -l)
if [ "$TOTAL_CONN" -gt 5 ]; then
    echo "... ($TOTAL_CONN líneas en total)"
fi

echo ""

HAS_ACCEPT=$(echo "$CONNECTION_RESULTS" | grep -c "accept(" || echo "0")
HAS_RECV=$(echo "$CONNECTION_RESULTS" | grep -c "recv" || echo "0")
HAS_SEND=$(echo "$CONNECTION_RESULTS" | grep -c "send" || echo "0")

echo -e "${YELLOW}📊 Funciones encontradas: accept($HAS_ACCEPT) recv($HAS_RECV) send($HAS_SEND)${NC}"

if [ "$HAS_ACCEPT" -gt 0 ] && [ "$HAS_RECV" -gt 0 ] && [ "$HAS_SEND" -gt 0 ]; then
    echo -e "${GREEN}✅ CORRECTO: Gestión completa servidor/cliente${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Gestión incompleta${NC}"
fi

echo ""

# =============================================================================
# 3. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$TOTAL_CALLS" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_ACCEPT" -gt 0 ] && [ "$HAS_RECV" -gt 0 ] && [ "$HAS_SEND" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/2 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 2 ]; then
    echo -e "${GREEN}🎉 EVALUACIÓN EXITOSA${NC}"
else
    echo -e "${RED}❌ EVALUACIÓN FALLIDA${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden mostrar y explicar cómo su único select() maneja:${NC}"
echo ""
echo -e "${BLUE}1. 🎯 Aceptación de nuevas conexiones del servidor${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Cuando select() detecta actividad en server_fds, usamos"
echo -e "    FD_ISSET() para verificar qué servidor tiene conexiones"
echo -e "    pendientes y llamamos accept() para aceptar la conexión'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'FD_ISSET.*server_fds\\|accept(' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""
echo -e "${YELLOW}   📋 Explicación del resultado:${NC}"
echo -e "${WHITE}   Debe mostrar código donde FD_ISSET() verifica server_fds"
echo -e "   seguido de accept() para aceptar nuevas conexiones${NC}"
echo ""

echo -e "${BLUE}2. 📥 Lectura de requests de clientes existentes${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Cuando select() detecta actividad en read_fds para un cliente,"
echo -e "    usamos FD_ISSET() para verificar qué cliente tiene datos"
echo -e "    listos y llamamos recv() para leer el request'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'FD_ISSET.*client.*read\\|recv(' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""
echo -e "${YELLOW}   📋 Explicación del resultado:${NC}"
echo -e "${WHITE}   Debe mostrar código donde FD_ISSET() verifica clientes en"
echo -e "   read_fds seguido de recv() para leer datos del cliente${NC}"
echo ""

echo -e "${BLUE}3. 📤 Escritura de responses a clientes${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Cuando select() detecta que un cliente está listo para"
echo -e "    escribir (write_fds), usamos FD_ISSET() para verificar"
echo -e "    qué cliente puede recibir datos y llamamos send()'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'FD_ISSET.*write_fds\\|send(' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""
echo -e "${YELLOW}   📋 Explicación del resultado:${NC}"
echo -e "${WHITE}   Debe mostrar código donde FD_ISSET() verifica clientes en"
echo -e "   write_fds seguido de send() para enviar respuestas${NC}"
echo ""

echo -e "${WHITE}¿Todo esto ocurre en el mismo bucle de eventos?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, todo ocurre en UN SOLO bucle while que contiene"
echo -e "    select() y procesa todos los tipos de file descriptors'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 30 -B 5 'while.*true\\|while.*1' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""
echo -e "${YELLOW}   📋 Explicación del resultado:${NC}"
echo -e "${WHITE}   Debe mostrar UN SOLO bucle principal con select() y"
echo -e "   procesamiento de todos los tipos de descriptores${NC}"
