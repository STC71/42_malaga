# 📐 Documentación Técnica - ft_printf

> Arquitectura, implementación y análisis de rendimiento

---

## 📋 Índice

- [Contexto del Proyecto](#-contexto-del-proyecto)
- [La Función printf Original](#-la-función-printf-original)
- [Arquitectura](#-arquitectura)
- [Estructuras de Datos](#-estructuras-de-datos)
- [Documentación de Funciones](#-documentación-de-funciones)
- [Análisis de Rendimiento](#-análisis-de-rendimiento)
- [Casos Límite](#-casos-límite)

---

## 🎯 Contexto del Proyecto

### ¿Qué es ft_printf?

**ft_printf** es una reimplementación desde cero de la función `printf()` de la biblioteca estándar de C (`<stdio.h>`). Este proyecto forma parte del currículo de **42 School** y tiene como objetivo comprender en profundidad:

- Cómo funciona el formateo de texto en C
- Manejo de funciones variádicas (número variable de argumentos)
- Parseo y análisis de cadenas de formato
- Operaciones de entrada/salida de bajo nivel
- Gestión eficiente de memoria sin fugas

### Objetivos de Aprendizaje

1. **Dominar funciones variádicas** - Trabajar con `va_list`, `va_start`, `va_arg`, `va_end`
2. **Parsing complejo** - Analizar especificadores de formato con múltiples componentes
3. **I/O de bajo nivel** - Usar solo `write()` sin buffering de stdio
4. **Arquitectura modular** - Diseñar código mantenible y escalable
5. **Casos límite** - Manejar edge cases como NULL, INT_MIN, precision cero

---

## 🖨️ La Función printf Original

### ¿Qué hace printf()?

`printf()` es una función de la biblioteca estándar de C que formatea e imprime datos en la salida estándar (stdout). Su nombre viene de "**print** **f**ormatted" (imprimir formateado).

**Prototipo:**
```c
int printf(const char *format, ...);
```

**Características:**
- Acepta un **número variable de argumentos** (función variádica)
- El primer argumento es una **cadena de formato** que contiene texto literal y especificadores
- Los especificadores comienzan con `%` y determinan cómo formatear los argumentos siguientes
- Retorna el **número de caracteres impresos** (o -1 si hay error)

### Anatomía de un Especificador de Formato

Un especificador completo sigue este patrón:

```
%[flags][width][.precision]conversion
```

**Ejemplo:** `%+010.5d`
- `%` - Inicio del especificador
- `+` - Flag: mostrar siempre el signo
- `0` - Flag: rellenar con ceros
- `10` - Width: ancho mínimo de 10 caracteres
- `.5` - Precision: mínimo 5 dígitos
- `d` - Conversion: entero decimal con signo

### Conversiones Básicas

| Especificador | Tipo | Descripción | Ejemplo Entrada | Ejemplo Salida |
|---------------|------|-------------|-----------------|----------------|
| `%c` | `int` | Carácter único | `'A'` | `A` |
| `%s` | `char *` | Cadena de caracteres | `"Hola"` | `Hola` |
| `%d` / `%i` | `int` | Entero decimal con signo | `42` | `42` |
| `%u` | `unsigned int` | Entero decimal sin signo | `4294967295U` | `4294967295` |
| `%x` | `unsigned int` | Hexadecimal minúsculas | `255` | `ff` |
| `%X` | `unsigned int` | Hexadecimal MAYÚSCULAS | `255` | `FF` |
| `%p` | `void *` | Dirección de puntero | `&variable` | `0x7ffd...` |
| `%%` | - | Símbolo % literal | - | `%` |

### Ejemplos Detallados de Funcionamiento

#### Ejemplo 1: Conversiones Básicas

**Código:**
```c
printf("Carácter: %c\n", 'A');
printf("Cadena: %s\n", "Hola Mundo");
printf("Decimal: %d\n", 42);
printf("Hex: %x\n", 255);
```

**Salida:**
```
Carácter: A
Cadena: Hola Mundo
Decimal: 42
Hex: ff
```

**¿Cómo funciona?**
1. `printf()` recorre la cadena de formato carácter por carácter
2. Cuando encuentra `%`, identifica el tipo de conversión siguiente
3. Extrae el argumento correspondiente de la lista variádica
4. Convierte el argumento al formato especificado
5. Imprime el resultado

#### Ejemplo 2: Width (Ancho Mínimo)

**Código:**
```c
printf("|%5d|\n", 42);      // Ancho 5, alineación derecha (default)
printf("|%-5d|\n", 42);     // Ancho 5, alineación izquierda (flag -)
```

**Salida:**
```
|   42|
|42   |
```

**Explicación:**
- `%5d` - Reserva **mínimo 5 espacios**, rellena con espacios a la izquierda
- `%-5d` - Igual pero rellena a la **derecha** (justificación izquierda)

#### Ejemplo 3: Precision

**Para números:**
```c
printf("%.5d\n", 42);       // Mínimo 5 dígitos
printf("%.5d\n", 123456);   // Ya tiene más de 5
```

**Salida:**
```
00042
123456
```

**Para strings:**
```c
printf("%.5s\n", "Hola Mundo");  // Máximo 5 caracteres
```

**Salida:**
```
Hola 
```

#### Ejemplo 4: Flags Combinados

**Código:**
```c
printf("%+d\n", 42);         // Flag +: siempre mostrar signo
printf("% d\n", 42);         // Flag espacio: espacio si positivo
printf("%#x\n", 255);        // Flag #: forma alternativa (0x)
printf("%010d\n", 42);       // Flag 0: relleno con ceros
printf("%+010d\n", 42);      // Combinación: + y 0
```

**Salida:**
```
+42
 42
0xff
0000000042
+000000042
```

#### Ejemplo 5: Width y Precision Juntos

**Código:**
```c
printf("%10.5d\n", 42);     // Width 10, precision 5
```

**Proceso:**
1. Precision `.5` → número se convierte a mínimo 5 dígitos: `00042`
2. Width `10` → resultado se expande a 10 caracteres: `     00042`

**Salida:**
```
     00042
```

#### Ejemplo 6: Width Dinámico con `*`

**Código:**
```c
int width = 10;
int precision = 5;
printf("%*d\n", width, 42);           // Width desde variable
printf("%.*d\n", precision, 42);      // Precision desde variable
printf("%*.*d\n", width, precision, 42);  // Ambos dinámicos
```

**Salida:**
```
        42
00042
     00042
```

### Flujo de Ejecución de printf()

```
1. printf("Resultado: %d puntos\n", score);
   │
   ├─→ Itera cadena formato: "Resultado: %d puntos\n"
   │
   ├─→ Encuentra texto literal: "Resultado: "
   │   └─→ IMPRIME: "Resultado: "
   │
   ├─→ Encuentra especificador: %d
   │   ├─→ Extrae siguiente argumento: score (ej: 42)
   │   ├─→ Convierte int → string: "42"
   │   └─→ IMPRIME: "42"
   │
   ├─→ Encuentra texto literal: " puntos\n"
   │   └─→ IMPRIME: " puntos\n"
   │
   └─→ RETORNA: 18 (caracteres impresos)
```

### Diferencias entre printf() y ft_printf()

| Aspecto | printf() estándar | ft_printf() |
|---------|------------------|-------------|
| **Buffering** | Usa buffer de stdio | Write directo (sin buffer) |
| **Conversiones** | ~15+ especificadores | 9 especificadores básicos |
| **Flags** | Todos los estándares | -, 0, ., #, +, espacio |
| **Funciones usadas** | Múltiples internas | Solo `write()` + variádicas |
| **Objetivo** | Producción general | Aprendizaje y comprensión |

---

## 🚀 Cómo Usar ft_printf

### Integración en tu Proyecto

#### Paso 1: Compilar la Biblioteca ft_printf

**¿Qué vamos a hacer?**  
Convertir todos los archivos `.c` de ft_printf en una **biblioteca estática** reutilizable.

**¿Qué es una biblioteca estática?**  
Es un archivo `.a` (archive) que contiene código compilado (archivos `.o`) empaquetado y listo para ser usado en otros programas. Es como una "caja de herramientas" que podemos vincular a nuestros proyectos.

**Comandos:**
```bash
# 1. Navega al directorio donde está ft_printf
cd ft_printf_bonus

# 2. Compila la biblioteca con todas las características bonus
make bonus
```

**¿Qué hace `make bonus` internamente?**
```
1. Compila cada archivo .c a .o (código objeto):
   gcc -c ft_printf_bonus.c -o obj/ft_printf_bonus.o
   gcc -c ft_parse_bonus.c -o obj/ft_parse_bonus.o
   gcc -c ft_dispatch_bonus.c -o obj/ft_dispatch_bonus.o
   ... (y así con todos los archivos)

2. Empaqueta todos los .o en un archivo .a:
   ar rcs libftprintf.a obj/*.o
   
   ↳ ar: comando para crear archives
   ↳ rcs: flags (replace, create, sort)
   ↳ libftprintf.a: nombre de la biblioteca
```

**Resultado después del Paso 1:**
```
ft_printf_bonus/
├── libftprintf.a          ← ¡BIBLIOTECA CREADA! (código compilado)
├── ft_printf_bonus.h      ← Header con declaraciones de funciones
├── obj/                   ← Directorio con archivos .o
│   ├── ft_printf_bonus.o
│   ├── ft_parse_bonus.o
│   └── ... (más .o)
└── ... (archivos fuente .c)
```

**Verificación:**
```bash
# Comprobar que se creó la biblioteca
ls -lh libftprintf.a

# Salida esperada:
# -rw-r--r-- 1 user group 18K Nov 14 12:00 libftprintf.a
```

---

#### Paso 2: Crear tu Programa

**¿Qué vamos a hacer?**  
Escribir un programa que **use** las funciones de ft_printf.

**Opción A: En el mismo directorio de ft_printf**

```bash
# Estando en ft_printf_bonus/
# Crea el archivo aquí mismo
nano main.c
```

```c
#include "ft_printf_bonus.h"  // ← Incluye las declaraciones de ft_printf

int main(void)
{
    // Ahora podemos usar ft_printf como si fuera printf
    ft_printf("¡Hola desde ft_printf!\n");
    ft_printf("Número: %d\n", 42);
    return (0);
}
```

**Opción B: En un directorio separado (más común)**

```bash
# Supongamos que tienes esta estructura:
mi_proyecto/
├── main.c                    ← Tu programa
└── ft_printf_bonus/          ← Carpeta con ft_printf
    ├── libftprintf.a
    ├── ft_printf_bonus.h
    └── ...

# Tu main.c en mi_proyecto/:
```

```c
#include "ft_printf_bonus/ft_printf_bonus.h"  // ← Ruta relativa al header

int main(void)
{
    ft_printf("¡Hola desde mi proyecto!\n");
    return (0);
}
```

**¿Qué hace el `#include`?**
```
1. El preprocesador busca el archivo ft_printf_bonus.h
2. Copia TODO su contenido en main.c en esa línea
3. Ahora main.c "conoce" la declaración de ft_printf():
   
   int ft_printf(const char *format, ...);
   
4. Pero main.c NO tiene el código de ft_printf todavía
   ↳ Solo sabe que existe (declaración)
   ↳ El código real está en libftprintf.a
```

**Resultado después del Paso 2:**
- Tenemos un `main.c` que **declara** que usará ft_printf
- El código de ft_printf está en `libftprintf.a`
- Falta **vincular** ambos

---

#### Paso 3: Compilar y Vincular tu Programa

**¿Qué vamos a hacer?**  
Decirle al compilador que:
1. Compile `main.c`
2. **Vincule** (link) nuestro código con el código de `libftprintf.a`
3. Genere un ejecutable final que contenga todo

**Escenario A: main.c en el mismo directorio que libftprintf.a**

```bash
# Estando en ft_printf_bonus/ donde está libftprintf.a
gcc main.c -L. -lftprintf -o mi_programa
```

**Escenario B: main.c en directorio separado**

```bash
# Estando en mi_proyecto/ donde está main.c
gcc main.c -L./ft_printf_bonus -lftprintf -o mi_programa
```

**¿Qué significa cada parte del comando?**

```bash
gcc main.c -L./ft_printf_bonus -lftprintf -o mi_programa
│   │      │                   │           │
│   │      │                   │           └─→ Nombre del ejecutable final
│   │      │                   │
│   │      │                   └──────────────→ Busca libftprintf.a y vincúlala
│   │      │                                    (gcc añade automáticamente "lib" + ".a")
│   │      │
│   │      └──────────────────────────────────→ Busca bibliotecas en esta carpeta
│   │                                            (L = Library path)
│   │
│   └─────────────────────────────────────────→ Archivo fuente a compilar
│
└─────────────────────────────────────────────→ Compilador GNU C
```

**¿Qué hace gcc internamente? (proceso completo)**

```
Paso 3.1 - PREPROCESAMIENTO:
   gcc -E main.c
   ↳ Expande #include, #define, etc.
   ↳ Resultado: main.c con código de ft_printf_bonus.h incrustado

Paso 3.2 - COMPILACIÓN:
   gcc -S main.c
   ↳ Convierte código C a lenguaje ensamblador
   ↳ Resultado: main.s (código assembly)

Paso 3.3 - ENSAMBLADO:
   gcc -c main.c
   ↳ Convierte assembly a código máquina
   ↳ Resultado: main.o (código objeto)
   
   En este punto:
   - main.o tiene el código de main()
   - main.o tiene REFERENCIAS a ft_printf()
   - Pero NO tiene el código de ft_printf aún

Paso 3.4 - VINCULACIÓN (LINKING):
   ld main.o libftprintf.a -o mi_programa
   
   El linker (ld):
   1. Ve que main.o necesita ft_printf()
   2. Busca ft_printf en libftprintf.a
   3. Extrae el código de ft_printf de libftprintf.a
   4. COMBINA main.o + código de ft_printf
   5. Genera el ejecutable final: mi_programa
   
   ↳ Resultado: mi_programa (ejecutable autónomo)
```

**Visualización del proceso completo:**

```
ANTES:                          DESPUÉS:
┌─────────────┐                ┌────────────────┐
│ main.c      │                │  mi_programa   │
│  - main()   │                │  (ejecutable)  │
│  - llama    │                │                │
│    ft_printf│                │  ┌───────────┐ │
└─────────────┘                │  │  main()   │ │
                               │  │  {código} │ │
┌──────────────────┐           │  └───────────┘ │
│ libftprintf.a    │           │                │
│  ┌──────────────┐│   gcc     │  ┌───────────┐ │
│  │ ft_printf()  ││  ─────>   │  │ft_printf()│ │
│  │ ft_dispatch()││           │  │{código}   │ │
│  │ ... más      ││           │  │ft_dispatch│ │
│  └──────────────┘│           │  │... etc    │ │
└──────────────────┘           │  └───────────┘ │
                               │                │
                               │  TODO JUNTO    │
                               └────────────────┘
```

**Resultado después del Paso 3:**
```
mi_proyecto/
├── main.c                    ← Código fuente (no modificado)
├── mi_programa               ← ¡EJECUTABLE FINAL! ✨
└── ft_printf_bonus/
    ├── libftprintf.a         ← Biblioteca (no modificada)
    └── ft_printf_bonus.h     ← Header (no modificado)
```

---

#### Paso 4: Ejecutar tu Programa

```bash
# Ejecuta el programa
./mi_programa
```

**Salida:**
```
¡Hola desde ft_printf!
Número: 42
```

**¿Qué ocurre al ejecutar?**
```
1. El sistema operativo carga mi_programa en memoria
2. Empieza a ejecutar desde main()
3. Llama a ft_printf() ← El código YA ESTÁ dentro del ejecutable
4. ft_printf() internamente usa write() para imprimir
5. El programa termina y devuelve 0
```

---

### Resumen Visual del Proceso Completo

```
PASO 1: Crear biblioteca
─────────────────────────
ft_printf_bonus.c  ┐
ft_parse_bonus.c   │  make bonus
ft_dispatch_bonus.c│  ─────────>  libftprintf.a
...                ┘              (biblioteca)

PASO 2: Escribir programa
──────────────────────────
main.c:
  #include "ft_printf_bonus.h"  ← Declara que usaremos ft_printf
  ft_printf("Hola");             ← Llama a la función

PASO 3: Compilar y vincular
────────────────────────────
main.c + libftprintf.a  
    │
    │  gcc -L. -lftprintf
    ▼
mi_programa (ejecutable con TODO el código)

PASO 4: Ejecutar
─────────────────
./mi_programa  ──>  Salida en pantalla
```

---

### Explicación Detallada de Flags de Compilación

```bash
gcc main.c -L./ft_printf_bonus -lftprintf -I./ft_printf_bonus -o mi_programa
```

| Flag | Significado | Ejemplo | Qué hace |
|------|-------------|---------|----------|
| `-L` | **Library path** (ruta de bibliotecas) | `-L./ft_printf_bonus` | Busca archivos `.a` en esta carpeta |
| `-l` | **Link library** (vincular biblioteca) | `-lftprintf` | Busca `libftprintf.a` y vincúlala |
| `-I` | **Include path** (ruta de headers) | `-I./ft_printf_bonus` | Busca archivos `.h` en esta carpeta |
| `-o` | **Output** (nombre de salida) | `-o mi_programa` | Nombre del ejecutable final |

**Nota:** El flag `-I` no es necesario si usas rutas relativas en el `#include`:
```c
#include "ft_printf_bonus/ft_printf_bonus.h"  // Ruta relativa
vs
#include "ft_printf_bonus.h"  // Necesita -I para encontrarlo
```

---

### Estructura de Proyecto Recomendada

**Opción 1: Proyecto pequeño**
```
mi_proyecto/
├── main.c
├── ft_printf_bonus/
│   ├── libftprintf.a
│   ├── ft_printf_bonus.h
│   └── ...
└── Makefile (opcional)

Compilar:
gcc main.c -L./ft_printf_bonus -lftprintf -o programa
```

**Opción 2: Proyecto más grande**
```
mi_proyecto/
├── srcs/
│   ├── main.c
│   └── utils.c
├── includes/
│   └── my_header.h
├── libs/
│   └── ft_printf_bonus/
│       ├── libftprintf.a
│       └── ft_printf_bonus.h
└── Makefile

Compilar:
gcc srcs/*.c -L./libs/ft_printf_bonus -lftprintf \
    -I./includes -I./libs/ft_printf_bonus -o programa
```

### Sintaxis y Uso

**Prototipo:**
```c
int ft_printf(const char *format, ...);
```

**Retorna:** Número de caracteres impresos (o -1 si error)

### Ejemplos Prácticos

#### Ejemplo 1: Programa Básico

```c
#include "ft_printf.h"

int main(void)
{
    char    *nombre = "Juan";
    int     edad = 25;
    
    ft_printf("Hola, me llamo %s\n", nombre);
    ft_printf("Tengo %d años\n", edad);
    
    return (0);
}
```

**Salida:**
```
Hola, me llamo Juan
Tengo 25 años
```

#### Ejemplo 2: Usar el Valor de Retorno

```c
#include "ft_printf.h"

int main(void)
{
    int caracteres;
    
    caracteres = ft_printf("Hola Mundo!\n");
    ft_printf("Se imprimieron %d caracteres\n", caracteres);
    
    return (0);
}
```

**Salida:**
```
Hola Mundo!
Se imprimieron 12 caracteres
```

#### Ejemplo 3: Múltiples Conversiones

```c
#include "ft_printf.h"

int main(void)
{
    char    letra = 'X';
    int     numero = 42;
    void    *ptr = &numero;
    
    ft_printf("Carácter: %c\n", letra);
    ft_printf("Decimal: %d\n", numero);
    ft_printf("Hexadecimal: %x\n", numero);
    ft_printf("HEXADECIMAL: %X\n", numero);
    ft_printf("Puntero: %p\n", ptr);
    ft_printf("Porcentaje: 100%%\n");
    
    return (0);
}
```

**Salida:**
```
Carácter: X
Decimal: 42
Hexadecimal: 2a
HEXADECIMAL: 2A
Puntero: 0x7ffc12345678
Porcentaje: 100%
```

#### Ejemplo 4: Formateo con Width (Ancho)

```c
#include "ft_printf.h"

int main(void)
{
    int precio = 99;
    
    ft_printf("┌────────────┐\n");
    ft_printf("│ Precio: %3d│\n", precio);      // Ancho 3
    ft_printf("└────────────┘\n");
    
    // Tabla con columnas alineadas
    ft_printf("\n%-10s %10s\n", "Producto", "Precio");
    ft_printf("%-10s %10d€\n", "Laptop", 999);
    ft_printf("%-10s %10d€\n", "Mouse", 25);
    
    return (0);
}
```

**Salida:**
```
┌────────────┐
│ Precio:  99│
└────────────┘

Producto        Precio
Laptop            999€
Mouse              25€
```

#### Ejemplo 5: Formateo con Precision

```c
#include "ft_printf.h"

int main(void)
{
    // Precision en números: mínimo de dígitos
    ft_printf("PIN: %.4d\n", 42);           // 0042
    ft_printf("Código: %.6d\n", 123);       // 000123
    
    // Precision en strings: máximo de caracteres
    char *texto = "Hola Mundo";
    ft_printf("Completo: %s\n", texto);     // Hola Mundo
    ft_printf("Truncado: %.4s\n", texto);   // Hola
    
    return (0);
}
```

**Salida:**
```
PIN: 0042
Código: 000123
Completo: Hola Mundo
Truncado: Hola
```

#### Ejemplo 6: Flags Avanzados

```c
#include "ft_printf.h"

int main(void)
{
    int num = 42;
    int neg = -42;
    
    // Flag +: mostrar siempre el signo
    ft_printf("Con +: %+d, %+d\n", num, neg);
    
    // Flag ' ' (espacio): espacio si positivo
    ft_printf("Con espacio: % d, % d\n", num, neg);
    
    // Flag 0: rellenar con ceros
    ft_printf("Con ceros: %010d\n", num);
    
    // Flag #: forma alternativa en hexadecimal
    ft_printf("Hex normal: %x\n", 255);
    ft_printf("Hex con #: %#x\n", 255);
    
    return (0);
}
```

**Salida:**
```
Con +: +42, -42
Con espacio:  42, -42
Con ceros: 0000000042
Hex normal: ff
Hex con #: 0xff
```

#### Ejemplo 7: Width y Precision Dinámicos

```c
#include "ft_printf.h"

int main(void)
{
    int ancho = 10;
    int precision = 5;
    int valor = 42;
    
    // Width dinámico con *
    ft_printf("Ancho %d: |%*d|\n", ancho, ancho, valor);
    
    // Precision dinámica con .*
    ft_printf("Precision %d: %.0*d\n", precision, precision, valor);
    
    // Ambos dinámicos
    ft_printf("Ambos: |%*.*d|\n", ancho, precision, valor);
    
    return (0);
}
```

**Salida:**
```
Ancho 10: |        42|
Precision 5: 00042
Ambos: |     00042|
```

#### Ejemplo 8: Debugging con ft_printf

```c
#include "ft_printf.h"

void debug_array(int *arr, int size)
{
    ft_printf("Array[%d]: { ", size);
    
    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            ft_printf(", ");
        ft_printf("%d", arr[i]);
    }
    
    ft_printf(" }\n");
}

int main(void)
{
    int numeros[] = {10, 20, 30, 40, 50};
    
    ft_printf("=== Debug Info ===\n");
    ft_printf("Variable address: %p\n", numeros);
    ft_printf("Array size: %d bytes\n", (int)sizeof(numeros));
    
    debug_array(numeros, 5);
    
    return (0);
}
```

**Salida:**
```
=== Debug Info ===
Variable address: 0x7ffc12345678
Array size: 20 bytes
Array[5]: { 10, 20, 30, 40, 50 }
```

#### Ejemplo 9: Manejo de Casos Especiales

```c
#include "ft_printf.h"

int main(void)
{
    char    *str_null = NULL;
    void    *ptr_null = NULL;
    
    // Strings NULL
    ft_printf("String NULL: %s\n", str_null);      // (null)
    
    // Punteros NULL
    ft_printf("Puntero NULL: %p\n", ptr_null);     // (nil)
    
    // Cero con precision cero
    ft_printf("Cero con .0: '%.0d'\n", 0);         // '' (vacío)
    
    // INT_MIN
    ft_printf("INT_MIN: %d\n", -2147483648);
    
    return (0);
}
```

**Salida:**
```
String NULL: (null)
Puntero NULL: (nil)
Cero con .0: ''
INT_MIN: -2147483648
```

### Makefile Integration

Si quieres integrar ft_printf en tu propio Makefile:

```makefile
NAME = mi_programa
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directorio de ft_printf
PRINTF_DIR = ./ft_printf_bonus
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(PRINTF_LIB):
	make bonus -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(PRINTF_DIR) -lftprintf -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
```

### Diferencias de Comportamiento

**⚠️ Nota importante:** Aunque ft_printf replica el comportamiento de printf, hay pequeñas diferencias:

1. **Solo conversiones básicas** - No soporta `%f`, `%g`, `%e` (floats), ni `%n`
2. **Sin modificadores de longitud** - No soporta `%ld`, `%lld`, `%hd`, etc.
3. **Write directo** - Sin buffering, puede ser más lento en algunos casos
4. **Solo flags básicos** - No todos los flags estándar están implementados

**✅ Compatibilidad garantizada:**
- Todas las conversiones: `c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%%`
- Flags bonus: `-`, `0`, `.`, `#`, `+`, ` ` (espacio)
- Width y precision (incluido `*`)
- Valor de retorno idéntico a printf

---

## 🏗️ Arquitectura

### Filosofía de Diseño

La implementación sigue principios modulares:

1. **Separación de Responsabilidades** - Cada módulo tiene una función específica
2. **Responsabilidad Única** - Las funciones hacen una cosa bien
3. **Reutilización** - Funciones auxiliares compartidas
4. **Programación Defensiva** - Checks extensivos de NULL y casos límite

### Diagrama de Flujo

```
┌────────────────────────────────┐
│       ft_printf()              │
│   [Punto de Entrada]           │
│  • Inicializa va_list          │
│  • Itera cadena de formato     │
│  • Despacha en '%'             │
└──────────┬─────────────────────┘
           │
           ▼
┌────────────────────────────────┐
│    ft_parse_format()           │
│    [Parser]                    │
│  • Parsea flags (-, 0, #, +)   │
│  • Parsea width y precision    │
│  • Identifica conversión       │
└──────────┬─────────────────────┘
           │
           ▼
┌────────────────────────────────┐
│      ft_dispatch()             │
│      [Router]                  │
│  • Enruta a handler correcto   │
└──────────┬─────────────────────┘
           │
    ┌──────┴──────┬──────┬──────┐
    ▼             ▼      ▼      ▼
 ┌────┐      ┌─────┐ ┌────┐ ┌────┐
 │ %c │      │ %d  │ │ %x │ │ %p │
 │ %s │      │ %u  │ │ %X │ │    │
 └────┘      └─────┘ └────┘ └────┘
 char/str    números  hex   puntero
```

### Módulos

| Módulo | Archivo | Responsabilidad |
|--------|---------|-----------------|
| **Core** | `ft_printf_bonus.c` | Punto de entrada, loop principal |
| **Parser** | `ft_parse_bonus.c` | Análisis de especificadores |
| **Router** | `ft_dispatch_bonus.c` | Despacho a handlers |
| **Utils** | `ft_utils_bonus.c` | Funciones auxiliares |
| **Numbers** | `ft_putnbr_bonus.c` | Enteros con signo |
| **Unsigned** | `ft_putunsigned_bonus.c` | Sin signo y hex |
| **Pointers** | `ft_putptr_bonus.c` | Direcciones de memoria |
| **Lengths** | `ft_numlen_bonus.c` | Cálculo de longitudes |

---

## 🔧 Estructuras de Datos

### t_format

```c
typedef struct s_format
{
    char    specifier;       // Tipo: c, s, d, i, u, x, X, p
    int     left_align;      // Flag '-': justificación izquierda
    int     zero_pad;        // Flag '0': relleno con ceros
    int     alt_form;        // Flag '#': forma alternativa (0x)
    int     force_sign;      // Flag '+': mostrar signo siempre
    int     space_sign;      // Flag ' ': espacio antes de positivos
    int     min_width;       // Ancho mínimo de campo
    int     precision;       // Valor de precisión
    int     has_precision;   // ¿Precisión especificada?
}   t_format;
```

**Propósito:** Encapsula todos los parámetros de formateo extraídos del especificador.

**Inicialización:**
```c
void init_format(t_format *fmt)
{
    fmt->specifier = 0;
    fmt->left_align = 0;
    fmt->zero_pad = 0;
    fmt->alt_form = 0;
    fmt->force_sign = 0;
    fmt->space_sign = 0;
    fmt->min_width = 0;
    fmt->precision = -1;
    fmt->has_precision = 0;
}
```

---

## 📚 Documentación de Funciones

### Formato de Documentación

Cada función incluye comentarios explicando:

1. **Purpose** - Qué hace
2. **Why** - Razón de decisiones de diseño
3. **How it works** - Lógica paso a paso
4. **Example** - Demostración entrada → salida

```c
/*
** function_name - Descripción breve
**
** Purpose: Qué hace esta función
** Why [design decision]: Razón de la elección
** How it works:
**   1. Paso uno
**   2. Paso dos
** Example: input → output
*/
```

### Funciones Principales

<details>
<summary><b>Core Functions (ft_printf_bonus.c)</b></summary>

#### `init_format()`
**Purpose:** Inicializa estructura con valores por defecto  
**Why struct:** Agrupa parámetros relacionados evitando 9+ parámetros en funciones

#### `ft_parse_format()`
**Purpose:** Parsea especificador completo desde '%' hasta conversión  
**How:**
1. Parsea flags (-, 0, #, +, espacio)
2. Parsea width (número o `*`)
3. Parsea precision (.número o `.*`)
4. Identifica tipo de conversión

#### `ft_printf()`
**Purpose:** Función variádica principal  
**How:**
1. Inicializa `va_list`
2. Itera cadena formato
3. Imprime literales o parsea '%'
4. Retorna total de caracteres escritos

</details>

<details>
<summary><b>Parser Functions (ft_parse_bonus.c)</b></summary>

#### `ft_isdigit()`
**Purpose:** Check si carácter es dígito  
**Why static:** Solo usada internamente en este módulo

#### `ft_atoi_skip()`
**Purpose:** Convierte string a int y avanza puntero  
**Why combined:** Eficiencia - un solo paso para convertir y avanzar

#### `parse_flags()`
**Purpose:** Extrae todos los flags (-, 0, #, +, espacio)  
**How:** Loop mientras encuentra caracteres de flag válidos

#### `parse_width_precision()`
**Purpose:** Parsea width y precision (soporta `*`)  
**How:** 
1. Width: número directo o fetch de `va_list` si `*`
2. Precision: tras '.', número o fetch si `.*`

</details>

<details>
<summary><b>Dispatcher Functions (ft_dispatch_bonus.c)</b></summary>

#### `ft_dispatch()`
**Purpose:** Enruta a handler correcto según conversión  
**Why switch:** Más eficiente que cadenas if-else

#### `handle_char()`
**Purpose:** Imprime carácter con width  
**How:** Padding izq/der según flag `-`

#### `handle_string()`
**Purpose:** Imprime string con width y precision  
**How:** Trunca según precision, aplica padding

#### `dispatch_numbers()`
**Purpose:** Enruta conversiones numéricas  
**How:** Separa signed (%d, %i) de unsigned (%u, %x, %X)

</details>

<details>
<summary><b>Utilities (ft_utils_bonus.c)</b></summary>

#### `ft_strlen()`
**Purpose:** Calcula longitud de cadena  
**Why reimplemented:** No se permite usar librerías externas

#### `ft_putchar_cnt()`
**Purpose:** Imprime carácter vía `write()` y devuelve 1  
**Why return:** Facilita conteo acumulativo

#### `ft_putstr_cnt()`
**Purpose:** Imprime string hasta longitud máxima  
**Why max:** Soporta precision de strings

#### `ft_putpad()`
**Purpose:** Imprime carácter de padding N veces  
**Why separate:** Reutilizable para espacios y ceros

</details>

<details>
<summary><b>Number Length (ft_numlen_bonus.c)</b></summary>

#### `ft_numlen_base()`
**Purpose:** Cuenta dígitos de número con signo en base dada  
**How:** División sucesiva por base, +1 si negativo

#### `ft_unumlen_base()`
**Purpose:** Cuenta dígitos de número sin signo  
**How:** División sucesiva por base

</details>

<details>
<summary><b>Signed Numbers (ft_putnbr_bonus.c)</b></summary>

#### `ft_putunbr_rec()`
**Purpose:** Impresión recursiva en cualquier base  
**Why recursive:** Elegante para reversión de dígitos

#### `get_num_len()`
**Purpose:** Longitud total incluyendo precision  
**How:** max(dígitos, precision)

#### `print_sign_prefix()`
**Purpose:** Maneja flags +, -, espacio para signo  
**Priority:** `-` > `+` > ` `

#### `print_number_body()`
**Purpose:** Imprime número con ceros de precision  
**How:** Relleno con ceros + dígitos

#### `ft_putnbr_base()`
**Purpose:** Orquesta salida completa con todos los flags  
**How:**
1. Calcula longitudes
2. Padding izquierdo (si no left_align)
3. Signo
4. Ceros (si zero_pad y no left_align)
5. Número con precision
6. Padding derecho (si left_align)

</details>

<details>
<summary><b>Unsigned Numbers (ft_putunsigned_bonus.c)</b></summary>

#### `ft_putunbr_rec()`
**Purpose:** Impresión recursiva sin signo

#### `print_prefix()`
**Purpose:** Imprime `0x` o `0X` si flag `#`  
**When:** Solo si valor != 0

#### `get_total_len()`
**Purpose:** Longitud incluyendo prefijo y precision

#### `apply_precision_padding()`
**Purpose:** Añade ceros por precision antes de dígitos

#### `ft_putunsigned()`
**Purpose:** Orquesta salida unsigned/hex con flags  
**How:** Similar a signed pero con prefijo `#`

</details>

<details>
<summary><b>Pointers (ft_putptr_bonus.c)</b></summary>

#### `ft_putunbr_rec()`
**Purpose:** Imprime dígitos hex de dirección

#### `print_nil_ptr()`
**Purpose:** Case especial para puntero NULL  
**Output:** `"(nil)"`

#### `ft_putptr()`
**Purpose:** Imprime dirección con prefijo `0x`  
**How:**
1. Check NULL → "(nil)"
2. Prefijo "0x"
3. Dirección en hex minúsculas

</details>

### Estadísticas de Documentación

- **Total funciones:** 37
- **Archivos documentados:** 12
- **Líneas de comentarios:** ~500
- **Formato:** Consistente en todos los módulos

---

## ⚡ Análisis de Rendimiento

### Benchmarks

| Métrica | Valor | Notas |
|---------|-------|-------|
| Tiempo de compilación | < 2s | Con optimizaciones |
| Tamaño binario | ~18 KB | Biblioteca estática (.a) |
| Ejecución tests (54) | < 1s | Suite completa |
| Huella de memoria | Mínima | Sin buffering |
| Fugas de memoria | 0 bytes | Verificado con valgrind |

### Complejidad

| Operación | Temporal | Espacial |
|-----------|----------|----------|
| Parseo de formato | O(n) | O(1) |
| Impresión números | O(log n) | O(log n)* |
| Impresión strings | O(n) | O(1) |
| **Global** | **O(n)** | **O(log n)** |

*\* Pila de recursión para conversión número → string*

### Optimizaciones

1. **Sin buffering dinámico** - Write directo, sin malloc/free por conversión
2. **Funciones inline estáticas** - Reducción de overhead de llamadas
3. **Cálculo de longitudes previo** - Un solo paso de padding
4. **Reutilización de código** - Funciones auxiliares compartidas

---

## 🔬 Casos Límite

### Punteros NULL

```c
ft_printf("%s\n", NULL);          // (null)
ft_printf("%p\n", NULL);          // (nil)
```

### INT_MIN / INT_MAX

```c
ft_printf("%d\n", INT_MIN);       // -2147483648
ft_printf("%d\n", INT_MAX);       // 2147483647
ft_printf("%+d\n", INT_MIN);      // -2147483648 (no +)
```

### Cero con Precision

```c
ft_printf("%.0d\n", 0);           // (vacío)
ft_printf("%.5d\n", 0);           // 00000
ft_printf("%#.0x\n", 0);          // (vacío, sin 0x)
```

### Ancho Negativo (vía *)

```c
ft_printf("%*d\n", -10, 42);      // Equivale a %-10d
// Salida: "42        "
```

### Conflictos de Flags

```c
// '-' tiene prioridad sobre '0'
ft_printf("%-010d\n", 42);        // "42        " (no ceros)

// '+' tiene prioridad sobre ' '
ft_printf("%+ d\n", 42);          // "+42" (no espacio)
```

### Strings Largos

```c
char *largo = "cadena muy muy larga...";
ft_printf("%.10s\n", largo);      // "cadena muy" (truncado)
ft_printf("%5.10s\n", largo);     // "cadena muy" (width ignorado si menor)
```

### Porcentaje Consecutivo

```c
ft_printf("100%%\n");             // 100%
ft_printf("%%%%\n");              // %%
```

---

## 🛠️ Funciones Permitidas

### Syscall

- **`write(int fd, const void *buf, size_t count)`**
  - Única función de I/O permitida
  - Usado para imprimir a stdout

### Variadic Functions

- **`va_start(va_list ap, last)`** - Inicializa lista de argumentos
- **`va_arg(va_list ap, type)`** - Obtiene siguiente argumento
- **`va_end(va_list ap)`** - Limpia lista
- **`va_copy(va_list dest, va_list src)`** - Copia lista (no usado en este proyecto)

### Memory Management

- **`malloc(size_t size)`** - Asignación dinámica (no usada en este proyecto)
- **`free(void *ptr)`** - Liberación (no usada)

---

## 📊 Cumplimiento Norminette

### Reglas Aplicadas

- ✅ Máx. 25 líneas por función
- ✅ Máx. 5 funciones por archivo
- ✅ Máx. 80 columnas por línea
- ✅ Indentación con tabuladores
- ✅ Espacios según estándar 42
- ✅ Nomenclatura consistente
- ✅ Sin variables globales (excepto autorizadas)
- ✅ Comentarios de header apropiados

### Verificación

```bash
norminette -R CheckForbiddenSourceHeader *.c *.h

# Output esperado:
# ft_printf_bonus.c: OK!
# ft_parse_bonus.c: OK!
# ... (14 archivos total)
```

---

## 🔍 Debugging Tips

### Con GDB

```bash
cc -g ft_printf_bonus.c ... -o test_debug
gdb ./test_debug

(gdb) break ft_printf
(gdb) run
(gdb) print fmt
(gdb) step
```

### Con Valgrind

```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./test_bonus

# Verificar:
# - definitely lost: 0 bytes
# - indirectly lost: 0 bytes
# - possibly lost: 0 bytes
```

### Con Sanitizers

```bash
cc -fsanitize=address -g *.c -o test_asan
./test_asan

cc -fsanitize=undefined -g *.c -o test_ubsan
./test_ubsan
```

---

## 📖 Referencias Técnicas

### Standards

- **ISO C99** - Funciones variádicas
- **POSIX.1-2008** - Syscall `write()`
- **42 Norminette v3.x** - Estilo de código

### Comportamiento printf()

- Man page: `man 3 printf`
- Cppreference: https://en.cppreference.com/w/c/io/fprintf
- POSIX spec: https://pubs.opengroup.org/onlinepubs/9699919799/

---

<div align="center">

[← Volver al README](README.md)

*Documentación técnica completa de ft_printf*

</div>
