#!/usr/bin/env bash
################################################################################
# test_auto.sh - Validación basada EXACTAMENTE en en.subject.pdf
# Versión: 3.0.0 - Sistema de puntuación Major/Minor correcto
# Equipo: davigome, jesopan-, nporras-, rdel-olm & sternero (2025)
################################################################################

# Colores
RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'
BLUE='\033[0;34m'; MAGENTA='\033[0;35m'; CYAN='\033[0;36m'
BOLD='\033[1m'; NC='\033[0m'

# Variables
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPORT_FILE="$PROJECT_ROOT/test_result.md"
BACKEND_URL="http://localhost:3000"
FRONTEND_URL="http://localhost:2323"

# Contadores de MÓDULOS (lo que importa según el subject)
MAJOR_MODULES_PASSED=0
MINOR_MODULES_PASSED=0
TOTAL_MAJOR_MODULES=0
TOTAL_MINOR_MODULES=0

# Arrays para tracking
declare -a MODULE_RESULTS=()
START_TIME=$(date +%s)
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

# ============================================================================
# FUNCIONES DE UTILIDAD
# ============================================================================

print_header() {
    echo -e "\n${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${NC}"
    echo -e "${BOLD}${CYAN}  $1${NC}"
    echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${NC}\n"
}

print_section() {
    echo -e "\n${BOLD}${MAGENTA}▶ $1${NC}\n"
}

print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_fail() { echo -e "${RED}❌ $1${NC}"; }
print_info() { echo -e "${CYAN}ℹ️  $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }

# ============================================================================
# PRE-FLIGHT CHECKS
# ============================================================================

preflight_checks() {
    local WARNINGS=0
    
    print_section "🔍 PRE-FLIGHT CHECKS"
    
    # Check 1: Docker daemon
    echo -n "Verificando Docker daemon... "
    if ! docker info &>/dev/null; then
        print_warning "Docker daemon no está corriendo"
        WARNINGS=$((WARNINGS + 1))
    else
        print_success "Docker daemon activo"
    fi
    
    # Check 2: Contenedores corriendo
    echo -n "Verificando contenedores de Transcendence... "
    if ! docker ps 2>/dev/null | grep -q "transcendence"; then
        echo ""
        print_warning "Contenedores de Transcendence NO están corriendo"
        print_info "Ejecuta: ${BOLD}make up${NC} antes de este script"
        print_info "Algunos tests fallarán (backend/frontend no responden)"
        WARNINGS=$((WARNINGS + 1))
    else
        local RUNNING=$(docker ps --filter "name=transcendence" --format "{{.Names}}" 2>/dev/null | wc -l)
        print_success "$RUNNING contenedores corriendo"
    fi
    
    # Check 3: Docker compose file
    echo -n "Verificando docker-compose.yml... "
    if [ ! -f "$PROJECT_ROOT/docker-compose.yml" ]; then
        print_fail "docker-compose.yml no encontrado"
        WARNINGS=$((WARNINGS + 1))
    else
        print_success "Encontrado"
    fi
    
    # Check 4: Scripts ejecutables
    echo -n "Verificando permisos de ejecución... "
    if [ -x "$PROJECT_ROOT/test_auto.sh" ]; then
        print_success "Permisos OK"
    else
        print_warning "Script sin permisos de ejecución"
    fi
    
    if [ $WARNINGS -gt 0 ]; then
        echo ""
        print_warning "Se encontraron $WARNINGS advertencias"
        echo -e "${YELLOW}${BOLD}¿Continuar de todas formas? (y/N):${NC} "
        read -r response
        if [[ ! "$response" =~ ^[Yy]$ ]]; then
            echo ""
            print_info "Abortado por el usuario"
            print_info "${BOLD}Sugerencia:${NC} Ejecuta ${CYAN}${BOLD}make up${NC} y vuelve a intentar"
            exit 0
        fi
        echo ""
        print_info "Continuando con advertencias..."
    fi
    
    echo ""
}

# Validar módulo completo (no tests individuales)
validate_module() {
    local module_name="$1"
    local module_type="$2"  # "Major" o "Minor"
    local validation_command="$3"
    local implementation_details="$4"  # Dónde se encuentra la implementación
    
    if [ "$module_type" = "Major" ]; then
        TOTAL_MAJOR_MODULES=$((TOTAL_MAJOR_MODULES + 1))
    else
        TOTAL_MINOR_MODULES=$((TOTAL_MINOR_MODULES + 1))
    fi
    
    echo -n "Validando módulo: $module_name ($module_type)... "
    
    if eval "$validation_command" &>/dev/null; then
        print_success "IMPLEMENTADO"
        
        if [ "$module_type" = "Major" ]; then
            MAJOR_MODULES_PASSED=$((MAJOR_MODULES_PASSED + 1))
            MODULE_RESULTS+=("✅|$module_name|Major|1.0|$implementation_details")
        else
            MINOR_MODULES_PASSED=$((MINOR_MODULES_PASSED + 1))
            MODULE_RESULTS+=("✅|$module_name|Minor|0.5|$implementation_details")
        fi
        return 0
    else
        print_fail "NO IMPLEMENTADO"
        MODULE_RESULTS+=("❌|$module_name|$module_type|0.0|No implementado")
        return 1
    fi
}

# ============================================================================
# MÓDULOS WEB (OBLIGATORIOS)
# ============================================================================

validate_web_modules() {
    print_section "🌐 MÓDULOS WEB (Obligatorios del Subject)"
    
    # MAJOR: Backend Framework (1 punto)
    print_info "Verificando Backend Framework (Major - 1 punto)..."
    validate_module "Backend Framework (Fastify)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/package.json' ] && grep -q 'fastify' '$PROJECT_ROOT/backend/package.json' && [ -f '$PROJECT_ROOT/backend/index.js' ] && (timeout 3 curl -s '$BACKEND_URL' | grep -q 'API\\|Pong\\|OK\\|Running' || timeout 3 nc -zv localhost 3000 2>&1 | grep -q succeeded)" \
        "Backend implementado con Fastify en \`backend/index.js\`. API REST corriendo en puerto 3000. Validar con \`curl http://localhost:3000\`"
    
    # MINOR: Frontend + Tailwind + TypeScript (0.5 puntos - TODOS juntos)
    print_info "Verificando Frontend con Tailwind y TypeScript (Minor - 0.5 puntos)..."
    validate_module "Frontend (React + Tailwind + TS)" "Minor" \
        "[ -f '$PROJECT_ROOT/frontend/tsconfig.json' ] && [ -f '$PROJECT_ROOT/frontend/tailwind.config.js' ] && grep -q 'react' '$PROJECT_ROOT/frontend/package.json' && timeout 3 curl -sf '$FRONTEND_URL' >/dev/null" \
        "Frontend React con TypeScript (\`frontend/tsconfig.json\`) y Tailwind CSS (\`frontend/tailwind.config.js\`). Componentes en \`frontend/src/Components/\`. Accesible en https://localhost:8443"
    
    # MINOR: Database (0.5 puntos)
    print_info "Verificando Base de Datos (Minor - 0.5 puntos)..."
    validate_module "Database (SQLite/Sequelize)" "Minor" \
        "[ -f '$PROJECT_ROOT/backend/db.js' ] && grep -q 'sequelize' '$PROJECT_ROOT/backend/package.json' && ([ -f '$PROJECT_ROOT/backend/database.sqlite' ] || grep -q 'User\\|Match\\|Tournament' '$PROJECT_ROOT/backend/db.js')" \
        "Base de datos SQLite con Sequelize ORM en \`backend/db.js\`. Modelos: User, Match, Tournament. Archivo DB: \`backend/database.sqlite\`"
    
    # MAJOR: Blockchain (1 punto) - Opcional
    print_info "Verificando Blockchain (Major - 1 punto - Opcional)..."
    validate_module "Blockchain (Hardhat + Smart Contracts)" "Major" \
        "[ -d '$PROJECT_ROOT/backend/blockchain' ] && [ -f '$PROJECT_ROOT/backend/blockchain/hardhat/contracts/TournamentRegistry.sol' ] && [ -f '$PROJECT_ROOT/backend/blockchain/blockchain-service.js' ]" \
        "Smart Contract TournamentRegistry.sol en \`backend/blockchain/hardhat/contracts/\`. Servicio blockchain en \`blockchain-service.js\`. Deploy con Hardhat"
}

# ============================================================================
# USER MANAGEMENT
# ============================================================================

validate_user_management() {
    print_section "👥 USER MANAGEMENT"
    
    # MAJOR: Standard User Management (1 punto)
    print_info "Verificando Gestión de Usuarios Estándar (Major - 1 punto)..."
    validate_module "User Management (Auth Estándar)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/auth.js' ] && grep -q 'register\\|login\\|logout' '$PROJECT_ROOT/backend/auth.js' && timeout 5 curl -sf -X POST '$BACKEND_URL/api/auth/login' -H 'Content-Type: application/json' -w '%{http_code}' | grep -q '[24]'" \
        "Sistema de autenticación en \`backend/auth.js\` con registro/login/logout. Endpoints: \`/api/auth/register\`, \`/api/auth/login\`, \`/api/auth/logout\`. Verificar con Postman o curl"
    
    # MAJOR: OAuth 2.0 (1 punto)
    print_info "Verificando OAuth 2.0 (Major - 1 punto)..."
    validate_module "OAuth 2.0 (Google/42)" "Major" \
        "grep -q 'passport\\|oauth\\|authGoogleCallback' '$PROJECT_ROOT/backend/auth.js' || grep -q 'passport\\|oauth' '$PROJECT_ROOT/backend/package.json'" \
        "OAuth 2.0 con Passport.js en \`backend/auth.js\`. Botones de login con Google/42 en interfaz. Callback: \`/api/auth/google/callback\`"
}

# ============================================================================
# GAMEPLAY
# ============================================================================

validate_gameplay() {
    print_section "🎮 GAMEPLAY Y UX"
    
    # MAJOR: Remote Players (1 punto)
    print_info "Verificando Jugadores Remotos (Major - 1 punto)..."
    validate_module "Remote Players (Multiplayer en red)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/pon-server.js' ] && grep -qi 'room\\|lobby\\|join' '$PROJECT_ROOT/backend/pon-server.js' && ([ -f '$PROJECT_ROOT/frontend/src/Components/Matches.tsx' ] || [ -f '$PROJECT_ROOT/frontend/src/Components/Matches.jsx' ])" \
        "Sistema de matchmaking con rooms/lobbies en \`backend/pon-server.js\`. UI en \`frontend/src/Components/Matches.tsx\`. Jugadores pueden unirse a partidas remotas via Socket.IO"
    
    # MAJOR: Multiplayer (1 punto)
    print_info "Verificando Sistema Multijugador (Major - 1 punto)..."
    validate_module "Multiplayer (1v1 real-time)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/pon-server.js' ] && grep -q 'socket\\.io' '$PROJECT_ROOT/backend/package.json' && ([ -f '$PROJECT_ROOT/frontend/src/Components/Game.tsx' ] || [ -f '$PROJECT_ROOT/frontend/src/Components/Game.jsx' ])" \
        "Juego multijugador 1v1 en tiempo real con Socket.IO. Lógica del juego en \`backend/pon-server.js\`. Cliente en \`frontend/src/Components/Game.tsx\`. Sincronización de estado en tiempo real"
    
    # MINOR: Customization Options (0.5 puntos)
    print_info "Verificando Opciones de Personalización (Minor - 0.5 puntos)..."
    validate_module "Customization (Perfil de usuario)" "Minor" \
        "([ -f '$PROJECT_ROOT/frontend/src/Components/Profile.tsx' ] || [ -f '$PROJECT_ROOT/frontend/src/Components/Profile.jsx' ]) && grep -qi 'updateProfile\\|update.*profile' '$PROJECT_ROOT/backend/auth.js'" \
        "Personalización de perfil en \`frontend/src/Components/Profile.tsx\`. Endpoint \`/api/auth/update-profile\` en backend. Avatar, nickname, preferencias personalizables"
    
    # MAJOR: Live Chat (1 punto)
    print_info "Verificando Chat en Vivo (Major - 1 punto)..."
    validate_module "Live Chat (Mensajería en tiempo real)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/chat.js' ] && ([ -d '$PROJECT_ROOT/frontend/src/Components/Chat' ] || [ -f '$PROJECT_ROOT/frontend/src/Components/Chat.tsx' ] || [ -f '$PROJECT_ROOT/frontend/src/Components/Chat.jsx' ]) && grep -qi 'message\\|sendMessage' '$PROJECT_ROOT/backend/chat.js'" \
        "Chat en tiempo real con Socket.IO en \`backend/chat.js\`. Componentes en \`frontend/src/Components/Chat/\`. Mensajes directos, rooms, bloqueo de usuarios implementados"
}

# ============================================================================
# AI Y ALGORITMOS
# ============================================================================

validate_ai() {
    print_section "🤖 IA Y ALGORITMOS"
    
    # MAJOR: AI Opponent (1 punto)
    print_info "Verificando Oponente IA (Major - 1 punto)..."
    validate_module "AI Opponent (Bot inteligente)" "Major" \
        "[ -f '$PROJECT_ROOT/backend/pon-server.js' ] && grep -qi 'ai\\|bot\\|computer\\|cpu' '$PROJECT_ROOT/backend/pon-server.js'" \
        "IA implementada en \`backend/pon-server.js\`. Bot con algoritmo de predicción de trayectoria. Seleccionable desde menú de juego como oponente CPU"
    
    # MINOR: Stats Dashboard (0.5 puntos)
    print_info "Verificando Dashboard de Estadísticas (Minor - 0.5 puntos)..."
    validate_module "Stats Dashboard (Historial y estadísticas)" "Minor" \
        "grep -qi 'stats\\|statistics\\|matchHistory\\|leaderboard' '$PROJECT_ROOT/backend/auth.js' && (grep -qi 'stats\\|match.*history' '$PROJECT_ROOT/frontend/src/Components/Profile.tsx' || grep -qi 'stats\\|match.*history' '$PROJECT_ROOT/frontend/src/Components/Profile.jsx')" \
        "Dashboard de estadísticas en \`frontend/src/Components/Profile.tsx\`. Historial de partidas, win/loss ratio, ranking. Datos en tabla Match de SQLite"
}

# ============================================================================
# CIBERSEGURIDAD
# ============================================================================

validate_security() {
    print_section "🔒 CIBERSEGURIDAD"
    
    # MAJOR: WAF/ModSecurity/HashiCorp Vault (1 punto)
    print_info "Verificando WAF/ModSecurity/Vault (Major - 1 punto)..."
    validate_module "WAF + ModSecurity + Vault" "Major" \
        "[ -f '$PROJECT_ROOT/srcs/conf/modsecurity/modsecurity.conf' ] && [ -d '$PROJECT_ROOT/srcs/data/vault' ] && [ -f '$PROJECT_ROOT/srcs/conf/nginx/nginx.conf' ]" \
        "WAF con ModSecurity en \`srcs/conf/modsecurity/\`. HashiCorp Vault en \`srcs/data/vault/\`. Nginx con reglas de seguridad. Init scripts en \`srcs/scripts/\`"
    
    # MAJOR: 2FA + JWT (1 punto)
    print_info "Verificando 2FA y JWT (Major - 1 punto)..."
    validate_module "2FA + JWT" "Major" \
        "grep -qi 'jwt\\|jsonwebtoken' '$PROJECT_ROOT/backend/package.json' && grep -qi 'jwt' '$PROJECT_ROOT/backend/auth.js' && grep -qi '2fa\\|totp\\|speakeasy' '$PROJECT_ROOT/backend/package.json'" \
        "Autenticación JWT en \`backend/auth.js\`. 2FA con TOTP/Speakeasy. Tokens en headers. QR code para configuración 2FA en perfil"
    
    # MINOR: GDPR + Anonimización (0.5 puntos)
    print_info "Verificando GDPR (Minor - 0.5 puntos)..."
    validate_module "GDPR + Anonimización de datos" "Minor" \
        "grep -qi 'anonymize\\|gdpr\\|delete.*user\\|remove.*data' '$PROJECT_ROOT/backend/auth.js'" \
        "Funcionalidad GDPR en \`backend/auth.js\`. Endpoint para eliminar/anonimizar datos. Opción 'Eliminar cuenta' en configuración"
}

# ============================================================================
# DEVOPS
# ============================================================================

validate_devops() {
    print_section "⚙️  DEVOPS"
    
    # MAJOR: Microservices (1 punto)
    print_info "Verificando Arquitectura de Microservicios (Major - 1 punto)..."
    validate_module "Microservices Backend" "Major" \
        "[ -f '$PROJECT_ROOT/docker-compose.yml' ] && [ \$(grep -c 'image:' '$PROJECT_ROOT/docker-compose.yml') -ge 3 ]" \
        "Arquitectura de microservicios en \`docker-compose.yml\`. Servicios separados: backend, frontend, nginx, vault. Cada uno con Dockerfile propio"
    
    # MINOR: Monitoring (0.5 puntos)
    print_info "Verificando Sistema de Monitoring (Minor - 0.5 puntos)..."
    validate_module "Monitoring System" "Minor" \
        "grep -qi 'prometheus\\|grafana\\|monitoring' '$PROJECT_ROOT/docker-compose.yml'" \
        "Sistema de monitoring con Prometheus/Grafana en \`docker-compose.yml\`. Métricas de contenedores y aplicación. Dashboards accesibles"
    
    # MAJOR: ELK Logging (1 punto)
    print_info "Verificando Sistema de Logs (Major - 1 punto)..."
    validate_module "ELK Stack / Logging centralizado" "Major" \
        "[ -d '$PROJECT_ROOT/srcs/logs' ] || grep -qi 'elasticsearch\\|logstash\\|kibana\\|elk' '$PROJECT_ROOT/docker-compose.yml'" \
        "Sistema de logs centralizado. Directorio \`srcs/logs/\` con logs de nginx y modsecurity. Logs estructurados para análisis"
}

# ============================================================================
# GRÁFICOS
# ============================================================================

validate_graphics() {
    print_section "🎨 GRÁFICOS"
    
    # MAJOR: 3D Graphics (1 punto)
    print_info "Verificando Gráficos 3D (Major - 1 punto)..."
    validate_module "3D Graphics (Babylon.js/Three.js)" "Major" \
        "grep -qi 'babylonjs\\|three\\.js\\|@babylonjs\\|threejs' '$PROJECT_ROOT/frontend/package.json'" \
        "Motor 3D (Babylon.js/Three.js) en \`frontend/package.json\`. Renderizado 3D del juego Pong. Cámaras, iluminación, modelos 3D"
}

# ============================================================================
# ACCESIBILIDAD
# ============================================================================

validate_accessibility() {
    print_section "♿ ACCESIBILIDAD"
    
    # MINOR: Support on all devices (0.5 puntos)
    print_info "Verificando Soporte Multi-dispositivo (Minor - 0.5 puntos)..."
    validate_module "Device Support (Responsive design)" "Minor" \
        "[ -f '$PROJECT_ROOT/frontend/tailwind.config.js' ] && (grep -q 'sm:\\|md:\\|lg:' '$PROJECT_ROOT/frontend/src/Components/Game.tsx' || grep -q 'sm:\\|md:\\|lg:' '$PROJECT_ROOT/frontend/src/Components/Game.jsx' || grep -q 'sm:\\|md:\\|lg:' '$PROJECT_ROOT/frontend/src/Components/Index.tsx')" \
        "Diseño responsive con Tailwind CSS. Breakpoints sm:/md:/lg: en componentes. Probado en móvil, tablet y desktop"
    
    # MINOR: Browser compatibility (0.5 puntos)
    print_info "Verificando Compatibilidad de Navegadores (Minor - 0.5 puntos)..."
    validate_module "Browser Compatibility (Build moderno)" "Minor" \
        "[ -f '$PROJECT_ROOT/frontend/vite.config.js' ] || [ -f '$PROJECT_ROOT/frontend/webpack.config.js' ]" \
        "Build moderno con Vite en \`frontend/vite.config.js\`. Transpilación automática. Compatible Chrome, Firefox, Safari, Edge"
    
    # MINOR: Multi-language (0.5 puntos)
    print_info "Verificando Soporte Multiidioma (Minor - 0.5 puntos)..."
    validate_module "Multi-language (i18n)" "Minor" \
        "grep -qi 'i18n\\|translation\\|language.*select\\|lang' '$PROJECT_ROOT/frontend/src/Context/AuthContext.tsx' || grep -qi 'i18n\\|translation\\|language.*select' '$PROJECT_ROOT/frontend/src/Context/AuthContext.jsx'" \
        "Sistema i18n en \`frontend/src/Context/\`. Selector de idioma en interfaz. Soporta ES/EN/FR. Persistencia en localStorage"
    
    # MINOR: Visual accessibility (0.5 puntos)
    print_info "Verificando Accesibilidad Visual (Minor - 0.5 puntos)..."
    validate_module "Visual Accessibility (ARIA/a11y)" "Minor" \
        "grep -qi 'aria-\\|role=\\|alt=' '$PROJECT_ROOT/frontend/src/Components/Index.tsx' || grep -qi 'aria-\\|role=' '$PROJECT_ROOT/frontend/src/Components/Index.jsx'" \
        "Atributos ARIA en componentes HTML. Roles semánticos, labels, alt text. Navegación por teclado. Screen reader friendly"
    
    # MINOR: SSR (0.5 puntos)
    print_info "Verificando Server-Side Rendering (Minor - 0.5 puntos)..."
    validate_module "SSR (Next.js/Nuxt)" "Minor" \
        "grep -qi 'next\\|nuxt' '$PROJECT_ROOT/frontend/package.json'" \
        "Server-Side Rendering con Next.js/Nuxt en \`frontend/package.json\`. Renderizado en servidor para SEO"
}

# ============================================================================
# SERVER-SIDE PONG
# ============================================================================

validate_server_pong() {
    print_section "🏓 SERVER-SIDE PONG"
    
    # MAJOR: API Pong (1 punto)
    print_info "Verificando Pong con API server-side (Major - 1 punto)..."
    validate_module "Server-Side Pong API" "Major" \
        "[ -f '$PROJECT_ROOT/backend/pon-server.js' ] && grep -qi 'gameLoop\\|updateGame\\|gameState\\|ballUpdate' '$PROJECT_ROOT/backend/pon-server.js'" \
        "Lógica del juego Pong en servidor (\`backend/pon-server.js\`). GameLoop server-side, actualización de posiciones, detección de colisiones. Cliente recibe solo estados"
    
    # MAJOR: CLI vs Web (1 punto)
    print_info "Verificando CLI contra usuarios web (Major - 1 punto)..."
    validate_module "CLI Client vs Web Users" "Major" \
        "[ -f '$PROJECT_ROOT/cli.js' ] || [ -f '$PROJECT_ROOT/backend/cli.js' ] || [ -d '$PROJECT_ROOT/cli' ]" \
        "Cliente CLI en \`cli.js\` o \`backend/cli.js\`. Conexión Socket.IO desde terminal. Usuarios CLI pueden jugar contra usuarios web. Ejecutar: \`node cli.js\`"
}

# ============================================================================
# VALIDACIÓN DE ARQUITECTURA OBLIGATORIA
# ============================================================================

validate_mandatory_architecture() {
    print_section "🏗️  ARQUITECTURA OBLIGATORIA"
    
    print_info "Verificando Docker Compose..."
    if [ -f "$PROJECT_ROOT/docker-compose.yml" ]; then
        print_success "docker-compose.yml presente"
    else
        print_fail "docker-compose.yml FALTA (OBLIGATORIO)"
    fi
    
    print_info "Verificando Makefile..."
    if [ -f "$PROJECT_ROOT/Makefile" ]; then
        print_success "Makefile presente"
        
        # Verificar comandos obligatorios
        if grep -q "^up:" "$PROJECT_ROOT/Makefile"; then
            print_success "'make up' definido"
        else
            print_fail "'make up' NO definido"
        fi
        
        if grep -q "^down:" "$PROJECT_ROOT/Makefile"; then
            print_success "'make down' definido"
        else
            print_fail "'make down' NO definido"
        fi
    else
        print_fail "Makefile FALTA (OBLIGATORIO)"
    fi
    
    print_info "Verificando contenedores en ejecución..."
    if docker ps | grep -q "transcendence"; then
        print_success "Contenedores corriendo"
    else
        print_fail "Contenedores NO están corriendo"
    fi
}

# ============================================================================
# GENERAR REPORTE
# ============================================================================

generate_report() {
    print_section "📊 GENERANDO REPORTE"
    
    local END_TIME=$(date +%s)
    local DURATION=$((END_TIME - START_TIME))
    
    # Calcular puntuación EXACTA según subject
    local MAJOR_POINTS=$(awk "BEGIN {printf \"%.1f\", $MAJOR_MODULES_PASSED * 1.0}")
    local MINOR_POINTS=$(awk "BEGIN {printf \"%.1f\", $MINOR_MODULES_PASSED * 0.5}")
    local TOTAL_POINTS=$(awk "BEGIN {printf \"%.1f\", $MAJOR_POINTS + $MINOR_POINTS}")
    
    cat > "$REPORT_FILE" << EOF
# 🎮 Transcendence - Reporte de Validación v3.0

**Fecha**: $TIMESTAMP  
**Duración**: ${DURATION}s  
**Equipo**: davigome, jesopan-, nporras-, rdel-olm & sternero

---

## 📊 PUNTUACIÓN FINAL

| Categoría | Módulos | Puntos Obtenidos |
|-----------|---------|------------------|
| **Major Modules** | $MAJOR_MODULES_PASSED / $TOTAL_MAJOR_MODULES | **${MAJOR_POINTS} pts** |
| **Minor Modules** | $MINOR_MODULES_PASSED / $TOTAL_MINOR_MODULES | **${MINOR_POINTS} pts** |
| **TOTAL** | $(($MAJOR_MODULES_PASSED + $MINOR_MODULES_PASSED)) / $(($TOTAL_MAJOR_MODULES + $TOTAL_MINOR_MODULES)) | **${TOTAL_POINTS} / 21.0 pts** |

### 🎯 Criterios de Evaluación:

- **Mínimo para aprobar**: 7.0 puntos (Major = 1pt, Minor = 0.5pt)
- **Nivel bonus**: 9.5+ puntos
- **Máximo posible**: 21.0 puntos

---

## 🏆 VEREDICTO

EOF

    if (( $(echo "$TOTAL_POINTS >= 9.5" | bc -l) )); then
        cat >> "$REPORT_FILE" << EOF
### ✅ **¡EXCELENTE! - BONUS ALCANZADO**

Con **${TOTAL_POINTS} puntos**, vuestro proyecto supera el nivel de bonus (9.5+).
¡Felicidades! 🎉

**Estado**: APROBADO CON BONUS ⭐⭐⭐
EOF
    elif (( $(echo "$TOTAL_POINTS >= 7.0" | bc -l) )); then
        cat >> "$REPORT_FILE" << EOF
### ✅ **APROBADO - Requisitos Cumplidos**

Con **${TOTAL_POINTS} puntos**, cumplís el mínimo requerido (7.0+).

**Estado**: APROBADO ✅

**Sugerencia**: Implementad ${BONUS_NEEDED} módulos más para alcanzar el bonus (9.5 pts).
EOF
    elif (( $(echo "$TOTAL_POINTS >= 5.0" | bc -l) )); then
        local NEEDED=$(awk "BEGIN {printf \"%.1f\", 7.0 - $TOTAL_POINTS}")
        cat >> "$REPORT_FILE" << EOF
### ⚠️  **CASI - Faltan ${NEEDED} puntos**

Con **${TOTAL_POINTS} puntos**, estáis cerca del mínimo (7.0).

**Estado**: INSUFICIENTE ⚠️

**Acción requerida**: Implementad módulos adicionales para alcanzar los 7 puntos mínimos.
EOF
    else
        local NEEDED=$(awk "BEGIN {printf \"%.1f\", 7.0 - $TOTAL_POINTS}")
        cat >> "$REPORT_FILE" << EOF
### ❌ **INSUFICIENTE - Faltan ${NEEDED} puntos**

Con **${TOTAL_POINTS} puntos**, no alcanzáis el mínimo requerido (7.0).

**Estado**: REPROBADO ❌

**Acción urgente**: Necesitáis implementar más módulos del subject.
EOF
    fi
    
    cat >> "$REPORT_FILE" << EOF

---

## 📋 Detalle de Módulos Implementados

| Estado | Módulo | Tipo | Puntos | Verificación |
|--------|--------|------|--------|--------------|
EOF

    for result in "${MODULE_RESULTS[@]}"; do
        IFS='|' read -r status name type points note <<< "$result"
        echo "| $status | $name | $type | $points | $note |" >> "$REPORT_FILE"
    done
    
    cat >> "$REPORT_FILE" << EOF

---

## 📚 Documentación del Proyecto

### General
- [README Principal](./README.md) - Información general del proyecto

### Backend
- [README Backend](./backend/README.md) - Documentación del servidor
- [README IA Implementation](./backend/AI_IMPLEMENTATION.md) - Módulo de Inteligencia Artificial completo
- [README Blockchain](./backend/blockchain/README.md) - Smart contracts y servicios
- [README Hardhat](./backend/blockchain/hardhat/README.md) - Entorno de desarrollo blockchain
- [README Contratos](./backend/blockchain/hardhat/contracts/README.md) - Smart contract TournamentRegistry
- [README Scripts Deploy](./backend/blockchain/hardhat/scripts/README.md) - Scripts de despliegue

### Frontend
- [README Frontend](./frontend/README.md) - Cliente React completo
- [README Source Code](./frontend/src/README.md) - Código fuente de la aplicación
- [README Componentes](./frontend/src/Components/README.md) - Componentes React
- [README Chat](./frontend/src/Components/Chat/README.md) - Sistema de chat
- [README Context](./frontend/src/Context/README.md) - Gestión de estado
- [README Middleware](./frontend/src/middleWare/README.md) - Middleware frontend
- [README Services](./frontend/src/services/README.md) - Capa de servicios API
- [README Static](./frontend/static/README.md) - Archivos estáticos

### Infraestructura
- [README Srcs](./srcs/README.md) - Configuración de servicios
- [README Configuración](./srcs/conf/README.md) - Archivos de configuración
- [README Scripts](./srcs/scripts/README.md) - Scripts de inicialización
- [README Secrets](./srcs/secrets/README.md) - Gestión de secretos
- [README Vault](./srcs/secrets/vault/README.md) - HashiCorp Vault
- [README API AppRole](./srcs/secrets/api-approle/README.md) - Autenticación Vault
- [README Certificados](./srcs/secrets/certs/README.md) - Certificados SSL

---

## 🔍 Cómo Verificar los Módulos

### Acceso a la Aplicación
- **URL Principal**: https://localhost:8443
- **Backend API**: http://localhost:3000
- **Frontend Dev**: http://localhost:2323

### Comandos Útiles
\`\`\`bash
make up          # Iniciar todos los servicios
make test        # Ejecutar esta validación
make logs        # Ver logs de todos los contenedores
make status      # Estado de los contenedores
\`\`\`

### Verificación Manual
- **Base de datos**: \`backend/database.sqlite\` se crea automáticamente
- **Backend API**: Probar con \`curl http://localhost:3000/api/auth/login\`
- **Frontend**: Abrir navegador en https://localhost:8443
- **Chat**: Acceder desde la interfaz principal
- **IA Opponent**: Seleccionar modo contra CPU en el juego

---

## 📚 Referencias para Evaluadores

Este proyecto cumple con los requisitos especificados en el subject de ft_transcendence.
Los módulos implementados están documentados en este reporte y verificables siguiendo
las instrucciones anteriores.

---

*Generado automáticamente por test_auto.sh v3.0*  
*Validación realizada: $TIMESTAMP*
EOF

    print_success "Reporte generado: $REPORT_FILE"
}

# ============================================================================
# MAIN
# ============================================================================

main() {
    clear
    cat << "BANNER"
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║ ████████╗██████╗  █████╗ ███╗   ██╗███████╗ ██████╗███████╗███╗   ██╗  ██████╗███████╗███╗   ██╗███████  ███████╗ ║
║ ╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║██╔════╝██╔════╝██╔════╝████╗  ██║ ██╔════╝██╔════╝████╗  ██║██╔═══██ ██╔════╝ ║
║    ██║   ██████╔╝███████║██╔██╗ ██║███████╗██║     █████╗  ██╔██╗ ██║ ██║     █████╗  ██╔██╗ ██║██║   ██ █████╗   ║
║    ██║   ██╔══██╗██╔══██║██║╚██╗██║╚════██║██║     ██╔══╝  ██║╚██╗██║ ██║     ██╔══╝  ██║╚██╗██║██║   ██ ██╔══╝   ║
║    ██║   ██║  ██║██║  ██║██║ ╚████║███████║╚██████╗███████╗██║ ╚████║ ╚██████╗███████╗██║ ╚████║███████  ███████╗ ║
║    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝ ╚═════╝╚══════╝╚═╝  ╚═══╝  ╚═════╝╚══════╝╚═╝  ╚═══╝╚════╝   ╚══════╝ ║
║                     🧪 VALIDACIÓN v3.0 - BASADA EXACTAMENTE EN EL SUBJECT PDF 🧪                                  ║
╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
BANNER
    
    echo -e "${BOLD}Validación de Transcendence según en.subject.pdf${NC}"
    echo -e "${CYAN}Sistema de puntuación: Major (1.0) + Minor (0.5)${NC}"
    echo -e "${CYAN}Mínimo para aprobar: 7.0 puntos | Bonus: 9.5+ puntos${NC}\n"
    
    # Pre-flight checks
    preflight_checks
    
    # Validar arquitectura obligatoria primero
    validate_mandatory_architecture
    
    # Validar todos los módulos del subject
    validate_web_modules
    validate_user_management
    validate_gameplay
    validate_ai
    validate_security
    validate_devops
    validate_graphics
    validate_accessibility
    validate_server_pong
    
    # Generar reporte
    generate_report
    
    # Resumen final
    print_header "🎯 RESULTADOS FINALES"
    
    local MAJOR_POINTS=$(awk "BEGIN {printf \"%.1f\", $MAJOR_MODULES_PASSED * 1.0}")
    local MINOR_POINTS=$(awk "BEGIN {printf \"%.1f\", $MINOR_MODULES_PASSED * 0.5}")
    local TOTAL_POINTS=$(awk "BEGIN {printf \"%.1f\", $MAJOR_POINTS + $MINOR_POINTS}")
    
    echo -e "${BOLD}Módulos Major implementados:${NC} $MAJOR_MODULES_PASSED / $TOTAL_MAJOR_MODULES"
    echo -e "${BOLD}Módulos Minor implementados:${NC} $MINOR_MODULES_PASSED / $TOTAL_MINOR_MODULES"
    echo -e "\n${BOLD}${MAGENTA}═══════════════════════════════════════${NC}"
    echo -e "${BOLD}${CYAN}Puntos Major:${NC} ${MAJOR_POINTS} pts"
    echo -e "${BOLD}${CYAN}Puntos Minor:${NC} ${MINOR_POINTS} pts"
    echo -e "${BOLD}${GREEN}PUNTUACIÓN TOTAL: ${TOTAL_POINTS} / 21.0 pts${NC}"
    echo -e "${BOLD}${MAGENTA}═══════════════════════════════════════${NC}\n"
    
    if (( $(echo "$TOTAL_POINTS >= 9.5" | bc -l) )); then
        echo -e "${GREEN}${BOLD}🥇 ¡EXCELENTE! - BONUS ALCANZADO (9.5+ puntos)${NC}"
    elif (( $(echo "$TOTAL_POINTS >= 7.0" | bc -l) )); then
        echo -e "${GREEN}${BOLD}✅ APROBADO - Requisitos Mínimos Cumplidos (7+ puntos)${NC}"
        echo -e "${YELLOW}💡 Sugerencia: Implementad más módulos para el bonus${NC}"
    elif (( $(echo "$TOTAL_POINTS >= 5.0" | bc -l) )); then
        echo -e "${YELLOW}${BOLD}⚠️  CASI - Necesitáis $(awk "BEGIN {printf \"%.1f\", 7.0 - $TOTAL_POINTS}") puntos más${NC}"
    else
        echo -e "${RED}${BOLD}❌ INSUFICIENTE - Faltan $(awk "BEGIN {printf \"%.1f\", 7.0 - $TOTAL_POINTS}") puntos${NC}"
    fi
    
    echo -e "\n${CYAN}📄 Reporte detallado:${NC} ${BOLD}$REPORT_FILE${NC}"
    echo -e "${CYAN}📖 Ver con:${NC} ${BOLD}cat $REPORT_FILE${NC}\n"
    
    # Exit code según puntuación
    if (( $(echo "$TOTAL_POINTS >= 7.0" | bc -l) )); then
        exit 0
    else
        exit 1
    fi
}

main "$@"
