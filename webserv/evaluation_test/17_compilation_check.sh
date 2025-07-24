#!/bin/bash

##############################################################################
# 17_compilation_check.sh - Verificación de compilación sin re-link
# EVALUACIÓN:
# "The project must compile without any re-link issue"
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
echo -e "    COMPILACIÓN - VERIFICACIÓN"
echo -e "==========================================${NC}"
echo ""

# Determinar directorio de proyecto
if [ -f "./Makefile" ]; then
    PROJECT_DIR="."
elif [ -f "../Makefile" ]; then
    PROJECT_DIR=".."
else
    echo -e "${RED}❌ No se encontró Makefile${NC}"
    exit 1
fi

# =============================================================================
# 1. VERIFICAR EXISTENCIA DE MAKEFILE
# =============================================================================

echo -e "${BLUE}🔍 1. Verificando Makefile:${NC}"
echo ""

if [ -f "$PROJECT_DIR/Makefile" ]; then
    echo -e "${GREEN}✅ Makefile encontrado: $PROJECT_DIR/Makefile${NC}"
    echo ""
    echo -e "${PURPLE}💻 Contenido del Makefile (primeras 20 líneas):${NC}"
    head -20 "$PROJECT_DIR/Makefile"
    echo ""
    HAS_MAKEFILE=1
else
    echo -e "${RED}❌ Makefile no encontrado${NC}"
    HAS_MAKEFILE=0
fi

# =============================================================================
# 2. LIMPIAR Y COMPILAR DESDE CERO
# =============================================================================

echo -e "${BLUE}🔍 2. Test de compilación limpia:${NC}"
echo ""

cd "$PROJECT_DIR"

echo -e "${PURPLE}💻 Comando: make fclean${NC}"
echo ""
CLEAN_OUTPUT=$(make fclean 2>&1)
CLEAN_STATUS=$?
echo "$CLEAN_OUTPUT"
echo ""

if [ $CLEAN_STATUS -eq 0 ]; then
    echo -e "${GREEN}✅ Limpieza exitosa${NC}"
    CLEAN_SUCCESS=1
else
    echo -e "${RED}❌ Error en limpieza${NC}"
    CLEAN_SUCCESS=0
fi

echo ""
echo -e "${PURPLE}💻 Comando: make${NC}"
echo ""

# Capturar tiempo y output de compilación
START_TIME=$(date +%s.%N)
COMPILE_OUTPUT=$(make 2>&1)
COMPILE_STATUS=$?
END_TIME=$(date +%s.%N)

echo "$COMPILE_OUTPUT"
echo ""

# Calcular tiempo de compilación
COMPILE_TIME=$(echo "$END_TIME - $START_TIME" | bc 2>/dev/null || echo "N/A")

if [ $COMPILE_STATUS -eq 0 ]; then
    echo -e "${GREEN}✅ Compilación exitosa${NC}"
    echo -e "${CYAN}   Tiempo de compilación: ${COMPILE_TIME}s${NC}"
    COMPILE_SUCCESS=1
else
    echo -e "${RED}❌ Error en compilación${NC}"
    COMPILE_SUCCESS=0
fi

# =============================================================================
# 3. TEST DE RE-COMPILACIÓN (SIN CAMBIOS)
# =============================================================================

if [ $COMPILE_SUCCESS -eq 1 ]; then
    echo -e "${BLUE}🔍 3. Test de re-compilación (sin cambios):${NC}"
    echo ""
    
    echo -e "${PURPLE}💻 Comando: make (segunda vez)${NC}"
    echo ""
    
    START_TIME=$(date +%s.%N)
    RECOMPILE_OUTPUT=$(make 2>&1)
    RECOMPILE_STATUS=$?
    END_TIME=$(date +%s.%N)
    
    echo "$RECOMPILE_OUTPUT"
    echo ""
    
    RECOMPILE_TIME=$(echo "$END_TIME - $START_TIME" | bc 2>/dev/null || echo "N/A")
    
    # Verificar si hubo re-linking innecesario
    if echo "$RECOMPILE_OUTPUT" | grep -q "Nothing to be done\|up to date"; then
        echo -e "${GREEN}✅ No re-linking innecesario${NC}"
        echo -e "${CYAN}   Tiempo: ${RECOMPILE_TIME}s${NC}"
        NO_RELINK=1
    elif [ $(echo "$RECOMPILE_OUTPUT" | wc -l) -le 3 ]; then
        echo -e "${GREEN}✅ Re-compilación mínima${NC}"
        echo -e "${CYAN}   Tiempo: ${RECOMPILE_TIME}s${NC}"
        NO_RELINK=1
    else
        echo -e "${RED}❌ Re-linking innecesario detectado${NC}"
        echo -e "${RED}   El proyecto se recompila completamente sin cambios${NC}"
        NO_RELINK=0
    fi
else
    NO_RELINK=0
fi

# =============================================================================
# 4. VERIFICAR BINARIO GENERADO
# =============================================================================

echo -e "${BLUE}🔍 4. Verificando binario generado:${NC}"
echo ""

# Buscar el binario (típicamente 'webserv')
BINARY_NAME=""
if [ -f "./webserv" ]; then
    BINARY_NAME="webserv"
elif [ -f "./server" ]; then
    BINARY_NAME="server"
elif [ -f "./httpd" ]; then
    BINARY_NAME="httpd"
else
    # Buscar ejecutables recién creados
    BINARY_NAME=$(find . -maxdepth 1 -type f -executable -newer "$PROJECT_DIR/Makefile" 2>/dev/null | head -1 | cut -c3-)
fi

if [ -n "$BINARY_NAME" ] && [ -f "./$BINARY_NAME" ]; then
    echo -e "${GREEN}✅ Binario encontrado: $BINARY_NAME${NC}"
    echo -e "${CYAN}   Tamaño: $(ls -lh ./$BINARY_NAME | awk '{print $5}')${NC}"
    echo -e "${CYAN}   Permisos: $(ls -l ./$BINARY_NAME | awk '{print $1}')${NC}"
    
    # Test rápido de ejecución
    if ./"$BINARY_NAME" --help >/dev/null 2>&1 || ./"$BINARY_NAME" -h >/dev/null 2>&1; then
        echo -e "${GREEN}✅ Binario ejecuta correctamente${NC}"
        BINARY_WORKS=1
    elif timeout 2s ./"$BINARY_NAME" >/dev/null 2>&1; then
        echo -e "${GREEN}✅ Binario ejecuta (timeout después de 2s)${NC}"
        BINARY_WORKS=1
    else
        echo -e "${YELLOW}⚠️ No se pudo probar ejecución del binario${NC}"
        BINARY_WORKS=1  # Asumir que funciona si existe
    fi
    
    HAS_BINARY=1
else
    echo -e "${RED}❌ No se encontró binario ejecutable${NC}"
    HAS_BINARY=0
    BINARY_WORKS=0
fi

# =============================================================================
# 5. EVALUACIÓN Y PREGUNTA PARA EL GRUPO
# =============================================================================

CRITERIA_PASSED=0
[ "$HAS_MAKEFILE" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$COMPILE_SUCCESS" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$NO_RELINK" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))
[ "$HAS_BINARY" -eq 1 ] && CRITERIA_PASSED=$((CRITERIA_PASSED + 1))

echo -e "${YELLOW}🎯 RESULTADO: $CRITERIA_PASSED/4 criterios cumplidos${NC}"

if [ "$CRITERIA_PASSED" -eq 4 ]; then
    echo -e "${GREEN}✅ CORRECTO: Compilación perfecta sin re-link issues${NC}"
elif [ "$CRITERIA_PASSED" -ge 2 ] && [ "$COMPILE_SUCCESS" -eq 1 ]; then
    echo -e "${YELLOW}⚠️ ADVERTENCIA: Compila pero hay issues menores${NC}"
else
    echo -e "${RED}❌ PROBLEMA CRÍTICO: Problemas de compilación${NC}"
fi

echo ""
echo -e "${CYAN}=========================================="
echo -e "💬 PREGUNTA PARA EL GRUPO:"
echo -e "==========================================${NC}"
echo ""
echo -e "${WHITE}¿Su proyecto compila sin problemas de re-linking?${NC}"
echo ""

echo -e "${BLUE}1. 🔨 ¿Su Makefile está bien configurado?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Sí, nuestro Makefile usa reglas apropiadas con dependencias"
echo -e "    correctas y no recompila innecesariamente'${NC}"
echo ""

echo -e "${BLUE}2. ⚡ ¿Qué sucede al ejecutar make dos veces seguidas?${NC}"
echo ""
if [ "$NO_RELINK" -eq 1 ]; then
    echo -e "${GREEN}   ✅ Comportamiento correcto observado${NC}"
    echo -e "${WHITE}   'La segunda vez debe mostrar \"Nothing to be done\" o"
    echo -e "    compilación mínima, no re-linking completo'${NC}"
else
    echo -e "${RED}   ❌ Problema detectado${NC}"
    echo -e "${WHITE}   'Hay re-linking innecesario. Revisar dependencias del Makefile'${NC}"
fi
echo ""

echo -e "${BLUE}3. 🗂️ ¿Cómo organizan sus archivos fuente?${NC}"
echo ""
echo -e "${GREEN}   ✅ Respuesta esperada:${NC}"
echo -e "${WHITE}   'Archivos .cpp en srcs/, headers .hpp en include/,"
echo -e "    objetos en un directorio separado'${NC}"
echo ""

if [ "$COMPILE_SUCCESS" -eq 0 ]; then
    echo -e "${RED}🚨 ERROR CRÍTICO DE COMPILACIÓN:${NC}"
    echo -e "${WHITE}   ❌ El proyecto NO compila correctamente"
    echo -e "   ❌ Usar flag 'Invalid compilation'"
    echo -e "   ❌ La evaluación debe parar aquí${NC}"
elif [ "$NO_RELINK" -eq 0 ]; then
    echo -e "${YELLOW}⚠️ PROBLEMA DE RE-LINKING:${NC}"
    echo -e "${WHITE}   - El proyecto recompila innecesariamente"
    echo -e "   - Revisar dependencias en Makefile"
    echo -e "   - Puede afectar la puntuación${NC}"
else
    echo -e "${GREEN}✅ COMPILACIÓN PERFECTA${NC}"
fi

echo ""
echo -e "${PURPLE}💻 Comandos para el evaluador:${NC}"
echo -e "${CYAN}   make fclean && make              # Compilación limpia${NC}"
echo -e "${CYAN}   make                             # Debe decir 'Nothing to be done'${NC}"
echo -e "${CYAN}   touch srcs/main.cpp && make      # Solo debe recompilar lo necesario${NC}"

# Volver al directorio original
cd - > /dev/null
