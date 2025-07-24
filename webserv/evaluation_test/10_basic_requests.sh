#!/bin/bash

##############################################################################
# 10_basic_requests.sh - Verificación de requests básicos
# EVALUACIÓN:
# "GET, POST and DELETE requests should work. UNKNOWN requests should not crash"
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
echo -e "  REQUESTS BÁSICOS - VERIFICACIÓN"
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

echo -e "${BLUE}🔍 1. Verificando implementación de métodos HTTP:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -A 5 -B 2 \"GET\\|POST\\|DELETE\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

HTTP_IMPL=$(grep -A 5 -B 2 "GET\|POST\|DELETE" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$HTTP_IMPL" | head -15
TOTAL_IMPL=$(echo "$HTTP_IMPL" | wc -l)
if [ "$TOTAL_IMPL" -gt 15 ]; then
    echo "... ($TOTAL_IMPL líneas en total)"
fi

echo ""

HAS_GET_IMPL=$(echo "$HTTP_IMPL" | grep -c "GET" || echo "0")
HAS_POST_IMPL=$(echo "$HTTP_IMPL" | grep -c "POST" || echo "0")
HAS_DELETE_IMPL=$(echo "$HTTP_IMPL" | grep -c "DELETE" || echo "0")

echo -e "${YELLOW}📊 Implementaciones encontradas: GET($HAS_GET_IMPL) POST($HAS_POST_IMPL) DELETE($HAS_DELETE_IMPL)${NC}"

# =============================================================================
# 2. VERIFICAR MANEJO DE MÉTODOS DESCONOCIDOS
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando manejo de métodos desconocidos:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"405\\|Method.*Not.*Allowed\\|unknown.*method\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

UNKNOWN_METHODS=$(grep -rn "405\|Method.*Not.*Allowed\|unknown.*method" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
if [ -n "$UNKNOWN_METHODS" ]; then
    echo "$UNKNOWN_METHODS"
    echo -e "${GREEN}✅ Se encontró manejo de métodos desconocidos${NC}"
    HAS_UNKNOWN_HANDLING=1
else
    echo -e "${YELLOW}⚠️  No se encontró manejo específico de métodos desconocidos${NC}"
    HAS_UNKNOWN_HANDLING=0
fi

echo ""

# =============================================================================
# 3. VERIFICAR CÓDIGOS DE ESTADO APROPIADOS
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando códigos de estado HTTP:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"200\\|404\\|405\\|500\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

STATUS_CODES=$(grep -rn "200\|404\|405\|500" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$STATUS_CODES" | head -10
TOTAL_STATUS=$(echo "$STATUS_CODES" | wc -l)
if [ "$TOTAL_STATUS" -gt 10 ]; then
    echo "... ($TOTAL_STATUS referencias en total)"
fi

echo ""

HAS_200=$(echo "$STATUS_CODES" | grep -c "200" || echo "0")
HAS_404=$(echo "$STATUS_CODES" | grep -c "404" || echo "0")
HAS_405=$(echo "$STATUS_CODES" | grep -c "405" || echo "0")
HAS_500=$(echo "$STATUS_CODES" | grep -c "500" || echo "0")

echo -e "${YELLOW}📊 Códigos de estado: 200($HAS_200) 404($HAS_404) 405($HAS_405) 500($HAS_500)${NC}"

# =============================================================================
# 4. VERIFICAR UPLOAD/DOWNLOAD DE ARCHIVOS
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando capacidad de upload/download:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"upload\\|download\\|file.*transfer\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

FILE_TRANSFER=$(grep -rn "upload\|download\|file.*transfer" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
if [ -n "$FILE_TRANSFER" ]; then
    echo "$FILE_TRANSFER"
    HAS_FILE_TRANSFER=1
else
    echo -e "${YELLOW}No se encontraron referencias específicas a upload/download${NC}"
    HAS_FILE_TRANSFER=0
fi

echo ""

# Verificar directorio de uploads
UPLOAD_DIR=""
if [ -d "$SEARCH_DIR/Uploads" ]; then
    UPLOAD_DIR="$SEARCH_DIR/Uploads"
elif [ -d "$SEARCH_DIR/www/Uploads" ]; then
    UPLOAD_DIR="$SEARCH_DIR/www/Uploads"
fi

if [ -n "$UPLOAD_DIR" ]; then
    echo -e "${GREEN}✅ Directorio de uploads encontrado: $UPLOAD_DIR${NC}"
    ls -la "$UPLOAD_DIR" 2>/dev/null || echo "Directorio vacío o sin permisos"
else
    echo -e "${YELLOW}⚠️  No se encontró directorio de uploads específico${NC}"
fi

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

echo ""
CRITERIA_PASSED=0
[ "$HAS_GET_IMPL" -gt 0 ] && [ "$HAS_POST_IMPL" -gt 0 ] && [ "$HAS_DELETE_IMPL" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_200" -gt 0 ] && [ "$HAS_404" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_UNKNOWN_HANDLING" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -ge 2 ]; then
    echo -e "${GREEN}✅ CORRECTO: Implementación de requests básicos presente${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Implementación de requests incompleta${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar que los requests básicos funcionan?${NC}"
echo ""

echo -e "${BLUE}1. 📥 ¿Funciona el método GET?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, GET obtiene recursos del servidor. Retorna 200 si"
echo -e "    el recurso existe, 404 si no existe'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para probar:${NC}"
echo -e "${CYAN}   curl -v http://localhost:8080/index.html${NC}"
echo -e "${CYAN}   telnet localhost 8080${NC}"
echo -e "${WHITE}   GET /index.html HTTP/1.1${NC}"
echo -e "${WHITE}   Host: localhost${NC}"
echo ""

echo -e "${BLUE}2. 📤 ¿Funciona el método POST?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, POST envía datos al servidor. Procesamos el body"
echo -e "    y retornamos el código de estado apropiado'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para probar:${NC}"
echo -e "${CYAN}   curl -X POST -d \"test data\" http://localhost:8080/upload${NC}"
echo ""

echo -e "${BLUE}3. 🗑️ ¿Funciona el método DELETE?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, DELETE elimina recursos del servidor. Verificamos"
echo -e "    permisos y retornamos el código apropiado'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para probar:${NC}"
echo -e "${CYAN}   curl -X DELETE http://localhost:8080/file.txt${NC}"
echo ""

echo -e "${BLUE}4. ❓ ¿Qué pasa con métodos desconocidos?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Los métodos desconocidos no crashean el servidor."
echo -e "    Retornamos 405 Method Not Allowed o similar'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para probar:${NC}"
echo -e "${CYAN}   curl -X PATCH http://localhost:8080/test${NC}"
echo -e "${CYAN}   curl -X UNKNOWN http://localhost:8080/test${NC}"
echo ""

echo -e "${BLUE}5. 📁 ¿Pueden subir y descargar archivos?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, podemos subir archivos con POST y descargarlos"
echo -e "    con GET. Los archivos se almacenan en directorio específico'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para probar:${NC}"
echo -e "${CYAN}   curl -X POST -F \"file=@test.txt\" http://localhost:8080/upload${NC}"
echo -e "${CYAN}   curl -O http://localhost:8080/uploads/test.txt${NC}"
echo ""

if [ -n "$UPLOAD_DIR" ]; then
    echo -e "${YELLOW}   📁 Directorio de uploads detectado:${NC}"
    echo -e "${WHITE}   $UPLOAD_DIR${NC}"
fi

echo ""
echo -e "${YELLOW}   📋 Importante:${NC}"
echo -e "${WHITE}   Para cada test deben recibir el código de estado apropiado${NC}"
