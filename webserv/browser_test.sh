#!/bin/bash

# Obtener ruta absoluta del ejecutable webserv
WEBSERV_PATH="$(cd "$(dirname "$0")" && pwd)/webserv"

# Comprobar si webserv está corriendo
if ! pgrep -f "$WEBSERV_PATH" > /dev/null; then
    echo "webserv no está en ejecución. Iniciando en una nueva terminal..."
    # Detectar terminal disponible
    if command -v gnome-terminal &> /dev/null; then
        gnome-terminal -- bash -c "$WEBSERV_PATH; exec bash" &
    elif command -v x-terminal-emulator &> /dev/null; then
        x-terminal-emulator -e "$WEBSERV_PATH; bash" &
    elif command -v konsole &> /dev/null; then
        konsole -e bash -c "$WEBSERV_PATH; exec bash" &
    elif command -v xfce4-terminal &> /dev/null; then
        xfce4-terminal -e "$WEBSERV_PATH; bash" &
    else
        echo "No se encontró un emulador de terminal compatible. Inicia ./webserv manualmente."
        exit 1
    fi
    sleep 2
fi

# Abrir la ventana de Firefox solo con la primera URL
firefox --new-window http://localhost:9000 &> /dev/null &
sleep 4

# Abrir el resto de URLs como nuevas pestañas en la misma ventana, una a una
for url in http://localhost:9001 http://localhost:9002 http://localhost:9003 http://localhost:9005 http://localhost:9005/index.html; do
    firefox --new-tab $url &> /dev/null &
    sleep 1
done

# Obtener resolución de pantalla
SCREEN_W=$(xdpyinfo | awk '/dimensions:/ {print $2}' | cut -d 'x' -f 1 2>/dev/null)
SCREEN_H=$(xdpyinfo | awk '/dimensions:/ {print $2}' | cut -d 'x' -f 2 2>/dev/null)
HALF_W=$((SCREEN_W / 2))
HALF_H=$((SCREEN_H / 2))

# Buscar la última ventana de Firefox y posicionarla en la mitad inferior izquierda (extremo izquierdo)
for i in {1..5}; do
    FF_WIN=$(wmctrl -l 2>/dev/null | grep -i 'Mozilla Firefox' | awk '{print $1}' | tail -n1)
    if [ -n "$FF_WIN" ]; then
        wmctrl -i -r "$FF_WIN" -b remove,maximized_vert,maximized_horz 2>/dev/null
        wmctrl -i -r "$FF_WIN" -e 0,0,$HALF_H,$HALF_W,$HALF_H 2>/dev/null
        break
    fi
    sleep 1
done

# Abrir Chrome en una sola ventana con todas las pestañas y tamaño/posición forzados
CHROME_BIN="google-chrome"
if ! command -v $CHROME_BIN &> /dev/null; then
    CHROME_BIN="chromium-browser"
fi
# Chrome totalmente a la derecha
CHROME_X=$((SCREEN_W - HALF_W))
$CHROME_BIN --new-window http://localhost:9000/index.html http://localhost:9000 http://localhost:9001 http://localhost:9002 http://localhost:9003 http://localhost:9005 \
    --window-size=$HALF_W,$HALF_H --window-position=$CHROME_X,0 &> /dev/null &
sleep 0.5

# Chrome: mitad superior derecha (redimensionar todas las ventanas de Chrome)
for i in {1..5}; do
    for CHROME_WIN in $(wmctrl -l 2>/dev/null | grep -iE 'Google Chrome|Chromium' | awk '{print $1}'); do
        wmctrl -i -r "$CHROME_WIN" -b remove,maximized_vert,maximized_horz 2>/dev/null
        wmctrl -i -r "$CHROME_WIN" -e 0,$CHROME_X,0,$HALF_W,$HALF_H 2>/dev/null
    done
    sleep 0.5
done

# Enfocar la ventana de Chrome y simular Ctrl+9 (ir a la última pestaña)
if command -v xdotool &> /dev/null; then
    CHROME_WIN_ID=$(wmctrl -l | grep -iE 'Google Chrome|Chromium' | awk '{print $1}' | head -n1)
    if [ -n "$CHROME_WIN_ID" ]; then
        wmctrl -ia "$CHROME_WIN_ID"
        sleep 1
        xdotool key --window "$CHROME_WIN_ID" ctrl+9
    fi
fi

exit