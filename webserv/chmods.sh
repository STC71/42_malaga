#!/bin/bash

##############################################################################
# chmods.sh - Script para gestión de permisos del proyecto webserv
# 
# Este script otorga los permisos necesarios a todos los archivos y directorios
# del proyecto webserv según su configuración final de funcionamiento.
#
# Uso: ./chmods.sh [check|help]
#       ./chmods.sh        - Aplicar permisos
#       ./chmods.sh check  - Solo verificar permisos
#       ./chmods.sh help   - Mostrar ayuda
##############################################################################

# Configuración de colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

show_help() {
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${WHITE}                    🔧 GESTIÓN DE PERMISOS - WEBSERV PROJECT${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
    echo -e "${YELLOW}USO:${NC}"
    echo -e "  ${WHITE}./chmods.sh${NC}        - Aplicar permisos correctos a todo el proyecto"
    echo -e "  ${WHITE}./chmods.sh check${NC}  - Solo verificar permisos actuales"
    echo -e "  ${WHITE}./chmods.sh help${NC}   - Mostrar esta ayuda"
    echo ""
    echo -e "${YELLOW}PERMISOS APLICADOS:${NC}"
    echo -e "${BLUE}• Directorios:${NC}       755 (rwxr-xr-x)"
    echo -e "${BLUE}• Scripts .sh:${NC}       755 (rwxr-xr-x) - Ejecutables"
    echo -e "${BLUE}• Documentación:${NC}     644 (rw-r--r--) - Solo lectura"
    echo -e "${BLUE}• Código fuente:${NC}     644 (rw-r--r--) - Archivos de texto"
    echo -e "${BLUE}• CGI Scripts:${NC}       755 (rwxr-xr-x) - Ejecutables para web"
    echo -e "${BLUE}• Configuración:${NC}     644 (rw-r--r--) - Archivos config"
    echo ""
    exit 0
}

check_permissions() {
    echo -e "${CYAN}🔍 VERIFICANDO PERMISOS ACTUALES...${NC}"
    echo ""
    
    echo -e "${YELLOW}📄 Scripts de evaluación:${NC}"
    if [[ -d "evaluation_test" ]]; then
        cd evaluation_test
        for script in [0-9][0-9]_*.sh run_all_evaluations.sh; do
            if [[ -f "$script" ]]; then
                if [[ -x "$script" ]]; then
                    echo -e "${GREEN}✓${NC} $script (ejecutable)"
                else
                    echo -e "${RED}✗${NC} $script (NO ejecutable)"
                fi
            fi
        done
        cd ..
    fi
    
    echo ""
    echo -e "${YELLOW}🌐 Scripts CGI:${NC}"
    find www*/cgi-bin -name "*.py" -o -name "*.php" 2>/dev/null | while read -r cgi; do
        if [[ -x "$cgi" ]]; then
            echo -e "${GREEN}✓${NC} $cgi (ejecutable)"
        else
            echo -e "${RED}✗${NC} $cgi (NO ejecutable)"
        fi
    done
    
    echo ""
    echo -e "${YELLOW}📋 Scripts del proyecto:${NC}"
    for script in *.sh; do
        if [[ -f "$script" ]]; then
            if [[ -x "$script" ]]; then
                echo -e "${GREEN}✓${NC} $script (ejecutable)"
            else
                echo -e "${RED}✗${NC} $script (NO ejecutable)"
            fi
        fi
    done
    
    exit 0
}

# Verificar argumentos
if [[ "$1" == "help" ]]; then
    show_help
elif [[ "$1" == "check" ]]; then
    check_permissions
fi

echo -e "${GREEN}🔧 Aplicando permisos del proyecto webserv...${NC}"

# =============================================================================
# PERMISOS DE DIRECTORIOS
# =============================================================================

echo -e "${BLUE}📁 Configurando permisos de directorios...${NC}"

# Directorios principales del proyecto (755 - rwxr-xr-x)
chmod 755 . 2>/dev/null
chmod 755 config 2>/dev/null
chmod 755 evaluation_ask 2>/dev/null
chmod 755 include 2>/dev/null
chmod 755 srcs 2>/dev/null
chmod 755 Uploads 2>/dev/null
chmod 755 .vscode 2>/dev/null
chmod 755 logs 2>/dev/null

# Directorios web (775 - rwxrwxr-x)
chmod 775 www 2>/dev/null
chmod 775 www2 2>/dev/null
chmod 775 www2/cgi-bin 2>/dev/null
chmod 775 www2/errors 2>/dev/null
chmod 775 www2/files 2>/dev/null
chmod 775 www2/Uploads 2>/dev/null
chmod 775 www/errors 2>/dev/null
chmod 775 www/files 2>/dev/null
chmod 775 www/Uploads 2>/dev/null

# Directorio CGI especial (777 - rwxrwxrwx)
chmod 777 www/cgi-bin 2>/dev/null

echo "✅ Permisos de directorios aplicados"

# =============================================================================
# PERMISOS DE ARCHIVOS DEL CÓDIGO FUENTE
# =============================================================================

echo "📄 Configurando permisos de archivos de código fuente..."

# Archivos de código fuente y configuración (644 - rw-r--r--)
chmod 644 config/default.conf 2>/dev/null
chmod 644 include/*.hpp 2>/dev/null
chmod 644 srcs/*.cpp 2>/dev/null
chmod 644 Makefile 2>/dev/null

echo "✅ Permisos de código fuente aplicados"

# =============================================================================
# PERMISOS DE ARCHIVOS DE DOCUMENTACIÓN
# =============================================================================

echo "📚 Configurando permisos de documentación..."

# Archivos de documentación y evaluación (644 - rw-r--r--)
chmod 644 evaluation_ask/*.md 2>/dev/null
chmod 644 evaluation.md 2>/dev/null
chmod 644 readme_evaluation.md 2>/dev/null

# Archivos de documentación en evaluation_test
chmod 644 evaluation_test/*.md 2>/dev/null
chmod 644 evaluation_test/README.md 2>/dev/null
chmod 644 evaluation_test/evaluation_mapping.md 2>/dev/null

chmod 644 headers.txt 2>/dev/null
chmod 644 output.html 2>/dev/null
chmod 644 Uploads/test.txt 2>/dev/null
chmod 644 .vscode/settings.json 2>/dev/null
chmod 644 logs/*.log 2>/dev/null
chmod 644 .siegerc 2>/dev/null

echo "✅ Permisos de documentación aplicados"

# =============================================================================
# PERMISOS DE SCRIPTS EJECUTABLES
# =============================================================================

echo "🚀 Configurando permisos de scripts ejecutables..."

# Scripts ejecutables (755 - rwxr-xr-x)
chmod 755 evaluation.sh 2>/dev/null
chmod 755 stress_tests.sh 2>/dev/null
chmod 755 siege_test.sh 2>/dev/null
chmod 755 browser_test.sh 2>/dev/null

# Scripts de evaluación automatizada
chmod 755 evaluation_test/*.sh 2>/dev/null
chmod 755 evaluation_test/run_all_evaluations.sh 2>/dev/null

echo "✅ Permisos de scripts aplicados"

# =============================================================================
# PERMISOS DE ARCHIVOS WEB
# =============================================================================

echo "🌐 Configurando permisos de archivos web..."

# Archivos HTML principales (775 - rwxrwxr-x)
chmod 775 www/index.html 2>/dev/null
chmod 775 www2/index.html 2>/dev/null

# Archivos de contenido web (775 - rwxrwxr-x)
chmod 775 www/files/file1.txt 2>/dev/null
chmod 775 www/files/file2.txt 2>/dev/null
chmod 775 www2/files/file3.txt 2>/dev/null

# Archivos de uploads (644 - rw-r--r--)
chmod 644 www/Uploads/retrieve_test.txt 2>/dev/null

echo "✅ Permisos de archivos web aplicados"

# =============================================================================
# PERMISOS DE ARCHIVOS DE ERROR
# =============================================================================

echo "⚠️  Configurando permisos de páginas de error..."

# Páginas de error (664 - rw-rw-r--)
chmod 664 www/errors/*.html 2>/dev/null
chmod 664 www2/errors/*.html 2>/dev/null

echo "✅ Permisos de páginas de error aplicados"

# =============================================================================
# PERMISOS DE SCRIPTS CGI
# =============================================================================

echo "⚙️  Configurando permisos de scripts CGI..."

# Scripts CGI ejecutables (755 - rwxr-xr-x)
chmod 755 www/cgi-bin/error.py 2>/dev/null
chmod 755 www/cgi-bin/invalid.php 2>/dev/null
chmod 755 www/cgi-bin/script.php 2>/dev/null
chmod 755 www/cgi-bin/script.py 2>/dev/null
chmod 755 www/cgi-bin/simple.php 2>/dev/null

chmod 755 www2/cgi-bin/script.php 2>/dev/null
chmod 755 www2/cgi-bin/script.py 2>/dev/null
chmod 755 www2/cgi-bin/simple.php 2>/dev/null

# Scripts CGI con permisos especiales (775 - rwxrwxr-x)
chmod 775 www/cgi-bin/test.php 2>/dev/null
chmod 775 www/cgi-bin/test.py 2>/dev/null
chmod 775 www2/cgi-bin/test.php 2>/dev/null
chmod 775 www2/cgi-bin/test.py 2>/dev/null

echo "✅ Permisos de scripts CGI aplicados"

# =============================================================================
# HACER SCRIPTS EJECUTABLES
# =============================================================================

# Hacer este script ejecutable para futuras ejecuciones
chmod 755 "$0" 2>/dev/null
chmod 755 chmods.sh 2>/dev/null

# =============================================================================
# VERIFICACIÓN FINAL
# =============================================================================

echo ""
echo "🔍 Verificación de permisos críticos:"

# Verificar permisos críticos
echo -n "📁 Directorio www/cgi-bin: "
ls -ld www/cgi-bin 2>/dev/null | awk '{print $1}' || echo "❌ No encontrado"

echo -n "🚀 Script evaluation.sh: "
ls -l evaluation.sh 2>/dev/null | awk '{print $1}' || echo "❌ No encontrado"

echo -n "⚡ Script stress_tests.sh: "
ls -l stress_tests.sh 2>/dev/null | awk '{print $1}' || echo "❌ No encontrado"

echo -n "🏛️ Script siege_test.sh: "
ls -l siege_test.sh 2>/dev/null | awk '{print $1}' || echo "❌ No encontrado"

echo -n "⚙️  Scripts CGI: "
ls -l www/cgi-bin/*.py 2>/dev/null | head -1 | awk '{print $1}' || echo "❌ No encontrados"

echo -n "🌐 Archivos web: "
ls -l www/index.html 2>/dev/null | awk '{print $1}' || echo "❌ No encontrado"

echo ""
echo "✅ Permisos del proyecto webserv aplicados correctamente!"
echo ""
echo "📋 Resumen de permisos aplicados:"
echo "   - Código fuente:     644 (rw-r--r--)"
echo "   - Scripts:           755 (rwxr-xr-x)"
echo "   - Archivos web:      775 (rwxrwxr-x)"
echo "   - Páginas error:     664 (rw-rw-r--)"
echo "   - Scripts CGI:       755/775 (rwxr-xr-x/rwxrwxr-x)"
echo "   - Directorios:       755/775/777"
echo ""
echo "🎉 ¡Proyecto listo para compilar y ejecutar!"
