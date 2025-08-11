#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    eval_url.sh                                       :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: sternero <sternero@student.42malaga.com>  +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025-08-07 by sternero          #+#    #+#             #
#    Updated: 2025-08-07 by sternero         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# Script para abrir URLs de servicios en el navegador para evaluación manual

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
BOLD='\033[1m'
RESET='\033[0m'

# Function to print headers
print_header() {
    echo -e "\n${CYAN}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
    echo -e "${CYAN}${BOLD} $1${RESET}"
    echo -e "${CYAN}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
}

# Function to detect browser
detect_browser() {
    if command -v firefox >/dev/null 2>&1; then
        echo "firefox"
    elif command -v google-chrome >/dev/null 2>&1; then
        echo "google-chrome"
    elif command -v chromium-browser >/dev/null 2>&1; then
        echo "chromium-browser"
    elif command -v chromium >/dev/null 2>&1; then
        echo "chromium"
    else
        echo ""
    fi
}

# Function to detect FTP client
detect_ftp_client() {
    if command -v filezilla >/dev/null 2>&1; then
        echo "filezilla"
    elif command -v nautilus >/dev/null 2>&1; then
        echo "nautilus"
    elif command -v dolphin >/dev/null 2>&1; then
        echo "dolphin"
    elif command -v thunar >/dev/null 2>&1; then
        echo "thunar"
    else
        echo ""
    fi
}

# Function to check service status
check_service() {
    local service="$1"
    if docker ps --format "{{.Names}}" | grep -q "^$service$"; then
        echo -e "${GREEN}✅ $service${RESET}"
    else
        echo -e "${RED}❌ $service${RESET}"
    fi
}

# Function to mask password for display
mask_password() {
    local password="$1"
    local length=${#password}
    if [ $length -gt 0 ]; then
        printf '*%.0s' $(seq 1 $length)
    fi
}

# Function to show password securely
show_password() {
    local label="$1"
    local password="$2"
    local masked=$(mask_password "$password")
    
    echo -e "${WHITE}   $label: ${YELLOW}$masked${RESET} ${CYAN}(presiona 's' para mostrar)${RESET}"
    
    # Allow user to reveal password if needed
    if [ -t 0 ]; then  # Check if running interactively
        read -n 1 -s key 2>/dev/null
        if [ "$key" = "s" ] || [ "$key" = "S" ]; then
            echo -e "${WHITE}   ${MAGENTA}→ Password: ${GREEN}$password${RESET}"
        fi
    else
        # Non-interactive mode, show password directly
        echo -e "${WHITE}   ${MAGENTA}→ Password: ${GREEN}$password${RESET}"
    fi
}

# Load environment
clear
print_header "🌐 EVALUADOR DE SERVICIOS WEB - INCEPTION"

if [ -f ".env" ]; then
    echo -e "${GREEN}✅ Cargando configuración desde .env${RESET}"
    set -a; source .env; set +a
    DOMAIN=${DOMAIN_NAME:-"sternero.42.fr"}
else
    echo -e "${YELLOW}⚠️  Usando configuración por defecto${RESET}"
    DOMAIN="sternero.42.fr"
fi

# Check services
echo -e "\n${CYAN}🔍 Estado de servicios:${RESET}"
check_service "nginx"
check_service "wordpress"
check_service "mariadb"
check_service "redis"
check_service "ftp-server"
check_service "adminer"
check_service "website"
check_service "portainer"

# Ask user preference
print_header "🚀 MODO DE APERTURA"
echo -e "${WHITE}1. ${GREEN}Automático${RESET} - Abrir todas las pestañas en una ventana"
echo -e "${WHITE}2. ${CYAN}Manual${RESET} - Mostrar URLs para copiar/pegar"
echo ""
read -p "$(echo -e ${YELLOW})Selecciona opción (1/2) [2]: $(echo -e ${RESET})" choice
choice=${choice:-2}

# Define URLs
URLS=(
    "https://$DOMAIN"
    "https://$DOMAIN/wp-admin/"
    "https://$DOMAIN/adminer/"
    "https://$DOMAIN/portfolio/"
    "http://localhost:9000"
)

FTP_URL="ftp://$DOMAIN:2121"

DESCRIPTIONS=(
    "WordPress - Sitio Principal"
    "WordPress - Panel Admin (admin: sternero/12345 | user: sergio/12345)"
    "Adminer - Base de Datos (con auto-fill)"
    "Portfolio - Sitio Estático"
    "Portainer - Gestión Docker"
)

if [ "$choice" = "1" ]; then
    # Automatic mode
    BROWSER=$(detect_browser)
    FTP_CLIENT=$(detect_ftp_client)
    
    if [ -z "$BROWSER" ]; then
        echo -e "${RED}❌ No se encontró navegador compatible${RESET}"
        echo -e "${YELLOW}   Instala Firefox, Chrome o Chromium${RESET}"
        exit 1
    fi
    
    echo -e "\n${GREEN}✅ Navegador detectado: ${BOLD}$BROWSER${RESET}"
    
    if [ -n "$FTP_CLIENT" ]; then
        echo -e "${GREEN}✅ Cliente FTP detectado: ${BOLD}$FTP_CLIENT${RESET}"
    else
        echo -e "${YELLOW}⚠️  No se encontró cliente FTP gráfico${RESET}"
        echo -e "${YELLOW}   Recomendado: sudo apt install filezilla${RESET}"
    fi
    
    echo -e "${CYAN}🚀 Abriendo servicios...${RESET}"
    
    # Open all URLs
    for i in "${!URLS[@]}"; do
        url="${URLS[$i]}"
        desc="${DESCRIPTIONS[$i]}"
        
        echo -e "${WHITE}🌐 ${desc}${RESET}"
        echo -e "${BLUE}   $url${RESET}"
        
        # First URL opens new window, rest as tabs
        if [ $i -eq 0 ]; then
            $BROWSER --new-window "$url" >/dev/null 2>&1 &
        else
            sleep 2  # Wait for window to open
            $BROWSER --new-tab "$url" >/dev/null 2>&1 &
        fi
        
        echo -e "${GREEN}   ✅ Abierto${RESET}"
        sleep 1
    done
    
    # Open FTP if client is available
    echo -e "\n${WHITE}📁 Abriendo cliente FTP...${RESET}"
    echo -e "${BLUE}   $FTP_URL${RESET}"
    
    if [ -n "$FTP_CLIENT" ]; then
        case "$FTP_CLIENT" in
            "filezilla")
                # Open FileZilla with pre-filled credentials
                echo -e "${GREEN}   🚀 Abriendo FileZilla con credenciales...${RESET}"
                filezilla "ftp://${FTP_USER:-sternero}:12345@$DOMAIN:2121" >/dev/null 2>&1 &
                sleep 1
                # Fallback: open FileZilla without credentials if above fails
                if ! pgrep filezilla >/dev/null 2>&1; then
                    echo -e "${YELLOW}   ⚠️  Reintentando FileZilla...${RESET}"
                    filezilla >/dev/null 2>&1 &
                fi
                ;;
            "nautilus")
                # Open file manager with FTP
                echo -e "${GREEN}   🚀 Abriendo Nautilus (Files)...${RESET}"
                nautilus "ftp://${FTP_USER:-sternero}@$DOMAIN:2121" >/dev/null 2>&1 &
                ;;
            "dolphin")
                echo -e "${GREEN}   🚀 Abriendo Dolphin...${RESET}"
                dolphin "ftp://${FTP_USER:-sternero}@$DOMAIN:2121" >/dev/null 2>&1 &
                ;;
            "thunar")
                echo -e "${GREEN}   🚀 Abriendo Thunar...${RESET}"
                thunar "ftp://${FTP_USER:-sternero}@$DOMAIN:2121" >/dev/null 2>&1 &
                ;;
        esac
        echo -e "${GREEN}   ✅ Cliente FTP $FTP_CLIENT iniciado${RESET}"
        echo -e "${CYAN}   💡 Si FileZilla no se conecta automáticamente, usa:${RESET}"
        echo -e "${WHITE}      Servidor: ${GREEN}$DOMAIN${RESET}"
        echo -e "${WHITE}      Puerto: ${GREEN}2121${RESET}"
        echo -e "${WHITE}      Usuario: ${GREEN}${FTP_USER:-sternero}${RESET}"
        echo -e "${WHITE}      Contraseña: ${GREEN}12345${RESET}"
        echo -e "${YELLOW}   ⚠️  Mensaje normal: 'Insecure server, it does not support FTP over TLS'${RESET}"
        echo -e "${CYAN}      Esto es esperado para FTP básico - continúa la conexión${RESET}"
        sleep 2
    else
        echo -e "${YELLOW}   ⚠️  No hay cliente FTP instalado${RESET}"
        echo -e "${WHITE}   ${CYAN}sudo apt install filezilla${RESET} - Instalar FileZilla"
        echo -e "${WHITE}   ${CYAN}sudo apt install nautilus${RESET} - Instalar Files (GNOME)"
        echo -e "${WHITE}   URL manual: ${BLUE}$FTP_URL${RESET}"
        
        # Try to open browser with FTP URL as fallback
        if [ -n "$BROWSER" ]; then
            echo -e "${WHITE}   💡 Intentando abrir FTP en navegador...${RESET}"
            $BROWSER "$FTP_URL" >/dev/null 2>&1 &
            echo -e "${GREEN}   ✅ FTP abierto en navegador${RESET}"
        fi
    fi
    
    echo -e "\n${GREEN}${BOLD}✨ ¡Todas las aplicaciones abiertas!${RESET}"
    
    echo -e "\n${YELLOW}${BOLD}🔑 Credenciales WordPress:${RESET}"
    echo -e "${WHITE}   ${GREEN}Administrador:${RESET}"
    echo -e "${WHITE}     Usuario: ${GREEN}sternero${RESET}"
    show_password "    Contraseña" "12345"
    echo -e "${WHITE}   ${CYAN}Usuario regular:${RESET}"
    echo -e "${WHITE}     Usuario: ${GREEN}sergio${RESET}"
    show_password "    Contraseña" "12345"
    
    echo -e "\n${YELLOW}${BOLD}🗄️  Credenciales Adminer:${RESET}"
    echo -e "${WHITE}   Servidor: ${GREEN}mariadb${RESET}"
    echo -e "${WHITE}   Puerto: ${GREEN}3306${RESET} ${CYAN}(dejar vacío si no aparece)${RESET}"
    echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
    show_password "Contraseña" "12345"
    echo -e "${WHITE}   Base de datos: ${GREEN}wordpress_db${RESET}"
    echo -e "${CYAN}   💡 Si no auto-completa, introduce manualmente${RESET}"
    
    if [ -n "$FTP_CLIENT" ]; then
        echo -e "\n${YELLOW}${BOLD}📁 Credenciales FTP:${RESET}"
        echo -e "${WHITE}   Servidor: ${GREEN}$DOMAIN${RESET}"
        echo -e "${WHITE}   Puerto: ${GREEN}2121${RESET}"
        echo -e "${WHITE}   Usuario: ${GREEN}${FTP_USER:-sternero}${RESET}"
        show_password "Contraseña" "12345"
        echo -e "${WHITE}   Directorio: ${GREEN}/var/www/html${RESET}"
    fi
    
else
    # Manual mode
    print_header "📋 URLS PARA ABRIR MANUALMENTE"
    
    for i in "${!URLS[@]}"; do
        url="${URLS[$i]}"
        desc="${DESCRIPTIONS[$i]}"
        
        echo -e "\n${CYAN}${BOLD}🌐 $desc${RESET}"
        echo -e "${WHITE}   URL: ${BLUE}${BOLD}$url${RESET}"
        echo -e "${WHITE}   ${MAGENTA}Ctrl+Click para abrir${RESET}"
    done
    
    echo -e "\n${CYAN}${BOLD}📁 Servidor FTP:${RESET}"
    echo -e "${WHITE}   URL: ${BLUE}${BOLD}$FTP_URL${RESET}"
    echo -e "${WHITE}   Servidor: ${GREEN}$DOMAIN${RESET}"
    echo -e "${WHITE}   Puerto: ${GREEN}2121${RESET}"
    echo -e "${WHITE}   Usuario: ${GREEN}${FTP_USER:-sternero}${RESET}"
    show_password "Contraseña" "12345"
    echo -e "${WHITE}   Directorio: ${GREEN}/var/www/html${RESET}"
    echo -e "${WHITE}   ${MAGENTA}Usar cliente FTP (FileZilla recomendado)${RESET}"
    
    echo -e "\n${YELLOW}${BOLD}🔑 Credenciales WordPress:${RESET}"
    echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
    show_password "Contraseña" "12345"
    
    echo -e "\n${YELLOW}${BOLD}🗄️  Credenciales Adminer:${RESET}"
    echo -e "${WHITE}   Servidor: ${GREEN}mariadb${RESET}"
    echo -e "${WHITE}   Puerto: ${GREEN}3306${RESET} ${CYAN}(dejar vacío si no aparece)${RESET}"
    echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
    show_password "Contraseña" "12345"
    echo -e "${WHITE}   Base de datos: ${GREEN}wordpress_db${RESET}"
    echo -e "${CYAN}   💡 Si auto-fill no funciona, copiar estos datos${RESET}"
fi

print_header "📋 CHECKLIST DE EVALUACIÓN"

echo -e "${WHITE}${BOLD}🔍 Verificar en cada servicio:${RESET}"

echo -e "\n${MAGENTA}🌐 WordPress Principal:${RESET}"
echo -e "${WHITE}   ☐ Página carga correctamente${RESET}"
echo -e "${WHITE}   ☐ Certificado SSL válido (icono candado/escudo en URL)${RESET}"
echo -e "${WHITE}   ☐ Contenido visible${RESET}"

echo -e "\n${MAGENTA}🔐 WordPress Admin:${RESET}"
echo -e "${WHITE}   ☐ Login funciona (sternero/12345)${RESET}"
echo -e "${WHITE}   ☐ Dashboard accesible${RESET}"
echo -e "${WHITE}   ☐ Puede editar contenido${RESET}"

echo -e "\n${MAGENTA}🗄️  Adminer:${RESET}"
echo -e "${WHITE}   ☐ Interfaz carga${RESET}"
echo -e "${WHITE}   ☐ Conecta a mariadb:3306${RESET}"
echo -e "${WHITE}   ☐ Base de datos visible${RESET}"

echo -e "\n${MAGENTA}👤 Portfolio:${RESET}"
echo -e "${WHITE}   ☐ Sitio estático funcional${RESET}"
echo -e "${WHITE}   ☐ Diseño correcto${RESET}"

echo -e "\n${MAGENTA}⚡ Redis Cache:${RESET}"
echo -e "${WHITE}   ☐ Servicio activo (docker ps)${RESET}"
echo -e "${WHITE}   ☐ WordPress conecta correctamente${RESET}"
echo -e "${WHITE}   ☐ Mejora rendimiento visible${RESET}"

echo -e "\n${MAGENTA}🐳 Portainer:${RESET}"
echo -e "${WHITE}   ☐ Interfaz accesible${RESET}"
echo -e "${WHITE}   ☐ Contenedores visibles${RESET}"

echo -e "\n${MAGENTA}📁 FTP:${RESET}"
echo -e "${WHITE}   ☐ Conexión exitosa${RESET}"
echo -e "${WHITE}   ☐ Acceso a /var/www/html${RESET}"

print_header "🛠️  COMANDOS ÚTILES"

echo -e "${YELLOW}${BOLD}🔧 Diagnóstico:${RESET}"
echo -e "${WHITE}   • ${CYAN}make status${RESET} - Estado servicios"
echo -e "${WHITE}   • ${CYAN}make logs${RESET} - Ver logs"
echo -e "${WHITE}   • ${CYAN}docker ps${RESET} - Contenedores activos"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli ping${RESET} - Verificar Redis"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli info stats${RESET} - Estadísticas Redis"

echo -e "\n${RED}${BOLD}🚨 Troubleshooting:${RESET}"
echo -e "${WHITE}   • ${CYAN}docker restart portainer${RESET} - Si Portainer está bloqueado (auto-lock 5 min)${RESET}"
echo -e "${WHITE}   • ${CYAN}docker logs adminer${RESET} - Si Adminer no auto-completa"
echo -e "${WHITE}   • ${CYAN}docker logs nginx${RESET} - Si WordPress admin no carga"
echo -e "${WHITE}   • ${CYAN}docker logs ftp-server${RESET} - Si FTP no conecta"
echo -e "${WHITE}   • ${CYAN}sudo apt install filezilla${RESET} - Instalar cliente FTP"
echo -e "${YELLOW}   • ${RED}FTP TLS warning${RESET} - Mensaje 'Insecure server' es normal, acepta y continúa"

echo -e "\n${MAGENTA}${BOLD}🔑 Credenciales Adminer (COPIA ESTOS DATOS):${RESET}"
echo -e "${WHITE}   ${CYAN}Sistema:${RESET} ${GREEN}MySQL${RESET}"
echo -e "${WHITE}   ${CYAN}Servidor:${RESET} ${GREEN}mariadb${RESET}"
echo -e "${WHITE}   ${CYAN}Puerto:${RESET} ${GREEN}3306${RESET} ${YELLOW}(dejar vacío en el form)${RESET}"
echo -e "${WHITE}   ${CYAN}Usuario:${RESET} ${GREEN}sternero${RESET}"
echo -e "${WHITE}   ${CYAN}Contraseña:${RESET} ${GREEN}12345${RESET}"
echo -e "${WHITE}   ${CYAN}Base de datos:${RESET} ${GREEN}wordpress_db${RESET}"
echo -e "${RED}   ⚠️  ${YELLOW}Auto-fill puede no funcionar, usar estos datos manualmente${RESET}"

echo -e "\n${MAGENTA}${BOLD}📁 Credenciales FTP:${RESET}"
echo -e "${WHITE}   Servidor: ${GREEN}$DOMAIN${RESET}"
echo -e "${WHITE}   Puerto: ${GREEN}2121${RESET}"
echo -e "${WHITE}   Usuario: ${GREEN}${FTP_USER:-sternero}${RESET}"
echo -e "${WHITE}   Contraseña: ${GREEN}12345${RESET}"
echo -e "${WHITE}   Directorio: ${GREEN}/var/www/html${RESET}"

echo -e "\n${GREEN}${BOLD}✨ ¡Listo para evaluar!${RESET}"
echo -e "${CYAN}Buena suerte con la evaluación 🚀${RESET}"

# Interactive evaluation guide
echo -e "\n${YELLOW}${BOLD}🎯 ¿Quieres una guía interactiva de evaluación?${RESET}"
read -p "$(echo -e ${CYAN})Presiona Enter para continuar con la demo guiada o Ctrl+C para salir: $(echo -e ${RESET})"

# Function for interactive pauses
wait_for_user() {
    local message="$1"
    echo -e "\n${CYAN}${BOLD}👆 $message${RESET}"
    read -p "$(echo -e ${GREEN})Presiona Enter cuando hayas terminado...$(echo -e ${RESET})"
}

# Function to show step header
show_step() {
    local step="$1"
    local title="$2"
    echo -e "\n${MAGENTA}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
    echo -e "${MAGENTA}${BOLD} PASO $step: $title${RESET}"
    echo -e "${MAGENTA}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
}

print_header "🎪 DEMO GUIADA INTERACTIVA"

echo -e "${WHITE}Esta guía te llevará paso a paso por cada servicio${RESET}"
echo -e "${WHITE}mostrando las funcionalidades más impresionantes.${RESET}"
echo -e "${CYAN}¡Perfecto para causar una buena impresión! ✨${RESET}"

# Step 1: WordPress Main Site
show_step "1" "WORDPRESS - SITIO PRINCIPAL"
echo -e "${WHITE}🌐 URL: ${BLUE}https://$DOMAIN${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Certificado SSL válido (icono de candado en URL)${RESET}"
echo -e "${WHITE}   ✅ Página WordPress completamente funcional${RESET}"
echo -e "${WHITE}   ✅ Diseño responsive y profesional${RESET}"
echo -e "${WHITE}   ✅ Velocidad de carga rápida${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Haz clic en el icono de candado/escudo junto a la URL${RESET}"
echo -e "${WHITE}      ${CYAN}• Firefox: Icono de candado/escudo a la izquierda de https://${RESET}"
echo -e "${WHITE}      ${CYAN}• Chrome: Candado verde/gris a la izquierda de la URL${RESET}"
echo -e "${WHITE}      ${YELLOW}• Certificado autofirmado - normal para desarrollo${RESET}"
echo -e "${WHITE}   2. Navega por las diferentes secciones del sitio${RESET}"
echo -e "${WHITE}   3. Redimensiona la ventana para mostrar responsive design${RESET}"
echo -e "${WHITE}   4. Inspecciona el código fuente (F12) para mostrar WordPress${RESET}"

wait_for_user "Explora el sitio principal de WordPress"

# Step 2: WordPress Admin
show_step "2" "WORDPRESS - PANEL DE ADMINISTRACIÓN"
echo -e "${WHITE}🔐 URL: ${BLUE}https://$DOMAIN/wp-admin/${RESET}"
echo -e "\n${YELLOW}${BOLD}🔑 Credenciales:${RESET}"
echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
echo -e "${WHITE}   Contraseña: ${GREEN}12345${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Login funciona perfectamente${RESET}"
echo -e "${WHITE}   ✅ Dashboard completo de WordPress${RESET}"
echo -e "${WHITE}   ✅ Gestión de contenido en tiempo real${RESET}"
echo -e "${WHITE}   ✅ Conexión con base de datos MariaDB${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Haz login con las credenciales${RESET}"
echo -e "${WHITE}   2. Ve a 'Entradas' → 'Añadir nueva' y crea un post${RESET}"
echo -e "${WHITE}      ${CYAN}• Título: 'Demo de Persistencia - Evaluación'${RESET}"
echo -e "${WHITE}      ${CYAN}• Contenido: 'Este post demuestra la persistencia de datos'${RESET}"
echo -e "${WHITE}      ${CYAN}• Publica inmediatamente${RESET}"
echo -e "${WHITE}   3. Ve a 'Apariencia' → 'Personalizar' para mostrar opciones${RESET}"
echo -e "${WHITE}   4. Ve a 'Usuarios' para mostrar gestión de usuarios${RESET}"
echo -e "${WHITE}   5. Ve a 'Comentarios' para gestionar moderación${RESET}"
echo -e "${WHITE}   6. ${YELLOW}IMPORTANTE${RESET}: Activa comentarios en 'Ajustes' → 'Comentarios'${RESET}"

wait_for_user "Explora el panel de administración de WordPress"

# Step 2.5: Prepare for persistence demo
show_step "2.5" "PREPARAR DEMO DE PERSISTENCIA"
echo -e "${WHITE}🎯 Configuración previa para la demo impresionante${RESET}"

echo -e "\n${YELLOW}${BOLD}🔑 Credenciales para WordPress Admin:${RESET}"
echo -e "${WHITE}   ${GREEN}Administrador:${RESET} ${GREEN}sternero${RESET} | Contraseña: ${GREEN}12345${RESET}"
echo -e "${WHITE}   ${CYAN}Usuario regular:${RESET} ${GREEN}sergio${RESET} | Contraseña: ${GREEN}12345${RESET}"
echo -e "${WHITE}   ${YELLOW}💡 Usa el administrador (sternero) para estas configuraciones${RESET}"

echo -e "\n${YELLOW}${BOLD}🔧 Configuraciones necesarias:${RESET}"
echo -e "${WHITE}   1. En WP Admin → 'Ajustes' → 'Comentarios'${RESET}"
echo -e "${WHITE}      ${CYAN}• Marca: 'Los usuarios deben estar registrados para comentar' = NO${RESET}"
echo -e "${WHITE}      ${CYAN}• Marca: 'Comentario debe ser aprobado manualmente' = SÍ${RESET}"
echo -e "${WHITE}      ${CYAN}• Guarda cambios${RESET}"
echo -e "${WHITE}   2. Crea una entrada de prueba:${RESET}"
echo -e "${WHITE}      ${CYAN}• Título: '🔥 DEMO PERSISTENCIA - Evaluación $(date +'%H:%M')'${RESET}"
echo -e "${WHITE}      ${CYAN}• Contenido: 'Este post demuestra la persistencia completa de datos'${RESET}"
echo -e "${WHITE}      ${CYAN}• Publica inmediatamente${RESET}"
echo -e "${WHITE}   3. Ve al sitio principal y busca tu entrada${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Esto prepara la demo de persistencia más impresionante${RESET}"

wait_for_user "Configura WordPress para la demo de persistencia"

# Step 3: Adminer Database
show_step "3" "ADMINER - GESTIÓN DE BASE DE DATOS"
echo -e "${WHITE}🗄️  URL: ${BLUE}https://$DOMAIN/adminer/${RESET}"
echo -e "\n${YELLOW}${BOLD}🔑 Credenciales (COPIAR MANUALMENTE):${RESET}"
echo -e "${WHITE}   Sistema: ${GREEN}MySQL${RESET}"
echo -e "${WHITE}   Servidor: ${GREEN}mariadb${RESET}"
echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
echo -e "${WHITE}   Contraseña: ${GREEN}12345${RESET}"
echo -e "${WHITE}   Base de datos: ${GREEN}wordpress_db${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Conexión directa a MariaDB${RESET}"
echo -e "${WHITE}   ✅ Visualización de todas las tablas de WordPress${RESET}"
echo -e "${WHITE}   ✅ Datos en tiempo real${RESET}"
echo -e "${WHITE}   ✅ Capacidad de ejecutar consultas SQL${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Conecta usando las credenciales de arriba${RESET}"
echo -e "${WHITE}   2. Explora la tabla 'wp_posts' para ver entradas${RESET}"
echo -e "${WHITE}      ${CYAN}• Busca tu post de 'DEMO PERSISTENCIA'${RESET}"
echo -e "${WHITE}      ${CYAN}• Nota el post_id para referencia${RESET}"
echo -e "${WHITE}   3. Ve a 'wp_comments' para ver comentarios${RESET}"
echo -e "${WHITE}      ${CYAN}• Verifica comment_post_ID coincide con tu post${RESET}"
echo -e "${WHITE}      ${CYAN}• Observa comment_approved (0=pendiente, 1=aprobado)${RESET}"
echo -e "${WHITE}   4. Ejecuta consultas útiles:${RESET}"
echo -e "${WHITE}      ${CYAN}• SELECT * FROM wp_options WHERE option_name = 'siteurl'${RESET}"
echo -e "${WHITE}      ${CYAN}• SELECT * FROM wp_posts WHERE post_title LIKE '%DEMO%'${RESET}"
echo -e "${WHITE}      ${CYAN}• SELECT * FROM wp_comments ORDER BY comment_date DESC${RESET}"
echo -e "${WHITE}   5. Muestra el esquema de la base de datos${RESET}"

wait_for_user "Explora la base de datos con Adminer"

# Step 4: Portfolio Site
show_step "4" "PORTFOLIO - SITIO ESTÁTICO"
echo -e "${WHITE}👤 URL: ${BLUE}https://$DOMAIN/portfolio/${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Sitio estático completamente funcional${RESET}"
echo -e "${WHITE}   ✅ Diseño moderno y atractivo${RESET}"
echo -e "${WHITE}   ✅ Optimización de recursos${RESET}"
echo -e "${WHITE}   ✅ Separación de servicios (estático vs dinámico)${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Navega por las diferentes secciones${RESET}"
echo -e "${WHITE}   2. Inspecciona el código para mostrar tecnologías usadas${RESET}"
echo -e "${WHITE}   3. Muestra la velocidad de carga (Network tab en DevTools)${RESET}"
echo -e "${WHITE}   4. Compara con WordPress para mostrar diferencias${RESET}"

wait_for_user "Explora el sitio portfolio"

# Step 5: Redis Cache
show_step "5" "REDIS - CACHE PARA WORDPRESS"
echo -e "${WHITE}⚡ Servicio: ${BLUE}Cache interno (sin interfaz gráfica)${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Mejora significativa del rendimiento de WordPress${RESET}"
echo -e "${WHITE}   ✅ Cache de objetos y consultas de base de datos${RESET}"
echo -e "${WHITE}   ✅ Configuración automática con WordPress${RESET}"
echo -e "${WHITE}   ✅ Monitoreo del servicio Redis${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas para demostrar Redis:${RESET}"
echo -e "${WHITE}   1. Abrir dos ventanas del navegador lado a lado${RESET}"
echo -e "${WHITE}   2. En terminal ejecutar: ${CYAN}docker logs redis --tail=20 --follow${RESET}"
echo -e "${WHITE}      ${YELLOW}• Verás las conexiones de WordPress a Redis${RESET}"
echo -e "${WHITE}   3. En una ventana navegar por WordPress (varias páginas)${RESET}"
echo -e "${WHITE}      ${YELLOW}• Observa los logs de Redis procesando cache${RESET}"
echo -e "${WHITE}   4. En Portainer → Containers → redis → Stats${RESET}"
echo -e "${WHITE}      ${YELLOW}• Muestra uso de memoria y CPU${RESET}"
echo -e "${WHITE}   5. Comando técnico: ${CYAN}docker exec redis redis-cli info stats${RESET}"
echo -e "${WHITE}      ${YELLOW}• Muestra estadísticas detalladas de Redis${RESET}"
echo -e "${WHITE}   6. Comando avanzado: ${CYAN}docker exec redis redis-cli monitor${RESET}"
echo -e "${WHITE}      ${YELLOW}• Muestra comandos Redis en tiempo real${RESET}"
echo -e "\n${MAGENTA}${BOLD}🔧 Comandos útiles para la demo:${RESET}"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli ping${RESET} - Verificar conectividad"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli info memory${RESET} - Uso de memoria"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli dbsize${RESET} - Número de claves cacheadas"
echo -e "${WHITE}   • ${CYAN}docker exec redis redis-cli keys wp:*${RESET} - Ver claves de WordPress"
echo -e "\n${YELLOW}${BOLD}💡 Explicación para el evaluador:${RESET}"
echo -e "${WHITE}   Redis actúa como cache de objetos para WordPress,${RESET}"
echo -e "${WHITE}   almacenando consultas de base de datos en memoria${RESET}"
echo -e "${WHITE}   para acelerar significativamente la carga de páginas.${RESET}"
echo -e "${WHITE}   ${GREEN}Es un bonus service que demuestra optimización avanzada.${RESET}"

wait_for_user "Demuestra el funcionamiento de Redis como cache"

# Step 6: Portainer
show_step "6" "PORTAINER - GESTIÓN DOCKER"
echo -e "${WHITE}🐳 URL: ${BLUE}http://localhost:9000${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Interfaz gráfica para Docker${RESET}"
echo -e "${WHITE}   ✅ Todos los contenedores visibles${RESET}"
echo -e "${WHITE}   ✅ Monitoreo en tiempo real${RESET}"
echo -e "${WHITE}   ✅ Gestión completa del stack${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Ve a 'Containers' para ver todos los servicios${RESET}"
echo -e "${WHITE}   2. Haz clic en un contenedor para ver detalles${RESET}"
echo -e "${WHITE}   3. Ve a 'Images' para mostrar imágenes Docker${RESET}"
echo -e "${WHITE}   4. Explora 'Networks' para ver la red inception${RESET}"
echo -e "${WHITE}   5. Ve a 'Volumes' para mostrar almacenamiento persistente${RESET}"
echo -e "${WHITE}   6. Muestra logs en tiempo real de un contenedor${RESET}"

echo -e "\n${RED}${BOLD}⚠️  IMPORTANTE - SEGURIDAD PORTAINER:${RESET}"
echo -e "${RED}   🔒 Portainer se bloquea automáticamente tras 5 minutos${RESET}"
echo -e "${RED}   🔐 Esto previene configuraciones no autorizadas${RESET}"
echo -e "${YELLOW}   🔧 Si se bloquea, ejecuta: ${CYAN}docker restart portainer${RESET}"
echo -e "${YELLOW}   ⏰ Luego ve inmediatamente a http://localhost:9000${RESET}"

wait_for_user "Explora la gestión Docker con Portainer"

# Step 7: FTP Server
show_step "7" "SERVIDOR FTP - ACCESO A ARCHIVOS"
echo -e "${WHITE}📁 Cliente FTP recomendado: ${GREEN}FileZilla${RESET}"
echo -e "\n${YELLOW}${BOLD}🔑 Credenciales:${RESET}"
echo -e "${WHITE}   Servidor: ${GREEN}$DOMAIN${RESET}"
echo -e "${WHITE}   Puerto: ${GREEN}2121${RESET}"
echo -e "${WHITE}   Usuario: ${GREEN}sternero${RESET}"
echo -e "${WHITE}   Contraseña: ${GREEN}12345${RESET}"
echo -e "\n${RED}${BOLD}⚠️  IMPORTANTE - Mensaje esperado:${RESET}"
echo -e "${YELLOW}   'Insecure server, it does not support FTP over TLS'${RESET}"
echo -e "${CYAN}   → Esto es NORMAL para FTP básico${RESET}"
echo -e "${CYAN}   → Haz clic en 'OK' o 'Continue' para proceder${RESET}"
echo -e "${CYAN}   → NO canceles la conexión${RESET}"
echo -e "\n${YELLOW}${BOLD}🎯 Qué mostrar:${RESET}"
echo -e "${WHITE}   ✅ Conexión FTP exitosa${RESET}"
echo -e "${WHITE}   ✅ Acceso directo a archivos de WordPress${RESET}"
echo -e "${WHITE}   ✅ Capacidad de subir/descargar archivos${RESET}"
echo -e "${WHITE}   ✅ Gestión de permisos${RESET}"
echo -e "\n${GREEN}${BOLD}💡 Acciones recomendadas:${RESET}"
echo -e "${WHITE}   1. Conecta con FileZilla usando las credenciales${RESET}"
echo -e "${WHITE}   2. ${YELLOW}ACEPTA${RESET} el mensaje sobre TLS (es normal)${RESET}"
echo -e "${WHITE}   3. Navega a /var/www/html para ver archivos WordPress${RESET}"
echo -e "${WHITE}   4. Explora wp-content/themes para mostrar temas${RESET}"
echo -e "${WHITE}   5. Sube un archivo de prueba (ej: test.txt)${RESET}"
echo -e "${WHITE}   6. Descarga un archivo para probar transferencia${RESET}"
echo -e "${WHITE}   7. Ve los permisos de archivos (chmod)${RESET}"

wait_for_user "Explora el servidor FTP"

# Final Demo Tips
show_step "8" "TIPS FINALES PARA IMPRESIONAR"
echo -e "\n${YELLOW}${BOLD}🚀 Demostraciones avanzadas:${RESET}"
echo -e "${WHITE}   1. ${CYAN}Persistencia de datos (DEMO IMPRESIONANTE):${RESET}"
echo -e "${WHITE}      ${GREEN}Paso A${RESET}: En WordPress Admin crea una entrada con título:"
echo -e "${WHITE}         '🔥 DEMO PERSISTENCIA - [Fecha actual]'"
echo -e "${WHITE}      ${GREEN}Paso B${RESET}: Ve al sitio principal y deja un comentario en esa entrada:"
echo -e "${WHITE}         'Comentario de prueba para demostrar persistencia'"
echo -e "${WHITE}      ${GREEN}Paso C${RESET}: Vuelve al admin y modera el comentario (apruébalo)"
echo -e "${WHITE}      ${GREEN}Paso D${RESET}: En Adminer, busca en wp_posts tu nueva entrada"
echo -e "${WHITE}      ${GREEN}Paso E${RESET}: En terminal ejecuta: ${CYAN}docker restart wordpress mariadb${RESET}"
echo -e "${WHITE}      ${GREEN}Paso F${RESET}: Verifica que TODO persiste después del reinicio"
echo -e "${WHITE}      ${YELLOW}¡El evaluador verá persistencia real en acción!${RESET}"
echo -e "\n${WHITE}   2. ${CYAN}Integración Redis:${RESET}"
echo -e "${WHITE}      • En Portainer, muestra el contenedor Redis${RESET}"
echo -e "${WHITE}      • Explica que acelera WordPress${RESET}"
echo -e "\n${WHITE}   3. ${CYAN}Networking Docker:${RESET}"
echo -e "${WHITE}      • En Portainer → Networks → inception${RESET}"
echo -e "${WHITE}      • Muestra cómo se comunican los contenedores${RESET}"
echo -e "\n${WHITE}   4. ${CYAN}SSL/TLS:${RESET}"
echo -e "${WHITE}      • Muestra certificados en el navegador${RESET}"
echo -e "${WHITE}      • ${YELLOW}Firefox${RESET}: Haz clic en el candado/escudo → 'Conexión segura'${RESET}"
echo -e "${WHITE}      • ${YELLOW}Chrome${RESET}: Haz clic en el candado → 'Certificado válido'${RESET}"
echo -e "${WHITE}      • ${CYAN}Certificado autofirmado${RESET} - CN=sternero.42.fr, esperado para el proyecto${RESET}"
echo -e "${WHITE}      • Explica la configuración de Nginx${RESET}"
echo -e "\n${WHITE}   5. ${CYAN}Monitoreo:${RESET}"
echo -e "${WHITE}      • Usa Portainer para mostrar uso de recursos${RESET}"
echo -e "${WHITE}      • Muestra logs de cada servicio${RESET}"

echo -e "\n${RED}${BOLD}🔧 Comandos útiles durante la demo:${RESET}"
echo -e "${WHITE}   • ${CYAN}docker ps${RESET} - Ver contenedores activos${RESET}"
echo -e "${WHITE}   • ${CYAN}docker logs [container]${RESET} - Ver logs específicos${RESET}"
echo -e "${WHITE}   • ${CYAN}docker exec -it [container] bash${RESET} - Acceder a contenedor${RESET}"
echo -e "${WHITE}   • ${CYAN}make status${RESET} - Estado general del proyecto${RESET}"
echo -e "${WHITE}   • ${YELLOW}Para demo persistencia${RESET}:${RESET}"
echo -e "${WHITE}     ${CYAN}docker restart wordpress mariadb${RESET} - Reiniciar servicios principales${RESET}"
echo -e "${WHITE}     ${CYAN}docker-compose restart${RESET} - Reiniciar todo el stack${RESET}"

echo -e "\n${GREEN}${BOLD}🎉 ¡DEMO COMPLETADA!${RESET}"
echo -e "${WHITE}Has recorrido todos los servicios principales.${RESET}"
echo -e "${CYAN}El evaluador debería estar impresionado con:${RESET}"
echo -e "${WHITE}   ✅ Arquitectura multi-contenedor${RESET}"
echo -e "${WHITE}   ✅ Servicios funcionando perfectamente${RESET}"
echo -e "${WHITE}   ✅ Gestión profesional con Docker${RESET}"
echo -e "${WHITE}   ✅ Seguridad (SSL, credenciales)${RESET}"
echo -e "${WHITE}   ✅ Persistencia de datos${RESET}"
echo -e "${WHITE}   ✅ Monitoreo y gestión${RESET}"

echo -e "\n${MAGENTA}${BOLD}🎭 GRAN FINAL - DEMO DE PERSISTENCIA COMPLETA:${RESET}"
echo -e "${WHITE}Si quieres hacer la demo más impresionante:${RESET}"
echo -e "\n${GREEN}${BOLD}1.${RESET} ${WHITE}Ve al sitio principal (https://$DOMAIN)${RESET}"
echo -e "${GREEN}${BOLD}2.${RESET} ${WHITE}Busca tu post 'DEMO PERSISTENCIA' y deja un comentario${RESET}"
echo -e "${GREEN}${BOLD}3.${RESET} ${WHITE}Ve al admin y aprueba el comentario en 'Comentarios'${RESET}"
echo -e "${WHITE}     ${CYAN}💡 Usa usuario administrador: ${GREEN}sternero${RESET} | Contraseña: ${GREEN}12345${RESET}"
echo -e "${WHITE}     ${CYAN}💡 También puedes usar usuario regular: ${GREEN}sergio${RESET} | Contraseña: ${GREEN}12345${RESET}"
echo -e "${GREEN}${BOLD}4.${RESET} ${WHITE}En Adminer, ejecuta: ${CYAN}SELECT * FROM wp_comments${RESET}"
echo -e "${GREEN}${BOLD}5.${RESET} ${WHITE}En terminal: ${CYAN}docker restart wordpress mariadb${RESET}"
echo -e "${GREEN}${BOLD}6.${RESET} ${WHITE}Espera 30 segundos y vuelve a comprobar todo${RESET}"
echo -e "${GREEN}${BOLD}7.${RESET} ${WHITE}¡Post, comentarios y datos persisten! 🎉${RESET}"
echo -e "\n${YELLOW}Esta demo muestra persistencia real de datos en acción${RESET}"
echo -e "${CYAN}y demuestra que tu arquitectura Docker es robusta.${RESET}"

echo -e "\n${YELLOW}${BOLD}💫 ¡Buena suerte con tu evaluación!${RESET} 🚀"