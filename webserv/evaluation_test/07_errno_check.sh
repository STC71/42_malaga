#!/bin/bash

##############################################################################
# 07_errno_check.sh - Verificación crítica de errno (PUNTO ELIMINATORIO)
# EVALUACIÓN:
# "If errno is checked after read/recv/write/send, the grade is 0 
#  and the evaluation process ends now"
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

echo -e "${RED}=========================================="
echo -e "  ⚠️  VERIFICACIÓN CRÍTICA DE ERRNO ⚠️"
echo -e "==========================================${NC}"
echo ""
echo -e "${RED}🚨 ATENCIÓN: Si se encuentra errno después de operaciones de socket,"
echo -e "   la nota será 0 y la evaluación terminará inmediatamente${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. BUSCAR USO DE ERRNO DESPUÉS DE OPERACIONES DE SOCKET
# =============================================================================

echo -e "${BLUE}🔍 1. Buscando uso de errno después de read/recv/write/send:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 10 -B 5 \"read\\|recv\\|write\\|send\" $SEARCH_DIR/srcs/*.cpp | grep -A 5 -B 5 errno${NC}"
echo ""

# Buscar errno en contexto de operaciones de socket
ERRNO_CONTEXT=$(grep -A 10 -B 5 "read\|recv\|write\|send" "$SEARCH_DIR"/srcs/*.cpp 2>/dev/null | grep -A 5 -B 5 "errno" 2>/dev/null)

if [ -n "$ERRNO_CONTEXT" ]; then
    echo -e "${RED}❌ ERRNO ENCONTRADO EN CONTEXTO DE SOCKET:${NC}"
    echo "$ERRNO_CONTEXT"
    echo ""
    echo -e "${RED}🚨 FALLO CRÍTICO: Se encontró uso de errno${NC}"
    ERRNO_FOUND=1
else
    echo -e "${GREEN}✅ No se encontró uso de errno en contexto de socket${NC}"
    ERRNO_FOUND=0
fi

echo ""

# =============================================================================
# 2. BÚSQUEDA ESPECÍFICA DE ERRNO
# =============================================================================

echo -e "${BLUE}🔍 2. Búsqueda específica de errno en todo el código:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"errno\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

ERRNO_ALL=$(grep -rn "errno" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)

if [ -n "$ERRNO_ALL" ]; then
    echo -e "${YELLOW}⚠️  Se encontraron referencias a errno:${NC}"
    echo "$ERRNO_ALL"
    echo ""
    
    # Verificar si está en includes o comentarios
    ERRNO_INCLUDES=$(echo "$ERRNO_ALL" | grep -c "#include\|//" || echo "0")
    ERRNO_TOTAL=$(echo "$ERRNO_ALL" | wc -l)
    ERRNO_ACTUAL=$((ERRNO_TOTAL - ERRNO_INCLUDES))
    
    echo -e "${YELLOW}📊 Referencias errno: Total($ERRNO_TOTAL) Includes/Comentarios($ERRNO_INCLUDES) Uso real($ERRNO_ACTUAL)${NC}"
    
    if [ "$ERRNO_ACTUAL" -gt 0 ]; then
        echo -e "${RED}❌ POSIBLE USO REAL DE ERRNO DETECTADO${NC}"
        ERRNO_FOUND=1
    fi
else
    echo -e "${GREEN}✅ No se encontraron referencias a errno${NC}"
fi

# =============================================================================
# 3. VERIFICAR PERROR Y STRERROR
# =============================================================================

echo ""
echo -e "${BLUE}🔍 3. Verificando perror() y strerror():${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"perror\\|strerror\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

ERROR_FUNCS=$(grep -rn "perror\|strerror" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)

if [ -n "$ERROR_FUNCS" ]; then
    echo -e "${YELLOW}⚠️  Se encontraron funciones relacionadas con errno:${NC}"
    echo "$ERROR_FUNCS"
    echo ""
    HAS_PERROR=$(echo "$ERROR_FUNCS" | grep -c "perror" || echo "0")
    HAS_STRERROR=$(echo "$ERROR_FUNCS" | grep -c "strerror" || echo "0")
    echo -e "${YELLOW}📊 Funciones encontradas: perror($HAS_PERROR) strerror($HAS_STRERROR)${NC}"
    
    if [ "$HAS_PERROR" -gt 0 ] || [ "$HAS_STRERROR" -gt 0 ]; then
        echo -e "${RED}❌ FUNCIONES QUE USAN ERRNO DETECTADAS${NC}"
        ERRNO_FOUND=1
    fi
else
    echo -e "${GREEN}✅ No se encontraron perror() ni strerror()${NC}"
fi

# =============================================================================
# 4. EVALUACIÓN FINAL CRÍTICA
# =============================================================================

echo ""
echo -e "${RED}=========================================="
echo -e "  🚨 EVALUACIÓN CRÍTICA FINAL 🚨"
echo -e "==========================================${NC}"
echo ""

if [ "$ERRNO_FOUND" -eq 1 ]; then
    echo -e "${RED}💀 FALLO CRÍTICO DETECTADO${NC}"
    echo -e "${RED}❌ Se encontró uso de errno en el código${NC}"
    echo -e "${RED}🚨 RESULTADO: NOTA = 0${NC}"
    echo -e "${RED}🛑 LA EVALUACIÓN DEBE TERMINAR AHORA${NC}"
else
    echo -e "${GREEN}🎉 VERIFICACIÓN EXITOSA${NC}"
    echo -e "${GREEN}✅ No se detectó uso de errno${NC}"
    echo -e "${GREEN}🚀 La evaluación puede continuar${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Por qué no deben usar errno en su servidor?${NC}"
echo ""

echo -e "${BLUE}1. 🚫 ¿Por qué está prohibido errno?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'errno es una variable global que puede ser modificada"
echo -e "    por cualquier función del sistema, causando race conditions"
echo -e "    y comportamiento impredecible en servidores'${NC}"
echo ""

echo -e "${BLUE}2. 🔧 ¿Cómo manejan errores sin errno?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Verificamos directamente los valores de retorno:"
echo -e "    -1 para errores, 0 para desconexión en recv(),"
echo -e "    sin necesidad de consultar errno'${NC}"
echo ""

echo -e "${BLUE}3. ✅ ¿Qué es un manejo correcto de errores?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Verificamos valores de retorno específicos y actuamos"
echo -e "    en consecuencia: cerrar conexiones, limpiar recursos,"
echo -e "    sin depender de variables globales como errno'${NC}"
echo ""

if [ "$ERRNO_FOUND" -eq 1 ]; then
    echo -e "${RED}   ⚠️  ACCIÓN REQUERIDA:${NC}"
    echo -e "${WHITE}   Deben eliminar todo uso de errno del código antes de continuar${NC}"
    echo ""
    echo -e "${RED}   💻 Ubicaciones encontradas arriba ⬆️${NC}"
fi
