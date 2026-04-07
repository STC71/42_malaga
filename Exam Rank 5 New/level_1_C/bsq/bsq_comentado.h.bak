#pragma once

#include <stdio.h>      // Para la sálida estándar: printf, fprintf...
#include <stdlib.h>     // Para la gestión de memoria dinámica: malloc, free...
#include <string.h>     // Para la manipulación de cadenas: strlen, strcpy...
#include <unistd.h>     // Para las llamadas al sistema: read, write...

#define MAX_Y 100       // Máximo número de filas
#define MAX_X 200       // Máximo número de columnas

typedef struct {
    int rows, cols;                 // Dimensiones del mapa, filas y columnas.
    char empty, obstacle, full;     // Caracteres que representan el estado de las celdas
    char map[MAX_Y][MAX_X];         // Mapa del juego. MAX para definir el tamaño máximo, aunque el mapa real puede ser menor.
} t_map;
/*  Estructura que representa el mapa.  */

int		min3(int a, int b, int c);              // Devuelve el mínimo de tres enteros
int		read_map(FILE *file, t_map *map);       // Lee el mapa desde un archivo, valida y lo almacena. Recibe un puntero a archivo y un puntero a mapa.
void	solve_bsq(t_map *map);                  // Resuelve el problema del cuadrado más grande, recibiendo un puntero a mapa
void	print_map(t_map *map);                  // Imprime el mapa, recibiendo un puntero a mapa
int		process_file(const char *filename);     // Procesa un archivo, recibiendo el nombre del archivo como cadena de caracteres
