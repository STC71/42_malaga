# 🧬 life
---
## ℹ️ Ficheros comentados y sin comentarios

Este proyecto incluye versiones de los ficheros fuente con y sin comentarios:
- Los ficheros comentados (por ejemplo, `life_comentado.c`, `life_comentado.h`) contienen explicaciones detalladas para facilitar el estudio y la comprensión del código.
- Los ficheros sin comentarios (`life.c`, `life.h`) están pensados para la entrega final, cumpliendo los requisitos del ejercicio.

Así puedes consultar la lógica explicada y la versión final, según lo que necesites.

**Implementación del Juego de la Vida de Conway en C**

---

## 📚 Descripción general

Este proyecto implementa el famoso "Juego de la Vida" de John Conway: un autómata celular donde cada celda de una cuadrícula vive o muere según reglas simples, generando patrones complejos a lo largo de generaciones.

Para una explicación visual y ejemplos animados, puedes ver este video introductorio sobre el Juego de la Vida:
[🔗 Video explicativo en YouTube](https://youtu.be/OWXD_wJxCKQ?si=12zhWOU-yk_JYgAc)

---

## 🎯 Objetivo y funcionamiento

Los **autómatas celulares** son modelos matemáticos formados por una cuadrícula de celdas, donde cada celda puede estar en un número finito de estados (por ejemplo, viva o muerta). El estado de cada celda evoluciona a lo largo de generaciones según reglas simples que dependen del estado de sus celdas vecinas. A pesar de su sencillez, los autómatas celulares pueden generar comportamientos y patrones muy complejos, y se utilizan para estudiar fenómenos en matemáticas, física, biología y computación.

El objetivo de este programa es simular el "Juego de la Vida" de Conway, un autómata celular donde cada celda de una cuadrícula puede estar viva o muerta. El usuario define el tamaño del tablero, el número de iteraciones (generaciones) a simular y el estado inicial del tablero mediante comandos sencillos por la entrada estándar.

- **Estado inicial:** El lápiz comienza siempre en la esquina superior izquierda de la cuadrícula (posición [0,0]). Se dibuja usando comandos (`w`, `a`, `s`, `d` para mover el lápiz y `x` para alternar entre dibujar o no). Así puedes crear cualquier patrón inicial de celdas vivas.
- **Evolución:** En cada iteración, el programa aplica las reglas clásicas del Juego de la Vida:
  - Una celda viva con 2 o 3 vecinas vivas sobrevive.
  - Una celda muerta con exactamente 3 vecinas vivas "nace" (se vuelve viva).
  - Todas las demás celdas vivas mueren y las muertas permanecen muertas.
- **Visualización:** Tras cada iteración, elv tablero se imprime usando '0' para celdas vivas y espacio para celdas muertas.

Esto permite experimentar con patrones, observar cómo evolucionan y entender los principios de los autómatas celulares de forma interactiva y visual.

---

## ✨ Características principales
- Simula generaciones del Juego de la Vida.
- Permite definir el estado inicial mediante archivos o código.
- Imprime la cuadrícula en cada generación.

---
v
## 🛠️ Archivos del proyecto
- `life.c` — Lógica principal y funciones del juego.
 `life.h` — Definiciones y estructuras.

---

### 🧬 Proyecto "Juego de la Vida" de Conway

Vamos a desglosar este proyecto del "Juego de la Vida" para que lo entiendas de principio a fin. No es tan complicado como parece. Es un autómata celular, un modelo matemático donde las celdas de una cuadrícula siguen reglas muy simples para crear patrones complejos.

---

### 📚 Descripción General y Objetivo

Imagina una cuadrícula infinita, como un tablero de ajedrez, donde cada casilla (o celda) puede estar **viva** o **muerta**. El objetivo de este programa es simular cómo evolucionan estas celdas a lo largo del tiempo, o por generaciones, siguiendo unas reglas específicas.

El programa que vas a crear se llama `life` y necesita tres argumentos para funcionar:
* `ancho`: el número de columnas de tu tablero.
* `alto`: el número de filas de tu tablero.
* `iteraciones`: cuántas generaciones quieres simular.

---

### ✍️ Creación del Estado Inicial del Tablero

Antes de que empiece la simulación, necesitas "dibujar" el patrón inicial de celdas vivas. Esto se hace usando la **entrada estándar** (lo que escribes en la terminal). Imagina que tienes un lápiz virtual que comienza en la esquina superior izquierda de tu tablero, en la posición `[0,0]`.

Los comandos para mover este lápiz son simples, un solo carácter:
* `w`: Mueve el lápiz **arriba**.
* `a`: Mueve el lápiz a la **izquierda**.
* `s`: Mueve el lápiz **abajo**.
* `d`: Mueve el lápiz a la **derecha**.
* `x`: Este es el comando clave. Levanta o baja el lápiz para empezar o dejar de dibujar. Cuando el lápiz está "abajo", cualquier celda por la que pase se volverá una celda viva (`1`).

El programa lee estos comandos uno por uno hasta que no hay más entrada. Esto permite que el patrón inicial (la "semilla") se defina de forma interactiva.

---

### 🔄 Las Reglas de la Simulación

Una vez que el patrón inicial está listo, el programa aplica las reglas del "Juego de la Vida" para cada generación. El estado de cada celda depende de sus **ocho vecinas** (las celdas que están a su alrededor, incluyendo las diagonales).

Para cada celda en el tablero, ocurren las siguientes transiciones en cada "tick" de tiempo:

* **Para las celdas vivas:**
   * Si tiene menos de 2 vecinas vivas, muere (por soledad).
   * Si tiene 2 o 3 vecinas vivas, sobrevive a la siguiente generación.
   * Si tiene más de 3 vecinas vivas, muere (por sobrepoblación).

* **Para las celdas muertas:**
   * Si tiene exactamente 3 vecinas vivas, "nace" y se convierte en una celda viva (por reproducción).
   * En cualquier otro caso, permanece muerta.

Es importante que los nacimientos y las muertes ocurren **simultáneamente** para todas las celdas. Es decir, se calcula el estado de todas las celdas para la siguiente generación basándose en el estado actual, y solo después se aplica el nuevo estado a todo el tablero. Esto se repite por el número de iteraciones que definiste al inicio.

---

### 🖥️ Impresión del Resultado

Al final de todas las simulaciones, el programa debe mostrar el estado final del tablero en la **salida estándar (`stdout`)**. Cada celda viva se representa con el carácter `'0'` y cada celda muerta con un espacio en blanco.

---

### ⚙️ Funciones Permitidas y Archivos del Proyecto

El proyecto solo te permite usar un conjunto limitado de funciones de la biblioteca estándar de C:
* `atoi`, `read`, `putchar`, `malloc`, `calloc`, `realloc`, `free`.

Tienes dos archivos principales: `life.c` (la lógica del programa) y `life.h` (un archivo de cabecera que en este caso está vacío, pero se usaría para modularizar el código).

El código que se adjunta muestra cómo se implementa todo esto:
* **En `main`:** Se validan los argumentos, se inicializan los dos tableros (uno para el estado actual `board` y otro para el siguiente `next`), se lee la entrada para dibujar el patrón inicial y, finalmente, se ejecuta un bucle para las iteraciones.
* **Para el dibujo inicial:** Un bucle `while (read(0, &c, 1) == 1)` lee cada carácter de la entrada estándar y actualiza la posición del lápiz (`x`, `y`) o su estado (`pen`). Si el lápiz está activo, la celda en la posición actual se marca como viva (`board[y][x] = 1`).
* **Para la simulación:** Un bucle anidado recorre cada celda del tablero. Dentro, otro bucle `for` de 3x3 cuenta las celdas vivas vecinas. Se usan las reglas para calcular el estado de la siguiente generación y se guarda en el tablero `next`. Finalmente, el tablero `next` se copia al `board` actual para la siguiente iteración.
* **Para la impresión:** Se recorre el tablero final y se usa `putchar` para imprimir un `'0'` o un espacio por cada celda.

---

Este proyecto es una excelente forma de practicar la manipulación de matrices, la lógica de simulación y el manejo de entrada/salida de la terminal. ¡Con esta visión general, seguro que el código te resulta mucho más claro!

## 🧪 Ejemplo de uso
Supón que el estado inicial está definido en el código o en un archivo.

Aquí tienes varios ejemplos prácticos de uso, con explicaciones para cada caso:

### Ejemplo 1: Dibujar un cuadrado y mostrarlo (0 iteraciones)

Comando:
```sh
echo 'sdxddssaaww' | ./life 5 5 0
```
Explicación:
- El tablero es de 5x5.
- El lápiz se mueve y dibuja un cuadrado usando los comandos indicados.
- Se muestran las celdas vivas ('0') y muertas (espacio) tras el dibujo inicial.

Salida:
```
     
 000 
 0 0 
 000 
     
```

---

### Ejemplo 2: Patrón más complejo (0 iteraciones)

Comando:
```sh
echo 'sdxssdswdxdddxsaddawxwdxwaa' | ./life 10 6 0
```
Explicación:
- El tablero es de 10x6.
- Se dibuja un patrón más complejo.
- Se muestra el estado inicial.

Salida:
```
          
 0   000  
 0     0  
 000  0   
  0  000  
          
```

---

### Ejemplo 3: Oscilador (barra vertical a horizontal)

Comando:
```sh
echo 'dxss' | ./life 3 3 0
```
Explicación:
- El tablero es de 3x3.
- Se dibuja una barra vertical de 3 celdas vivas.
- Se muestra el estado inicial (0 iteraciones).

Salida:
```
 0 
 0 
 0 
```

Ahora, con 1 iteración:

```sh
echo 'dxss' | ./life 3 3 1
```
Salida:
```
   
000
   
```

Y con 2 iteraciones:

```sh
echo 'dxss' | ./life 3 3 2
```
Salida:
```
 0 
 0 
 0 
```

Estos ejemplos muestran cómo el estado inicial y el número de iteraciones afectan la evolución del tablero según las reglas del Juego de la Vida.

---

## ⚙️ Compilación y ejecución
1. Compila el programa:
   ```sh
   gcc life.c -o life
   ```
2. Ejecuta el programa:
   ```sh
   ./life
   ```

---

## 🚦 Consejos
- Modifica el estado inicial para experimentar con diferentes patrones.
- Lee el código y los comentarios para entender la lógica de actualización.
- Observa cómo evolucionan los patrones a lo largo de las generaciones.

---

## 👨‍💻 Autoría
Ejercicio de programación en C para practicar simulaciones, matrices y lógica algorítmica. sternero (2025).

---

