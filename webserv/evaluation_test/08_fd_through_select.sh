#!/bin/bash

##############################################################################
# 08_fd_through_select.sh - Verificación de que todo I/O pasa por select()
# EVALUACIÓN:
# "Writing or reading ANY file descriptor without going through 
#  the select() (or equivalent) is strictly FORBIDDEN"
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
echo -e "  TODO I/O A TRAVÉS DE SELECT() - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. BUSCAR OPERACIONES I/O FUERA DE SELECT
# =============================================================================

echo -e "${BLUE}🔍 1. Buscando operaciones I/O potencialmente fuera de select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"read\\|write\\|recv\\|send\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

IO_OPERATIONS=$(grep -rn "read\|write\|recv\|send" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$IO_OPERATIONS" | head -12
TOTAL_IO=$(echo "$IO_OPERATIONS" | wc -l)
if [ "$TOTAL_IO" -gt 12 ]; then
    echo "... ($TOTAL_IO operaciones I/O en total)"
fi

echo ""

# =============================================================================
# 2. VERIFICAR UBICACIÓN DEL SELECT()
# =============================================================================

echo -e "${BLUE}🔍 2. Localizando el bucle principal con select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 20 -B 5 \"while.*true\\|while.*1\" $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

MAIN_LOOP=$(grep -A 20 -B 5 "while.*true\|while.*1" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null)
echo "$MAIN_LOOP" | head -15
TOTAL_LOOP=$(echo "$MAIN_LOOP" | wc -l)
if [ "$TOTAL_LOOP" -gt 15 ]; then
    echo "... ($TOTAL_LOOP líneas del bucle principal)"
fi

echo ""

# =============================================================================
# 3. VERIFICAR OPERACIONES I/O EN BUCLE PRINCIPAL
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando que I/O está dentro del bucle con select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 50 \"while.*true\" $SEARCH_DIR/srcs/*.cpp | grep \"recv\\|send\\|read\\|write\"${NC}"
echo ""

IO_IN_LOOP=$(grep -A 50 "while.*true\|while.*1" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null | grep "recv\|send\|read\|write" 2>/dev/null)
echo "$IO_IN_LOOP"
echo ""

HAS_IO_IN_LOOP=$(echo "$IO_IN_LOOP" | wc -l)
echo -e "${YELLOW}📊 Operaciones I/O dentro del bucle principal: $HAS_IO_IN_LOOP${NC}"

# =============================================================================
# 4. BUSCAR I/O FUERA DEL CONTEXTO DE SELECT
# =============================================================================

echo -e "${BLUE}🔍 4. Buscando posible I/O fuera del contexto de select():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -B 10 -A 2 \"recv\\|send\" $SEARCH_DIR/srcs/*.cpp | grep -v \"select\\|FD_ISSET\"${NC}"
echo ""

# Buscar I/O que no tenga select o FD_ISSET en el contexto
IO_WITHOUT_SELECT=$(grep -B 10 -A 2 "recv\|send" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null | grep -v "select\|FD_ISSET" 2>/dev/null)
if [ -n "$IO_WITHOUT_SELECT" ]; then
    echo -e "${YELLOW}⚠️  I/O potencialmente fuera de contexto select():${NC}"
    echo "$IO_WITHOUT_SELECT" | head -10
    if [ "$(echo "$IO_WITHOUT_SELECT" | wc -l)" -gt 10 ]; then
        echo "... (más líneas encontradas)"
    fi
    echo ""
    echo -e "${RED}❌ POSIBLE VIOLACIÓN: I/O sin select() detectado${NC}"
    VIOLATION_FOUND=1
else
    echo -e "${GREEN}✅ Todo I/O parece estar en contexto de select()${NC}"
    VIOLATION_FOUND=0
fi

# =============================================================================
# 5. VERIFICAR ARCHIVOS DE CONFIGURACIÓN
# =============================================================================

echo ""
echo -e "${BLUE}🔍 5. Verificando lectura de archivos de configuración:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"ifstream\\|fopen\\|open.*conf\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

CONFIG_IO=$(grep -rn "ifstream\|fopen\|open.*conf" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
if [ -n "$CONFIG_IO" ]; then
    echo "$CONFIG_IO"
    echo ""
    echo -e "${GREEN}ℹ️  Nota: La lectura de archivos de configuración está permitida${NC}"
else
    echo -e "${YELLOW}No se encontró lectura específica de archivos de configuración${NC}"
fi

# =============================================================================
# 6. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

echo ""
echo -e "${YELLOW}🎯 RESULTADO DE VERIFICACIÓN:${NC}"

if [ "$VIOLATION_FOUND" -eq 0 ] && [ "$HAS_IO_IN_LOOP" -gt 0 ]; then
    echo -e "${GREEN}✅ CORRECTO: Todo I/O parece pasar por select()${NC}"
else
    echo -e "${RED}❌ POSIBLE PROBLEMA: I/O fuera de select() detectado${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar que todo I/O pasa por select()?${NC}"
echo ""

echo -e "${BLUE}1. 🔄 ¿Dónde está su bucle principal?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Nuestro bucle principal está en [archivo:línea] y contiene"
echo -e "    select() seguido de verificaciones FD_ISSET() para"
echo -e "    procesar todas las operaciones I/O'${NC}"
echo ""

echo -e "${BLUE}2. 📋 ¿Todas las operaciones recv/send están después de FD_ISSET?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, cada recv() y send() está precedido por una verificación"
echo -e "    FD_ISSET() que confirma que el descriptor está listo"
echo -e "    según lo determinado por select()'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -B 5 -A 2 'recv\\|send' $SEARCH_DIR/srcs/*.cpp | grep 'FD_ISSET' -A 7${NC}"
echo ""

echo -e "${BLUE}3. 🚫 ¿No tienen I/O bloqueante en otros lugares?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'No hacemos ninguna operación I/O bloqueante fuera del"
echo -e "    contexto de select(). Todo I/O de red pasa por el"
echo -e "    bucle principal con multiplexación'${NC}"
echo ""

echo -e "${BLUE}4. 📁 ¿Qué pasa con archivos de configuración?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Los archivos de configuración se leen al inicio,"
echo -e "    antes del bucle principal. No son I/O de red y"
echo -e "    están permitidos fuera de select()'${NC}"
echo ""

echo -e "${RED}   ⚠️  REGLA ESTRICTA:${NC}"
echo -e "${WHITE}   Cualquier I/O de red fuera de select() está ESTRICTAMENTE PROHIBIDO${NC}"
