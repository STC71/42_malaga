#!/bin/bash

##############################################################################
# 02_http_basics.sh - Verificación de conceptos básicos de servidor HTTP
# EVALUACIÓN:
# "Ask explanations about the basics of an HTTP server"
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
echo -e "  CONCEPTOS BÁSICOS HTTP - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR IMPLEMENTACIÓN DE MÉTODOS HTTP
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando métodos HTTP implementados:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"GET\\|POST\\|DELETE\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

HTTP_METHODS=$(grep -rn "GET\|POST\|DELETE" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)
echo "$HTTP_METHODS" | head -10
TOTAL_HTTP=$(echo "$HTTP_METHODS" | wc -l)
if [ "$TOTAL_HTTP" -gt 10 ]; then
    echo "... ($TOTAL_HTTP líneas en total)"
fi

echo ""

HAS_GET=$(echo "$HTTP_METHODS" | grep -c "GET" || echo "0")
HAS_POST=$(echo "$HTTP_METHODS" | grep -c "POST" || echo "0")
HAS_DELETE=$(echo "$HTTP_METHODS" | grep -c "DELETE" || echo "0")

echo -e "${YELLOW}📊 Métodos encontrados: GET($HAS_GET) POST($HAS_POST) DELETE($HAS_DELETE)${NC}"

# =============================================================================
# 2. VERIFICAR PARSING DE HEADERS HTTP
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando parsing de headers HTTP:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"Content-Type\\|Content-Length\\|Host\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

HEADERS_RESULTS=$(grep -rn "Content-Type\|Content-Length\|Host" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$HEADERS_RESULTS" | head -5
TOTAL_HEADERS=$(echo "$HEADERS_RESULTS" | wc -l)
if [ "$TOTAL_HEADERS" -gt 5 ]; then
    echo "... ($TOTAL_HEADERS líneas en total)"
fi

echo ""

HAS_CONTENT_TYPE=$(echo "$HEADERS_RESULTS" | grep -c "Content-Type" || echo "0")
HAS_CONTENT_LENGTH=$(echo "$HEADERS_RESULTS" | grep -c "Content-Length" || echo "0")
HAS_HOST=$(echo "$HEADERS_RESULTS" | grep -c "Host" || echo "0")

echo -e "${YELLOW}📊 Headers encontrados: Content-Type($HAS_CONTENT_TYPE) Content-Length($HAS_CONTENT_LENGTH) Host($HAS_HOST)${NC}"

# =============================================================================
# 3. VERIFICAR CÓDIGOS DE ESTADO HTTP
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando códigos de estado HTTP:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"200\\|404\\|500\\|400\\|403\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

STATUS_RESULTS=$(grep -rn "200\|404\|500\|400\|403" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$STATUS_RESULTS" | head -8
TOTAL_STATUS=$(echo "$STATUS_RESULTS" | wc -l)
if [ "$TOTAL_STATUS" -gt 8 ]; then
    echo "... ($TOTAL_STATUS líneas en total)"
fi

echo ""

HAS_200=$(echo "$STATUS_RESULTS" | grep -c "200" || echo "0")
HAS_404=$(echo "$STATUS_RESULTS" | grep -c "404" || echo "0")
HAS_500=$(echo "$STATUS_RESULTS" | grep -c "500" || echo "0")

echo -e "${YELLOW}📊 Códigos encontrados: 200($HAS_200) 404($HAS_404) 500($HAS_500)${NC}"

# =============================================================================
# 4. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$HAS_GET" -gt 0 ] && [ "$HAS_POST" -gt 0 ] && [ "$HAS_DELETE" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_CONTENT_TYPE" -gt 0 ] && [ "$HAS_CONTENT_LENGTH" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_200" -gt 0 ] && [ "$HAS_404" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 3 ]; then
    echo -e "${GREEN}✅ CORRECTO: Implementación HTTP básica presente${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Implementación HTTP incompleta${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden explicar los conceptos básicos de su servidor HTTP?${NC}"
echo ""

echo -e "${BLUE}1. 🌐 ¿Qué es un servidor HTTP y cómo funciona?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Un servidor HTTP es un programa que escucha peticiones"
echo -e "    HTTP, las procesa y devuelve respuestas HTTP apropiadas."
echo -e "    Funciona en el modelo cliente-servidor usando TCP/IP'${NC}"
echo ""

echo -e "${BLUE}2. 📝 ¿Qué métodos HTTP han implementado?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Hemos implementado GET (obtener recursos), POST (enviar datos)"
echo -e "    y DELETE (eliminar recursos). Cada método tiene su propósito específico'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 10 -B 2 'method.*GET\\|method.*POST\\|method.*DELETE' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}3. 📋 ¿Cómo procesan los headers HTTP?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Parseamos headers como Content-Type, Content-Length, Host..."
echo -e "    Cada header tiene información específica para procesar la request'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 5 -B 2 'getHeader\\|parseHeader\\|Content-' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${BLUE}4. 🔢 ¿Qué códigos de estado HTTP manejan?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Manejamos códigos como 200 (OK), 404 (Not Found),"
echo -e "    500 (Internal Server Error), 400 (Bad Request), etc.'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -A 3 -B 1 'status.*=.*[0-9][0-9][0-9]\\|setStatus' $SEARCH_DIR/srcs/*.cpp${NC}"
echo ""

echo -e "${YELLOW}   📋 Nota importante:${NC}"
echo -e "${WHITE}   Durante la evaluación, cualquier código de estado HTTP incorrecto"
echo -e "   resultará en la pérdida de puntos relacionados${NC}"
