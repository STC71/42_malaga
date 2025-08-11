#!/bin/sh

# Script de configuración para Uptime Kuma
# Este script se ejecuta al iniciar el contenedor

echo "🔍 Iniciando Uptime Kuma..."
echo "📊 Configurando monitorización de servicios..."

# Verificar que el directorio de datos existe
if [ ! -d "/app/data" ]; then
    echo "📁 Creando directorio de datos..."
    mkdir -p /app/data
fi

# Iniciar Uptime Kuma
echo "🚀 Iniciando servidor Uptime Kuma en puerto 3001..."
exec node server/server.js
