#!/bin/bash

##############################################################################
# 00_siege_installation.sh - Verificación e instalación de Siege
# EVALUACIÓN:
# "Launch the installation of siege with homebrew"
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
echo -e "    INSTALACIÓN SIEGE - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# =============================================================================
# 1. VERIFICAR SI SIEGE ESTÁ INSTALADO
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando si Siege está instalado:${NC}"
echo ""

if command -v siege >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Siege ya está instalado en el sistema${NC}"
    SIEGE_VERSION=$(siege --version 2>&1 | head -1)
    echo -e "${CYAN}   Versión: $SIEGE_VERSION${NC}"
    echo -e "${CYAN}   Ubicación: $(which siege)${NC}"
    SIEGE_INSTALLED=1
else
    echo -e "${RED}❌ Siege NO está instalado${NC}"
    SIEGE_INSTALLED=0
fi

echo ""

# =============================================================================
# 2. VERIFICAR HOMEBREW (si estamos en macOS)
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando sistema y herramientas de instalación:${NC}"
echo ""

OS_TYPE=$(uname -s)
echo -e "${YELLOW}Sistema operativo detectado: $OS_TYPE${NC}"

case "$OS_TYPE" in
    "Darwin")
        echo -e "${BLUE}🍺 Sistema macOS - Verificando Homebrew:${NC}"
        if command -v brew >/dev/null 2>&1; then
            echo -e "${GREEN}✅ Homebrew está instalado${NC}"
            BREW_VERSION=$(brew --version | head -1)
            echo -e "${CYAN}   $BREW_VERSION${NC}"
            HAS_BREW=1
        else
            echo -e "${RED}❌ Homebrew NO está instalado${NC}"
            echo -e "${YELLOW}💡 Para instalar Homebrew:${NC}"
            echo -e "${CYAN}   /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"${NC}"
            HAS_BREW=0
        fi
        ;;
    "Linux")
        echo -e "${BLUE}🐧 Sistema Linux - Verificando package managers:${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            echo -e "${GREEN}✅ apt-get disponible (Ubuntu/Debian)${NC}"
            HAS_APT=1
        else
            HAS_APT=0
        fi
        
        if command -v yum >/dev/null 2>&1; then
            echo -e "${GREEN}✅ yum disponible (CentOS/RHEL)${NC}"
            HAS_YUM=1
        else
            HAS_YUM=0
        fi
        
        if command -v pacman >/dev/null 2>&1; then
            echo -e "${GREEN}✅ pacman disponible (Arch Linux)${NC}"
            HAS_PACMAN=1
        else
            HAS_PACMAN=0
        fi
        ;;
    *)
        echo -e "${YELLOW}⚠️ Sistema no reconocido: $OS_TYPE${NC}"
        ;;
esac

echo ""

# =============================================================================
# 3. MOSTRAR COMANDOS DE INSTALACIÓN
# =============================================================================

echo -e "${BLUE}🔍 3. Comandos de instalación para Siege:${NC}"
echo ""

if [ "$SIEGE_INSTALLED" -eq 0 ]; then
    echo -e "${RED}📥 SIEGE NECESITA SER INSTALADO:${NC}"
    echo ""
    
    case "$OS_TYPE" in
        "Darwin")
            if [ "$HAS_BREW" -eq 1 ]; then
                echo -e "${GREEN}✅ Comando recomendado para macOS:${NC}"
                echo -e "${CYAN}   brew install siege${NC}"
            else
                echo -e "${RED}❌ Instalar Homebrew primero, luego:${NC}"
                echo -e "${CYAN}   brew install siege${NC}"
            fi
            ;;
        "Linux")
            echo -e "${GREEN}✅ Comandos disponibles para Linux:${NC}"
            
            if [ "$HAS_APT" -eq 1 ]; then
                echo -e "${CYAN}   sudo apt-get update && sudo apt-get install siege${NC}"
            fi
            
            if [ "$HAS_YUM" -eq 1 ]; then
                echo -e "${CYAN}   sudo yum install siege${NC}"
            fi
            
            if [ "$HAS_PACMAN" -eq 1 ]; then
                echo -e "${CYAN}   sudo pacman -S siege${NC}"
            fi
            ;;
    esac
    
    echo ""
    echo -e "${YELLOW}📋 Después de instalar, verificar con:${NC}"
    echo -e "${CYAN}   siege --version${NC}"
else
    echo -e "${GREEN}✅ Siege ya está disponible para testing${NC}"
fi

# =============================================================================
# 4. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$SIEGE_INSTALLED" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

case "$OS_TYPE" in
    "Darwin")
        [ "$HAS_BREW" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
        ;;
    "Linux")
        ([ "$HAS_APT" -eq 1 ] || [ "$HAS_YUM" -eq 1 ] || [ "$HAS_PACMAN" -eq 1 ]) && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
        ;;
esac

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/2 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 2 ]; then
    echo -e "${GREEN}✅ CORRECTO: Sistema preparado para Siege${NC}"
elif [ "$SIEGE_INSTALLED" -eq 1 ]; then
    echo -e "${GREEN}✅ CORRECTO: Siege disponible${NC}"
else
    echo -e "${RED}❌ ACCIÓN REQUERIDA: Instalar Siege antes de continuar${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Tienen Siege instalado y listo para stress testing?${NC}"
echo ""

echo -e "${BLUE}1. 🍺 ¿Cómo instalaron Siege en su sistema?${NC}"
echo ""
if [ "$OS_TYPE" = "Darwin" ]; then
    echo -e "${GREEN}   ✅ En macOS, respuesta esperada:${NC}"
    echo -e "${WHITE}   'Usamos Homebrew: brew install siege'${NC}"
else
    echo -e "${GREEN}   ✅ En Linux, respuesta esperada:${NC}"
    echo -e "${WHITE}   'Usamos el package manager: apt-get/yum/pacman install siege'${NC}"
fi
echo ""

echo -e "${BLUE}2. 🧪 ¿Pueden verificar que Siege funciona?${NC}"
echo ""
echo -e "${GREEN}   ✅ Comando de verificación:${NC}"
echo -e "${CYAN}   siege --version${NC}"
echo -e "${CYAN}   siege --help${NC}"
echo ""

echo -e "${BLUE}3. 🎯 ¿Entienden por qué necesitamos Siege?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Siege es una herramienta de stress testing que nos permite"
echo -e "    verificar que nuestro servidor mantiene >99.5% disponibilidad"
echo -e "    bajo carga y no tiene memory leaks o hanging connections'${NC}"
echo ""

if [ "$SIEGE_INSTALLED" -eq 1 ]; then
    echo -e "${GREEN}🧪 DEMO RÁPIDA:${NC}"
    echo -e "${CYAN}   siege --version${NC}"
    echo ""
    echo -e "${PURPLE}💻 Test básico (si el servidor está corriendo):${NC}"
    echo -e "${CYAN}   siege -b -t 5s http://localhost:8080/${NC}"
else
    echo -e "${RED}⚠️ INSTALAR SIEGE ANTES DE CONTINUAR CON LA EVALUACIÓN${NC}"
    echo ""
    echo -e "${YELLOW}📋 Nota para el evaluador:${NC}"
    echo -e "${WHITE}   Sin Siege, no se pueden completar los tests de stress obligatorios.${NC}"
fi

echo ""
echo -e "${RED}🚨 IMPORTANTE:${NC}"
echo -e "${WHITE}Este es el PRIMER paso de la evaluación. Sin Siege instalado,"
echo -e "no se pueden realizar los stress tests obligatorios más adelante.${NC}"
echo ""
echo -e "Se recomienda el uso de ${CYAN}siege_test.sh${WHITE} para verificar la instalación y"
echo -e "funcionalidad de Siege, disponible en el directorio principal del proyecto.${NC}"
