#!/bin/bash

##############################################################################
# 16_bonus_features.sh - Verificación de características bonus
# EVALUACIÓN:
# "Bonus part - Cookies and session, CGI multiple systems"
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
echo -e "    CARACTERÍSTICAS BONUS - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de búsqueda
if [ -d "./srcs" ] || [ -d "./include" ]; then
    SEARCH_DIR="."
else
    SEARCH_DIR=".."
fi

# =============================================================================
# 1. VERIFICAR SISTEMA DE COOKIES Y SESIONES
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando sistema de cookies y sesiones:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"Cookie\\|Session\\|Set-Cookie\" --include=\"*.cpp\" --include=\"*.hpp\" $SEARCH_DIR${NC}"
echo ""

COOKIE_SESSION=$(grep -rn "Cookie\|Session\|Set-Cookie\|JSESSIONID\|PHPSESSID" --include="*.cpp" --include="*.hpp" "$SEARCH_DIR" 2>/dev/null)
echo "$COOKIE_SESSION" | head -10
TOTAL_COOKIE=$(echo "$COOKIE_SESSION" | wc -l)
if [ "$TOTAL_COOKIE" -gt 10 ]; then
    echo "... ($TOTAL_COOKIE líneas en total)"
fi

echo ""

HAS_COOKIE=$(echo "$COOKIE_SESSION" | grep -c "Cookie" || echo "0")
HAS_SESSION=$(echo "$COOKIE_SESSION" | grep -c "Session" || echo "0")
HAS_SET_COOKIE=$(echo "$COOKIE_SESSION" | grep -c "Set-Cookie" || echo "0")

echo -e "${YELLOW}📊 Cookies/Sessions: Cookie($HAS_COOKIE) Session($HAS_SESSION) Set-Cookie($HAS_SET_COOKIE)${NC}"

# =============================================================================
# 2. VERIFICAR MÚLTIPLES SISTEMAS CGI
# =============================================================================

echo -e "${BLUE}🔍 2. Verificando múltiples sistemas CGI:${NC}"
echo ""

# Buscar directorios CGI
CGI_DIRS=()
if [ -d "$SEARCH_DIR/www/cgi-bin" ]; then
    CGI_DIRS+=("$SEARCH_DIR/www/cgi-bin")
fi
if [ -d "$SEARCH_DIR/www2/cgi-bin" ]; then
    CGI_DIRS+=("$SEARCH_DIR/www2/cgi-bin")
fi
if [ -d "$SEARCH_DIR/cgi-bin" ]; then
    CGI_DIRS+=("$SEARCH_DIR/cgi-bin")
fi

CGI_LANGUAGES=()
for dir in "${CGI_DIRS[@]}"; do
    echo -e "${GREEN}📁 Directorio CGI: $dir${NC}"
    
    # Buscar diferentes tipos de CGI
    if [ -n "$(find "$dir" -name "*.py" 2>/dev/null)" ]; then
        CGI_LANGUAGES+=("Python")
        echo -e "${CYAN}   ✓ Python CGI encontrado${NC}"
    fi
    
    if [ -n "$(find "$dir" -name "*.php" 2>/dev/null)" ]; then
        CGI_LANGUAGES+=("PHP")
        echo -e "${CYAN}   ✓ PHP CGI encontrado${NC}"
    fi
    
    if [ -n "$(find "$dir" -name "*.pl" 2>/dev/null)" ]; then
        CGI_LANGUAGES+=("Perl")
        echo -e "${CYAN}   ✓ Perl CGI encontrado${NC}"
    fi
    
    if [ -n "$(find "$dir" -name "*.rb" 2>/dev/null)" ]; then
        CGI_LANGUAGES+=("Ruby")
        echo -e "${CYAN}   ✓ Ruby CGI encontrado${NC}"
    fi
    
    if [ -n "$(find "$dir" -name "*.sh" 2>/dev/null)" ]; then
        CGI_LANGUAGES+=("Shell")
        echo -e "${CYAN}   ✓ Shell CGI encontrado${NC}"
    fi
    
    echo ""
done

UNIQUE_CGI=$(printf "%s\n" "${CGI_LANGUAGES[@]}" | sort -u | wc -l)
echo -e "${YELLOW}📊 Sistemas CGI únicos: $UNIQUE_CGI${NC}"
echo -e "${CYAN}   Lenguajes: $(printf "%s " "${CGI_LANGUAGES[@]}" | sort -u | tr '\n' ' ')${NC}"

# =============================================================================
# 3. VERIFICAR IMPLEMENTACIÓN AVANZADA
# =============================================================================

echo -e "${BLUE}🔍 3. Verificando implementaciones avanzadas:${NC}"
echo ""
echo -e "${PURPLE}💻 Comando: grep -rn \"kqueue\\|epoll\\|poll\" --include=\"*.cpp\" $SEARCH_DIR${NC}"
echo ""

ADVANCED_IO=$(grep -rn "kqueue\|epoll\|poll" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$ADVANCED_IO" | head -5
TOTAL_ADVANCED=$(echo "$ADVANCED_IO" | wc -l)
if [ "$TOTAL_ADVANCED" -gt 5 ]; then
    echo "... ($TOTAL_ADVANCED líneas en total)"
fi

echo ""

HAS_KQUEUE=$(echo "$ADVANCED_IO" | grep -c "kqueue" || echo "0")
HAS_EPOLL=$(echo "$ADVANCED_IO" | grep -c "epoll" || echo "0")
HAS_POLL=$(echo "$ADVANCED_IO" | grep -c "poll" || echo "0")

echo -e "${YELLOW}📊 I/O Avanzado: kqueue($HAS_KQUEUE) epoll($HAS_EPOLL) poll($HAS_POLL)${NC}"

# =============================================================================
# 4. VERIFICAR OTRAS CARACTERÍSTICAS BONUS
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando otras características bonus:${NC}"
echo ""

# Buscar características adicionales
BONUS_FEATURES=$(grep -rn "chunked\|gzip\|compression\|keep-alive\|persistent" --include="*.cpp" "$SEARCH_DIR" 2>/dev/null)
echo "$BONUS_FEATURES" | head -6
TOTAL_BONUS=$(echo "$BONUS_FEATURES" | wc -l)
if [ "$TOTAL_BONUS" -gt 6 ]; then
    echo "... ($TOTAL_BONUS líneas en total)"
fi

echo ""

HAS_CHUNKED=$(echo "$BONUS_FEATURES" | grep -c "chunked" || echo "0")
HAS_COMPRESSION=$(echo "$BONUS_FEATURES" | grep -c "gzip\|compression" || echo "0")
HAS_KEEPALIVE=$(echo "$BONUS_FEATURES" | grep -c "keep-alive\|persistent" || echo "0")

echo -e "${YELLOW}📊 Features bonus: chunked($HAS_CHUNKED) compression($HAS_COMPRESSION) keep-alive($HAS_KEEPALIVE)${NC}"

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

BONUS_POINTS=0

# Cookies y sesiones
if [ "$HAS_COOKIE" -gt 0 ] && [ "$HAS_SESSION" -gt 0 ]; then
    BONUS_POINTS=$((BONUS_POINTS + 1))
    echo -e "${GREEN}✅ BONUS: Sistema de cookies y sesiones implementado${NC}"
else
    echo -e "${YELLOW}⚪ Cookies y sesiones: No implementado${NC}"
fi

# Múltiples CGI
if [ "$UNIQUE_CGI" -gt 1 ]; then
    BONUS_POINTS=$((BONUS_POINTS + 1))
    echo -e "${GREEN}✅ BONUS: Múltiples sistemas CGI implementados${NC}"
else
    echo -e "${YELLOW}⚪ Múltiples CGI: Solo un sistema o ninguno${NC}"
fi

# I/O avanzado
if [ "$HAS_KQUEUE" -gt 0 ] || [ "$HAS_EPOLL" -gt 0 ]; then
    BONUS_POINTS=$((BONUS_POINTS + 1))
    echo -e "${GREEN}✅ BONUS: I/O multiplexing avanzado (kqueue/epoll)${NC}"
else
    echo -e "${YELLOW}⚪ I/O avanzado: Solo select() básico${NC}"
fi

echo ""
echo -e "${YELLOW}🎯 PUNTOS BONUS DETECTADOS: $BONUS_POINTS/3${NC}"

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Qué características bonus han implementado?${NC}"
echo ""

echo -e "${BLUE}1. 🍪 ¿Tienen sistema de cookies y sesiones funcionando?${NC}"
echo ""
if [ "$HAS_COOKIE" -gt 0 ] && [ "$HAS_SESSION" -gt 0 ]; then
    echo -e "${GREEN}   ✅ Detectado en código. Respuesta esperada:${NC}"
    echo -e "${WHITE}   'Implementamos manejo de cookies HTTP y sistema de sesiones"
    echo -e "    para mantener estado entre requests del cliente'${NC}"
else
    echo -e "${YELLOW}   ⚪ No detectado. Si lo tienen, explicar cómo funciona${NC}"
fi
echo ""

echo -e "${BLUE}2. 🔧 ¿Soportan múltiples sistemas CGI?${NC}"
echo ""
if [ "$UNIQUE_CGI" -gt 1 ]; then
    echo -e "${GREEN}   ✅ Detectados: $(printf "%s " "${CGI_LANGUAGES[@]}" | sort -u | tr '\n' ' ')${NC}"
    echo -e "${WHITE}   'Soportamos múltiples lenguajes CGI con handlers específicos"
    echo -e "    para cada tipo de script'${NC}"
else
    echo -e "${YELLOW}   ⚪ Solo detectado: $(printf "%s " "${CGI_LANGUAGES[@]}" | head -1)${NC}"
fi
echo ""

echo -e "${BLUE}3. ⚡ ¿Usan I/O multiplexing avanzado (kqueue/epoll)?${NC}"
echo ""
if [ "$HAS_KQUEUE" -gt 0 ] || [ "$HAS_EPOLL" -gt 0 ]; then
    echo -e "${GREEN}   ✅ Detectado. Respuesta esperada:${NC}"
    echo -e "${WHITE}   'Usamos kqueue/epoll para mejor performance que select()"
    echo -e "    especialmente con muchas conexiones concurrentes'${NC}"
else
    echo -e "${YELLOW}   ⚪ Solo select() detectado. Si tienen kqueue/epoll, mostrar${NC}"
fi
echo ""

echo -e "${BLUE}4. 🎁 ¿Qué otras características bonus implementaron?${NC}"
echo ""
echo -e "${GREEN}   ✅ Posibles bonus adicionales:${NC}"
echo -e "${WHITE}   - Transfer-Encoding: chunked"
echo -e "   - Compresión gzip"
echo -e "   - Keep-alive connections"
echo -e "   - Virtual hosts avanzados"
echo -e "   - HTTPS/TLS"
echo -e "   - WebSocket support${NC}"
echo ""

if [ "$BONUS_POINTS" -gt 0 ]; then
    echo -e "${GREEN}🧪 DEMO DE CARACTERÍSTICAS BONUS:${NC}"
    
    if [ "$HAS_COOKIE" -gt 0 ]; then
        echo -e "${CYAN}   # Test cookies:${NC}"
        echo -e "${CYAN}   curl -I http://localhost:8080/login${NC}"
        echo -e "${CYAN}   curl -H 'Cookie: session=abc123' http://localhost:8080/profile${NC}"
    fi
    
    if [ "$UNIQUE_CGI" -gt 1 ]; then
        echo -e "${CYAN}   # Test múltiples CGI:${NC}"
        for lang in "${CGI_LANGUAGES[@]}"; do
            case "$lang" in
                "Python") echo -e "${CYAN}   curl http://localhost:8080/cgi-bin/test.py${NC}" ;;
                "PHP") echo -e "${CYAN}   curl http://localhost:8080/cgi-bin/test.php${NC}" ;;
                "Perl") echo -e "${CYAN}   curl http://localhost:8080/cgi-bin/test.pl${NC}" ;;
            esac
        done
    fi
else
    echo -e "${YELLOW}⚠️ No se detectaron características bonus${NC}"
    echo -e "${WHITE}   Bonus solo se evalúa si mandatory está perfecto${NC}"
fi

echo ""
echo -e "${RED}🚨 RECORDATORIO IMPORTANTE:${NC}"
echo -e "${WHITE}Los bonus SOLO se evalúan si la parte mandatory está"
echo -e "completamente perfecta y el manejo de errores es impecable${NC}"
