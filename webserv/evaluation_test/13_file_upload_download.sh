#!/bin/bash

##############################################################################
# 13_file_upload_download.sh - Verificación de upload/download de archivos
# EVALUACIÓN:
# "Upload some file to the server and get it back"
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
echo -e "   UPLOAD/DOWNLOAD - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR DIRECTORIO DE UPLOADS
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando directorio de uploads:${NC}"
echo ""

UPLOAD_DIRS=()
if [ -d "$SEARCH_DIR/Uploads" ]; then
    UPLOAD_DIRS+=("$SEARCH_DIR/Uploads")
fi
if [ -d "$SEARCH_DIR/www/Uploads" ]; then
    UPLOAD_DIRS+=("$SEARCH_DIR/www/Uploads")
fi
if [ -d "$SEARCH_DIR/www2/Uploads" ]; then
    UPLOAD_DIRS+=("$SEARCH_DIR/www2/Uploads")
fi

for dir in "${UPLOAD_DIRS[@]}"; do
    echo -e "${GREEN}📁 Directorio uploads encontrado: $dir${NC}"
    echo -e "${PURPLE}💻 Contenido actual:${NC}"
    ls -la "$dir" 2>/dev/null || echo "   (directorio vacío o sin permisos)"
    echo ""
done

UPLOAD_COUNT=${#UPLOAD_DIRS[@]}
echo -e "${YELLOW}📊 Directorios de upload encontrados: $UPLOAD_COUNT${NC}"

# =============================================================================
# 2. VERIFICAR IMPLEMENTACIÓN DE POST PARA UPLOADS
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando implementación de POST para uploads:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"POST\\|multipart\\|form-data\\|upload\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

POST_UPLOAD=$(grep -rn "POST\|multipart\|form-data\|upload\|boundary" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$POST_UPLOAD" | head -10
TOTAL_POST=$(echo "$POST_UPLOAD" | wc -l)
if [ "$TOTAL_POST" -gt 10 ]; then
    echo "... ($TOTAL_POST líneas en total)"
fi

echo ""

HAS_POST=$(echo "$POST_UPLOAD" | grep -c "POST" || echo "0")
HAS_MULTIPART=$(echo "$POST_UPLOAD" | grep -c "multipart" || echo "0")
HAS_BOUNDARY=$(echo "$POST_UPLOAD" | grep -c "boundary" || echo "0")

echo -e "${YELLOW}📊 Upload features: POST($HAS_POST) multipart($HAS_MULTIPART) boundary($HAS_BOUNDARY)${NC}"

# =============================================================================
# 3. VERIFICAR MANEJO DE ARCHIVOS
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando manejo de archivos:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"fopen\\|ofstream\\|ifstream\\|file\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

FILE_HANDLING=$(grep -rn "fopen\|ofstream\|ifstream\|fwrite\|fread\|std::ofstream\|std::ifstream" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$FILE_HANDLING" | head -8
TOTAL_FILE=$(echo "$FILE_HANDLING" | wc -l)
if [ "$TOTAL_FILE" -gt 8 ]; then
    echo "... ($TOTAL_FILE líneas en total)"
fi

echo ""

HAS_OFSTREAM=$(echo "$FILE_HANDLING" | grep -c "ofstream" || echo "0")
HAS_IFSTREAM=$(echo "$FILE_HANDLING" | grep -c "ifstream" || echo "0")
HAS_FOPEN=$(echo "$FILE_HANDLING" | grep -c "fopen" || echo "0")

echo -e "${YELLOW}📊 File handling: ofstream($HAS_OFSTREAM) ifstream($HAS_IFSTREAM) fopen($HAS_FOPEN)${NC}"

# =============================================================================
# 4. VERIFICAR LÍMITES DE TAMAÑO
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando límites de tamaño de archivo:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"client_max_body_size\\|max.*size\\|Content-Length\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

SIZE_LIMITS=$(grep -rn "client_max_body_size\|max.*size\|Content-Length\|413\|body.*limit" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$SIZE_LIMITS" | head -6
TOTAL_SIZE=$(echo "$SIZE_LIMITS" | wc -l)
if [ "$TOTAL_SIZE" -gt 6 ]; then
    echo "... ($TOTAL_SIZE líneas en total)"
fi

echo ""

HAS_BODY_SIZE=$(echo "$SIZE_LIMITS" | grep -c "client_max_body_size\|body.*size" || echo "0")
HAS_413=$(echo "$SIZE_LIMITS" | grep -c "413" || echo "0")

echo -e "${YELLOW}📊 Size limits: body_size_check($HAS_BODY_SIZE) error_413($HAS_413)${NC}"

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$UPLOAD_COUNT" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_POST" -gt 0 ] && [ "$HAS_MULTIPART" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_OFSTREAM" -gt 0 ] && [ "$HAS_IFSTREAM" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 3 ]; then
    echo -e "${GREEN}✅ CORRECTO: Sistema de upload/download implementado${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Sistema de upload/download incompleto${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar el upload y download de archivos?${NC}"
echo ""

echo -e "${BLUE}1. 📤 ¿Cómo implementan el upload de archivos?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Usamos POST con multipart/form-data, parseamos el boundary"
echo -e "    y guardamos el contenido en el directorio de uploads'${NC}"
echo ""

echo -e "${BLUE}2. 📥 ¿Cómo sirven archivos para download?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Con GET leemos el archivo del filesystem y lo enviamos"
echo -e "    con el Content-Type y Content-Length apropiados'${NC}"
echo ""

echo -e "${BLUE}3. 📏 ¿Manejan límites de tamaño de archivo?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, verificamos client_max_body_size y devolvemos 413"
echo -e "    (Payload Too Large) si el archivo es muy grande'${NC}"
echo ""

echo -e "${BLUE}4. 🧪 ¿Pueden hacer una demo de upload/download?${NC}"
echo ""
echo -e "${GREEN}   ✅ Test sugerido:${NC}"
echo -e "${CYAN}   # Crear archivo de test${NC}"
echo -e "${CYAN}   echo 'Test upload content' > test_upload.txt${NC}"
echo ""
echo -e "${CYAN}   # Upload del archivo${NC}"
echo -e "${CYAN}   curl -X POST -F 'file=@test_upload.txt' http://localhost:8080/upload${NC}"
echo ""
echo -e "${CYAN}   # Download del archivo${NC}"
echo -e "${CYAN}   curl http://localhost:8080/uploads/test_upload.txt${NC}"
echo ""
echo -e "${CYAN}   # Verificar que el contenido es el mismo${NC}"
echo -e "${CYAN}   curl -s http://localhost:8080/uploads/test_upload.txt > downloaded.txt${NC}"
echo -e "${CYAN}   diff test_upload.txt downloaded.txt${NC}"
echo ""

echo -e "${BLUE}5. ⚠️ ¿Qué errores manejan en uploads?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Error 413 para archivos muy grandes, 400 para formato"
echo -e "    incorrecto, 500 para errores de escritura, 403 sin permisos'${NC}"
echo ""

echo -e "${RED}   🚨 IMPORTANTE PARA LA EVALUACIÓN:${NC}"
echo -e "${WHITE}   - El evaluador debe probar upload y download completo"
echo -e "   - Verificar que el archivo se puede recuperar intacto"
echo -e "   - Comprobar manejo de archivos grandes y errores${NC}"

if [ "$UPLOAD_COUNT" -gt 0 ]; then
    echo ""
    echo -e "${PURPLE}💻 Test rápido (si el servidor está corriendo):${NC}"
    echo -e "${CYAN}   curl -I http://localhost:8080/uploads/     # Ver si directorio es accesible${NC}"
fi
