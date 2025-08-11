#!/bin/bash

#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    create_env.sh                                      :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: sternero <sternero@student.42malaga.com>  +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025-08-06 13:25:00 by sternero          #+#    #+#             #
#    Updated: 2025-08-06 13:25:00 by sternero         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# Colors for professional output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
BOLD='\033[1m'
RESET='\033[0m'

# Professional header
clear
echo -e "${CYAN}${BOLD}"
echo "╔══════════════════════════════════════════════════════════════════════════════╗"
echo "║                           INCEPTION PROJECT                                  ║"
echo "║                     Environment Configuration Wizard                        ║"
echo "║                                                                              ║"
echo "║                          🐳 Docker Infrastructure 🐳                         ║"
echo "╚══════════════════════════════════════════════════════════════════════════════╝"
echo -e "${RESET}"

# Check and remove existing .env file
if [ -f .env ]; then
    echo -e "${YELLOW}⚠️  Existing .env file found${RESET}"
    echo -e "${WHITE}Removing previous configuration to ensure clean setup...${RESET}"
    rm -f .env
    echo -e "${GREEN}✓ Previous .env file removed${RESET}"
    echo ""
fi

echo -e "${WHITE}Configuring environment variables for multi-container Docker deployment${RESET}"
echo -e "${YELLOW}Press Enter to use default values shown in brackets${RESET}"
echo ""

# Obtener información del sistema
CURRENT_USER=$(whoami)
CREATION_DATE=$(date '+%Y-%m-%d %H:%M:%S')
TIMEZONE=$(date '+%Z %z')

# Function to prompt for password with default
prompt_password() {
    local prompt_text="$1"
    local default_value="$2"
    local password=""
    
    read -s -p "$(echo -e ${GREEN})${prompt_text} [$(echo -e ${RED})***$(echo -e ${GREEN})]: $(echo -e ${RESET})" password
    echo ""
    if [ -z "$password" ]; then
        password="$default_value"
    fi
    # Use tr to remove any potential newlines or carriage returns
    echo "$password" | tr -d '\n\r'
}

# ===============================================================================
# SECTION 1: DOMAIN CONFIGURATION
# ===============================================================================
echo -e "${CYAN}${BOLD}[1/5] 🌐 Domain Configuration${RESET}"
echo -e "${WHITE}──────────────────────────────────────${RESET}"
read -p "$(echo -e ${GREEN})Domain name [${CURRENT_USER}.42.fr]: $(echo -e ${RESET})" DOMAIN_NAME
DOMAIN_NAME=${DOMAIN_NAME:-"${CURRENT_USER}.42.fr"}
echo -e "${GREEN}✓ Domain configured: ${DOMAIN_NAME}${RESET}"
echo ""

# ===============================================================================
# SECTION 2: DATABASE CONFIGURATION  
# ===============================================================================
echo -e "${CYAN}${BOLD}[2/5] 📊 MariaDB Database Configuration${RESET}"
echo -e "${WHITE}──────────────────────────────────────────────${RESET}"
MARIADB_ROOT_PASSWORD=$(prompt_password "MariaDB root password" "12345")

read -p "$(echo -e ${GREEN})Database name [wordpress_db]: $(echo -e ${RESET})" MARIADB_DATABASE
MARIADB_DATABASE=${MARIADB_DATABASE:-"wordpress_db"}

read -p "$(echo -e ${GREEN})Database user [${CURRENT_USER}]: $(echo -e ${RESET})" MARIADB_USER
MARIADB_USER=${MARIADB_USER:-"${CURRENT_USER}"}

MARIADB_PASSWORD=$(prompt_password "Database user password" "12345")
echo -e "${GREEN}✓ Database configuration completed${RESET}"
echo ""

# ===============================================================================
# SECTION 3: WORDPRESS CONFIGURATION
# ===============================================================================
echo -e "${CYAN}${BOLD}[3/5] 🌐 WordPress CMS Configuration${RESET}"
echo -e "${WHITE}────────────────────────────────────────${RESET}"
read -p "$(echo -e ${GREEN})Site title [\"Inception Project - ${CURRENT_USER}\"]: $(echo -e ${RESET})" TITLE
TITLE=${TITLE:-"\"Inception Project - ${CURRENT_USER}\""}

read -p "$(echo -e ${GREEN})Admin username [${CURRENT_USER}]: $(echo -e ${RESET})" WORDPRESS_ADMIN_USER
WORDPRESS_ADMIN_USER=${WORDPRESS_ADMIN_USER:-"${CURRENT_USER}"}

WORDPRESS_ADMIN_PWD=$(prompt_password "Admin password" "12345")

read -p "$(echo -e ${GREEN})Admin email [${CURRENT_USER}@student.42malaga.com]: $(echo -e ${RESET})" WORDPRESS_ADMIN_EMAIL
WORDPRESS_ADMIN_EMAIL=${WORDPRESS_ADMIN_EMAIL:-"${CURRENT_USER}@student.42malaga.com"}

echo -e "${WHITE}Additional WordPress User:${RESET}"
read -p "$(echo -e ${GREEN})Additional user name [sergio]: $(echo -e ${RESET})" WORDPRESS_USER
WORDPRESS_USER=${WORDPRESS_USER:-"sergio"}

read -p "$(echo -e ${GREEN})Additional user email [sergio@example.com]: $(echo -e ${RESET})" WORDPRESS_USER_EMAIL
WORDPRESS_USER_EMAIL=${WORDPRESS_USER_EMAIL:-"sergio@example.com"}

WORDPRESS_PASSWORD=$(prompt_password "Additional user password" "12345")
echo -e "${GREEN}✓ WordPress configuration completed${RESET}"
echo ""

# ===============================================================================
# SECTION 4: BONUS SERVICES CONFIGURATION
# ===============================================================================
echo -e "${CYAN}${BOLD}[4/5] 🎯 Bonus Services Configuration${RESET}"
echo -e "${WHITE}───────────────────────────────────────────${RESET}"
echo -e "${MAGENTA}Configuring Redis Cache, FTP Server & Adminer${RESET}"
echo ""

echo -e "${WHITE}Redis Cache Configuration:${RESET}"
REDIS_PASSWORD=$(prompt_password "Redis password" "12345")
echo -e "${GREEN}✓ Redis cache configured${RESET}"
echo ""

echo -e "${WHITE}FTP Server Configuration:${RESET}"
read -p "$(echo -e ${GREEN})FTP username [${CURRENT_USER}]: $(echo -e ${RESET})" FTP_USER
FTP_USER=${FTP_USER:-"${CURRENT_USER}"}

FTP_PASSWORD=$(prompt_password "FTP password" "12345")
echo -e "${GREEN}✓ FTP server configured${RESET}"
echo ""

# ===============================================================================
# SECTION 5: PORTAINER CONFIGURATION
# ===============================================================================
echo -e "${CYAN}${BOLD}[5/5] 🐳 Portainer Container Management${RESET}"
echo -e "${WHITE}─────────────────────────────────────────────${RESET}"
echo -e "${GREEN}✓ Portainer configured for Docker management${RESET}"
echo -e "${WHITE}  • Web interface on port 9000${RESET}"
echo -e "${WHITE}  • Docker socket access enabled${RESET}"
echo ""

echo -e "${GREEN}✓ All services configuration completed${RESET}"
echo ""

# ===============================================================================
# GENERATING CONFIGURATION FILE
# ===============================================================================
echo -e "${YELLOW}${BOLD}🔧 Generating .env configuration file...${RESET}"

# Clean variables to ensure no line breaks
CLEAN_MARIADB_ROOT_PASSWORD=$(echo "$MARIADB_ROOT_PASSWORD" | tr -d '\n\r')
CLEAN_MARIADB_PASSWORD=$(echo "$MARIADB_PASSWORD" | tr -d '\n\r')
CLEAN_WORDPRESS_ADMIN_PWD=$(echo "$WORDPRESS_ADMIN_PWD" | tr -d '\n\r')
CLEAN_WORDPRESS_PASSWORD=$(echo "$WORDPRESS_PASSWORD" | tr -d '\n\r')
CLEAN_REDIS_PASSWORD=$(echo "$REDIS_PASSWORD" | tr -d '\n\r')
CLEAN_FTP_PASSWORD=$(echo "$FTP_PASSWORD" | tr -d '\n\r')

# Crear el archivo .env
cat > .env << EOF
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    .env - Environment Configuration                   :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: ${CURRENT_USER} <${CURRENT_USER}@student.42malaga.com>  +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: ${CREATION_DATE} by ${CURRENT_USER}          #+#    #+#             #
#    Updated: ${CREATION_DATE} by ${CURRENT_USER}         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# INCEPTION PROJECT - DOCKER INFRASTRUCTURE CONFIGURATION
# =============================================================================
# 
# This file contains environment variables for the Inception project,
# a multi-container Docker infrastructure featuring:
#   • WordPress CMS with PHP-FPM
#   • MariaDB Database Server  
#   • Nginx Web Server with TLS
#   • Redis Cache (Bonus)
#   • FTP Server (Bonus)
#   • Adminer Database Manager (Bonus)
#   • Static Portfolio Website (Bonus)
#   • Portainer Container Management (Bonus)
#
# Generated on: ${CREATION_DATE} (${TIMEZONE})
# Target user: ${CURRENT_USER}
# =============================================================================
# Domain configuration
DOMAIN_NAME=${DOMAIN_NAME}

# SSL certificates paths
CERTS_CRT_PATH=/etc/nginx/ssl/${DOMAIN_NAME}.crt
CERTS_KEY_PATH=/etc/nginx/ssl/${DOMAIN_NAME}.key

# MariaDB configuration
MARIADB_ROOT_PASSWORD=${CLEAN_MARIADB_ROOT_PASSWORD}
MARIADB_DATABASE=${MARIADB_DATABASE}
MARIADB_USER=${MARIADB_USER}
MARIADB_PASSWORD=${CLEAN_MARIADB_PASSWORD}

# WordPress database configuration
WORDPRESS_DB_NAME=${MARIADB_DATABASE}
WORDPRESS_DB_USER=${MARIADB_USER}
WORDPRESS_DB_PASSWORD=${CLEAN_MARIADB_PASSWORD}
WORDPRESS_DB_HOST=mariadb
WORDPRESS_PATH=/var/www/html
WORDPRESS_URL=https://${DOMAIN_NAME}

# WordPress site configuration
TITLE=${TITLE}
WORDPRESS_ADMIN_USER=${WORDPRESS_ADMIN_USER}
WORDPRESS_PASSWORD=${CLEAN_WORDPRESS_ADMIN_PWD}
WORDPRESS_ADMIN_EMAIL=${WORDPRESS_ADMIN_EMAIL}

# WordPress additional user
WORDPRESS_USER=${WORDPRESS_USER}
WORDPRESS_USER_EMAIL=${WORDPRESS_USER_EMAIL}

# Data locations
WORDPRESS_DATA_LOCATION="/home/${CURRENT_USER}/Inception/data/wordpress"
MARIADB_DATA_LOCATION="/home/${CURRENT_USER}/Inception/data/database"
PORTAINER_DATA_LOCATION="/home/${CURRENT_USER}/Inception/data/portainer"
SSL_CERTS_LOCATION="/home/${CURRENT_USER}/Inception/data/ssl-certs"

# BONUS SERVICES #
# Redis configuration
REDIS_PASSWORD=${CLEAN_REDIS_PASSWORD}

# FTP configuration
FTP_USER=${FTP_USER}
FTP_PASSWORD=${CLEAN_FTP_PASSWORD}

# Adminer configuration
ADMINER_DEFAULT_SERVER=mariadb

# Portainer configuration
PORTAINER_PORT=9000
EOF

echo ""
echo -e "${GREEN}${BOLD}╔══════════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${GREEN}${BOLD}║                        ✅ CONFIGURATION COMPLETED                            ║${RESET}"
echo -e "${GREEN}${BOLD}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""
echo -e "${CYAN}📄 Configuration file created: ${BOLD}.env${RESET}"
echo -e "${CYAN}📍 Location: ${BOLD}$(pwd)/.env${RESET}"
echo -e "${CYAN}🕒 Generated: ${BOLD}${CREATION_DATE}${RESET}"
echo ""
echo -e "${BLUE}${BOLD}📁 Project Structure (Optimized):${RESET}"
echo -e "${WHITE}${BOLD}Inception/${RESET}"
echo -e "${WHITE}├── ${CYAN}📄 .env${RESET}                      ${YELLOW}# Centralized configuration${RESET}"
echo -e "${WHITE}├── ${CYAN}📋 Makefile${RESET}                  ${YELLOW}# Project automation${RESET}"
echo -e "${WHITE}├── ${CYAN}🗃️  data/${RESET}                     ${YELLOW}# Persistent data (organized)${RESET}"
echo -e "${WHITE}│   ├── ${MAGENTA}🗄️  database/${RESET}             ${YELLOW}# MariaDB data${RESET}"
echo -e "${WHITE}│   ├── ${MAGENTA}🌐 wordpress/${RESET}            ${YELLOW}# WordPress files${RESET}"
echo -e "${WHITE}│   └── ${MAGENTA}🐳 portainer/${RESET}            ${YELLOW}# Portainer data & config${RESET}"
echo -e "${WHITE}└── ${CYAN}📁 srcs/${RESET}                     ${YELLOW}# Clean source code${RESET}"
echo -e "${WHITE}    ├── ${GREEN}⚙️  docker-compose.yml${RESET}     ${YELLOW}# Service orchestration${RESET}"
echo -e "${WHITE}    └── ${GREEN}📦 requirements/${RESET}          ${YELLOW}# Dockerfiles by service${RESET}"
echo -e "${WHITE}        ├── ${BLUE}🌐 nginx/${RESET}               ${YELLOW}# Web server${RESET}"
echo -e "${WHITE}        ├── ${BLUE}🗄️  mariadb/${RESET}             ${YELLOW}# Database${RESET}"
echo -e "${WHITE}        ├── ${BLUE}📝 wordpress/${RESET}           ${YELLOW}# CMS${RESET}"
echo -e "${WHITE}        └── ${BLUE}🎯 bonus/${RESET}               ${YELLOW}# Additional services${RESET}"
echo -e "${WHITE}            ├── ${MAGENTA}🔄 redis/${RESET}           ${YELLOW}# Cache${RESET}"
echo -e "${WHITE}            ├── ${MAGENTA}📁 ftp/${RESET}             ${YELLOW}# File server${RESET}"
echo -e "${WHITE}            ├── ${MAGENTA}🔧 adminer/${RESET}         ${YELLOW}# DB manager${RESET}"
echo -e "${WHITE}            ├── ${MAGENTA}👤 portfolio/${RESET}       ${YELLOW}# Static site${RESET}"
echo -e "${WHITE}            └── ${MAGENTA}🐳 portainer/${RESET}       ${YELLOW}# Container manager${RESET}"
echo ""
echo -e "${WHITE}${BOLD}📋 Configuration Summary:${RESET}"
echo -e "${WHITE}  ${YELLOW}🌐 Domain:${RESET}        ${BOLD}${DOMAIN_NAME}${RESET}"
echo -e "${WHITE}  ${YELLOW}📊 Database:${RESET}      ${BOLD}${MARIADB_DATABASE}${RESET}"
echo -e "${WHITE}  ${YELLOW}👤 Admin User:${RESET}    ${BOLD}${WORDPRESS_ADMIN_USER}${RESET}"
echo -e "${WHITE}  ${YELLOW}📧 Admin Email:${RESET}   ${BOLD}${WORDPRESS_ADMIN_EMAIL}${RESET}"
echo -e "${WHITE}  ${YELLOW}👥 Extra User:${RESET}    ${BOLD}${WORDPRESS_USER}${RESET}"
echo -e "${WHITE}  ${YELLOW}🎯 Bonus Services:${RESET} ${BOLD}Redis, FTP, Adminer, Portfolio, Portainer${RESET}"
echo ""
echo -e "${GREEN}${BOLD}✨ Structure Benefits:${RESET}"
echo -e "${WHITE}  • ${GREEN}Clean separation${RESET}    - Source code vs persistent data"
echo -e "${WHITE}  • ${GREEN}Easy maintenance${RESET}    - Organized by service function"
echo -e "${WHITE}  • ${GREEN}Backup-friendly${RESET}     - Data grouped for easy backup"
echo -e "${WHITE}  • ${GREEN}Scalable design${RESET}     - Ready for additional services"
echo ""
echo -e "${MAGENTA}${BOLD}🚀 Next Steps:${RESET}"
echo -e "${WHITE}  1. ${CYAN}make all${RESET}        - Build and deploy complete infrastructure"
echo -e "${WHITE}  2. ${CYAN}make setup${RESET}      - Configure domain in /etc/hosts (optional)"
echo -e "${WHITE}  3. ${CYAN}make status${RESET}     - Monitor deployment status"
echo ""
echo -e "${GREEN}Ready to launch your Inception project! 🐳✨${RESET}"
