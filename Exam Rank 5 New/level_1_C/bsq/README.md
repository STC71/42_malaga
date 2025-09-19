# 🟫 bsq

**Solución al problema del Biggest Square (BSQ) en C**

---

## 📚 Descripción general
Para una explicación visual y ejemplos animados, puedes ver el siguiente video:

**Problema del Biggest Square**
[🔗 Video explicativo en YouTube](https://youtu.be/6X7Ha2PrDmM?si=77fq0w3G5E-tMAg6)

Este proyecto resuelve el clásico problema del "Biggest Square" (BSQ): dado un mapa rectangular con celdas vacías y obstáculos, encuentra el mayor cuadrado posible que no contenga obstáculos y márcalo en el mapa.

---

## ✨ Características principales
- Lee mapas desde archivos de texto.
- Encuentra y marca el mayor cuadrado sin obstáculos.
- Imprime el mapa resultante con el cuadrado resaltado.

---

## 🛠️ Archivos del proyecto
- `bsq.c` — Lógica principal y funciones del algoritmo.
- `bsq.h` — Definiciones y estructuras.
- `example_file` — Ejemplo de mapa de entrada.

---

## ℹ️ Ficheros comentados y sin comentarios

En este proyecto encontrarás versiones de los ficheros fuente con y sin comentarios:
- Los ficheros con comentarios (por ejemplo, `bsq_comentado.c`, `bsq_comentado.h`) incluyen explicaciones detalladas para facilitar el aprendizaje y la comprensión del código.
- Los ficheros sin comentarios (`bsq.c`, `bsq.h`) están pensados para la entrega final, cumpliendo los requisitos del ejercicio.

Esto permite comparar la solución final con la versión explicada y usar ambos como referencia.

-----

Vamos a desglosar este proyecto del "Biggest Square" (BSQ) para que tengas una visión completa y detallada de cómo funciona. Este es un ejercicio clásico de programación que combina el manejo de archivos, la lectura de datos estructurados y un algoritmo de búsqueda.

-----

### 📚 Descripción General y Objetivo del Proyecto

El objetivo principal de este proyecto es **encontrar y marcar el cuadrado más grande** dentro de un mapa rectangular. El mapa está formado por dos tipos de caracteres: **celdas vacías** (`.`) y **obstáculos** (`o`). El programa debe encontrar el cuadrado más grande posible que contenga solo celdas vacías y, una vez encontrado, reemplazar esas celdas vacías por un tercer tipo de carácter, que representa el **cuadrado "lleno"** (`x`).

El programa se llama `bsq` y debe tomar un archivo de mapa como argumento. Si no se le pasa ningún argumento, debe ser capaz de leer el mapa directamente desde la entrada estándar (la terminal).

-----

### 📝 Estructura y Formato del Mapa

El archivo de mapa de entrada tiene una estructura muy específica:

   * La **primera línea** contiene cuatro elementos en este orden:
      1.  El número de líneas (filas) del mapa.
      2.  El carácter que representa una celda **vacía** (por ejemplo, `.` ).
      3.  El carácter que representa un **obstáculo** (por ejemplo, `o`).
      4.  El carácter que se usará para marcar el cuadrado **lleno** (por ejemplo, `x`).
   * Las **líneas siguientes** contienen el mapa real, compuesto solo por caracteres de "vacío" y "obstáculo".
   * Cada línea del mapa debe tener la **misma longitud**, estar compuesta solo por los caracteres definidos, y terminar con un salto de línea. Si el mapa no cumple con estas reglas, se considera inválido.

-----

### 🧠 El Algoritmo de Solución

El proyecto utiliza una técnica llamada **programación dinámica** para resolver el problema de manera eficiente. La idea es construir una matriz auxiliar (`dp` en el código) donde cada celda `dp[i][j]` almacena el tamaño del cuadrado más grande que termina en esa posición.

El proceso es el siguiente:

1.  Se recorre el mapa original, celda por celda.
2.  Si la celda actual es un **obstáculo**, el valor en la matriz `dp` para esa posición es `0` (porque no puede ser parte de un cuadrado).
3.  Si la celda es **vacía**, su valor en la matriz `dp` se calcula mirando las tres celdas vecinas que están encima, a la izquierda y en diagonal superior-izquierda. El valor es `1 +` el mínimo de los valores en esas tres celdas vecinas. Esto permite "construir" el cuadrado más grande posible hasta esa posición.
4.  A medida que se recorre el mapa, se lleva un registro del valor máximo encontrado en la matriz `dp`, junto con las coordenadas de la celda donde se encontró.
5.  Una vez que se ha recorrido todo el mapa, el valor máximo representa el tamaño del cuadrado más grande.
6.  Usando las coordenadas de la celda donde se encontró el valor máximo, se puede retroceder para marcar el cuadrado en el mapa original, reemplazando las celdas vacías por el carácter `full`.

Si hay más de una solución (varios cuadrados del mismo tamaño máximo), el programa debe elegir el que esté más arriba en el mapa, y si hay un empate, el que esté más a la izquierda.

-----

### 🛠️ Archivos y Funciones Clave

El proyecto se divide en los siguientes archivos:

   * **`bsq.c`**: Contiene la lógica principal.
	  * `main`: Función principal que maneja los argumentos de la línea de comandos y llama a `process_file`.
	  * `process_file`: Abre el archivo o usa la entrada estándar, llama a las funciones para leer, resolver y imprimir el mapa, y maneja los errores.
	  * `read_map`: Lee la primera línea del archivo para obtener el tamaño y los caracteres. Luego, lee el resto del mapa línea por línea, validando la longitud y los caracteres.
	  * `solve_bsq`: Implementa el algoritmo de programación dinámica para encontrar el cuadrado más grande.
	  * `print_map`: Imprime el mapa final con el cuadrado marcado.
	  * `min3`: Una función auxiliar que devuelve el mínimo de tres números enteros, usada en el algoritmo de búsqueda.

   * **`bsq.h`**: El archivo de cabecera.
	  * Define la estructura `t_map` que contiene las dimensiones del mapa (`rows`, `cols`), los caracteres (`empty`, `obstacle`, `full`), y la matriz real del mapa.
	  * Declara los prototipos de las funciones para que puedan ser utilizadas en `bsq.c`.

El proyecto también incluye versiones con comentarios (`bsq_comentado.c` y `bsq_comentado.h`) para una mejor comprensión, y una versión sin comentarios para la entrega final.

-----

### 🧪 Ejemplo de Uso y Salida Esperada

Si ejecutas el programa con el archivo de ejemplo proporcionado (`example_file`):

```bash
./bsq example_file
```

El programa leerá el mapa, encontrará el cuadrado de tamaño `7x7` y lo marcará con el carácter `x` en la salida.

**Salida:**

```
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx...o...........
.....xxxxxxx...............
......o..............o.....
..o.......o................
```

Este proyecto es una excelente manera de practicar la resolución de problemas algorítmicos con C, el manejo de entrada/salida y el uso de estructuras de datos.

---

## 🧪 Ejemplo de uso

Aquí tienes un ejemplo práctico de uso:

Supón que tienes un archivo de entrada llamado `example_file` con el siguiente contenido:

```
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
```

Al ejecutar el programa:

```sh
./bsq example_file
```

La salida será:

```
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx...o...........
.....xxxxxxx...............
......o..............o.....
..o.......o................
```

Puedes modificar el archivo de entrada para probar otros casos. El programa siempre buscará el mayor cuadrado posible sin obstáculos y lo marcará en el mapa.

---

## ⚙️ Compilación y ejecución
1. Compila el programa:
   ```sh
   gcc bsq.c -o bsq
   ```
2. Ejecuta el programa pasando el archivo de mapa como argumento:
   ```sh
   ./bsq example_file
   ```

---

## 🚦 Consejos
- Modifica `example_file` para probar diferentes mapas.
- Lee el código y los comentarios para entender el algoritmo.
- Experimenta con mapas de distintos tamaños y obstáculos.

---

## 👨‍💻 Autoría
 Ejercicio de programación en C para practicar manejo de archivos, matrices y algoritmos de búsqueda. sternero (2025).
 
 
