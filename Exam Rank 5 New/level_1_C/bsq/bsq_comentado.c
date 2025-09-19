#include "bsq.h"   // Incluye la cabecera del módulo con las definiciones necesarias

// Este programa resuelve el problema del Biggest Square (BSQ) usando programación dinámica.
// Lee un mapa desde archivo o stdin, valida los datos y encuentra el mayor cuadrado sin obstáculos.

int min3(int a, int b, int c) {
	// Devuelve el menor de tres valores, usado para calcular el tamaño máximo de cuadrado en cada celda
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}
/* Se usa en el algoritmo de programación dinámica (solve_bsq) para determinar el tamaño del
   cuadrado más grande posible en una posición dada.
   Ejemplo: min3(2, 1, 3) → 1 */

int read_map(FILE *file, t_map *map) {
	// El siguiente fragmento hace dos cosas importante:
	// fscanf(file, "%d %c %c %c\n", ...) intenta leer cuatro valores de la primera línea del archivo:
	// - Un entero (%d), el número de filas del mapa.
	// - Tres caracteres (%c), que representan: el caracter para celdas vacías, el caracter para obstáculos 
	//		y el caracter para celdas llenas.
	// Si no se logra leer exactamente cuatro valores (!= 4) o si el número de filas es menor que 1 (map->rows < 1),
	// la función devuelve 0 indicando un error de formato o datos inválidos. La función se comporta como un booleano.
	// En resumen: valida que la cabecera del mapa sea correcta y que el número de filas sea válido.
	if (fscanf(file, "%d %c %c %c\n", &map->rows, &map->empty, &map->obstacle,
			&map->full) != 4 || map->rows < 1)
		return (0);
	// El siguiente fragmento verifica que los caracteres para celdas vacías, obstáculos y llenas sean distintos entre sí.
	// Esta comprobación es crucial para evitar ambigüedades al interpretar el mapa.
	if (map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		return (0);
	// A continuación se inicializan dos variable para leer líneas del archivo de mapa.
	char *line = NULL;		// Puntero a una cadena que se usará para almacenar cada línea leída del archivo.
	// La función getline se asegura de asignar memoria suficiente para la línea leída y llenarla con el contenido de cada línea.
	size_t len = 0;			// Variable que guarda el tamaño del buffer asignado para line.
	// getline puede aumentar el tamaño del buffer si la línea es más larga de lo esperado.
	// A continuación se inicializa la matriz del mapa. Es el núcleo de la función que lee y valida cada línea del mapa.
	// Primero se inicia un bucle que itera sobre el número de filas especificado en la cabecera del mapa. map->rows
	for (int i = 0; i < map->rows; i++) {
		// Se lee una linea del archivo y se almacena en 'line', actualizando 'len' si es necesario. 
		// ssize_t es un tipo de dato que puede representar el tamaño de un objeto o una cantidad de bytes leídos/escritos.
		// read_bytes es la longitud de la línea leída, incluyendo el salto de línea si existe.
		// getline toma el puntero al archivo, la dirección del puntero a la línea y la dirección de la variable len, para gestionar la memoria.
		// El resultado de getline se almacena en read_bytes. Si es <= 0, indica un error o fin de archivo.
		ssize_t read_bytes = getline(&line, &len, file);
		// Seguidamente se comprueba que Si no se puede leer la línea, se libera memoria y devolvemos error
		// Esto puede ocurrir si el archivo termina antes de leer todas las filas esperadas o si hay un error de lectura.
		if (read_bytes <= 0) {
			free(line);
			return (0);
		}
		// Si la línea termina con un salto de línea, se elimina y se ajusta el contador de caracteres.
		if (line[read_bytes - 1] == '\n')
			line[--read_bytes] = 0;
		// En la primera línea, guarda el número de columnas basado en la longitud de la línea leída.
		// Esto asume que todas las filas deben tener la misma longitud (número de columnas).
		if (i == 0)
			map->cols = read_bytes;
		// Si alguna fila tiene diferente cantidad de columnas o es vacía, se libera memoria y devolvemos error.
		if (read_bytes != map->cols || read_bytes == 0) {
			free(line);
			return (0);
		}
		// Recorremos cada carácter de la línea leída
		for (int j = 0; j < read_bytes; j++) {
			// Validamos que cada carácter sea válido: debe ser el caracter de celda vacía o el de obstáculo.
			// Si encontramos un carácter inválido, liberamos la memoria y devolvemos error.
			if (line[j] != map->empty && line[j] != map->obstacle) {
				free(line);
				return (0);
			}
			// Guardamos el carácter en la matriz del mapa
			map->map[i][j] = line[j];
		}
		// En resumen: este bucle lee cada línea del mapa, valida su formato y contenido, y llena la matriz del mapa.
		// Si todo es correcto, se continúa con la siguiente línea hasta completar todas las filas.
		// Si algo falla, se libera la memoria y se devuelve error.
		// Así se asegura que el mapa sea rectangular y contenga solo caracteres válidos antes de procesarlo.
	}
	free(line);		// Liberamos la memoria asignada para la línea con getline
	// Si todo es correcto, devolvemos 1, ya que su comportamiento es como un booleano y es lo que espera process_file:
	// 0 indica error, 1 indica éxito.
	return (1);
}

void solve_bsq(t_map *map)
{
	// Matriz auxiliar para programación dinámica
	int dp[MAX_Y][MAX_X] = {0};
	// Variables para rastrear el tamaño y posición del cuadrado más grande
	int max = 0, max_i = 0, max_j = 0;
	// Recorremos cada celda del mapa. Cada celda dp[i][j] almacenará el tamaño del mayor cuadrado que termina en (i,j)
	// La idea es que si la celda actual es vacía, el tamaño del cuadrado es 1 más el mínimo de los cuadrados que terminan arriba, 
	// a la izquierda y en diagonal
	// Si la celda es un obstáculo, el tamaño es 0 (no puede haber cuadrado)
	// Si estamos en la primera fila o columna, el tamaño máximo es 1 (si es vacía)
	// Actualizamos el máximo encontrado y su posición 
	for (int i = 0; i < map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			// Si hay obstáculo, no puede haber cuadrado
			if (map->map[i][j] == map->obstacle)
				dp[i][j] = 0;
			// En la primera fila o columna, solo puede haber cuadrados de tamaño 1
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			// Calculamos el tamaño máximo de cuadrado en la celda actual
			else
				dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
			// Actualizamos el máximo encontrado
			if (dp[i][j] > max) {
				max = dp[i][j];
				max_i = i;
				max_j = j;
			}
		}
	}
	// Marcamos el cuadrado más grande en el mapa usando el carácter 'full'
	// max es el tamaño del cuadrado, (max_i, max_j) es la esquina inferior derecha del cuadrado.
	// El bucle recorre las filas y columnas que forman el cuadrado y reemplaza esos caracteres en el mapa original con 'full'
	// Ejemplo: si el cuadrado es de tamaño 3 y termina en (4, 5), max_i = 4, max_j = 5. El bucle recorrerá desde la fila 
	// 4 - 3 + 1 = 2 hasta la fila 4, y desde la columna 5 - 3 + 1 = 3 hasta la columna 5, es decir, las posiciones (2,3) a (4,5)
	// todas esas posiciones se marcan como llenas (full)
	for (int i = max_i - max + 1; i <= max_i; i++)
		for (int j = max_j - max + 1; j <= max_j; j++)
			map->map[i][j] = map->full;
}

void print_map(t_map *map)
{
	// Imprime el mapa final, mostrando el cuadrado encontrado
	for (int i = 0; i < map->rows; i++) {
		for (int j = 0; j < map->cols; j++)
			printf("%c", map->map[i][j]);		// Imprime cada carácter del mapa.
		printf("\n");
	}
}

int process_file(const char *filename)
{
	// Abre el archivo de entrada o usa stdin si no hay argumento
	// FILE *f hace que se abra el archivo especificado por filename en modo lectura ("r"),  en el caso de que filename no sea NULL.()
	// Si filename es NULL, se usa stdin (entrada estándar), para permitir la lectura desde la consola o redirección.
	FILE *f = filename ? fopen(filename, "r") : stdin;	
	// Si el archivo no se puede abrir, muestra un error y sale
	if (!f) {
		printf("Error: cannot open file\n");
		return (1);
	}
	// Inicializa la estructura del mapa con ceros
	t_map m = {0};
	// Lee y valida el mapa
	// Si no se puede leer el mapa, muestra un error y sale
	if (!read_map(f, &m)) {
		printf("Error: invalid map\n");
		// Si filename no es NULL, cerramos el archivo abierto para evitar fugas de memoria
		if (filename)
			fclose(f);
		return (1);
	}
	// Resuelve el problema y muestra el resultado
	solve_bsq(&m);
	print_map(&m);
	// Cierra el archivo si fue abierto desde un nombre de archivo
	if (filename)
		fclose(f);
	return (0);
}

int main(int argc, char *argv[]) {
	// El programa puede recibir 0 o 1 argumento (nombre de archivo)
	// Si no hay argumentos (argc == 1), se procesa la entrada estándar (stdin) indicando NULL a process_file
	if (argc == 1)
		process_file(NULL);
	// Si hay un argumento (argc == 2), se procesa el archivo indicado.
	else if (argc == 2)
		process_file(argv[1]);
	// Si hay más de un argumento, muestra un error y sale del programa.
	else {
		printf("Error: too many arguments\n");
		return (1);
	}
	// Si todo va bien, devuelve 0 finalizando la ejecución del programa.
	return (0);
}