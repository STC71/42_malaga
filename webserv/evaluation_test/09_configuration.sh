#!/bin/bash

##############################################################################
# 09_configuration.sh - Verificación de archivo de configuración
# EVALUACIÓN:
# "In the configuration file, check whether you can do the following"
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
echo -e "  ARCHIVO DE CONFIGURACIÓN - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. LOCALIZAR ARCHIVO DE CONFIGURACIÓN
# =============================================================================

echo -e "${BLUE}🔍 1. Localizando archivo(s) de configuración:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: find $SEARCH_DIR -name \"*.conf\" -o -name \"config.*\" -o -name \"*.cfg\"${NC}"
echo ""

CONFIG_FILES=$(find "$SEARCH_DIR" -name "*.conf" -o -name "config.*" -o -name "*.cfg" 2>/dev/null)
if [ -n "$CONFIG_FILES" ]; then
    echo "$CONFIG_FILES"
    CONFIG_FILE=$(echo "$CONFIG_FILES" | head -1)
    echo ""
    echo -e "${GREEN}✅ Archivo de configuración encontrado: $CONFIG_FILE${NC}"
else
    echo -e "${RED}❌ No se encontró archivo de configuración${NC}"
    exit 1
fi

# =============================================================================
# 2. VERIFICAR CONTENIDO DEL ARCHIVO DE CONFIGURACIÓN
# =============================================================================

echo ""
echo -e "${BLUE}🔍 2. Analizando contenido del archivo de configuración:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: head -20 $CONFIG_FILE${NC}"
echo ""

if [ -f "$CONFIG_FILE" ]; then
    head -20 "$CONFIG_FILE"
    echo ""
    
    TOTAL_LINES=$(wc -l < "$CONFIG_FILE")
    if [ "$TOTAL_LINES" -gt 20 ]; then
        echo "... ($TOTAL_LINES líneas en total)"
    fi
else
    echo -e "${RED}❌ No se puede leer el archivo de configuración${NC}"
    exit 1
fi

# =============================================================================
# 3. VERIFICAR CARACTERÍSTICAS DE CONFIGURACIÓN
# =============================================================================

echo ""
echo -e "${BLUE}🔍 3. Verificando características de configuración:${NC}"
echo ""

# Verificar puertos múltiples
MULTIPLE_PORTS=$(grep -c "port\|listen" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Configuraciones de puerto encontradas: $MULTIPLE_PORTS${NC}"

# Verificar nombres de servidor
SERVER_NAMES=$(grep -c "server_name\|hostname\|host" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Configuraciones de servidor/hostname: $SERVER_NAMES${NC}"

# Verificar páginas de error
ERROR_PAGES=$(grep -c "error_page\|error.*[0-9][0-9][0-9]" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Páginas de error configuradas: $ERROR_PAGES${NC}"

# Verificar límite de body
BODY_LIMIT=$(grep -c "client_max_body_size\|body.*limit\|max.*body" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Límites de body configurados: $BODY_LIMIT${NC}"

# Verificar rutas y directorios
ROUTES=$(grep -c "location\|route\|directory\|root" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Rutas/directorios configurados: $ROUTES${NC}"

# Verificar métodos HTTP
HTTP_METHODS=$(grep -c "allow.*method\|methods\|GET\|POST\|DELETE" "$CONFIG_FILE" 2>/dev/null || echo "0")
echo -e "${YELLOW}📊 Configuraciones de métodos HTTP: $HTTP_METHODS${NC}"

# =============================================================================
# 4. VERIFICAR PARSING DE CONFIGURACIÓN EN CÓDIGO
# =============================================================================

echo ""
echo -e "${BLUE}🔍 4. Verificando parsing de configuración en código:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"config\\|Config\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

CONFIG_PARSING=$(grep -rn "config\|Config" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)
echo "$CONFIG_PARSING" | head -8
TOTAL_CONFIG=$(echo "$CONFIG_PARSING" | wc -l)
if [ "$TOTAL_CONFIG" -gt 8 ]; then
    echo "... ($TOTAL_CONFIG referencias en total)"
fi

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

echo ""
CRITERIA_PASSED=0
[ "$MULTIPLE_PORTS" -gt 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$ERROR_PAGES" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$BODY_LIMIT" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$ROUTES" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/4 características encontradas${NC}"

if [ "$CRITERIA_PASSED" -ge 3 ]; then
    echo -e "${GREEN}✅ CORRECTO: Configuración parece completa${NC}"
else
    echo -e "${RED}❌ PROBLEMA: Configuración incompleta${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar las siguientes funcionalidades de configuración?${NC}"
echo ""

echo -e "${BLUE}1. 🌐 Múltiples servidores con diferentes puertos${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, configuramos múltiples bloques server con diferentes"
echo -e "    valores de listen/port. Cada servidor escucha en"
echo -e "    un puerto específico'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -n 'listen\\|port' $CONFIG_FILE${NC}"
echo ""

echo -e "${BLUE}2. 🏷️ Múltiples servidores con diferentes hostnames${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos server_name para cada servidor virtual."
echo -e "    Usar: curl --resolve example.com:80:127.0.0.1 http://example.com/'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -n 'server_name\\|hostname' $CONFIG_FILE${NC}"
echo ""

echo -e "${BLUE}3. ❌ Páginas de error personalizadas (404, etc.)${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos error_page para diferentes códigos de estado."
echo -e "    Cada error muestra una página personalizada'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -n 'error_page\\|error.*404' $CONFIG_FILE${NC}"
echo ""

echo -e "${BLUE}4. 📏 Límite de client body${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos client_max_body_size. Probar con:"
echo -e "    curl -X POST -H \"Content-Type: plain/text\" --data \"BODY\"'${NC}"
echo ""
echo -e "${PURPLE}   💻 Comando para verificar:${NC}"
echo -e "${CYAN}   grep -n 'body.*size\\|body.*limit' $CONFIG_FILE${NC}"
echo ""

echo -e "${BLUE}5. 📁 Rutas a diferentes directorios${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Configuramos location/route para mapear URLs"
echo -e "    a diferentes directorios del sistema de archivos'${NC}"
echo ""

echo -e "${BLUE}6. 🔧 Métodos HTTP permitidos por ruta${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Cada location puede especificar qué métodos acepta:"
echo -e "    GET, POST, DELETE, etc.'${NC}"
echo ""

echo -e "${YELLOW}   📋 Archivo de configuración detectado:${NC}"
echo -e "${WHITE}   $CONFIG_FILE${NC}"
