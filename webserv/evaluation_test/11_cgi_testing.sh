#!/bin/bash

##############################################################################
# 11_cgi_testing.sh - Verificación de funcionalidad CGI
# EVALUACIÓN:
# "Check CGI - The server is working fine using a CGI"
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
echo -e "    VERIFICACIÓN CGI - FUNCIONALIDAD"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR IMPLEMENTACIÓN CGI EN CÓDIGO
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando implementación CGI en el código:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"CGI\\|cgi\\|execve\\|fork\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

CGI_CODE=$(grep -rn "CGI\|cgi\|execve\|fork" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)
echo "$CGI_CODE" | head -10
TOTAL_CGI=$(echo "$CGI_CODE" | wc -l)
if [ "$TOTAL_CGI" -gt 10 ]; then
    echo "... ($TOTAL_CGI líneas en total)"
fi

echo ""

HAS_CGI_CLASS=$(echo "$CGI_CODE" | grep -c "class.*CGI\|CGI.*class" || echo "0")
HAS_EXECVE=$(echo "$CGI_CODE" | grep -c "execve" || echo "0")
HAS_FORK=$(echo "$CGI_CODE" | grep -c "fork" || echo "0")

echo -e "${YELLOW}📊 CGI encontrado: Clase CGI($HAS_CGI_CLASS) execve($HAS_EXECVE) fork($HAS_FORK)${NC}"

# =============================================================================
# 2. VERIFICAR ARCHIVOS CGI DISPONIBLES
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando archivos CGI disponibles:${NC}"
echo ""

CGI_DIR_FOUND=""
if [ -d "$SEARCH_DIR/www/cgi-bin" ]; then
    CGI_DIR_FOUND="$SEARCH_DIR/www/cgi-bin"
elif [ -d "$SEARCH_DIR/cgi-bin" ]; then
    CGI_DIR_FOUND="$SEARCH_DIR/cgi-bin"
elif [ -d "$SEARCH_DIR/www2/cgi-bin" ]; then
    CGI_DIR_FOUND="$SEARCH_DIR/www2/cgi-bin"
fi

if [ -n "$CGI_DIR_FOUND" ]; then
    echo -e "${GREEN}✅ Directorio CGI encontrado: $CGI_DIR_FOUND${NC}"
    echo ""
    echo -e "${PURPLE}💻 Listando archivos CGI:${NC}"
    ls -la "$CGI_DIR_FOUND"
    
    CGI_FILES=$(find "$CGI_DIR_FOUND" -type f \( -name "*.py" -o -name "*.php" -o -name "*.pl" \) 2>/dev/null)
    CGI_COUNT=$(echo "$CGI_FILES" | grep -v "^$" | wc -l)
    
    echo ""
    echo -e "${YELLOW}📊 Archivos CGI encontrados: $CGI_COUNT${NC}"
    
    # Verificar tipos de CGI
    PYTHON_CGI=$(echo "$CGI_FILES" | grep -c "\.py$" || echo "0")
    PHP_CGI=$(echo "$CGI_FILES" | grep -c "\.php$" || echo "0")
    PERL_CGI=$(echo "$CGI_FILES" | grep -c "\.pl$" || echo "0")
    
    echo -e "${YELLOW}   - Python scripts: $PYTHON_CGI${NC}"
    echo -e "${YELLOW}   - PHP scripts: $PHP_CGI${NC}"
    echo -e "${YELLOW}   - Perl scripts: $PERL_CGI${NC}"
else
    echo -e "${RED}❌ No se encontró directorio cgi-bin${NC}"
    CGI_COUNT=0
fi

# =============================================================================
# 3. VERIFICAR VARIABLES DE ENTORNO CGI
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando variables de entorno CGI:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"SCRIPT_NAME\\|PATH_INFO\\|QUERY_STRING\\|REQUEST_METHOD\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

ENV_VARS=$(grep -rn "SCRIPT_NAME\|PATH_INFO\|QUERY_STRING\|REQUEST_METHOD\|CONTENT_TYPE\|CONTENT_LENGTH" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$ENV_VARS" | head -8
TOTAL_ENV=$(echo "$ENV_VARS" | wc -l)
if [ "$TOTAL_ENV" -gt 8 ]; then
    echo "... ($TOTAL_ENV líneas en total)"
fi

echo ""

HAS_SCRIPT_NAME=$(echo "$ENV_VARS" | grep -c "SCRIPT_NAME" || echo "0")
HAS_REQUEST_METHOD=$(echo "$ENV_VARS" | grep -c "REQUEST_METHOD" || echo "0")
HAS_QUERY_STRING=$(echo "$ENV_VARS" | grep -c "QUERY_STRING" || echo "0")

echo -e "${YELLOW}📊 Variables ENV: SCRIPT_NAME($HAS_SCRIPT_NAME) REQUEST_METHOD($HAS_REQUEST_METHOD) QUERY_STRING($HAS_QUERY_STRING)${NC}"

# =============================================================================
# 4. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$HAS_CGI_CLASS" -gt 0 ] && [ "$HAS_EXECVE" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$CGI_COUNT" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_SCRIPT_NAME" -gt 0 ] && [ "$HAS_REQUEST_METHOD" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 3 ]; then
    echo -e "${GREEN}✅ CORRECTO: Implementación CGI presente${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Implementación CGI incompleta${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar que su servidor funciona correctamente con CGI?${NC}"
echo ""

echo -e "${BLUE}1. 🔧 ¿Cómo han implementado la ejecución de CGI?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Usamos fork() para crear un proceso hijo y execve() para ejecutar"
echo -e "    el script CGI. Configuramos las variables de entorno necesarias'${NC}"
echo ""

echo -e "${BLUE}2. 📂 ¿En qué directorio se ejecutan los scripts CGI?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Los scripts se ejecutan en el directorio correcto para acceso"
echo -e "    a archivos con rutas relativas. Cambiamos el working directory'${NC}"
echo ""

echo -e "${BLUE}3. 🌐 ¿Qué variables de entorno CGI configuran?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos REQUEST_METHOD, SCRIPT_NAME, PATH_INFO, QUERY_STRING,"
echo -e "    CONTENT_TYPE, CONTENT_LENGTH, etc.'${NC}"
echo ""

echo -e "${BLUE}4. 🧪 ¿Pueden mostrar un test con GET y POST?${NC}"
echo ""
echo -e "${GREEN}   ✅ Comandos sugeridos para probar:${NC}"
if [ -n "$CGI_DIR_FOUND" ] && [ "$CGI_COUNT" -gt 0 ]; then
    FIRST_CGI=$(echo "$CGI_FILES" | head -1 | xargs basename)
    echo -e "${CYAN}   curl http://localhost:8080/cgi-bin/$FIRST_CGI${NC}"
    echo -e "${CYAN}   curl -X POST -d 'test=data' http://localhost:8080/cgi-bin/$FIRST_CGI${NC}"
else
    echo -e "${CYAN}   curl http://localhost:8080/cgi-bin/test.py${NC}"
    echo -e "${CYAN}   curl -X POST -d 'test=data' http://localhost:8080/cgi-bin/test.py${NC}"
fi
echo ""

echo -e "${BLUE}5. ⚠️ ¿Cómo manejan errores en CGI?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Si el script falla, devolvemos error 500. Si no existe, 404."
echo -e "    Monitoreamos el proceso hijo y manejamos timeouts'${NC}"
echo ""

echo -e "${RED}   🚨 IMPORTANTE PARA LA EVALUACIÓN:${NC}"
echo -e "${WHITE}   - El evaluador debe probar CGI con GET y POST"
echo -e "   - Probar archivos con errores para ver el manejo de errores"
echo -e "   - El servidor nunca debe crashear, errores deben ser visibles${NC}"
