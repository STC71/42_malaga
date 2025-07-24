#!/bin/bash

##############################################################################
# 15_stress_testing.sh - Verificación de stress testing con Siege
# EVALUACIÓN:
# "Siege & stress test - Use Siege to run some stress tests"
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
echo -e "     STRESS TESTING - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# =============================================================================
# 1. VERIFICAR INSTALACIÓN DE SIEGE
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando instalación de Siege:${NC}"
echo ""

if command -v siege >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Siege encontrado en el sistema${NC}"
    SIEGE_VERSION=$(siege --version 2>&1 | head -1)
    echo -e "${CYAN}   $SIEGE_VERSION${NC}"
    SIEGE_INSTALLED=1
else
    echo -e "${RED}❌ Siege no está instalado${NC}"
    echo -e "${YELLOW}💡 Para instalar:${NC}"
    echo -e "${CYAN}   # Ubuntu/Debian:${NC}"
    echo -e "${CYAN}   sudo apt-get install siege${NC}"
    echo -e "${CYAN}   # macOS (con Homebrew):${NC}"
    echo -e "${CYAN}   brew install siege${NC}"
    echo -e "${CYAN}   # CentOS/RHEL:${NC}"
    echo -e "${CYAN}   sudo yum install siege${NC}"
    SIEGE_INSTALLED=0
fi

echo ""

# =============================================================================
# 2. VERIFICAR CONFIGURACIÓN PARA STRESS TESTING
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando configuración del servidor para stress tests:${NC}"
echo ""

# Buscar configuración de timeouts y límites
SEARCH_DIR="."
if [ ! -d "./srcs" ] && [ ! -d "./include" ]; then
    SEARCH_DIR=".."
fi

echo -e "${PURPLE}💻 Comando: grep -rn \"timeout\\|limit\\|max.*connection\" --include=\"*.cpp\" --include=\"*.conf\" $SEARCH_DIR${NC}"
echo ""

STRESS_CONFIG=$(grep -rn "timeout\|limit\|max.*connection\|SOMAXCONN\|backlog" --include="*.cpp" --include="*.conf" "$SEARCH_DIR" 2>/dev/null)
echo "$STRESS_CONFIG" | head -8
TOTAL_STRESS=$(echo "$STRESS_CONFIG" | wc -l)
if [ "$TOTAL_STRESS" -gt 8 ]; then
    echo "... ($TOTAL_STRESS líneas en total)"
fi

echo ""

HAS_TIMEOUT=$(echo "$STRESS_CONFIG" | grep -c "timeout" || echo "0")
HAS_LIMIT=$(echo "$STRESS_CONFIG" | grep -c "limit\|max.*connection" || echo "0")
HAS_BACKLOG=$(echo "$STRESS_CONFIG" | grep -c "SOMAXCONN\|backlog" || echo "0")

echo -e "${YELLOW}📊 Stress config: timeout($HAS_TIMEOUT) limits($HAS_LIMIT) backlog($HAS_BACKLOG)${NC}"

# =============================================================================
# 3. VERIFICAR MANEJO DE MEMORIA
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando manejo de memoria:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"delete\\|free\\|malloc\\|new\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

MEMORY_MGMT=$(grep -rn "delete\|free\|malloc\|new\[\]\|vector.*clear\|string.*clear" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$MEMORY_MGMT" | head -8
TOTAL_MEMORY=$(echo "$MEMORY_MGMT" | wc -l)
if [ "$TOTAL_MEMORY" -gt 8 ]; then
    echo "... ($TOTAL_MEMORY líneas en total)"
fi

echo ""

HAS_DELETE=$(echo "$MEMORY_MGMT" | grep -c "delete" || echo "0")
HAS_FREE=$(echo "$MEMORY_MGMT" | grep -c "free" || echo "0")
HAS_NEW=$(echo "$MEMORY_MGMT" | grep -c "new" || echo "0")

echo -e "${YELLOW}📊 Memory mgmt: delete($HAS_DELETE) free($HAS_FREE) new($HAS_NEW)${NC}"

# =============================================================================
# 4. COMANDOS DE PRUEBA CON SIEGE
# =============================================================================

echo -e "${BLUE}🔍 4. Comandos de prueba con Siege:${NC}"
echo ""

if [ "$SIEGE_INSTALLED" -eq 1 ]; then
    echo -e "${GREEN}✅ Siege está disponible. Comandos sugeridos:${NC}"
    echo ""
    echo -e "${PURPLE}💻 Test básico de disponibilidad (>99.5% requerido):${NC}"
    echo -e "${CYAN}   siege -b -t 30s http://localhost:8080/${NC}"
    echo ""
    echo -e "${PURPLE}💻 Test de conexiones concurrentes:${NC}"
    echo -e "${CYAN}   siege -c 50 -t 60s http://localhost:8080/${NC}"
    echo ""
    echo -e "${PURPLE}💻 Test indefinido (no debe requerir restart):${NC}"
    echo -e "${CYAN}   siege -b http://localhost:8080/ &${NC}"
    echo -e "${CYAN}   # Dejar corriendo y monitorear memoria${NC}"
    echo ""
    echo -e "${PURPLE}💻 Monitoreo de memoria durante stress test:${NC}"
    echo -e "${CYAN}   # En otra terminal:${NC}"
    echo -e "${CYAN}   watch 'ps aux | grep webserv | grep -v grep'${NC}"
    echo -e "${CYAN}   # O usar htop/top${NC}"
    
    SIEGE_READY=1
else
    echo -e "${RED}❌ Siege no disponible - instalar primero${NC}"
    SIEGE_READY=0
fi

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$SIEGE_INSTALLED" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_TIMEOUT" -gt 0 ] && [ "$HAS_LIMIT" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_DELETE" -gt 0 ] && [ "$HAS_NEW" -gt 0 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/3 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -ge 2 ]; then
    echo -e "${GREEN}✅ CORRECTO: Preparado para stress testing${NC}"
else
    echo -e "${RED}❌ PROBLEMA: No preparado para stress testing${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Pueden demostrar que su servidor resiste stress testing?${NC}"
echo ""

echo -e "${BLUE}1. 📊 ¿Su servidor mantiene >99.5% disponibilidad con Siege?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, nuestro servidor mantiene alta disponibilidad bajo carga."
echo -e "    Manejamos conexiones concurrentes eficientemente'${NC}"
echo ""

echo -e "${BLUE}2. 🧠 ¿Cómo previenen memory leaks durante stress tests?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Liberamos toda memoria asignada, cerramos file descriptors,"
echo -e "    y limpiamos estructuras de datos correctamente'${NC}"
echo ""

echo -e "${BLUE}3. 🔗 ¿Manejan hanging connections?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Implementamos timeouts, cerramos conexiones inactivas,"
echo -e "    y monitoreamos el estado de todas las conexiones'${NC}"
echo ""

echo -e "${BLUE}4. ♾️ ¿El servidor funciona indefinidamente sin restart?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, puede correr siege indefinidamente sin problemas"
echo -e "    de memoria o necesidad de reiniciar el servidor'${NC}"
echo ""

echo -e "${RED}   🚨 PRUEBAS OBLIGATORIAS:${NC}"
echo -e "${WHITE}   ✓ Availability >99.5% en GET simple con siege -b"
echo -e "   ✓ No memory leaks (memoria no crece indefinidamente)"
echo -e "   ✓ No hanging connections"
echo -e "   ✓ Uso indefinido de siege sin restart del servidor${NC}"

if [ "$SIEGE_INSTALLED" -eq 1 ]; then
    echo ""
    echo -e "${BLUE}🧪 DEMO RÁPIDA (si el servidor está corriendo):${NC}"
    echo ""
    echo -e "${PURPLE}💻 Test de 10 segundos:${NC}"
    echo -e "${CYAN}   siege -b -t 10s http://localhost:8080/${NC}"
    echo ""
    echo -e "${PURPLE}💻 Ver memoria actual del servidor:${NC}"
    echo -e "${CYAN}   ps aux | grep webserv | grep -v grep${NC}"
    echo ""
    echo -e "${YELLOW}📋 Nota: Durante la evaluación real, usar tests más largos${NC}"
else
    echo ""
    echo -e "${RED}⚠️ INSTALAR SIEGE ANTES DE LA EVALUACIÓN${NC}"
fi
