#!/bin/bash

##############################################################################
# run_all_evaluations.sh - Script maestro para ejecutar todas las evaluaciones
# Ejecuta todos los scripts de evaluación en ORDEN OFICIAL
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

echo -e "${CYAN}============================================================"
echo -e "  🚀 WEBSERV - SUITE COMPLETA DE EVALUACIÓN 🚀"
echo -e "============================================================${NC}"
echo ""
echo -e "${WHITE}Esta suite ejecuta todas las verificaciones de la hoja de evaluación"
echo -e "del proyecto webserv de 42 School en ORDEN OFICIAL.${NC}"
echo ""

# Lista de scripts de evaluación (en orden OFICIAL de evaluación)
SCRIPTS=(
    "01_siege_installation.sh"
    "02_http_basics.sh"
    "03_io_multiplexing.sh"
    "04_select_explanation.sh"
    "05_only_one_select.sh"
    "06_read_write_per_select.sh"
    "07_error_handling.sh"
    "08_errno_check.sh"
    "09_fd_through_select.sh"
    "10_compilation_check.sh"
    "11_configuration.sh"
    "12_port_configuration.sh"
    "13_basic_requests.sh"
    "14_file_upload_download.sh"
    "15_cgi_testing.sh"
    "16_browser_compatibility.sh"
    "17_stress_testing.sh"
    "18_bonus_features.sh"
)

# Descripciones de los scripts (siguiendo orden OFICIAL de evaluación)
DESCRIPTIONS=(
    "🍺 PRIMER PASO: Instalación de Siege"
    "Explicación de conceptos básicos HTTP"
    "Función usada para I/O Multiplexing"
    "Explicación de funcionamiento de select()"
    "⚠️  CRÍTICO: Solo un select() (eliminatorio)"
    "Solo un read/write por cliente por select()"
    "Manejo de errores en operaciones de socket"
    "⚠️  CRÍTICO: Verificación de errno (eliminatorio)"
    "⚠️  CRÍTICO: Todo I/O debe pasar por select()"
    "Compilación sin problemas de re-link"
    "Archivo de configuración y características"
    "Configuración de múltiples puertos"
    "Requests básicos (GET/POST/DELETE)"
    "Sistema de upload/download de archivos"
    "Testing de funcionalidad CGI"
    "Compatibilidad con navegador web"
    "Stress testing con Siege (>99.5%)"
    "Características bonus (cookies, múltiples CGI)"
)

# Función para mostrar menú
show_menu() {
    echo -e "${CYAN}=========================================="
    echo -e "  📋 MENÚ DE EVALUACIÓN"
    echo -e "==========================================${NC}"
    echo ""
    echo -e "${WHITE}Selecciona una opción:${NC}"
    echo ""
    echo -e "${GREEN}0)${NC} ${WHITE}Ejecutar TODAS las evaluaciones en secuencia${NC}"
    echo ""
    
    for i in "${!SCRIPTS[@]}"; do
        num=$((i + 1))
        script="${SCRIPTS[$i]}"
        desc="${DESCRIPTIONS[$i]}"
        
        if [[ "$desc" == *"CRÍTICO"* ]]; then
            echo -e "${RED}$num)${NC} ${YELLOW}$desc${NC}"
        else
            echo -e "${BLUE}$num)${NC} ${WHITE}$desc${NC}"
        fi
    done
    
    echo ""
    echo -e "${PURPLE}19)${NC} ${WHITE}Salir${NC}"
    echo ""
}

# Función para ejecutar un script específico
run_script() {
    local script="$1"
    local desc="$2"
    
    echo -e "${CYAN}============================================================${NC}"
    echo -e "${WHITE}🔧 Ejecutando: $desc${NC}"
    echo -e "${CYAN}============================================================${NC}"
    echo ""
    
    if [ -f "./$script" ] && [ -x "./$script" ]; then
        ./"$script"
        local exit_code=$?
        
        echo ""
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✅ Evaluación completada: $script${NC}"
        else
            echo -e "${RED}❌ Evaluación falló: $script (código: $exit_code)${NC}"
            
            # Si es el script de errno (crítico), detener todo
            if [[ "$script" == "08_errno_check.sh" ]] && [ $exit_code -ne 0 ]; then
                echo -e "${RED}🚨 EVALUACIÓN CRÍTICA FALLIDA - DETENIENDO EJECUCIÓN${NC}"
                return 1
            fi
        fi
    else
        echo -e "${RED}❌ Script no encontrado o no ejecutable: $script${NC}"
        return 1
    fi
    
    echo ""
    echo -e "${YELLOW}Presiona Enter para continuar...${NC}"
    read -r
    
    return 0
}

# Función para ejecutar todos los scripts
run_all() {
    echo -e "${CYAN}🚀 Iniciando evaluación completa...${NC}"
    echo ""
    
    local failed_count=0
    local total_count=${#SCRIPTS[@]}
    
    for i in "${!SCRIPTS[@]}"; do
        script="${SCRIPTS[$i]}"
        desc="${DESCRIPTIONS[$i]}"
        
        echo -e "${BLUE}📊 Progreso: $((i + 1))/$total_count${NC}"
        
        if ! run_script "$script" "$desc"; then
            failed_count=$((failed_count + 1))
            
            # Si falla el script crítico de errno, detener
            if [[ "$script" == "08_errno_check.sh" ]]; then
                echo -e "${RED}🛑 EVALUACIÓN TERMINADA - Error crítico detectado${NC}"
                return 1
            fi
        fi
    done
    
    echo -e "${CYAN}============================================================${NC}"
    echo -e "${WHITE}📊 RESUMEN FINAL DE EVALUACIÓN${NC}"
    echo -e "${CYAN}============================================================${NC}"
    echo ""
    
    local passed_count=$((total_count - failed_count))
    echo -e "${GREEN}✅ Evaluaciones exitosas: $passed_count/$total_count${NC}"
    
    if [ $failed_count -gt 0 ]; then
        echo -e "${RED}❌ Evaluaciones fallidas: $failed_count/$total_count${NC}"
        echo ""
        echo -e "${YELLOW}⚠️  Revisar los scripts que fallaron antes de la evaluación final${NC}"
    else
        echo -e "${GREEN}🎉 ¡TODAS LAS EVALUACIONES EXITOSAS!${NC}"
        echo -e "${GREEN}✅ El proyecto está listo para la evaluación${NC}"
    fi
    
    return 0
}

# Bucle principal del menú
while true; do
    clear
    show_menu
    
    echo -e "${CYAN}Ingresa tu opción (0-19): ${NC}"
    read -r choice
    
    case $choice in
        0)
            clear
            run_all
            echo ""
            echo -e "${YELLOW}Presiona Enter para volver al menú...${NC}"
            read -r
            ;;
        [1-9]|1[0-8])
            if [ "$choice" -le "${#SCRIPTS[@]}" ]; then
                clear
                script_index=$((choice - 1))
                script="${SCRIPTS[$script_index]}"
                desc="${DESCRIPTIONS[$script_index]}"
                run_script "$script" "$desc"
            else
                echo -e "${RED}Opción inválida${NC}"
                sleep 1
            fi
            ;;
        19)
            echo -e "${GREEN}👋 ¡Hasta luego! Buena suerte en la evaluación${NC}"
            exit 0
            ;;
        *)
            echo -e "${RED}Opción inválida. Selecciona 0-19${NC}"
            sleep 1
            ;;
    esac
done
