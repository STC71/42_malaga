#!/bin/bash

##############################################################################
# 12_browser_compatibility.sh - Verificación de compatibilidad con navegador
# EVALUACIÓN:
# "Check with a browser - Use the reference browser of the team"
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
echo -e "  COMPATIBILIDAD NAVEGADOR - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR ARCHIVOS ESTÁTICOS DISPONIBLES
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando archivos estáticos para servir:${NC}"
echo ""

STATIC_DIRS=()
if [ -d "$SEARCH_DIR/www" ]; then
    STATIC_DIRS+=("$SEARCH_DIR/www")
fi
if [ -d "$SEARCH_DIR/www2" ]; then
    STATIC_DIRS+=("$SEARCH_DIR/www2")
fi

for dir in "${STATIC_DIRS[@]}"; do
    echo -e "${GREEN}📁 Directorio encontrado: $dir${NC}"
    echo -e "${PURPLE}💻 Contenido:${NC}"
    ls -la "$dir" | head -10
    echo ""
done

# Buscar archivos HTML, CSS, JS
HTML_FILES=$(find "${STATIC_DIRS[@]}" -name "*.html" 2>/dev/null | wc -l)
CSS_FILES=$(find "${STATIC_DIRS[@]}" -name "*.css" 2>/dev/null | wc -l)
JS_FILES=$(find "${STATIC_DIRS[@]}" -name "*.js" 2>/dev/null | wc -l)
IMG_FILES=$(find "${STATIC_DIRS[@]}" \( -name "*.jpg" -o -name "*.png" -o -name "*.gif" \) 2>/dev/null | wc -l)

echo -e "${YELLOW}📊 Archivos estáticos: HTML($HTML_FILES) CSS($CSS_FILES) JS($JS_FILES) Imágenes($IMG_FILES)${NC}"

# =============================================================================
# 2. VERIFICAR MIME TYPES
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando MIME types implementados:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"text/html\\|text/css\\|image/\\|application/\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

MIME_RESULTS=$(grep -rn "text/html\|text/css\|image/\|application/\|text/plain" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$MIME_RESULTS" | head -8
TOTAL_MIME=$(echo "$MIME_RESULTS" | wc -l)
if [ "$TOTAL_MIME" -gt 8 ]; then
    echo "... ($TOTAL_MIME líneas en total)"
fi

echo ""

HAS_HTML_MIME=$(echo "$MIME_RESULTS" | grep -c "text/html" || echo "0")
HAS_CSS_MIME=$(echo "$MIME_RESULTS" | grep -c "text/css" || echo "0")
HAS_IMAGE_MIME=$(echo "$MIME_RESULTS" | grep -c "image/" || echo "0")

echo -e "${YELLOW}📊 MIME types: text/html($HAS_HTML_MIME) text/css($HAS_CSS_MIME) image/*($HAS_IMAGE_MIME)${NC}"

# =============================================================================
# 3. VERIFICAR DIRECTORY LISTING
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando directory listing:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"directory\\|listing\\|autoindex\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

DIR_LISTING=$(grep -rn "directory\|listing\|autoindex\|readdir" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$DIR_LISTING" | head -5
TOTAL_DIR=$(echo "$DIR_LISTING" | wc -l)
if [ "$TOTAL_DIR" -gt 5 ]; then
    echo "... ($TOTAL_DIR líneas en total)"
fi

echo ""

HAS_AUTOINDEX=$(echo "$DIR_LISTING" | grep -c "autoindex\|directory.*list\|readdir" || echo "0")

echo -e "${YELLOW}📊 Directory listing: Autoindex($HAS_AUTOINDEX)${NC}"

# =============================================================================
# 4. VERIFICAR REDIRECCIONES
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando redirecciones HTTP:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"301\\|302\\|redirect\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

REDIRECT_RESULTS=$(grep -rn "301\|302\|redirect\|Location:" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$REDIRECT_RESULTS" | head -5
TOTAL_REDIRECT=$(echo "$REDIRECT_RESULTS" | wc -l)
if [ "$TOTAL_REDIRECT" -gt 5 ]; then
    echo "... ($TOTAL_REDIRECT líneas en total)"
fi

echo ""

HAS_301=$(echo "$REDIRECT_RESULTS" | grep -c "301" || echo "0")
HAS_302=$(echo "$REDIRECT_RESULTS" | grep -c "302" || echo "0")
HAS_LOCATION=$(echo "$REDIRECT_RESULTS" | grep -c "Location" || echo "0")

echo -e "${YELLOW}📊 Redirecciones: 301($HAS_301) 302($HAS_302) Location header($HAS_LOCATION)${NC}"

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$HTML_FILES" -gt 0 ] && [ "$HAS_HTML_MIME" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_AUTOINDEX" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_301" -gt 0 ] || [ "$HAS_302" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -ge 2 ]; then
    echo -e "${GREEN}✅ CORRECTO: Servidor compatible con navegador${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Compatibilidad de navegador limitada${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar la compatibilidad de su servidor con un navegador?${NC}"
echo ""

echo -e "${BLUE}1. 🌐 ¿Su servidor puede servir un sitio web estático completo?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, servimos archivos HTML, CSS, JS e imágenes con los"
echo -e "    MIME types correctos para renderizado completo'${NC}"
echo ""

echo -e "${BLUE}2. 📂 ¿Cómo manejan el directory listing?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Cuando se accede a un directorio sin index, mostramos"
echo -e "    una lista de archivos si autoindex está habilitado'${NC}"
echo ""

echo -e "${BLUE}3. 🔀 ¿Implementan redirecciones HTTP?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, manejamos redirecciones 301/302 con el header Location"
echo -e "    para cambios de URL y rutas alternativas'${NC}"
echo ""

echo -e "${BLUE}4. 🧪 ¿Pueden mostrar tests en navegador?${NC}"
echo ""
echo -e "${GREEN}   ✅ Tests sugeridos:${NC}"
echo -e "${CYAN}   1. Abrir http://localhost:8080 en navegador${NC}"
echo -e "${CYAN}   2. Verificar que carga CSS e imágenes correctamente${NC}"
echo -e "${CYAN}   3. Probar URL incorrecta para ver página 404${NC}"
echo -e "${CYAN}   4. Acceder a directorio para ver listing${NC}"
echo -e "${CYAN}   5. Probar redirección configurada${NC}"
echo ""

echo -e "${RED}   🚨 IMPORTANTE PARA LA EVALUACIÓN:${NC}"
echo -e "${WHITE}   - Usar herramientas de desarrollo del navegador"
echo -e "   - Verificar headers de request y response"
echo -e "   - Comprobar que se sirve sitio web estático completo"
echo -e "   - Probar diferentes funcionalidades desde navegador${NC}"

echo ""
echo -e "${PURPLE}💻 Comandos útiles para verificar en terminal:${NC}"
echo -e "${CYAN}curl -I http://localhost:8080/                    # Headers de respuesta${NC}"
echo -e "${CYAN}curl -H 'Accept: text/html' http://localhost:8080/ # Request completa${NC}"
echo -e "${CYAN}curl http://localhost:8080/nonexistent/            # Test 404${NC}"
