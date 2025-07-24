#!/bin/bash

##############################################################################
# 06_error_handling.sh - Verificación de manejo de errores en sockets
# EVALUACIÓN:
# "Search for all read/recv/write/send on a socket and check that, 
#  if an error is returned, the client is removed"
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
echo -e "  MANEJO DE ERRORES EN SOCKETS - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. BUSCAR TODAS LAS OPERACIONES DE SOCKET
# =============================================================================

echo -e "${BLUE}🔍 1. Buscando operaciones de socket:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"read\\|recv\\|write\\|send\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

SOCKET_OPS=$(grep -rn "read\|recv\|write\|send" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$SOCKET_OPS" | head -10
TOTAL_OPS=$(echo "$SOCKET_OPS" | wc -l)
if [ "$TOTAL_OPS" -gt 10 ]; then
    echo "... ($TOTAL_OPS operaciones en total)"
fi

echo ""

HAS_READ=$(echo "$SOCKET_OPS" | grep -c "read(" || echo "0")
HAS_RECV=$(echo "$SOCKET_OPS" | grep -c "recv(" || echo "0")
HAS_WRITE=$(echo "$SOCKET_OPS" | grep -c "write(" || echo "0")
HAS_SEND=$(echo "$SOCKET_OPS" | grep -c "send(" || echo "0")

echo -e "${YELLOW}📊 Operaciones encontradas: read($HAS_READ) recv($HAS_RECV) write($HAS_WRITE) send($HAS_SEND)${NC}"

# =============================================================================
# 2. VERIFICAR MANEJO DE ERRORES EN READ/RECV
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando manejo de errores en read/recv:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 5 -B 2 \"recv.*==.*-1\\|read.*==.*-1\\|recv.*<=.*0\\|read.*<=.*0\" $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

READ_ERRORS=$(grep -A 5 -B 2 "recv.*==.*-1\|read.*==.*-1\|recv.*<=.*0\|read.*<=.*0" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null)
echo "$READ_ERRORS"
echo ""

# =============================================================================
# 3. VERIFICAR MANEJO DE ERRORES EN WRITE/SEND
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando manejo de errores en write/send:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 5 -B 2 \"send.*==.*-1\\|write.*==.*-1\\|send.*<=.*0\\|write.*<=.*0\" $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

WRITE_ERRORS=$(grep -A 5 -B 2 "send.*==.*-1\|write.*==.*-1\|send.*<=.*0\|write.*<=.*0" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null)
echo "$WRITE_ERRORS"
echo ""

# =============================================================================
# 4. VERIFICAR ELIMINACIÓN DE CLIENTES
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando eliminación de clientes con errores:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"close\\|remove\\|disconnect\\|erase\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

CLIENT_REMOVAL=$(grep -rn "close\|remove\|disconnect\|erase" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$CLIENT_REMOVAL" | head -8
TOTAL_REMOVAL=$(echo "$CLIENT_REMOVAL" | wc -l)
if [ "$TOTAL_REMOVAL" -gt 8 ]; then
    echo "... ($TOTAL_REMOVAL referencias en total)"
fi

echo ""

HAS_CLOSE=$(echo "$CLIENT_REMOVAL" | grep -c "close(" || echo "0")
HAS_REMOVE=$(echo "$CLIENT_REMOVAL" | grep -c "remove\|erase" || echo "0")

echo -e "${YELLOW}📊 Eliminación encontrada: close($HAS_CLOSE) remove/erase($HAS_REMOVE)${NC}"

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ -n "$READ_ERRORS" ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ -n "$WRITE_ERRORS" ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_CLOSE" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 3 ]; then
    echo -e "${GREEN}✅ CORRECTO: Manejo de errores implementado${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Manejo de errores incompleto${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Cómo manejan los errores en operaciones de socket?${NC}"
echo ""

echo -e "${BLUE}1. 📥 ¿Qué hacen cuando recv() o read() falla?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Verificamos si recv()/read() retorna -1 (error) o 0 (desconexión)."
echo -e "    En ambos casos, cerramos el socket y eliminamos el cliente"
echo -e "    de nuestras estructuras de datos'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 10 -B 2 'if.*recv.*-1\\|if.*recv.*<=.*0' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}2. 📤 ¿Qué hacen cuando send() o write() falla?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Si send()/write() retorna -1, verificamos el error."
echo -e "    Si es un error fatal, cerramos la conexión y eliminamos"
echo -e "    el cliente del sistema'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 10 -B 2 'if.*send.*-1\\|if.*send.*<=.*0' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}3. 🗑️ ¿Cómo eliminan un cliente con errores?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Llamamos close() en el file descriptor, lo eliminamos"
echo -e "    de los fd_sets y borramos la información del cliente"
echo -e "    de nuestras estructuras (maps, vectors, etc.)'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'close.*client\\|clients.*erase\\|FD_CLR' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}4. 🔄 ¿Verifican tanto -1 como 0 en recv()?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, verificamos ambos valores:"
echo -e "    - recv() == -1: Error en la operación"
echo -e "    - recv() == 0: Cliente cerró la conexión limpiamente'${NC}"
echo ""

echo -e "${RED}   ⚠️  CRÍTICO:${NC}"
echo -e "${WHITE}   Verificar solo -1 O solo 0 no es suficiente - deben verificar ambos${NC}"
