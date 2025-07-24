#!/bin/bash

##############################################################################
# 14_port_configuration.sh - Configuración y pruebas de puertos
# EVALUACIÓN: PORT ISSUES - Verificación de configuración de puertos múltiples
##############################################################################

# Configuración de colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Configuración
WEBSERV_DIR="/home/sternero/Desktop/MyGitHub/42_malaga/webserv"
TEST_CONFIG_DIR="${WEBSERV_DIR}/config"

print_header() {
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${WHITE}                    📊 EVALUACIÓN 14: CONFIGURACIÓN DE PUERTOS${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}OBJETIVO:${NC} Verificar el correcto manejo de puertos múltiples y prevención de conflictos"
    echo ""
}

ask_question() {
    local question="$1"
    echo -e "${BLUE}❓ ${WHITE}PREGUNTA:${NC} $question"
    echo -e "${CYAN}   Responde brevemente y presiona ENTER para continuar${NC}"
    read -r response
    echo -e "${GREEN}✓ Respuesta registrada${NC}"
    echo ""
}

print_section() {
    local title="$1"
    echo -e "${MAGENTA}▶ $title${NC}"
    echo ""
}

check_ports() {
    echo -e "${YELLOW}🔍 Verificando configuración de puertos...${NC}"
    
    # Buscar configuraciones de listen en archivos de configuración
    if find "$TEST_CONFIG_DIR" -name "*.conf" -type f 2>/dev/null | head -1 > /dev/null; then
        echo -e "${GREEN}✓ Archivos de configuración encontrados:${NC}"
        find "$TEST_CONFIG_DIR" -name "*.conf" -type f | while read -r conf_file; do
            echo -e "  📄 $(basename "$conf_file")"
            echo -e "${CYAN}     Puerto(s) configurado(s):${NC}"
            grep -n "listen\|port" "$conf_file" 2>/dev/null | head -5 | while read -r line; do
                echo -e "     ${YELLOW}→${NC} $line"
            done || echo -e "     ${RED}✗ No se encontraron directivas de puerto${NC}"
            echo ""
        done
    else
        echo -e "${RED}✗ No se encontraron archivos de configuración en $TEST_CONFIG_DIR${NC}"
    fi
}

test_multiple_ports() {
    echo -e "${YELLOW}🔧 Prueba de puertos múltiples...${NC}"
    echo "Verificaremos si el servidor puede manejar múltiples puertos simultáneamente"
    echo ""
    
    # Simular test con curl en diferentes puertos
    local test_ports=(8080 8081 8082)
    
    for port in "${test_ports[@]}"; do
        echo -e "${CYAN}📡 Testeando puerto $port...${NC}"
        
        # Verificar si el puerto está en uso
        if netstat -tuln 2>/dev/null | grep ":$port " > /dev/null; then
            echo -e "${GREEN}✓ Puerto $port está activo${NC}"
        else
            echo -e "${YELLOW}⚠ Puerto $port no está activo (servidor no ejecutándose)${NC}"
        fi
        
        # Simular curl test
        echo -e "${BLUE}  $ curl -s -o /dev/null -w \"%{http_code}\" http://localhost:$port/${NC}"
        echo -e "${CYAN}  Resultado esperado: 200 OK o respuesta apropiada${NC}"
        echo ""
    done
}

test_port_conflicts() {
    echo -e "${YELLOW}⚔️ Prueba de conflictos de puertos...${NC}"
    echo "Verificando que el servidor rechace configuraciones con puertos duplicados"
    echo ""
    
    echo -e "${CYAN}📋 Casos a verificar:${NC}"
    echo "1. Mismo puerto en múltiples directivas listen"
    echo "2. Puerto ya ocupado por otro proceso"
    echo "3. Puertos reservados del sistema"
    echo ""
    
    echo -e "${BLUE}💡 Comando de verificación sugerido:${NC}"
    echo -e "${WHITE}./webserv config_con_puertos_duplicados.conf${NC}"
    echo -e "${CYAN}Debería mostrar error y no iniciar${NC}"
    echo ""
}

check_hostname_configuration() {
    echo -e "${YELLOW}🌐 Verificación de hostnames múltiples...${NC}"
    echo "Comprobando configuración de server_name en diferentes puertos"
    echo ""
    
    if find "$TEST_CONFIG_DIR" -name "*.conf" -type f 2>/dev/null | head -1 > /dev/null; then
        find "$TEST_CONFIG_DIR" -name "*.conf" -type f | while read -r conf_file; do
            echo -e "${CYAN}📄 Analizando $(basename "$conf_file"):${NC}"
            echo -e "${YELLOW}   Server names configurados:${NC}"
            grep -n "server_name\|host" "$conf_file" 2>/dev/null | head -3 | while read -r line; do
                echo -e "   ${GREEN}→${NC} $line"
            done || echo -e "   ${RED}✗ No se encontraron server_name${NC}"
            echo ""
        done
    fi
}

main() {
    clear
    print_header
    
    # ================================================
    # SECCIÓN 1: PREGUNTAS CONCEPTUALES
    # ================================================
    print_section "📚 1. PREGUNTAS SOBRE CONFIGURACIÓN DE PUERTOS"
    
    ask_question "¿Cómo maneja tu servidor múltiples puertos simultáneamente? ¿Usas un socket por puerto?"
    
    ask_question "¿Qué sucede si intentas configurar el mismo puerto dos veces en el archivo de configuración?"
    
    ask_question "¿Cómo detecta tu servidor si un puerto ya está en uso por otro proceso?"
    
    ask_question "¿Puedes tener diferentes sitios web (server_name) en el mismo puerto?"
    
    # ================================================
    # SECCIÓN 2: VERIFICACIÓN DE CONFIGURACIÓN
    # ================================================
    print_section "🔍 2. ANÁLISIS DE CONFIGURACIÓN"
    
    check_ports
    
    echo -e "${BLUE}Presiona ENTER para continuar con las pruebas...${NC}"
    read -r
    
    # ================================================
    # SECCIÓN 3: PRUEBAS DE PUERTOS MÚLTIPLES
    # ================================================
    print_section "🧪 3. PRUEBAS DE PUERTOS MÚLTIPLES"
    
    test_multiple_ports
    
    ask_question "¿Has probado tu servidor con múltiples puertos activos al mismo tiempo? ¿Funciona correctamente?"
    
    # ================================================
    # SECCIÓN 4: PRUEBAS DE CONFLICTOS
    # ================================================
    print_section "⚔️ 4. PRUEBAS DE CONFLICTOS DE PUERTOS"
    
    test_port_conflicts
    
    ask_question "¿Qué mensaje de error muestra tu servidor cuando intentas usar un puerto ya ocupado?"
    
    # ================================================
    # SECCIÓN 5: CONFIGURACIÓN DE HOSTNAMES
    # ================================================
    print_section "🌐 5. CONFIGURACIÓN DE HOSTNAMES"
    
    check_hostname_configuration
    
    ask_question "¿Puedes configurar diferentes server_name en el mismo puerto? ¿Cómo distingue las peticiones?"
    
    # ================================================
    # EVALUACIÓN FINAL
    # ================================================
    print_section "📊 EVALUACIÓN FINAL - CONFIGURACIÓN DE PUERTOS"
    
    echo -e "${CYAN}┌─ Puntos a verificar por el evaluador:${NC}"
    echo -e "${CYAN}│${NC}"
    echo -e "${CYAN}├─${NC} ${GREEN}✓${NC} ${WHITE}Multiple ports with different websites${NC}"
    echo -e "${CYAN}├─${NC} ${GREEN}✓${NC} ${WHITE}Same port multiple times should not work${NC}"
    echo -e "${CYAN}├─${NC} ${GREEN}✓${NC} ${WHITE}Multiple servers with common ports${NC}"
    echo -e "${CYAN}├─${NC} ${GREEN}✓${NC} ${WHITE}Proper error handling for port conflicts${NC}"
    echo -e "${CYAN}├─${NC} ${GREEN}✓${NC} ${WHITE}Hostname differentiation on same port${NC}"
    echo -e "${CYAN}│${NC}"
    echo -e "${CYAN}└─${NC} ${YELLOW}⚠ Verificar que todas las configuraciones funcionen correctamente${NC}"
    echo ""
    
    echo -e "${WHITE}📋 COMANDOS RECOMENDADOS PARA EVALUADOR:${NC}"
    echo -e "${BLUE}• netstat -tuln | grep :8080${NC} - Verificar puertos activos"
    echo -e "${BLUE}• curl -H \"Host: site1.local\" http://localhost:8080/${NC} - Test hostname"
    echo -e "${BLUE}• curl -H \"Host: site2.local\" http://localhost:8080/${NC} - Test hostname 2"
    echo ""
    
    echo -e "${GREEN}🎯 Evaluación de configuración de puertos completada${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

# Ejecutar el script
main "$@"
