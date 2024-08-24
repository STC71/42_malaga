/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-23 11:43:53 by sternero          #+#    #+#             */
/*   Updated: 2024-08-23 11:43:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flood_fill.h"

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x 
        || tab[cur.y][cur.x] != to_fill)
		return;
	tab[cur.y][cur.x] = 'F';
	fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}

// From here, you can test the code with the main function below,
// or you can use your own implementation. But it is to look at the
// main function to understand how the flood_fill function is used.
// It is not necessary to the exercise.

char** make_area(char** zone, t_point size)
{
	char** new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {7, 4};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}

// The fill function is a recursive function that fills the area around 
// a given point with a specific character. The function takes 
// the following parameters:
// - tab: a two-dimensional array of characters representing the area to fill
// - size: a t_point structure representing the size of the area
// - cur: a t_point structure representing the current position
// - to_fill: a character representing the character to fill the area with
// The function recursively fills the area around the current point with
// the character to_fill. It checks if the current position is within the
// bounds of the area and if the character at that position is equal to
// the character to_fill. If so, it fills the current position with the
// character 'F' and recursively calls the fill function on the adjacent
// positions (left, right, up, down).
// The flood_fill function is a wrapper function that calls the fill function
// with the initial position and character to fill. It is used to start the
// flood fill algorithm on the given area.

// The main function demonstrates the usage of the flood_fill function by
// filling a specific area in a two-dimensional array with the character 'F'.

// To compile and excute the code, you can use the following command:
// gcc flood_fill.c flood_fill.h -o flood_fill; ./flood_fill

/*
Este código implementa un algoritmo de "flood fill", que es similar al que se 
utiliza en programas de dibujo para llenar áreas conectadas de un color en una 
imagen, como el bote de pintura en MS Paint.

Vamos a desglosar cada parte del código y explicar su funcionamiento.

### Descripción de las funciones

1. **`fill`**: Esta es la función recursiva que realiza el llenado. Se encarga 
de recorrer las celdas adyacentes (arriba, abajo, izquierda y derecha) y cambiar 
su valor si cumplen ciertas condiciones.

2. **`flood_fill`**: Esta función es la que inicializa el proceso de llenado 
llamando a `fill`. Recibe como parámetro la posición inicial (`begin`) desde 
donde comienza el llenado.

### Parámetros de las funciones

- **`tab`**: Es una matriz de caracteres (`char **`), que representa una especie 
	de "tablero" o "imagen" en la que se va a realizar el llenado.
- **`size`**: Es una estructura `t_point` que indica el tamaño de la matriz 
	(`size.x` es el número de columnas y `size.y` es el número de filas).
- **`cur`**: Es una estructura `t_point` que representa la posición actual en 
	la matriz durante el llenado.
- **`to_fill`**: Es el carácter que se está buscando llenar.

### Estructura `t_point`

La estructura `t_point` se define en flood_fill.h de la siguiente manera:

typedef struct  s_point
{
    int x;
    int y;
}               t_point;
```

### Funcionamiento de `fill`

La función `fill` sigue estos pasos:

1. **Comprobaciones de límites**: Verifica si la posición actual (`cur`) está 
	fuera de los límites de la matriz. Si `cur.y` es menor que 0 o mayor o igual 
	al número de filas, o si `cur.x` es menor que 0 o mayor o igual al número de 
	columnas, la función retorna sin hacer nada.
2. **Verificación del contenido**: Comprueba si la celda actual 
	(`tab[cur.y][cur.x]`) no es igual al carácter que estamos tratando de llenar 
	(`to_fill`). Si no es igual, no se realiza ninguna acción y se retorna.
3. **Llenado de la celda**: Si las comprobaciones anteriores pasan, la celda actual 
	(`tab[cur.y][cur.x]`) se llena con `'F'` (u otro carácter que podrías cambiar 
	según la necesidad).
4. **Llamadas recursivas**: Se llama recursivamente a `fill` para las posiciones 
	adyacentes (izquierda, derecha, arriba, abajo) con la misma lógica.

### Funcionamiento de `flood_fill`

La función `flood_fill` es simplemente un punto de entrada para el algoritmo de 
llenado. Lo que hace es llamar a `fill` con la posición inicial (`begin`) y el 
carácter que se encuentra en esa posición (`tab[begin.y][begin.x]`).

### Ejemplo de uso

Supongamos que tienes la siguiente matriz:

```c
char *tab[] = {
    "0000",
    "0110",
    "0110",
    "0000"
};
```

Y el tamaño de la matriz es `size = {4, 4}` (4 columnas y 4 filas).

Si llamas a `flood_fill(tab, size, (t_point){1, 1})`, comenzará el llenado desde 
la posición `(1, 1)`, donde hay un '1'. El resultado después del llenado será:

```c
char *tab[] = {
    "0000",
    "0FF0",
    "0FF0",
    "0000"
};
```

Aquí se explica lo que pasa en detalle:

1. La función `fill` se llama con `(1, 1)`.
2. La celda `(1, 1)` contiene `1`, así que se cambia a `'F'`.
3. La función `fill` ahora se llama para las celdas adyacentes:
    - `(0, 1)` no contiene `1`, así que no hace nada.
    - `(2, 1)` contiene `1`, así que se cambia a `'F'`.
    - `(1, 0)` no contiene `1`, así que no hace nada.
    - `(1, 2)` contiene `1`, así que se cambia a `'F'`.
4. Esto continúa hasta que todas las celdas conectadas que originalmente contenían 
	`1` se han cambiado a `'F'`.

Si llamas a `flood_fill(tab, size, (t_point){0, 0})`, no se llenará nada porque 
la posición `(0, 0)` tiene un `0` y no está conectada a ningún `1`.

Este código es útil para tareas como detectar y llenar regiones conectadas en un 
espacio bidimensional, como una imagen en blanco y negro o una matriz de bits.
*/