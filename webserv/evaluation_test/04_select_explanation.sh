#!/bin/bash

##############################################################################
# 04_select_explanation.sh - Explicación de cómo funciona select()
# EVALUACIÓN:
# "Ask for an explanation of how does select() (or equivalent) work"
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
echo -e "  CÓMO FUNCIONA SELECT() - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR IMPLEMENTACIÓN DE SELECT()
# =============================================================================

echo -e "${BLUE}🔍 1. Analizando implementación de select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 10 -B 5 \"select(\" $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

SELECT_IMPL=$(grep -A 10 -B 5 "select(" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null)
echo "$SELECT_IMPL"
echo ""

# =============================================================================
# 2. VERIFICAR CONFIGURACIÓN DE TIMEOUT
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando configuración de timeout:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"timeout\\|timeval\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

TIMEOUT_RESULTS=$(grep -rn "timeout\|timeval" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$TIMEOUT_RESULTS" | head -5
TOTAL_TIMEOUT=$(echo "$TIMEOUT_RESULTS" | wc -l)
if [ "$TOTAL_TIMEOUT" -gt 5 ]; then
    echo "... ($TOTAL_TIMEOUT líneas en total)"
fi

echo ""

HAS_TIMEOUT=$(echo "$TIMEOUT_RESULTS" | grep -c "timeout" || echo "0")
HAS_TIMEVAL=$(echo "$TIMEOUT_RESULTS" | grep -c "timeval" || echo "0")

echo -e "${YELLOW}📊 Timeout encontrado: timeout($HAS_TIMEOUT) timeval($HAS_TIMEVAL)${NC}"

# =============================================================================
# 3. VERIFICAR MANEJO DE ERRORES
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando manejo de errores de select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 5 -B 2 \"select.*==.*-1\\|EINTR\\|EAGAIN\" $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

ERROR_RESULTS=$(grep -A 5 -B 2 "select.*==.*-1\|EINTR\|EAGAIN" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null)
echo "$ERROR_RESULTS"
echo ""

HAS_ERROR_CHECK=$(echo "$ERROR_RESULTS" | grep -c "=.*-1\|< 0" || echo "0")
HAS_EINTR=$(echo "$ERROR_RESULTS" | grep -c "EINTR" || echo "0")

echo -e "${YELLOW}📊 Manejo de errores: Error check($HAS_ERROR_CHECK) EINTR($HAS_EINTR)${NC}"

# =============================================================================
# 4. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$HAS_TIMEOUT" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_ERROR_CHECK" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo ""
echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/2 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 2 ]; then
    echo -e "${GREEN}✅ CORRECTO: Implementación de select() completa${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Implementación de select() incompleta${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden explicar cómo funciona select() en su implementación?${NC}"
echo ""

echo -e "${BLUE}1. 🔧 ¿Qué hace select() exactamente?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'select() monitorea múltiples file descriptors y bloquea"
echo -e "    hasta que al menos uno esté listo para I/O. Permite manejar"
echo -e "    múltiples conexiones sin threads'${NC}"
echo ""

echo -e "${BLUE}2. 📋 ¿Qué parámetros le pasan a select()?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Pasamos: nfds (max fd + 1), readfds, writefds, exceptfds"
echo -e "    y timeout. Los fd_sets contienen los descriptors a monitorear'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 3 -B 1 'select.*max_fd\\|select.*nfds' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}3. ⏰ ¿Cómo manejan el timeout?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos un struct timeval para evitar bloqueo infinito."
echo -e "    Esto permite que el servidor responda a otras tareas periódicamente'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 3 -B 1 'timeval.*timeout\\|timeout.*tv_' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}4. 🚨 ¿Cómo manejan los errores de select()?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Verificamos si select() retorna -1, manejamos EINTR"
echo -e "    (señales del sistema) y otros errores apropiadamente'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'if.*select.*-1\\|errno.*EINTR' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}5. 🔄 ¿Qué sucede después de select()?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Después usamos FD_ISSET() para verificar qué descriptors"
echo -e "    están listos y procesamos cada uno (accept, read, write)'${NC}"
echo ""

echo -e "${YELLOW}   📋 Concepto clave:${NC}"
echo -e "${WHITE}   select() es el corazón de la multiplexación I/O - permite"
echo -e "   manejar múltiples conexiones de forma eficiente sin threads${NC}"
