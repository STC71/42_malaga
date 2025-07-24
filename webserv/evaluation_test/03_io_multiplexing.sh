#!/bin/bash

##############################################################################
# 03_io_multiplexing.sh - Verificación de función de multiplexación I/O
# EVALUACIÓN:
# "Ask what function the group used for I/O Multiplexing"
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
echo -e "  MULTIPLEXACIÓN I/O - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. IDENTIFICAR FUNCIÓN DE MULTIPLEXACIÓN
# =============================================================================

echo -e "${BLUE}🔍 1. Identificando función de multiplexación I/O:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"select\\|poll\\|epoll\\|kqueue\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

MULTIPLEX_RESULTS=$(grep -rn "select\|poll\|epoll\|kqueue" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)

if [ -z "$MULTIPLEX_RESULTS" ]; then
    echo -e "${RED}❌ ERROR: No se encontró función de multiplexación I/O${NC}"
    exit 1
fi

echo "$MULTIPLEX_RESULTS"
echo ""

# Identificar qué función específica usan
HAS_SELECT=$(echo "$MULTIPLEX_RESULTS" | grep -c "select(" || echo "0")
HAS_POLL=$(echo "$MULTIPLEX_RESULTS" | grep -c "poll(" || echo "0")
HAS_EPOLL=$(echo "$MULTIPLEX_RESULTS" | grep -c "epoll" || echo "0")
HAS_KQUEUE=$(echo "$MULTIPLEX_RESULTS" | grep -c "kqueue" || echo "0")

echo -e "${YELLOW}📊 Funciones encontradas:${NC}"
echo -e "${WHITE}   select(): $HAS_SELECT llamadas${NC}"
echo -e "${WHITE}   poll(): $HAS_POLL llamadas${NC}"
echo -e "${WHITE}   epoll: $HAS_EPOLL referencias${NC}"
echo -e "${WHITE}   kqueue: $HAS_KQUEUE referencias${NC}"

# Determinar función principal
MAIN_FUNCTION=""
if [ "$HAS_SELECT" -gt 0 ]; then
    MAIN_FUNCTION="select()"
elif [ "$HAS_POLL" -gt 0 ]; then
    MAIN_FUNCTION="poll()"
elif [ "$HAS_EPOLL" -gt 0 ]; then
    MAIN_FUNCTION="epoll"
elif [ "$HAS_KQUEUE" -gt 0 ]; then
    MAIN_FUNCTION="kqueue"
fi

echo ""
if [ -n "$MAIN_FUNCTION" ]; then
    echo -e "${GREEN}✅ FUNCIÓN PRINCIPAL DETECTADA: $MAIN_FUNCTION${NC}"
else
    echo -e "${RED}❌ ERROR: No se pudo determinar la función principal${NC}"
fi

# =============================================================================
# 2. VERIFICAR CONFIGURACIÓN DE FILE DESCRIPTORS
# =============================================================================

echo ""
echo -e "${BLUE}🔍 2. Verificando configuración de file descriptors:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"FD_ZERO\\|FD_SET\\|FD_ISSET\\|fd_set\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

FD_RESULTS=$(grep -rn "FD_ZERO\|FD_SET\|FD_ISSET\|fd_set" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$FD_RESULTS" | head -8
TOTAL_FD=$(echo "$FD_RESULTS" | wc -l)
if [ "$TOTAL_FD" -gt 8 ]; then
    echo "... ($TOTAL_FD líneas en total)"
fi

echo ""

HAS_FD_ZERO=$(echo "$FD_RESULTS" | grep -c "FD_ZERO" || echo "0")
HAS_FD_SET=$(echo "$FD_RESULTS" | grep -c "FD_SET" || echo "0")
HAS_FD_ISSET=$(echo "$FD_RESULTS" | grep -c "FD_ISSET" || echo "0")

echo -e "${YELLOW}📊 Macros encontradas: FD_ZERO($HAS_FD_ZERO) FD_SET($HAS_FD_SET) FD_ISSET($HAS_FD_ISSET)${NC}"

# =============================================================================
# 3. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ -n "$MAIN_FUNCTION" ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_FD_ZERO" -gt 0 ] && [ "$HAS_FD_SET" -gt 0 ] && [ "$HAS_FD_ISSET" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo ""
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
echo -e "${WHITE}¿Qué función han usado para multiplexación I/O?${NC}"
echo ""

echo -e "${BLUE}1. 🔧 ¿Qué función de multiplexación I/O utilizan?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
if [ "$MAIN_FUNCTION" = "select()" ]; then
    echo -e "${WHITE}   'Utilizamos select() porque es portable, estándar POSIX"
    echo -e "    y adecuado para nuestro proyecto. Permite monitorear múltiples"
    echo -e "    file descriptors simultáneamente'${NC}"
elif [ "$MAIN_FUNCTION" = "poll()" ]; then
    echo -e "${WHITE}   'Utilizamos poll() porque es más eficiente que select()"
    echo -e "    para muchos descriptors y no tiene límite FD_SETSIZE'${NC}"
elif [ "$MAIN_FUNCTION" = "epoll" ]; then
    echo -e "${WHITE}   'Utilizamos epoll porque es muy eficiente en Linux"
    echo -e "    para gran cantidad de conexiones simultáneas'${NC}"
else
    echo -e "${WHITE}   'Utilizamos [FUNCIÓN DETECTADA: $MAIN_FUNCTION]'${NC}"
fi
echo ""

echo -e "${BLUE}2. ⚙️ ¿Cómo configuran los file descriptors?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Usamos FD_ZERO para limpiar los sets, FD_SET para añadir"
echo -e "    descriptors y FD_ISSET para verificar cuáles están listos"
echo -e "    después de select()'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'FD_ZERO\\|FD_SET.*server\\|FD_SET.*client' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}3. 📊 ¿Por qué eligieron esta función?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Elegimos esta función porque [razones técnicas específicas"
echo -e "    como portabilidad, rendimiento, simplicidad, etc.]'${NC}"
echo ""

echo -e "${YELLOW}   📋 Función detectada automáticamente:${NC}"
echo -e "${WHITE}   Su proyecto utiliza: ${GREEN}$MAIN_FUNCTION${NC}"
