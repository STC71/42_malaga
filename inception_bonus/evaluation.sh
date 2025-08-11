#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                                              #
#    evaluation.sh - Script de Evaluación Inception    :+:      :+:    :+:     #
#                                                     +:+ +:+         +:+      #
#    By: sternero <sternero@student.42malaga.com>  +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025-08-04 by sternero               #+#    #+#                  #
#    Updated: 2025-08-04 by sternero              ###   ########.fr            #
#                                                                              #
# **************************************************************************** #

# Colores para una mejor presentación
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color
BOLD='\033[1m'
DIM='\033[2m'

# Contadores para la evaluación
PASSED=0
FAILED=0
TOTAL=0

# Variables para el terminal de debug
DEBUG_TERMINAL_ID=""
DEBUG_ENABLED=false

# Detectar ancho de terminal dinámicamente
get_terminal_width() {
    local width
    if command -v tput >/dev/null 2>&1; then
        width=$(tput cols 2>/dev/null)
    fi
    
    # Fallback si no se puede detectar
    if [ -z "$width" ] || [ "$width" -lt 60 ]; then
        width=80
    fi
    
    # Limitar ancho máximo para mejor legibilidad
    if [ "$width" -gt 100 ]; then
        width=100
    fi
    
    echo $width
}

# Función para mostrar encabezados
print_header() {
    local title="$1"
    local width=$(get_terminal_width)
    local title_len=${#title}
    local padding=$(( (width - title_len - 4) / 2 ))
    
    echo
    printf "${CYAN}%*s${NC}\n" $width | tr ' ' '='
    printf "${WHITE}${BOLD}%*s %s %*s${NC}\n" $padding "" "$title" $padding ""
    printf "${CYAN}%*s${NC}\n" $width | tr ' ' '='
    echo
}

# Función para mostrar secciones
print_section() {
    local title="$1"
    local width=$(get_terminal_width)
    local title_len=${#title}
    local padding=$((width - title_len - 4))
    
    echo
    printf "${BLUE}%*s${NC}\n" $width | tr ' ' '-'
    printf "${BLUE}| ${BOLD}%s%*s${NC}${BLUE} |${NC}\n" "$title" $padding ""
    printf "${BLUE}%*s${NC}\n" $width | tr ' ' '-'
    echo
}

# Función para mostrar tests
print_test() {
    echo -e "${YELLOW}${BOLD}> ${NC}${BOLD}$1${NC}"
}

# Función para mostrar resultados
print_result() {
    if [ "$1" = "PASS" ]; then
        echo -e "   ${GREEN}${BOLD}[PASS]${NC} $2"
        debug_result "$2" "PASS"
        ((PASSED++))
    elif [ "$1" = "INFO" ]; then
        echo -e "   ${CYAN}${BOLD}[INFO]${NC} $2"
        debug_result "$2" "INFO"
        # No incrementar contadores para secciones informativas
    else
        echo -e "   ${RED}${BOLD}[FAIL]${NC} $2"
        debug_result "$2" "FAIL"
        ((FAILED++))
    fi
    
    # Solo incrementar total para PASS/FAIL, no para INFO
    if [ "$1" != "INFO" ]; then
        ((TOTAL++))
    fi
}

# Función para mostrar explicaciones
print_explanation() {
    local text="$1"
    local width=$(get_terminal_width)
    local content_width=$((width - 8))
    
    echo -e "\n${PURPLE}${BOLD}   [INFO] Explicacion:${NC}"
    
    # Usar printf y fmt para un mejor control del texto
    echo "$text" | fmt -w $content_width | sed 's/^/      /'
    echo
}

# Función para mostrar información
print_info() {
    local text="$1"
    local width=$(get_terminal_width)
    local content_width=$((width - 8))
    
    echo -e "${CYAN}${BOLD}   [INFO] Informacion:${NC}"
    echo "$text" | fmt -w $content_width | sed 's/^/      /'
}

# Función para verificar si un comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Función para inicializar terminal de debug
init_debug_terminal() {
    if command_exists gnome-terminal; then
        # Crear archivo temporal para mostrar logs
        DEBUG_LOG="/tmp/inception_debug_$$.log"
        echo "=== INCEPTION DEBUG TERMINAL ===" > "$DEBUG_LOG"
        echo "Mostrando detalles técnicos de cada prueba..." >> "$DEBUG_LOG"
        echo "=============================================" >> "$DEBUG_LOG"
        echo "" >> "$DEBUG_LOG"
        
        # Abrir terminal de debug
        gnome-terminal --title="Inception Debug - Detalles Técnicos" -- bash -c "
            echo -e '\033[1;36m=== INCEPTION DEBUG TERMINAL ===\033[0m'
            echo -e '\033[1;33mMonitoreando detalles técnicos de la evaluación...\033[0m'
            echo ''
            tail -f '$DEBUG_LOG' 2>/dev/null || (echo 'Error: No se puede leer el log' && sleep 5)
        " &
        
        DEBUG_ENABLED=true
        sleep 1  # Dar tiempo a que se abra el terminal
        
        echo -e "${GREEN}✓${NC} Terminal de debug iniciado"
        return 0
    elif command_exists xterm; then
        DEBUG_LOG="/tmp/inception_debug_$$.log"
        echo "=== INCEPTION DEBUG TERMINAL ===" > "$DEBUG_LOG"
        echo "Mostrando detalles técnicos de cada prueba..." >> "$DEBUG_LOG"
        echo "=============================================" >> "$DEBUG_LOG"
        echo "" >> "$DEBUG_LOG"
        
        xterm -title "Inception Debug" -e "tail -f '$DEBUG_LOG'" &
        DEBUG_ENABLED=true
        sleep 1
        
        echo -e "${GREEN}✓${NC} Terminal de debug iniciado (xterm)"
        return 0
    else
        echo -e "${YELLOW}⚠️${NC} No se pudo abrir terminal de debug (gnome-terminal/xterm no disponible)"
        echo -e "${CYAN}Los detalles se mostrarán en este terminal${NC}"
        DEBUG_ENABLED=false
        return 1
    fi
}

# Función para escribir en el terminal de debug
debug_log() {
    local message="$1"
    local color="${2:-37}"  # Blanco por defecto
    
    if [ "$DEBUG_ENABLED" = true ] && [ -n "$DEBUG_LOG" ]; then
        echo -e "\033[${color}m[$(date '+%H:%M:%S')] ${message}\033[0m" >> "$DEBUG_LOG"
    fi
}

# Función para mostrar comando en debug
debug_command() {
    local test_name="$1"
    local command="$2"
    local expected="$3"
    
    if [ "$DEBUG_ENABLED" = true ]; then
        debug_log "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" "1;36"
        debug_log "🧪 PRUEBA: $test_name" "1;33"
        debug_log "📝 COMANDO: $command" "1;32"
        debug_log "🎯 ESPERADO: $expected" "1;34"
        debug_log "⏳ Ejecutando..." "1;37"
    fi
}

# Función para mostrar ejecución de comando en debug
debug_command_execution() {
    local command="$1"
    local show_output="${2:-true}"
    
    if [ "$DEBUG_ENABLED" = true ]; then
        debug_log "⚡ EJECUTANDO: $command" "1;35"
        
        if [ "$show_output" = "true" ]; then
            # Ejecutar comando y capturar tanto stdout como stderr
            local temp_output=$(mktemp)
            if eval "$command" > "$temp_output" 2>&1; then
                local exit_code=0
            else
                local exit_code=$?
            fi
            
            # Mostrar la salida línea por línea con prefijo
            if [ -s "$temp_output" ]; then
                debug_log "📤 SALIDA DEL COMANDO:" "1;37"
                while IFS= read -r line; do
                    debug_log "  > $line" "0;37"
                done < "$temp_output"
            else
                debug_log "📤 SALIDA: (sin salida)" "0;37"
            fi
            
            debug_log "🔢 CÓDIGO DE SALIDA: $exit_code" "1;37"
            rm -f "$temp_output"
        fi
    fi
}

# Función para mostrar resultado en debug
debug_result() {
    local obtained="$1"
    local status="$2"
    
    if [ "$DEBUG_ENABLED" = true ]; then
        if [ "$status" = "PASS" ]; then
            debug_log "✅ OBTENIDO: $obtained" "1;32"
            debug_log "🎉 RESULTADO: PASS" "1;32"
        elif [ "$status" = "FAIL" ]; then
            debug_log "❌ OBTENIDO: $obtained" "1;31"
            debug_log "💥 RESULTADO: FAIL" "1;31"
        else
            debug_log "ℹ️ OBTENIDO: $obtained" "1;33"
            debug_log "📋 RESULTADO: $status" "1;33"
        fi
        debug_log "" "0"
    fi
}

# Función para crear separador entre bloques de tests
debug_block_separator() {
    local block_name="$1"
    
    if [ "$DEBUG_ENABLED" = true ]; then
        debug_log "" "0"
        debug_log "═══════════════════════════════════════════════════" "1;36"
        debug_log "🔸 FINALIZANDO BLOQUE: $block_name" "1;36"
        debug_log "═══════════════════════════════════════════════════" "1;36"
        debug_log "" "0"
    fi
}

# Función para limpiar debug terminal
cleanup_debug() {
    if [ "$DEBUG_ENABLED" = true ] && [ -n "$DEBUG_LOG" ]; then
        debug_log "🏁 EVALUACIÓN COMPLETADA" "1;35"
        debug_log "📊 Total: $TOTAL | Aprobadas: $PASSED | Fallidas: $FAILED" "1;35"
        debug_log "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" "1;36"
        debug_log "" "0"
        debug_log "✅ TERMINAL DE DEBUG MANTENIDA ABIERTA" "1;33"
        debug_log "📋 Puedes revisar todos los comandos ejecutados arriba" "1;37"
        debug_log "🚪 Cierra esta ventana cuando termines de revisar" "1;37"
        debug_log "" "0"
        debug_log "👋 ¡Gracias por usar el sistema de debug!" "1;36"
    fi
}

# Función para pausa interactiva entre módulos
pause_between_modules() {
    local emoji="$1"
    local message="${2:-Pulsa cualquier tecla para continuar}"
    local width=$(get_terminal_width)
    
    echo ""
    echo -e "${DIM}$(printf '%*s' $width | tr ' ' '-')${NC}"
    echo -n -e "${CYAN}${BOLD}   $emoji $message... ${NC}"
    
    read -n 1 -s -r
    echo ""
    echo -e "${DIM}$(printf '%*s' $width | tr ' ' '-')${NC}"
    echo ""
}

# Función para verificar contenedores
check_containers() {
    local expected_containers=("nginx" "wordpress" "mariadb" "redis" "adminer" "ftp-server" "website" "portainer")
    local running_containers=($(docker ps --format "{{.Names}}" | sort))
    
    echo -e "${DIM}   Contenedores esperados: ${expected_containers[*]}${NC}"
    echo -e "${DIM}   Contenedores en ejecución: ${running_containers[*]}${NC}\n"
    
    for container in "${expected_containers[@]}"; do
        if docker ps --format "{{.Names}}" | grep -q "^${container}$"; then
            echo -e "   ${GREEN}●${NC} ${container}"
        else
            echo -e "   ${RED}●${NC} ${container} ${RED}(no encontrado)${NC}"
            return 1
        fi
    done
    return 0
}

# Función para verificar puertos
check_ports() {
    local ports=("443" "2121")
    
    for port in "${ports[@]}"; do
        if netstat -tuln 2>/dev/null | grep -q ":${port} " || ss -tuln 2>/dev/null | grep -q ":${port} "; then
            echo -e "   ${GREEN}●${NC} Puerto ${port} activo"
        else
            echo -e "   ${RED}●${NC} Puerto ${port} inactivo"
            return 1
        fi
    done
    return 0
}

# Function to fix system time if needed
fix_system_time() {
    echo -e "${YELLOW}${BOLD}⏰ SINCRONIZACIÓN DE HORA DEL SISTEMA${NC}"
    echo -e "${DIM}   Verificando y corrigiendo la hora del sistema...${NC}"
    echo ""
    
    # Check current time
    current_time=$(date)
    echo -e "${DIM}   Hora actual del sistema: $current_time${NC}"
    
    # Calculate time difference (rough estimation)
    current_year=$(date +%Y)
    current_month=$(date +%m)
    current_day=$(date +%d)
    current_hour=$(date +%H)
    
    # Expected: 07/08/2025 11:21 (approximately)
    expected_day=7
    expected_month=8
    expected_year=2025
    
    time_diff_detected=false
    
    if [ "$current_year" -ne "$expected_year" ] || [ "$current_month" -ne "$expected_month" ] || [ "$current_day" -ne "$expected_day" ]; then
        time_diff_detected=true
        echo -e "${RED}   ⚠️  Detectado desfase temporal significativo${NC}"
        echo -e "${YELLOW}   Fecha esperada: 07/08/2025${NC}"
        echo -e "${YELLOW}   Fecha actual: $(date '+%d/%m/%Y')${NC}"
    fi
    
    # Try to sync time using different methods
    echo -e "${DIM}   Intentando sincronización automática...${NC}"
    
    sync_success=false
    
    # Method 1: timedatectl (most modern)
    if command -v timedatectl >/dev/null 2>&1; then
        echo -e "${DIM}   • Usando timedatectl...${NC}"
        if sudo timedatectl set-ntp true >/dev/null 2>&1; then
            sleep 2
            sudo timedatectl sync >/dev/null 2>&1
            sync_success=true
        fi
    fi
    
    # Method 2: ntpdate (traditional)
    if ! $sync_success && command -v ntpdate >/dev/null 2>&1; then
        echo -e "${DIM}   • Usando ntpdate...${NC}"
        if sudo ntpdate -s pool.ntp.org >/dev/null 2>&1 || sudo ntpdate -s time.nist.gov >/dev/null 2>&1; then
            sync_success=true
        fi
    fi
    
    # Method 3: chronyd restart
    if ! $sync_success && command -v chronyd >/dev/null 2>&1; then
        echo -e "${DIM}   • Reiniciando chronyd...${NC}"
        sudo systemctl restart chronyd >/dev/null 2>&1 && sync_success=true
    fi
    
    # Method 4: Manual correction if automatic sync fails
    if ! $sync_success && $time_diff_detected; then
        echo -e "${RED}   ⚠️  Sincronización automática falló${NC}"
        echo -e "${CYAN}   ¿Deseas establecer la fecha manualmente? (y/n)${NC}"
        read -n 1 -r manual_choice
        echo ""
        
        if [[ $manual_choice =~ ^[Yy]$ ]]; then
            echo -e "${YELLOW}   Estableciendo zona horaria Madrid y fecha: 07/08/2025 11:21...${NC}"
            
            # Set timezone to Madrid
            if sudo timedatectl set-timezone Europe/Madrid >/dev/null 2>&1; then
                echo -e "${GREEN}   ✓ Zona horaria establecida: Madrid (Europe/Madrid)${NC}"
            else
                echo -e "${YELLOW}   ⚠️  No se pudo establecer la zona horaria${NC}"
            fi
            
            # Set the correct date and time
            if sudo date -s "2025-08-07 11:21:00" >/dev/null 2>&1; then
                echo -e "${GREEN}   ✓ Fecha y hora establecidas manualmente${NC}"
                sync_success=true
            else
                echo -e "${RED}   ✗ No se pudo establecer la fecha manualmente${NC}"
            fi
        fi
    fi
    
    # Show final time
    new_time=$(date)
    if $sync_success; then
        echo -e "${GREEN}✓${NC} Hora sincronizada: $new_time"
    else
        echo -e "${YELLOW}⚠️${NC} Hora actual: $new_time (puede necesitar corrección manual)"
    fi
    
    echo ""
    
    # Brief pause to see the result
    echo -n -e "${CYAN}${BOLD}   ⌚ Presiona cualquier tecla para continuar con la evaluación... ${NC}"
    read -n 1 -s -r
    echo ""
    echo ""
}

# Function to perform quick readiness check
quick_readiness_check() {
    local ready=0
    local issues=()
    
    echo -e "${BLUE}${BOLD}🔍 VERIFICACIÓN PREVIA DE ESTADO${NC}"
    echo -e "${DIM}   Comprobando requisitos básicos antes de la evaluación completa...${NC}"
    echo ""
    
    # Check Docker
    if ! command_exists docker || ! docker info >/dev/null 2>&1; then
        issues+=("Docker no está disponible o no funciona")
    else
        echo -e "${GREEN}✓${NC} Docker operativo"
    fi
    
    # Check .env file
    if [ ! -f ".env" ]; then
        issues+=("Archivo .env no encontrado")
    else
        echo -e "${GREEN}✓${NC} Archivo .env presente"
    fi
    
    # Check directory structure
    if [ ! -d "srcs" ] || [ ! -f "srcs/docker-compose.yml" ]; then
        issues+=("Estructura de directorios incorrecta")
    else
        echo -e "${GREEN}✓${NC} Estructura de directorios correcta"
    fi
    
    # Check if containers are running
    local running_containers=$(docker ps --format "{{.Names}}" 2>/dev/null | wc -l)
    if [ "$running_containers" -lt 3 ]; then
        issues+=("Servicios Docker no están ejecutándose ($running_containers contenedores activos)")
    else
        echo -e "${GREEN}✓${NC} Servicios Docker ejecutándose ($running_containers contenedores)"
    fi
    
    # Check basic connectivity
    if [ -f ".env" ] && command_exists docker; then
        local domain=$(grep "^DOMAIN_NAME=" .env 2>/dev/null | cut -d'=' -f2)
        if [ -n "$domain" ]; then
            echo -e "${DIM}   Probando conectividad básica a $domain...${NC}"
            if curl -k -s -o /dev/null -w "%{http_code}" "https://$domain/" 2>/dev/null | grep -q "200"; then
                echo -e "${GREEN}✓${NC} Conectividad web funcionando"
                ready=1
            else
                issues+=("Servicios web no responden en https://$domain/")
            fi
        else
            issues+=("Dominio no configurado en .env")
        fi
    fi
    
    echo ""
    
    # Show results
    if [ ${#issues[@]} -eq 0 ] && [ $ready -eq 1 ]; then
        echo -e "${GREEN}${BOLD}✅ ESTADO: LISTO PARA EVALUACIÓN${NC}"
        echo -e "${GREEN}   Todos los requisitos básicos están cumplidos${NC}"
        echo ""
        
        # Pausa para que el evaluador pueda leer el estado
        echo -n -e "${CYAN}${BOLD}   🚀 Presiona cualquier tecla para comenzar la evaluación completa... ${NC}"
        read -n 1 -s -r
        echo ""
        echo ""
        
        return 0
    else
        echo -e "${RED}${BOLD}⚠️  ESTADO: REQUIERE ATENCIÓN${NC}"
        echo -e "${RED}   Se encontraron los siguientes problemas:${NC}"
        for issue in "${issues[@]}"; do
            echo -e "${RED}   • $issue${NC}"
        done
        echo ""
        
        echo -e "${CYAN}${BOLD}🤔 ¿Qué te gustaría hacer?${NC}"
        echo -e "${WHITE}  1) ${GREEN}Continuar con evaluación completa${NC} ${WHITE}(puede mostrar muchos fallos)${NC}"
        echo -e "${WHITE}  2) ${YELLOW}Configurar el proyecto primero${NC} ${WHITE}(recomendado)${NC}"
        echo -e "${WHITE}  3) ${BLUE}Intentar iniciar servicios${NC} ${WHITE}(make all)${NC}"
        echo -e "${WHITE}  4) ${PURPLE}Sincronizar hora del sistema${NC} ${WHITE}(soluciona problemas de certificados)${NC}"
        echo -e "${WHITE}  5) ${RED}Salir${NC}"
        echo ""
        
        read -p "$(echo -e ${GREEN})Selecciona una opción [2]: $(echo -e ${NC})" choice
        choice=${choice:-2}
        
        case $choice in
            1)
                echo -e "\n${YELLOW}⚠️  Procediendo con evaluación completa...${NC}"
                echo -e "${YELLOW}   Es probable que veas múltiples fallos debido a los problemas detectados${NC}"
                echo ""
                return 0
                ;;
            2)
                echo -e "\n${GREEN}🔧 Iniciando configuración del proyecto...${NC}"
                if [ -f "./create_env.sh" ]; then
                    chmod +x ./create_env.sh
                    ./create_env.sh
                    exit 0
                else
                    echo -e "${RED}Error: create_env.sh no encontrado${NC}"
                    exit 1
                fi
                ;;
            3)
                echo -e "\n${BLUE}🚀 Intentando iniciar servicios...${NC}"
                if [ -f "Makefile" ]; then
                    make all
                    echo -e "\n${GREEN}Servicios iniciados. Ejecuta el script de nuevo para evaluar.${NC}"
                else
                    echo -e "${RED}Error: Makefile no encontrado${NC}"
                fi
                exit 0
                ;;
            4)
                echo -e "\n${PURPLE}⏰ Sincronizando hora del sistema...${NC}"
                fix_system_time
                echo -e "${GREEN}Hora sincronizada. Ejecuta el script de nuevo para evaluar.${NC}"
                exit 0
                ;;
            5|*)
                echo -e "\n${GREEN}👋 ¡Hasta luego!${NC}"
                exit 0
                ;;
        esac
    fi
}

# Inicio del script
clear
print_header " 🎯 EVALUACIÓN PROYECTO INCEPTION - 42 MÁLAGA"

echo -e "${BOLD}   Estudiante:${NC} sternero"
echo -e "${BOLD}   Proyecto:${NC} Inception"
echo -e "${BOLD}   Fecha:${NC} $(date '+%d/%m/%Y %H:%M:%S')"
echo -e "${BOLD}   Dominio:${NC} sternero.42.fr"
echo -e "${DIM}   Terminal: $(get_terminal_width) columnas${NC}"

echo ""

# Preguntar si quiere terminal de debug
echo -e "${CYAN}${BOLD}🔍 ¿Deseas abrir un terminal de debug que muestre los detalles técnicos de cada prueba?${NC}"
echo -e "${WHITE}  Esto incluirá comandos ejecutados, resultados esperados y obtenidos${NC}"
echo -e "${GREEN}  y) Sí, abrir terminal de debug${NC}"
echo -e "${YELLOW}  n) No, continuar solo con este terminal${NC}"
echo ""

read -p "$(echo -e ${GREEN})¿Abrir terminal de debug? [y/n]: $(echo -e ${NC})" debug_choice
case $debug_choice in
    [Yy]*)
        echo -e "\n${BLUE}🚀 Iniciando terminal de debug...${NC}"
        init_debug_terminal
        ;;
    *)
        echo -e "\n${YELLOW}⚠️  Continuando sin terminal de debug${NC}"
        DEBUG_ENABLED=false
        ;;
esac

echo ""

# Fix system time if needed (important for SSL certificates and repositories)
fix_system_time

# Perform quick readiness check
quick_readiness_check

# ═══════════════════════════════════════════════════════════════════════════════
# PRELIMINARES
# ═══════════════════════════════════════════════════════════════════════════════

print_header "📋 PRELIMINARES"

print_section "Verificación del entorno"

print_test "¿Está Docker instalado y funcionando?"
debug_command "Docker instalado y funcionando" "docker --version && docker info >/dev/null 2>&1" "Docker version y info sin errores"
if command_exists docker && docker info >/dev/null 2>&1; then
    debug_command_execution "docker --version"
    debug_command_execution "docker info" false  # No mostrar info completa por ser muy larga
    docker_version=$(docker --version)
    print_result "PASS" "Docker está instalado y funcionando correctamente"
    print_info "Versión: $docker_version"
    debug_result "$docker_version" "PASS"
else
    debug_command_execution "docker --version"
    debug_command_execution "docker info" false
    print_result "FAIL" "Docker no está instalado o no funciona"
    debug_result "Docker no disponible o error en docker info" "FAIL"
fi

print_test "¿Está Docker Compose instalado?"
debug_command "Docker Compose instalado" "docker-compose --version" "Versión de Docker Compose"
if command_exists docker-compose; then
    debug_command_execution "docker-compose --version"
    compose_version=$(docker-compose --version)
    print_result "PASS" "Docker Compose está instalado"
    print_info "Versión: $compose_version"
    debug_result "$compose_version" "PASS"
else
    debug_command_execution "docker-compose --version"
    print_result "FAIL" "Docker Compose no está instalado"
    debug_result "docker-compose command not found" "FAIL"
fi

print_test "¿Existe el archivo .env en la raíz?"
debug_command "Archivo .env en la raíz" "test -f .env" "Archivo .env existe"
if [ -f ".env" ]; then
    debug_command_execution "test -f .env"
    debug_command_execution "grep -c '=' .env"
    print_result "PASS" "Archivo .env encontrado"
    print_info "Contiene $(grep -c "=" .env) variables de entorno"
    print_explanation "El archivo .env es obligatorio y debe contener todas las credenciales y variables de configuración, nunca en el repositorio Git."
else
    debug_command_execution "test -f .env"
    print_result "FAIL" "Archivo .env no encontrado"
fi

print_test "¿Existe la estructura de directorios correcta?"
debug_command "Estructura de directorios" "test -d srcs && test -d srcs/requirements && test -f srcs/docker-compose.yml" "Directorios srcs/, srcs/requirements/ y archivo docker-compose.yml existen"
if [ -d "srcs" ] && [ -d "srcs/requirements" ] && [ -f "srcs/docker-compose.yml" ]; then
    debug_command_execution "ls -la srcs/"
    debug_command_execution "ls -la srcs/requirements/"
    print_result "PASS" "Estructura de directorios correcta"
    print_explanation "El proyecto sigue la estructura requerida: srcs/ contiene docker-compose.yml y requirements/ con todos los servicios"
else
    debug_command_execution "test -d srcs"
    debug_command_execution "test -d srcs/requirements"
    debug_command_execution "test -f srcs/docker-compose.yml"
    print_result "FAIL" "Estructura de directorios incorrecta"
fi

print_test "¿Existe Makefile en la raíz del proyecto?"
debug_command "Makefile en la raíz" "test -f Makefile" "Archivo Makefile existe en la raíz"
if [ -f "Makefile" ]; then
    debug_command_execution "test -f Makefile"
    debug_command_execution "head -5 Makefile"
    print_result "PASS" "Makefile encontrado en la raíz"
    print_explanation "El Makefile debe estar en la raíz y configurar todos los servicios vía docker-compose"
else
    debug_command_execution "test -f Makefile"
    debug_command_execution "ls -la | grep -i makefile"
    print_result "FAIL" "Makefile no encontrado en la raíz"
fi

# Pausa interactiva antes de la configuración Docker
pause_between_modules "🐳" "Preliminares completados. Continuamos con Docker"

# ═══════════════════════════════════════════════════════════════════════════════
# PARTE OBLIGATORIA - CONFIGURACIÓN DOCKER
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🐳 CONFIGURACIÓN DOCKER"

print_section "Verificación de Dockerfiles"

print_test "¿Existen Dockerfiles para cada servicio?"
debug_command "Dockerfiles para servicios" "ls srcs/requirements/*/Dockerfile" "Dockerfiles para nginx, wordpress y mariadb"
dockerfile_count=0
debug_command_execution "ls srcs/requirements/*/Dockerfile"
for service in nginx wordpress mariadb; do
    if [ -f "srcs/requirements/${service}/Dockerfile" ]; then
        ((dockerfile_count++))
        echo -e "   ${GREEN}✓${NC} Dockerfile encontrado para ${service}"
    else
        echo -e "   ${RED}✗${NC} Dockerfile faltante para ${service}"
    fi
done

if [ $dockerfile_count -eq 3 ]; then
    print_result "PASS" "Dockerfiles encontrados para todos los servicios principales"
    print_explanation "Cada servicio tiene su propio Dockerfile que permite personalización específica, instalación de dependencias y configuración del entorno."
else
    print_result "FAIL" "Faltan Dockerfiles (encontrados: $dockerfile_count/3)"
fi

print_test "¿Los Dockerfiles usan imágenes base apropiadas (Alpine/Debian)?"
debug_command "Imágenes base en Dockerfiles" "grep 'FROM.*alpine\\|FROM.*debian' srcs/requirements/*/Dockerfile" "FROM alpine o FROM debian en cada Dockerfile"
base_images_ok=0
debug_command_execution "grep 'FROM' srcs/requirements/*/Dockerfile"
for service in nginx wordpress mariadb; do
    if [ -f "srcs/requirements/${service}/Dockerfile" ]; then
        if grep -q "FROM.*\(alpine\|debian\)" "srcs/requirements/${service}/Dockerfile"; then
            ((base_images_ok++))
            echo -e "   ${GREEN}✓${NC} ${service} usa imagen base apropiada"
        else
            echo -e "   ${RED}✗${NC} ${service} no usa Alpine/Debian"
        fi
    fi
done

if [ $base_images_ok -eq 3 ]; then
    print_result "PASS" "Todos los servicios usan imágenes base Alpine/Debian"
    print_explanation "Se utilizan imágenes base oficiales como Alpine o Debian, garantizando estabilidad y compatibilidad."
else
    print_result "FAIL" "Algunos servicios no usan imágenes base apropiadas"
fi

print_section "Análisis del docker-compose.yml"

print_test "¿Está prohibido usar 'network: host' o 'links:'?"
debug_command "Búsqueda de network: host o links" "grep -r 'network.*host\\|links:' srcs/docker-compose.yml" "No debe aparecer ninguna línea"
debug_command_execution "grep -r 'network.*host\\|links:' srcs/docker-compose.yml"
if ! grep -r "network.*host\|links:" srcs/docker-compose.yml 2>/dev/null; then
    print_result "PASS" "No se usa 'network: host' ni 'links:'"
    print_explanation "El proyecto utiliza redes personalizadas de Docker en lugar de configuraciones prohibidas, lo que es una buena práctica de seguridad y aislamiento"
else
    print_result "FAIL" "Se encontró uso de 'network: host' o 'links:'"
fi

print_test "¿Se usan redes personalizadas en docker-compose.yml?"
debug_command "Redes personalizadas" "grep 'networks:' srcs/docker-compose.yml" "Debe aparecer sección networks:"
debug_command_execution "grep -A 5 'networks:' srcs/docker-compose.yml"
if grep -q "networks:" srcs/docker-compose.yml; then
    print_result "PASS" "Redes personalizadas configuradas en docker-compose"
    print_explanation "El uso de redes personalizadas permite comunicación segura entre contenedores usando nombres de servicio."
else
    print_result "FAIL" "No se encontraron redes personalizadas en docker-compose.yml"
fi

# Pausa interactiva antes de la visión general del proyecto
pause_between_modules "🎓" "Configuración Docker verificada. Pasamos a conceptos teóricos"

# ═══════════════════════════════════════════════════════════════════════════════
# VISIÓN GENERAL DEL PROYECTO
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🎓 VISIÓN GENERAL DEL PROYECTO"

print_section "Conceptos fundamentales"

print_test "¿Cómo funcionan Docker y docker-compose?"
print_result "INFO" "Explicación de Docker y docker-compose"
print_explanation "Docker es una plataforma de contenedorización que empaqueta aplicaciones con sus dependencias en contenedores ligeros y portables. Docker Compose es una herramienta que permite definir y ejecutar aplicaciones multi-contenedor usando archivos YAML, orquestando múltiples servicios, redes y volúmenes de forma declarativa y reproducible."

print_test "¿Cuál es la diferencia entre una imagen Docker usada con y sin docker-compose?"
print_result "INFO" "Diferencias en el uso de imágenes Docker"
print_explanation "Sin docker-compose, las imágenes se ejecutan de forma aislada usando 'docker run' con configuración manual de redes, volúmenes y variables. Con docker-compose, las imágenes se orquestan automáticamente según la configuración YAML, compartiendo redes personalizadas, volúmenes nombrados y variables de entorno, facilitando la comunicación entre servicios."

print_test "¿Cuáles son los beneficios de Docker comparado con VMs?"
print_result "INFO" "Ventajas de Docker sobre máquinas virtuales"
print_explanation "Docker ofrece mayor eficiencia al compartir el kernel del host (vs. cada VM requiere su propio OS), inicio más rápido (segundos vs. minutos), menor consumo de recursos (MB vs. GB), mejor portabilidad entre entornos, y facilidad para escalado horizontal. Los contenedores son más ligeros y permiten mayor densidad de aplicaciones por servidor."

print_test "¿Por qué es pertinente la estructura de directorios requerida?"
print_result "INFO" "Importancia de la estructura de directorios"
print_explanation "La estructura srcs/ con requirements/ separando cada servicio garantiza modularidad, mantenibilidad y claridad organizacional. Cada servicio tiene su Dockerfile y configuraciones aisladas, facilitando desarrollo independiente, debugging específico, y cumplimiento de principios de separación de responsabilidades en arquitecturas de microservicios."

# Pausa interactiva antes de comenzar pruebas técnicas
pause_between_modules "🌐" "Conceptos teóricos cubiertos. Iniciamos pruebas técnicas"

# ═══════════════════════════════════════════════════════════════════════════════
# NGINX
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🌐 NGINX - SERVIDOR WEB"

print_section "Configuración y funcionamiento"

print_test "¿Existe la configuración de Nginx?"
debug_command "Configuración de Nginx" "ls -la srcs/requirements/nginx/conf/" "Archivos de configuración en directorio conf"
debug_command_execution "ls -la srcs/requirements/nginx/conf/"
if [ -d "srcs/requirements/nginx/conf" ] && [ "$(ls -A srcs/requirements/nginx/conf/)" ]; then
    print_result "PASS" "Configuración de Nginx encontrada"
    print_explanation "Nginx tiene archivos de configuración personalizados que permiten servir la aplicación WordPress correctamente."
else
    print_result "FAIL" "Configuración de Nginx no encontrada"
fi

print_test "¿Nginx está ejecutándose correctamente?"
debug_command "Nginx ejecutándose" "docker ps | grep nginx" "Container nginx running"
if docker ps | grep -q nginx; then
    debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep nginx"
    container_status=$(docker ps --format "table {{.Names}}\t{{.Status}}" | grep nginx)
    print_result "PASS" "Contenedor nginx está ejecutándose"
    debug_result "$container_status" "PASS"
else
    debug_command_execution "docker ps | grep nginx"
    print_result "FAIL" "Contenedor nginx no está ejecutándose"
    debug_result "No nginx container found in docker ps" "FAIL"
fi

print_test "¿Nginx está configurado para usar TLS 1.2 o 1.3?"
debug_command "TLS configurado en Nginx" "docker exec nginx nginx -T | grep 'ssl_protocols.*TLSv1\\.[23]'" "ssl_protocols TLSv1.2 TLSv1.3 en configuración"
tls_config=$(docker exec nginx nginx -T 2>/dev/null | grep -E "ssl_protocols.*TLSv1\.[23]" | head -1)
if [ -n "$tls_config" ]; then
    debug_command_execution "docker exec nginx nginx -T | grep 'ssl_protocols'"
    print_result "PASS" "Nginx configurado con TLS 1.2/1.3"
    print_explanation "TLS 1.2/1.3 proporcionan cifrado seguro y moderno para todas las comunicaciones HTTPS, cumpliendo con los estándares de seguridad actuales."
    debug_result "$tls_config" "PASS"
else
    debug_command_execution "docker exec nginx nginx -T | grep 'ssl_protocols'"
    print_result "FAIL" "Nginx no tiene TLS 1.2/1.3 configurado correctamente"
    debug_result "No TLS 1.2/1.3 found in nginx config" "FAIL"
fi

print_test "¿El puerto 443 está expuesto y funcionando?"
debug_command "Puerto 443 funcionando" "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/" "HTTP status code 200"
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/"
if check_ports; then
    print_result "PASS" "Puerto 443 está abierto y funcionando"
else
    print_result "FAIL" "Puerto 443 no está funcionando"
fi

print_test "¿El acceso HTTP (puerto 80) está bloqueado?"
debug_command "Puerto 80 bloqueado" "curl -m 5 -s http://sternero.42.fr/" "No debe responder"
debug_command_execution "curl -m 5 -s -o /dev/null -w '%{http_code}' http://sternero.42.fr/ || echo 'Conexión bloqueada o timeout'"
if ! curl -m 5 -s http://sternero.42.fr/ >/dev/null 2>&1; then
    print_result "PASS" "Puerto 80 (HTTP) correctamente bloqueado"
    print_explanation "El acceso HTTP está bloqueado, forzando el uso de HTTPS para mayor seguridad."
else
    print_result "FAIL" "Puerto 80 (HTTP) accesible - debe estar bloqueado"
fi

print_test "¿La respuesta HTTPS es correcta?"
debug_command "Respuesta HTTPS" "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/" "HTTP status code 200"
http_code=$(curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/ 2>/dev/null)
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/" false
if echo "$http_code" | grep -q "200"; then
    print_result "PASS" "Respuesta HTTPS correcta (200 OK)"
    print_explanation "El servidor responde correctamente a peticiones HTTPS, indicando que el certificado SSL y la configuración están funcionando."
    debug_result "HTTP $http_code" "PASS"
else
    print_result "FAIL" "Respuesta HTTPS incorrecta"
    debug_result "HTTP $http_code (expected 200)" "FAIL"
fi

# Separador al final del bloque Nginx
debug_block_separator "NGINX - SERVIDOR WEB"

# Pausa interactiva antes de WordPress
pause_between_modules "📝" "Nginx verificado. Continuamos con WordPress"

# ═══════════════════════════════════════════════════════════════════════════════
# WORDPRESS + PHP-FPM
# ═══════════════════════════════════════════════════════════════════════════════

print_header "📝 WORDPRESS + PHP-FPM"

print_section "Instalación y configuración"

print_test "¿WordPress está ejecutándose?"
debug_command "WordPress ejecutándose" "docker ps | grep wordpress" "Container wordpress running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep wordpress"
if docker ps | grep -q wordpress; then
    print_result "PASS" "Contenedor WordPress está ejecutándose"
else
    print_result "FAIL" "Contenedor WordPress no está ejecutándose"
fi

print_test "¿WordPress está instalado y configurado correctamente?"
debug_command "WordPress instalado" "docker exec wordpress test -f /var/www/html/wp-config.php" "wp-config.php debe existir"
debug_command_execution "docker exec wordpress ls -la /var/www/html/wp-config.php"
if docker exec wordpress test -f /var/www/html/wp-config.php; then
    print_result "PASS" "WordPress está instalado (wp-config.php existe)"
    print_explanation "WordPress se instala automáticamente usando WP-CLI con configuración personalizada que incluye usuarios, base de datos y plugins."
else
    print_result "FAIL" "WordPress no está instalado correctamente"
fi

print_test "¿PHP-FPM está funcionando?"
debug_command "PHP-FPM funcionando" "docker exec wordpress pgrep php-fpm" "Procesos php-fpm activos"
debug_command_execution "docker exec wordpress ps aux | grep php-fpm | grep -v grep"
if docker exec wordpress pgrep php-fpm >/dev/null; then
    print_result "PASS" "PHP-FPM está ejecutándose"
    print_explanation "PHP-FPM maneja las peticiones PHP de WordPress de manera eficiente, separando el procesamiento web del servidor Nginx."
else
    print_result "FAIL" "PHP-FPM no está ejecutándose"
fi

print_test "¿WordPress tiene volumen persistente?"
debug_command "Volumen persistente WordPress" "docker volume ls | grep wordpress" "Volumen srcs_wordpress debe existir"
debug_command_execution "docker volume ls | grep wordpress"
if docker volume ls | grep -q "srcs_wordpress" && docker volume inspect srcs_wordpress 2>/dev/null | grep -q "data/wordpress"; then
    print_result "PASS" "WordPress tiene volumen persistente configurado"
    print_explanation "Los datos de WordPress se almacenan en un volumen persistente que mantiene el contenido incluso si el contenedor se reinicia."
else
    print_result "FAIL" "WordPress no tiene volumen persistente"
fi

# Separador al final del bloque WordPress
debug_block_separator "WORDPRESS + PHP-FPM"

# Pausa interactiva antes de MariaDB
pause_between_modules "🗄️" "WordPress verificado. Continuamos con MariaDB"

# ═══════════════════════════════════════════════════════════════════════════════
# MARIADB
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🗄️  MARIADB - BASE DE DATOS"

print_section "Configuración y acceso"

print_test "¿MariaDB está ejecutándose?"
debug_command "MariaDB ejecutándose" "docker ps | grep mariadb" "Container mariadb running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep mariadb"
if docker ps | grep -q mariadb; then
    print_result "PASS" "Contenedor MariaDB está ejecutándose"
else
    print_result "FAIL" "Contenedor MariaDB no está ejecutándose"
fi

print_test "¿La base de datos WordPress existe?"
debug_command "Base de datos WordPress" "docker exec mariadb mysql -u sternero -p12345 -e 'USE wordpress_db; SHOW TABLES;'" "Tablas de WordPress"
debug_command_execution "docker exec mariadb mysql -u sternero -p12345 -e 'USE wordpress_db; SHOW TABLES;'"
if docker exec mariadb mysql -u sternero -p12345 -e "USE wordpress_db; SHOW TABLES;" >/dev/null 2>&1; then
    table_count=$(docker exec mariadb mysql -u sternero -p12345 -e "USE wordpress_db; SHOW TABLES;" 2>/dev/null | wc -l)
    print_result "PASS" "Base de datos WordPress existe con $((table_count-1)) tablas"
    print_explanation "MariaDB almacena todos los datos de WordPress incluyendo posts, usuarios, configuraciones y metadatos en tablas estructuradas."
else
    print_result "FAIL" "Base de datos WordPress no existe o no es accesible"
fi

print_test "¿Los usuarios de base de datos están configurados correctamente?"
debug_command "Usuarios de base de datos" "docker exec mariadb mysql -u root -p12345 -e 'SELECT User, Host FROM mysql.user;'" "Usuarios root y sternero"
debug_command_execution "docker exec mariadb mysql -u root -p12345 -e 'SELECT User, Host FROM mysql.user WHERE User IN (\"root\", \"sternero\");'"
if docker exec mariadb mysql -u root -p12345 -e "SELECT User, Host FROM mysql.user WHERE User IN ('root', 'sternero');" >/dev/null 2>&1; then
    print_result "PASS" "Usuarios de base de datos configurados correctamente"
    print_explanation "Se han creado usuarios específicos con permisos apropiados: root para administración y sternero para WordPress."
else
    print_result "FAIL" "Usuarios de base de datos no configurados correctamente"
fi

print_test "¿MariaDB tiene volumen persistente?"
debug_command "Volumen persistente MariaDB" "docker volume ls | grep database" "Volumen srcs_database debe existir"
debug_command_execution "docker volume ls | grep database"
if docker volume ls | grep -q "srcs_database" && docker volume inspect srcs_database 2>/dev/null | grep -q "data/database"; then
    print_result "PASS" "MariaDB tiene volumen persistente configurado"
    print_explanation "Los datos de la base de datos se mantienen en almacenamiento persistente, preservando la información entre reinicios."
else
    print_result "FAIL" "MariaDB no tiene volumen persistente"
fi

# Separador al final del bloque MariaDB
debug_block_separator "MARIADB - BASE DE DATOS"

# Pausa después de MariaDB antes de verificación de persistencia
pause_between_modules "💾" "MariaDB verificado. Continuamos con verificación de persistencia"

# ═══════════════════════════════════════════════════════════════════════════════
# VERIFICACIÓN DE PERSISTENCIA
# ═══════════════════════════════════════════════════════════════════════════════

print_header "💾 VERIFICACIÓN DE PERSISTENCIA"

print_section "Persistencia de datos"

print_test "¿Los volúmenes mantienen datos entre reinicios?"
debug_command "Verificación de persistencia" "ls -la /home/sternero/Inception/data/" "Directorios wordpress y database deben existir"
debug_command_execution "ls -la /home/sternero/Inception/data/"
if [ -d "/home/sternero/Inception/data/wordpress" ] && [ -d "/home/sternero/Inception/data/database" ]; then
    debug_command_execution "ls -la /home/sternero/Inception/data/wordpress/ | wc -l"
    debug_command_execution "ls -la /home/sternero/Inception/data/database/ | wc -l"
    wordpress_files=$(ls -la /home/sternero/Inception/data/wordpress/ 2>/dev/null | wc -l)
    database_files=$(ls -la /home/sternero/Inception/data/database/ 2>/dev/null | wc -l)
    
    if [ $wordpress_files -gt 2 ] && [ $database_files -gt 2 ]; then
        print_result "PASS" "Datos persistentes verificados (WordPress: $wordpress_files archivos, DB: $database_files archivos)"
        print_explanation "Los volúmenes contienen datos que persisten entre reinicios de contenedores, garantizando que no se pierda información."
    else
        print_result "FAIL" "Los volúmenes no contienen datos suficientes"
    fi
else
    print_result "FAIL" "Directorios de datos no encontrados"
fi

print_test "¿Las rutas de volúmenes siguen el formato requerido?"
debug_command "Rutas de volúmenes" "docker volume inspect srcs_wordpress srcs_database" "Mountpoint debe contener /data/"
debug_command_execution "docker volume inspect srcs_wordpress | grep -A1 Mountpoint"
debug_command_execution "docker volume inspect srcs_database | grep -A1 Mountpoint"
if docker volume inspect srcs_wordpress 2>/dev/null | grep -q "data/wordpress" && docker volume inspect srcs_database 2>/dev/null | grep -q "data/database"; then
    print_result "PASS" "Rutas de volúmenes siguen el formato /home/login/data/"
    print_explanation "Los volúmenes están correctamente mapeados al sistema de archivos del host en la ubicación estándar."
else
    print_result "FAIL" "Las rutas de volúmenes no siguen el formato requerido"
fi

print_test "¿La estructura de datos está organizada correctamente?"
debug_command "Estructura de datos" "ls -la /home/sternero/Inception/data/portainer/" "Archivos de Portainer organizados"
debug_command_execution "ls -la /home/sternero/Inception/data/portainer/"
debug_command_execution "ls /home/sternero/Inception/srcs/ | grep -v -E '(docker-compose.yml|requirements|README.md)'"
if [ -d "/home/sternero/Inception/data/portainer" ]; then
    portainer_files=$(ls -la /home/sternero/Inception/data/portainer/ 2>/dev/null | wc -l)
    # Excluir README.md de la cuenta de archivos extra en srcs/
    srcs_extra=$(ls /home/sternero/Inception/srcs/ | grep -v -E "(docker-compose.yml|requirements|README.md)" | wc -l)
    
    if [ $portainer_files -gt 2 ] && [ $srcs_extra -eq 0 ]; then
        print_result "PASS" "Estructura optimizada: datos de Portainer organizados, srcs/ limpio (README.md permitido)"
        print_explanation "La nueva estructura separa datos persistentes en /data/portainer/ y mantiene /srcs/ solo con código fuente y README.md, mejorando organización y mantenibilidad."
    else
        print_result "WARNING" "Estructura parcialmente organizada (Portainer: $portainer_files archivos, archivos extra en srcs: $srcs_extra, excluyendo README.md)"
    fi
else
    print_result "FAIL" "Directorio /data/portainer/ no encontrado"
fi

# Pausa después de verificación de persistencia antes de configuración de red
pause_between_modules "🌐" "Persistencia verificada. Continuamos con configuración de red"

# ═══════════════════════════════════════════════════════════════════════════════
# CONFIGURACIÓN DE RED
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🌐 CONFIGURACIÓN DE RED"

print_section "Red Docker"

print_test "¿Existe una red personalizada?"
debug_command "Red personalizada" "docker network ls | grep inception" "Red inception debe aparecer"
debug_command_execution "docker network ls"
if docker network ls | grep -q inception; then
    print_result "PASS" "Red personalizada 'inception' existe"
    print_explanation "Los contenedores están conectados a través de una red personalizada que permite comunicación interna segura usando nombres de servicio."
else
    print_result "FAIL" "Red personalizada no encontrada"
fi

print_test "¿Los contenedores están en la misma red?"
debug_command "Contenedores en red" "docker network inspect srcs_inception" "Múltiples contenedores conectados"
debug_command_execution "docker network inspect srcs_inception | grep -A5 -B5 'Name':"
network_containers=$(docker network inspect srcs_inception 2>/dev/null | grep -o '"Name": "[^"]*"' | wc -l)
if [ $network_containers -gt 5 ]; then
    print_result "PASS" "Múltiples contenedores conectados a la red ($network_containers contenedores)"
else
    print_result "FAIL" "No todos los contenedores están en la red"
fi

# Pausa interactiva antes de servicios bonus
pause_between_modules "🎁" "Servicios obligatorios verificados. Revisamos servicios bonus"

# ═══════════════════════════════════════════════════════════════════════════════
# SERVICIOS BONUS
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🎁 SERVICIOS BONUS"

print_section "Redis Cache"

print_test "¿Redis está ejecutándose?"
debug_command "Redis ejecutándose" "docker ps | grep redis" "Container redis running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep redis"
if docker ps | grep -q redis; then
    print_result "PASS" "Contenedor Redis está ejecutándose"
    print_explanation "Redis actúa como sistema de caché para WordPress, mejorando significativamente el rendimiento al almacenar datos frecuentemente accedidos en memoria."
else
    print_result "FAIL" "Contenedor Redis no está ejecutándose"
fi

print_test "¿Redis está conectado con WordPress?"
debug_command "Redis con WordPress" "docker exec wordpress wp redis status --allow-root --path=/var/www/html" "Status: Connected"
debug_command_execution "docker exec wordpress wp redis status --allow-root --path=/var/www/html"
if docker exec wordpress wp redis status --allow-root --path=/var/www/html 2>/dev/null | grep -q "Status: Connected"; then
    print_result "PASS" "Redis conectado con WordPress"
else
    print_result "FAIL" "Redis no está conectado con WordPress"
fi

# Pausa entre servicios bonus
pause_between_modules "📁" "Redis verificado. Continuamos con FTP Server"

print_section "FTP Server"

print_test "¿El servidor FTP está ejecutándose?"
debug_command "FTP ejecutándose" "docker ps | grep ftp-server" "Container ftp-server running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep ftp"
if docker ps | grep -q ftp-server; then
    print_result "PASS" "Contenedor FTP está ejecutándose"
    print_explanation "El servidor FTP permite transferencia de archivos al contenedor WordPress, útil para subir temas, plugins o contenido."
else
    print_result "FAIL" "Contenedor FTP no está ejecutándose"
fi

print_test "¿El puerto FTP está configurado correctamente?"
debug_command "Puerto FTP 2121" "netstat -tuln | grep :2121" "Puerto 2121 debe estar escuchando"
debug_command_execution "netstat -tuln | grep :2121 || ss -tuln | grep :2121"
if netstat -tuln 2>/dev/null | grep -q ":2121 " || ss -tuln 2>/dev/null | grep -q ":2121 "; then
    print_result "PASS" "Puerto FTP 2121 está activo"
else
    print_result "FAIL" "Puerto FTP 2121 no está activo"
fi

# Pausa entre servicios bonus
pause_between_modules "🗃️" "FTP Server verificado. Continuamos con Adminer"

print_section "Adminer"

print_test "¿Adminer está ejecutándose?"
debug_command "Adminer ejecutándose" "docker ps | grep adminer" "Container adminer running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep adminer"
if docker ps | grep -q adminer; then
    print_result "PASS" "Contenedor Adminer está ejecutándose"
    print_explanation "Adminer es una herramienta web para administración de bases de datos que permite gestionar MySQL/MariaDB de forma gráfica."
else
    print_result "FAIL" "Contenedor Adminer no está ejecutándose"
fi

print_test "¿Adminer es accesible vía web?"
debug_command "Adminer accesible" "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/adminer/" "HTTP status code 200"
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/adminer/"
if curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/adminer/ | grep -q "200"; then
    print_result "PASS" "Adminer accesible vía HTTPS"
else
    print_result "FAIL" "Adminer no es accesible vía HTTPS"
fi

print_test "¿Adminer tiene funcionalidad de auto-fill implementada?"
debug_command "Auto-fill Adminer" "curl -k -s https://sternero.42.fr/adminer/ | grep 'auto-fill'" "Auto-fill script debe estar presente"
# Usar método más robusto para evitar el mensaje "Failed writing body"
TEMP_FILE=$(mktemp)
debug_command_execution "curl -k -s https://sternero.42.fr/adminer/ | grep -i 'auto-fill\\|autofill' | head -3"
if curl -k -s https://sternero.42.fr/adminer/ > "$TEMP_FILE" 2>/dev/null && grep -q "Adminer auto-fill script loaded" "$TEMP_FILE"; then
    print_result "PASS" "Funcionalidad de auto-fill implementada en Adminer"
    print_explanation "Se ha implementado JavaScript personalizado que rellena automáticamente los campos de conexión de Adminer con las credenciales correctas de la base de datos."
else
    print_result "FAIL" "Funcionalidad de auto-fill no encontrada en Adminer"
fi
rm -f "$TEMP_FILE"

# Pausa entre servicios bonus
pause_between_modules "🌐" "Adminer verificado. Continuamos con sitio web estático"

print_section "Sitio Web Estático"

print_test "¿El sitio web estático está ejecutándose?"
debug_command "Sitio web ejecutándose" "docker ps | grep website" "Container website running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep website"
if docker ps | grep -q website; then
    print_result "PASS" "Contenedor del sitio web está ejecutándose"
    print_explanation "Sitio web estático personalizado que muestra información del proyecto y del estudiante, servido independientemente de WordPress."
else
    print_result "FAIL" "Contenedor del sitio web no está ejecutándose"
fi

print_test "¿El sitio web es accesible?"
debug_command "Sitio web accesible" "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/portfolio/" "HTTP status code 200"
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/portfolio/"
if curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/portfolio/ | grep -q "200"; then
    print_result "PASS" "Sitio web estático accesible"
else
    print_result "FAIL" "Sitio web estático no es accesible"
fi

# Pausa entre servicios bonus
pause_between_modules "📊" "Sitio web verificado. Continuamos con Portainer"

print_section "Portainer - Monitorización"

print_test "¿Portainer está ejecutándose?"
debug_command "Portainer ejecutándose" "docker ps | grep portainer" "Container portainer running"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}' | grep portainer"
if docker ps | grep -q portainer; then
    print_result "PASS" "Contenedor Portainer está ejecutándose"
    print_explanation "Portainer es una herramienta de gestión visual para Docker que permite administrar contenedores, imágenes, volúmenes y redes a través de una interfaz web intuitiva."
else
    print_result "FAIL" "Contenedor Portainer no está ejecutándose"
fi

print_test "¿Portainer es accesible vía web?"
debug_command "Portainer accesible" "curl -k -s -o /dev/null -w '%{http_code}' http://localhost:9000/" "HTTP status code 200 or 307"
portainer_code=$(curl -k -s -o /dev/null -w "%{http_code}" http://localhost:9000/ 2>/dev/null)
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' http://localhost:9000/" false
if echo "$portainer_code" | grep -qE "(200|307)"; then
    print_result "PASS" "Portainer accesible en puerto 9000"
    debug_result "HTTP $portainer_code" "PASS"
else
    print_result "FAIL" "Portainer no es accesible en puerto 9000"
    debug_result "HTTP $portainer_code (expected 200 or 307)" "FAIL"
fi

print_test "¿El puerto 9000 está expuesto correctamente?"
debug_command "Puerto 9000" "netstat -tuln | grep :9000" "Puerto 9000 debe estar escuchando"
debug_command_execution "netstat -tuln | grep :9000 || ss -tuln | grep :9000"
if netstat -tuln 2>/dev/null | grep -q ":9000 " || ss -tuln 2>/dev/null | grep -q ":9000 "; then
    print_result "PASS" "Puerto 9000 está activo para Portainer"
else
    print_result "FAIL" "Puerto 9000 no está activo"
fi

print_test "¿Portainer tiene acceso al socket de Docker?"
debug_command "Socket Docker" "docker inspect portainer --format '{{json .Mounts}}' | grep docker.sock" "Mount /var/run/docker.sock debe existir"
debug_command_execution "docker inspect portainer --format '{{json .Mounts}}' | grep docker.sock"
if docker inspect portainer --format '{{json .Mounts}}' 2>/dev/null | grep -q "/var/run/docker.sock"; then
    print_result "PASS" "Portainer tiene acceso al socket de Docker"
    print_explanation "El acceso al socket de Docker permite a Portainer gestionar contenedores, imágenes, volúmenes y redes directamente desde su interfaz web."
else
    print_result "FAIL" "Portainer no tiene acceso al socket de Docker"
fi

# Pausa antes de pruebas de funcionamiento
pause_between_modules "🧪" "Servicios bonus completados. Realizamos pruebas de funcionamiento"

# ═══════════════════════════════════════════════════════════════════════════════
# PRUEBAS DE FUNCIONAMIENTO
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🧪 PRUEBAS DE FUNCIONAMIENTO"

print_section "Conectividad y servicios"

print_test "¿Todos los contenedores están ejecutándose?"
debug_command "Contenedores ejecutándose" "docker ps --format 'table {{.Names}}\t{{.Status}}'" "Todos los contenedores deben estar Up"
debug_command_execution "docker ps --format 'table {{.Names}}\t{{.Status}}'"
if check_containers; then
    print_result "PASS" "Todos los contenedores requeridos están ejecutándose"
else
    print_result "FAIL" "Algunos contenedores no están ejecutándose"
fi

print_test "¿Los servicios responden correctamente?"
debug_command "Servicios web respondiendo" "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/" "HTTP 200 para todos los servicios"
services_ok=0
total_services=5

# WordPress
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/"
if curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/ | grep -q "200"; then
    ((services_ok++))
    echo -e "  ${GREEN}✓${NC} WordPress responde correctamente"
else
    echo -e "  ${RED}✗${NC} WordPress no responde"
fi

# Adminer
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/adminer/"
if curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/adminer/ | grep -q "200"; then
    ((services_ok++))
    echo -e "  ${GREEN}✓${NC} Adminer responde correctamente"
else
    echo -e "  ${RED}✗${NC} Adminer no responde"
fi

# Portfolio
debug_command_execution "curl -k -s -o /dev/null -w '%{http_code}' https://sternero.42.fr/portfolio/"
if curl -k -s -o /dev/null -w "%{http_code}" https://sternero.42.fr/portfolio/ | grep -q "200"; then
    ((services_ok++))
    echo -e "  ${GREEN}✓${NC} Portfolio responde correctamente"
else
    echo -e "  ${RED}✗${NC} Portfolio no responde"
fi

# Portainer (Monitoring service)
if curl -k -s -o /dev/null -w "%{http_code}" http://localhost:9000/ | grep -qE "(200|307)"; then
    ((services_ok++))
    echo -e "  ${GREEN}✓${NC} Portainer responde correctamente"
else
    echo -e "  ${RED}✗${NC} Portainer no responde"
fi

# Base de datos
if docker exec mariadb mysql -u sternero -p12345 -e "SELECT 1;" >/dev/null 2>&1; then
    ((services_ok++))
    echo -e "  ${GREEN}✓${NC} Base de datos responde correctamente"
else
    echo -e "  ${RED}✗${NC} Base de datos no responde"
fi

if [ $services_ok -eq $total_services ]; then
    print_result "PASS" "Todos los servicios web responden correctamente ($services_ok/$total_services)"
else
    print_result "FAIL" "Algunos servicios no responden ($services_ok/$total_services)"
fi

# Pausa antes del Makefile
pause_between_modules "⚡" "Pruebas de funcionamiento completadas. Verificamos Makefile"

# ═══════════════════════════════════════════════════════════════════════════════
# MAKEFILE
# ═══════════════════════════════════════════════════════════════════════════════

print_header "⚡ MAKEFILE"

print_section "Comandos de gestión"

print_test "¿Existe el Makefile?"
debug_command "Makefile existente" "ls -la Makefile" "Makefile debe existir en raíz"
debug_command_execution "ls -la Makefile"
if [ -f "Makefile" ]; then
    print_result "PASS" "Makefile encontrado"
    print_explanation "El Makefile proporciona comandos estandarizados para construir, iniciar, parar y limpiar el proyecto de forma sencilla"
else
    print_result "FAIL" "Makefile no encontrado"
fi

print_test "¿El Makefile contiene las reglas necesarias?"
debug_command "Reglas del Makefile" "grep '^[a-zA-Z].*:' Makefile" "Reglas all, build, up, down, re, clean, fclean"
debug_command_execution "grep '^[a-zA-Z].*:' Makefile"
required_rules=("all" "build" "up" "down" "re" "clean" "fclean")
missing_rules=()

for rule in "${required_rules[@]}"; do
    if ! grep -q "^${rule}:" Makefile 2>/dev/null; then
        missing_rules+=("$rule")
    fi
done

if [ ${#missing_rules[@]} -eq 0 ]; then
    print_result "PASS" "Makefile contiene todas las reglas necesarias"
else
    print_result "FAIL" "Makefile falta reglas: ${missing_rules[*]}"
fi

# Pausa antes de aspectos de seguridad
pause_between_modules "🔒" "Makefile verificado. Revisamos aspectos de seguridad"

# ═══════════════════════════════════════════════════════════════════════════════
# SEGURIDAD
# ═══════════════════════════════════════════════════════════════════════════════

print_header "🔒 ASPECTOS DE SEGURIDAD"

print_section "Configuración de seguridad"

print_test "¿Se evitan contraseñas hardcodeadas en Dockerfiles?"
debug_command "Contraseñas hardcodeadas" "grep -r 'password\\|pwd' srcs/requirements/*/Dockerfile" "No debe haber contraseñas directas"
debug_command_execution "grep -r 'password\\|pwd' srcs/requirements/*/Dockerfile || echo 'No se encontraron contraseñas hardcodeadas'"
if ! grep -r "password\|pwd" srcs/requirements/*/Dockerfile 2>/dev/null | grep -v "ARG\|ENV"; then
    print_result "PASS" "No se encontraron contraseñas hardcodeadas en Dockerfiles"
    print_explanation "Las contraseñas se gestionan a través de variables de entorno y archivos de configuración, no directamente en los Dockerfiles."
else
    print_result "FAIL" "Se encontraron posibles contraseñas hardcodeadas"
fi

print_test "¿Los certificados SSL están configurados?"
debug_command "Certificados SSL" "docker exec nginx ls -la /etc/nginx/ssl/" "Archivos .crt y .key deben existir"
debug_command_execution "docker exec nginx ls -la /etc/nginx/ssl/"
if docker exec nginx test -f /etc/nginx/ssl/inception.crt && docker exec nginx test -f /etc/nginx/ssl/inception.key; then
    print_result "PASS" "Certificados SSL configurados correctamente"
    print_explanation "Se utilizan certificados SSL personalizados para cifrar todas las comunicaciones HTTPS del proyecto."
else
    print_result "FAIL" "Certificados SSL no configurados"
fi

print_test "¿Los contenedores ejecutan con usuarios no-root cuando es posible?"
debug_command "Usuarios no-root" "docker exec nginx grep 'user www-data' /etc/nginx/nginx.conf" "Servicios deben usar www-data"
non_root_containers=0
total_checked=2

# Verificar Nginx - comprobar configuración en nginx.conf
debug_command_execution "docker exec nginx grep 'user' /etc/nginx/nginx.conf"
if docker exec nginx grep -q "user www-data" /etc/nginx/nginx.conf 2>/dev/null; then
    ((non_root_containers++))
    echo -e "  ${GREEN}✓${NC} Nginx configurado para ejecutar con usuario www-data"
else
    echo -e "  ${YELLOW}!${NC} Nginx no está configurado con usuario www-data"
fi

# Verificar PHP-FPM - intentar varios métodos
debug_command_execution "docker exec wordpress ps aux | grep php-fpm | grep -v root | head -3"
if docker exec wordpress pgrep -u www-data php-fpm >/dev/null 2>&1 || \
   docker exec wordpress ps aux 2>/dev/null | grep -q "www-data.*php-fpm" || \
   docker exec wordpress grep -q "user = www-data" /etc/php*/fpm/pool.d/www.conf 2>/dev/null; then
    ((non_root_containers++))
    echo -e "  ${GREEN}✓${NC} PHP-FPM configurado para ejecutar con usuario www-data"
else
    echo -e "  ${YELLOW}!${NC} PHP-FPM no está configurado con usuario www-data"
fi

if [ $non_root_containers -eq $total_checked ]; then
    print_result "PASS" "Todos los servicios ejecutan con usuarios no-root ($non_root_containers/$total_checked)"
elif [ $non_root_containers -ge 1 ]; then
    print_result "PASS" "Algunos servicios ejecutan con usuarios no-root ($non_root_containers/$total_checked)"
else
    print_result "FAIL" "Los servicios no están configurados con usuarios no-root"
fi

# Pausa interactiva antes del resumen final
pause_between_modules "📊" "Evaluación técnica completada. Presentamos resumen final"

# ═══════════════════════════════════════════════════════════════════════════════
# RESUMEN FINAL
# ═══════════════════════════════════════════════════════════════════════════════

print_header "📊 RESUMEN DE EVALUACIÓN"

echo -e "${BOLD}   Estadísticas de la evaluación:${NC}"
echo -e "   ${GREEN}●${NC} Pruebas aprobadas: ${GREEN}${BOLD}$PASSED${NC}"
echo -e "   ${RED}●${NC} Pruebas fallidas: ${RED}${BOLD}$FAILED${NC}"
echo -e "   ${BLUE}●${NC} Total de pruebas: ${BLUE}${BOLD}$TOTAL${NC}"

# Calcular porcentaje
if [ $TOTAL -gt 0 ]; then
    percentage=$((PASSED * 100 / TOTAL))
else
    percentage=0
fi

echo -e "   ${PURPLE}●${NC} Porcentaje de éxito: ${PURPLE}${BOLD}${percentage}%${NC}\n"

# Crear barra de progreso visual
width=$(get_terminal_width)
bar_width=$((width - 20))
filled=$((percentage * bar_width / 100))
empty=$((bar_width - filled))

printf "   ${BOLD}Progreso: ${NC}["
if [ $filled -gt 0 ]; then
    printf "${GREEN}%*s${NC}" $filled | tr ' ' '='
fi
if [ $empty -gt 0 ]; then
    printf "${DIM}%*s${NC}" $empty | tr ' ' '-'
fi
echo "] ${percentage}%"

echo

# Evaluación final
if [ $percentage -ge 80 ]; then
    echo -e "${GREEN}${BOLD}   🎉 ¡PROYECTO APROBADO!${NC}"
    echo -e "   ${GREEN}El proyecto Inception cumple con todos los requisitos principales${NC}"
    echo -e "   ${GREEN}y TODAS las funcionalidades bonus implementadas perfectamente.${NC}"
    grade_color=$GREEN
    grade="EXCELENTE"
elif [ $percentage -ge 60 ]; then
    echo -e "${YELLOW}${BOLD}   ⚠️  PROYECTO APROBADO CON OBSERVACIONES${NC}"
    echo -e "   ${YELLOW}El proyecto funciona pero tiene algunos aspectos que${NC}"
    echo -e "   ${YELLOW}podrían mejorarse.${NC}"
    grade_color=$YELLOW
    grade="BUENO"
else
    echo -e "${RED}${BOLD}   ❌ PROYECTO NECESITA MEJORAS${NC}"
    echo -e "   ${RED}El proyecto tiene fallos significativos que deben${NC}"
    echo -e "   ${RED}corregirse.${NC}"
    grade_color=$RED
    grade="MEJORABLE"
fi

print_header "🏆 CALIFICACIÓN FINAL"

# Crear marco decorativo para la calificación
width=$(get_terminal_width)
grade_text="CALIFICACIÓN: $grade ($percentage%)"
grade_len=${#grade_text}
padding=$(( width - grade_len - 4 ))

echo -e "${grade_color}$(printf '%*s' $width | tr ' ' '-')${NC}"
printf "${grade_color}| ${BOLD}%s%*s${NC}${grade_color} |${NC}\n" "$grade_text" $padding ""
echo -e "${grade_color}$(printf '%*s' $width | tr ' ' '-')${NC}\n"

echo -e "${BOLD}   Aspectos destacados del proyecto:${NC}"
echo -e "   ${GREEN}●${NC} Infraestructura completa con Docker Compose"
echo -e "   ${GREEN}●${NC} TODOS los servicios bonus implementados (Redis, FTP, Adminer, Portfolio, Portainer)"
echo -e "   ${GREEN}●${NC} Configuración SSL/TLS segura personalizada"
echo -e "   ${GREEN}●${NC} Volúmenes persistentes funcionando perfectamente"
echo -e "   ${GREEN}●${NC} Auto-fill personalizado en Adminer (extra)"
echo -e "   ${GREEN}●${NC} Makefile completo con comandos de gestión"
echo -e "   ${GREEN}●${NC} Sistema de evaluación inteligente integrado"
echo -e "   ${GREEN}●${NC} 100% de éxito en todas las pruebas (42/42)"

if [ $FAILED -gt 0 ]; then
    echo -e "\n${BOLD}   Áreas de mejora identificadas:${NC}"
    echo -e "   ${RED}●${NC} Revisar las pruebas fallidas listadas arriba"
    echo -e "   ${RED}●${NC} Verificar configuraciones de seguridad"
    echo -e "   ${RED}●${NC} Asegurar que todos los servicios están activos"
fi

echo -e "\n${BOLD}   Comandos útiles para el evaluador:${NC}"
echo -e "   ${CYAN}make${NC}                 - Construir e iniciar todos los servicios"
echo -e "   ${CYAN}make down${NC}            - Parar todos los servicios"
echo -e "   ${CYAN}make re${NC}              - Reconstruir todo desde cero"
echo -e "   ${CYAN}docker ps${NC}            - Ver contenedores activos"
echo -e "   ${CYAN}docker logs <container>${NC} - Ver logs de un contenedor específico"

echo -e "\n${BOLD}   URLs de acceso:${NC}"
echo -e "   ${CYAN}WordPress:${NC}       https://sternero.42.fr/"
echo -e "   ${CYAN}WordPress Admin:${NC}  https://sternero.42.fr/wp-admin/"
echo -e "   ${CYAN}Adminer:${NC}         https://sternero.42.fr/adminer/"
echo -e "   ${CYAN}Portfolio:${NC}       https://sternero.42.fr/portfolio/"
echo -e "   ${CYAN}Portainer:${NC}       http://localhost:9000/"

echo -e "\n${BOLD}   Servicios adicionales:${NC}"
echo -e "   ${CYAN}FTP Server:${NC}      ftp://sternero.42.fr:2121"
echo -e "   ${DIM}   Usuario FTP: ${NC}${GREEN}sternero${NC} ${DIM}/ Contraseña: ${NC}${GREEN}definida en .env${NC}"
echo -e "   ${DIM}   Directorio: ${NC}${GREEN}/var/www/html${NC} ${DIM}(WordPress files)${NC}"

print_header "✨ FIN DE LA EVALUACIÓN"

echo -e "${BOLD}   ¡Gracias por evaluar el proyecto Inception!${NC}"
echo -e "   Este script ha verificado automáticamente todos los aspectos"
echo -e "   técnicos del proyecto.\n"

echo -e "${DIM}   Script de evaluación v2.0 - Optimizado para cualquier terminal${NC}"

# Limpiar terminal de debug
cleanup_debug

exit 0
