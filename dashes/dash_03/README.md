# 🔐 Cifrado Atbash - 42 Málaga DASH 07

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Estado-Completado-brightgreen?style=for-the-badge)

**Un proyecto desafío implementando el antiguo cifrado Atbash en C bajo presión de tiempo**

[Características](#-características) • [Instalación](#-instalación) • [Uso](#-uso) • [Algoritmo](#-algoritmo) • [Estructura](#-estructura-del-proyecto)

</div>

---

## 📖 Acerca del Proyecto

El **Cifrado Atbash** es un antiguo sistema de cifrado creado en Oriente Medio. Consiste en sustituir cada letra del alfabeto por su opuesta en el alfabeto invertido. La primera letra se sustituye por la última, la segunda por la penúltima, y así sucesivamente.

### 🏛️ Contexto Histórico y Criptográfico

El cifrado Atbash tiene sus orígenes en la cultura hebrea antigua y se menciona en textos bíblicos. Su nombre proviene de las primeras y últimas letras del alfabeto hebreo: **Aleph-Tav-Bet-Shin** (אתבש).

#### Fortalezas Históricas
En su época, el Atbash ofrecía:
- **Simplicidad de uso**: Fácil de memorizar y aplicar sin herramientas
- **Reversibilidad**: El mismo algoritmo sirve para cifrar y descifrar
- **Ocultación básica**: Suficiente para proteger mensajes de lectores casuales

#### Debilidades Criptográficas Modernas
Sin embargo, desde una perspectiva contemporánea de criptografía, el Atbash presenta importantes vulnerabilidades:

- **🔑 Clave estática**: Siempre utiliza la misma sustitución, sin posibilidad de variación
- **📊 Cifrado monoalfabético**: Cada letra siempre se transforma en la misma letra cifrada
- **📈 Vulnerable al análisis de frecuencias**: Los patrones del idioma original se mantienen
- **🔓 Fuerza bruta trivial**: Solo existe una posible configuración de clave
- **⚡ Computacionalmente insignificante**: Se puede romper instantáneamente con herramientas modernas

> **Nota educativa**: Este proyecto implementa el Atbash como ejercicio académico para comprender los fundamentos de la criptografía clásica. En aplicaciones reales, siempre se deben usar algoritmos modernos como AES, RSA o algoritmos de cifrado de curvas elípticas.

---

### 💡 Sobre Este Proyecto

Este proyecto fue desarrollado como parte del **DASH 07** en **42 Málaga** - un desafío de programación con tiempo limitado que pone a prueba las habilidades de programación, la calidad del código y la resolución de problemas bajo presión.

### 🎯 Restricciones del Desafío
- ⏱️ **Límite de Tiempo**: 2 horas
- 📏 **Norma Estricta**: Estándares de código de 42 (Norminette)
- 🔧 **Funciones Permitidas**: Solo `write`, `malloc`, `free`
- 🧪 **Requisito**: Pasar todos los casos de prueba del subject
- 💾 **Sin Fugas de Memoria**: Limpio en Valgrind

---

## ✨ Características

### 🔒 Codificación (Encode)
- Transforma texto usando el cifrado Atbash
- Convierte mayúsculas a minúsculas
- Preserva los números sin cambios
- Elimina puntuación y caracteres especiales
- Agrupa la salida en **bloques de 5 caracteres** separados por espacios

### 🔓 Decodificación (Decode)
- Revierte el cifrado Atbash de vuelta a texto plano
- Maneja entrada con espacios (grupos de 5 caracteres)
- Transformación simétrica (codificar = decodificar en Atbash)

### 🛡️ Manejo de Errores
- Valida los argumentos de línea de comandos
- Verifica strings vacíos
- Confirma que el modo es exactamente "encode" o "decode"
- Retorna mensajes de error apropiados

---

## 🚀 Instalación

```bash
# Clonar el repositorio
git clone <url-del-repositorio>
cd dash_03

# Compilar el proyecto
cd ex
gcc -Wall -Wextra -Werror *.c -o atbash

# Ejecutar el programa
./atbash encode "Hola, Mundo!"
```

### 📋 Requisitos
- Compilador de C: **GCC**, **Clang** o **cc** (compatible con estándar C99)
- **Valgrind** (para pruebas de memoria)
- **Norminette** (para validación de estilo de código)

> **Nota importante**: El subject requiere entregar solo archivos `*.c` en el directorio `ex/`. La ausencia de archivos `.h` implica que todos los prototipos de funciones deben declararse directamente en los archivos `.c` que los necesiten, lo que requiere una organización cuidadosa de las dependencias entre módulos.

---

## 💻 Uso

### Sintaxis Básica
```bash
./atbash [encode|decode] [texto]
```

### 📝 Ejemplos

#### Codificación
```bash
$ ./atbash encode hello
svool

$ ./atbash encode 'Hello, World!'
svool dliow

$ ./atbash encode 'test123'
gvhg1 23
```

#### Decodificación
```bash
$ ./atbash decode gvhg
test

$ ./atbash decode "gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt"
thequickbrownfoxjumpsoverthelazydog
```

#### Casos de Error
```bash
$ ./atbash
Error: Incorrect number of arguments

$ ./atbash "e" "test"
Error

$ ./atbash decode ""
Error
```

---

## 🔬 Algoritmo

### Transformación Atbash

El cifrado Atbash usa una sustitución simple basada en el alfabeto invertido:

```
Original:  a b c d e f g h i j k l m n o p q r s t u v w x y z
Atbash:    z y x w v u t s r q p o n m l k j i h g f e d c b a
```

#### Fórmula Matemática
Para una letra en la posición `n` (donde a=0, b=1, ..., z=25):
```
posición_cifrada = 25 - n
```

### 🔄 Proceso de Codificación

1. **Filtrar Caracteres**: Mantener solo letras (a-z, A-Z) y dígitos (0-9)
2. **Convertir Mayúsculas**: Transformar mayúsculas a minúsculas
3. **Aplicar Cifrado**: Sustituir usando el mapeo Atbash
4. **Formatear Salida**: Agrupar en bloques de 5 caracteres con espacios

### 🔄 Proceso de Decodificación

1. **Eliminar Espacios**: Quitar espacios de formato
2. **Aplicar Cifrado**: Atbash es simétrico (misma transformación)
3. **Salida**: Imprimir texto plano decodificado

---

## 📂 Estructura del Proyecto

```
dash_03/
├── ex/
│   ├── atbash.c       # Programa principal y manejo de argumentos
│   ├── encode.c       # Implementación de codificación
│   ├── decode.c       # Implementación de decodificación
│   ├── utils.c        # Funciones utilidad (transform, strings, print)
│   └── validate.c     # Funciones de validación de entrada
└── README.md          # Este archivo
```

### 🗂️ Desglose de Archivos

#### `atbash.c` (Principal)
- Parseo de argumentos de línea de comandos
- Validación del modo (encode/decode)
- Manejo de errores
- Orquestación de funciones

#### `encode.c`
- Filtrado y validación de caracteres
- Transformación Atbash para codificación
- Reserva de memoria para el resultado

#### `decode.c`
- Manejo de espacios en entrada codificada
- Transformación Atbash inversa
- Salida directa (no necesita reserva de memoria)

#### `utils.c`
- `transform_char()`: Lógica central del cifrado Atbash
- `str_len()`: Cálculo de longitud de string
- `count_valid_chars()`: Conteo de caracteres válidos
- `str_cmp()`: Comparación de strings
- `print_encoded()`: Salida formateada en grupos de 5

#### `validate.c`
- `validate_mode()`: Verificación exacta del string de modo
- `validate_input()`: Validación completa de entrada

---

## 🎨 Calidad del Código

### ✅ Cumplimiento de la Norma de 42
- Todos los archivos pasan la validación de **Norminette**
- Funciones limitadas a **25 líneas**
- Máximo **4 parámetros** por función
- Máximo **5 variables** por función
- Máximo **5 funciones** por archivo
- Headers de 42 apropiados en todos los archivos

### 🧪 Testing
```bash
# Todos los tests oficiales del subject pasan
✓ encode hello → svool
✓ encode 'Hello, World!' → svool dliow
✓ Manejo de argumentos inválidos
✓ decode gvhg → test
✓ decode con espacios
✓ Error con string vacío

# Testing de memoria
$ valgrind --leak-check=full ./atbash encode "test"
# Resultado: 0 bytes filtrados, todos los bloques liberados
```

### 📊 Rendimiento
- **Complejidad Temporal**: O(n) donde n es la longitud de entrada
- **Complejidad Espacial**: O(n) para salida codificada
- **Memoria**: Sin fugas, reporte limpio de valgrind

---

## 🔧 Detalles Técnicos

### Funciones Permitidas
Según el subject, solo estas funciones están permitidas:
- `write()` - Salida a stdout
- `malloc()` - Reserva dinámica de memoria
- `free()` - Liberación de memoria

### Compilación
```bash
gcc -Wall -Wextra -Werror *.c -o atbash
```
Compila sin warnings ni errores.

### Estándares
- Compatible con **C99**
- Cumple con **POSIX**
- Conforme a **Norma de 42** v4

---

## 🧠 Puntos Clave de Aprendizaje

### Habilidades Demostradas
1. **Implementación de Algoritmos**: Lógica de cifrado y manipulación de caracteres
2. **Procesamiento de Strings**: Filtrado, transformación y formateo
3. **Gestión de Memoria**: Reserva, uso y liberación apropiados
4. **Manejo de Errores**: Validación de entrada y casos edge
5. **Organización del Código**: Diseño modular con clara separación de responsabilidades
6. **Gestión del Tiempo**: Implementación completa bajo tiempo limitado

### Mejores Prácticas Aplicadas
- ✅ **Principio DRY**: Funciones reutilizables
- ✅ **Responsabilidad Única**: Cada función tiene un propósito claro
- ✅ **Nombres Claros**: Código autodocumentado con nombres descriptivos
- ✅ **Validación de Entrada**: Verificación robusta de errores
- ✅ **Seguridad de Memoria**: Sin fugas, limpieza apropiada
- ✅ **Documentación**: Comentarios completos explicando la lógica

---

## 📚 Recursos

### Sobre el Cifrado Atbash
- [Wikipedia - Atbash](https://es.wikipedia.org/wiki/Atbash)
- [Historia de la Criptografía](https://www.khanacademy.org/computing/computer-science/cryptography)

### 42 School
- [Red 42](https://www.42network.org/)
- [42 Málaga](https://www.42malaga.com/)

---

## 👨‍💻 Desarrollo

### Checklist de Testing
- [x] Todos los ejemplos del subject pasan
- [x] Validación de Norminette aprobada
- [x] Valgrind no reporta fugas
- [x] Casos edge manejados
- [x] Compilación limpia con todos los warnings habilitados
- [x] Código revisado y comentado

### Desglose de Tiempo
- **Análisis y Planificación**: 10 minutos
- **Implementación Core**: 30 minutos
- **Cumplimiento de Norma**: 15 minutos
- **Testing y Debugging**: 15 minutos
- **Total**: ~70 minutos ⚡

---

## 🏆 Estado del Proyecto

**✅ COMPLETADO** - Todos los requisitos cumplidos

- ✅ Codificación funciona correctamente
- ✅ Decodificación funciona correctamente
- ✅ Todos los casos de error manejados
- ✅ Norminette aprobada
- ✅ Sin fugas de memoria
- ✅ Todos los tests pasan

---

## 📄 Licencia

<div align="center">

Este proyecto es parte del curriculum de 42 School.

Siéntete libre de estudiar el código con fines educativos.

**sternero** (noviembre/2025)

</div>

---

## 🤝 Agradecimientos

- **42 Málaga** por los desafiantes y educativos proyectos DASH
- **Red 42** por la innovadora metodología de aprendizaje peer-to-peer
- Los antiguos criptógrafos que crearon el cifrado Atbash

---

<div align="center">

**Hecho con ⚡ y ☕ en 42 Málaga**

*"La única manera de aprender un nuevo lenguaje de programación es escribiendo programas en él."* - Dennis Ritchie

</div>
