#include "life.h"				// Incluye el archivo de cabecera del Juego de la Vida	

int main(int ac, char **av)
{
	// Comprobamos que se reciben exactamente 3 argumentos: ancho, alto e iteraciones
	if (ac != 4)
		return 1;

	// Convertimos los argumentos a enteros: ancho (w), alto (h) y número de iteraciones (iter)
	int		w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);

	// Declaramos las matrices del tablero actual y el siguiente, y variables para la posición del lápiz y su estado
	// Necesitamos dos tableros: uno para el estado actual y otro para calcular el siguiente estado. 
	// La diferencia entre ambos es que mientras uno se usa para leer el estado actual de las células,
	// el otro se usa para escribir el nuevo estado basado en las reglas del juego.
	// Iniciamos la posición del lápiz (x, y) en la esquina superior izquierda (0,0) y el estado del lápiz (pen) como apagado (0)
	// x representa la columna actual del lápiz, y representa la fila actual del lápiz
	int		board[h][w], next[h][w], x = 0, y = 0, pen = 0;
	char	c;		// Variable para leer caracteres de entrada.

	// Inicializamos el tablero: todas las celdas empiezan muertas (0)
	for (int i = 0; i < h; i++)				// Recorremos cada fila
		for (int j = 0; j < w; j++)			// Recorremos cada columna de la fila actual
			board[i][j] = 0;				// Marcamos la celda como muerta (0)

	// Leemos comandos de la entrada estándar para mover el lápiz y dibujar el patrón inicial,
	// while (read(0, &c, 1) == 1) hace que leamos un carácter a la vez hasta que no haya más datos,
	// En el contexto de este código, read(0, &c, 1) dentro del bucle while sirve para leer, uno a uno, los comandos que el usuario 
	// introduce por la entrada estándar (stdin). Cada carácter leído representa una acción para mover el lápiz (w, a, s, d) 
	// o alternar el modo de dibujo (x). El bucle se repite hasta que no hay más datos por leer.
	// En resumen: permite procesar la secuencia de comandos que define el patrón inicial del tablero, leyendo cada carácter y ejecutando 
	// la acción correspondiente en tiempo real.
	while (read(0, &c, 1) == 1)
	{
		// Mover el lápiz según las teclas: w (arriba), s (abajo), a (izquierda), d (derecha)
		if (c == 'w' && y > 0)					// Si se presiona 'w' y no estamos en la fila superior
			y--;								// Movemos el lápiz hacia arriba (decrementamos y)	
		else if (c == 's' && y < h - 1)			// Si se presiona 's' y no estamos en la fila inferior
			y++;								// Movemos el lápiz hacia abajo (incrementamos y)
		else if (c == 'a' && x > 0)				// Si se presiona 'a' y no estamos en la columna izquierda		
			x--;								// Movemos el lápiz hacia la izquierda (decrementamos x)
		else if (c == 'd' && x < w - 1)			// Si se presiona 'd' y no estamos en la columna derecha
			x++;								// Movemos el lápiz hacia la derecha (incrementamos x)
		// Alternar el estado del lápiz (dibujar/no dibujar) con 'x'
		else if (c == 'x')						// Si se presiona 'x'
			pen = !pen;							// Cambiamos el estado del lápiz (si estaba apagado, se enciende y viceversa)
		// Si el lápiz está activo, marcamos la celda como viva
		if (pen)								// Si el lápiz está activo (pen es 1)	
			board[y][x] = 1;					// Marcamos la celda actual como viva (1)
	}
	// Simulamos la evolución del tablero durante 'iter' generaciones
	for (int t = 0; t < iter; t++)				// Repetimos el proceso de actualización del tablero 'iter' veces
	{
		for (int i = 0; i < h; i++)				// Recorremos cada fila del tablero
		{
			for (int j = 0; j < w; j++)			// Recorremos cada columna de la fila actual
			{
				// Contamos las celdas vivas vecinas de la celda actual
				int alive = 0;					// alive cuenta las células vivas alrededor de la célula actual
				// La siguiente expresión: for (int di = -1; di <= 1; di++) es un bucle que recorre los valores -1, 0 y 1. 
				// En este contexto, di representa el desplazamiento vertical respecto a la celda actual del tablero.
				// Se usa para visitar todas las posiciones vecinas (arriba, abajo y la misma fila) de una celda. 
				// Combinado con el bucle anidado for (int dj = -1; dj <= 1; dj++), permite recorrer la matriz de 3x3 
				// centrada en la celda actual, es decir, todas sus vecinas (incluyendo diagonales).
				// En resumen: este bucle sirve para contar cuántas células vivas rodean a la celda actual, 
				// necesario para aplicar las reglas del Juego de la Vida.
				for (int di = -1; di <= 1; di++)
					for (int dj = -1; dj <= 1; dj++)
						// A continación, (di || dj): asegura que no se cuenta la celda actual (cuando ambos desplazamientos son cero, 
						// es decir, la propia celda).
						// i + di >= 0 && i + di < h: verifica que la fila vecina está dentro de los límites del tablero.
						// j + dj >= 0 && j + dj < w: verifica que la columna vecina está dentro de los límites del tablero.
						// Si todas estas condiciones se cumplen, se suma el valor de la celda vecina (board[i + di][j + dj]) 
						// a la variable alive. Así, se cuenta cuántas células vivas rodean a la celda actual, sin salirse del tablero 
						// y sin contar la propia celda.
						if ((di || dj) && i + di >= 0 && i + di < h && j + dj >= 0 && j + dj < w)
							alive += board[i + di][j + dj];
				// En la siguiente línea se aplica las reglas del Juego de la Vida para decidir si la celda estará viva en la 
				// siguiente generación:
				// Si la celda está viva (board[i][j] es 1) y tiene 2 o 3 vecinas vivas (alive == 2 || alive == 3), sobrevive.
				// Si la celda está muerta (board[i][j] es 0) y tiene exactamente 3 vecinas vivas (alive == 3), "nace" y se vuelve viva.
				// En cualquier otro caso, la celda muere o permanece muerta.
				// Así, se calcula el estado de cada celda para la siguiente generación según las reglas clásicas del Juego de la Vida de Conway.
				next[i][j] = (board[i][j] && (alive == 2 || alive == 3)) || (!board[i][j] && alive == 3);
			}
		}
		// Actualizamos el tablero con el nuevo estado
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				board[i][j] = next[i][j];
	}
	// Imprimimos el tablero final: '0' para vivas, espacio para muertas
	for (int i = 0; i < h; i++)						// Recorremos cada fila del tablero
	{
		for (int j = 0; j < w; j++)					// Recorremos cada columna de la fila actual
			putchar(board[i][j] ? 'O' : ' ');		// Si la celda está viva (1), imprimimos 'O', si está muerta (0), imprimimos un espacio
			// OJO!!! O es diferente de 0, no es el número cero... o puede que sí... ATENCIÓN CON ESTO!!!
		putchar('\n');								// Al final de cada fila, imprimimos un salto de línea para pasar a la siguiente fila
	}
	// Fin del programa
	return 0;
}
