#!/usr/bin/env python3
import sys
import os

# Asegurar que las headers se escriben correctamente
print("Content-Type: text/html")
print("")  # Línea vacía para separar headers del contenido

print("<h1>Hello from Python!</h1>")

# Leer body desde stdin
body = ""
try:
    body = sys.stdin.read().strip()
except:
    body = "No body received"

if not body:
    body = "No body received"

print(f"<p>Received body: {body}</p>")
