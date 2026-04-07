/* 
 * Refactorizacion C89: 
 * - Eliminada la macro _POSIX para el estandar ANSI C puro.
 * - Modificadas las directivas de preprocesador al estandar C89 (#ifndef en vez de #pragma once).
 * - Solo se utilizan bibliotecas estandar.
 */
#ifndef BSQ_COMENTADO_H
#define BSQ_COMENTADO_H

#include <stdio.h>      /* Para la salida estandar: printf, fprintf... */
#include <stdlib.h>     /* Para la gestion de memoria dinamica: malloc, free... */
#include <string.h>     /* Para la manipulacion de cadenas: strlen, strcpy... */
#include <unistd.h>     /* Para las llamadas al sistema: read, write... */

#define MAX_Y 100       /* Maximo numero de filas */
#define MAX_X 200       /* Maximo numero de columnas */

typedef struct {
    int rows, cols;                 /* Dimensiones del mapa, filas y columnas. */
    char empty, obstacle, full;     /* Caracteres que representan el estado de las celdas */
    char map[MAX_Y][MAX_X];         /* Mapa del juego. MAX para definir el tamaño maximo, aunque el mapa real puede ser menor. */
} t_map;
/*  Estructura que representa el mapa.  */

int             min3(int a, int b, int c);              /* Devuelve el minimo de tres enteros */
char    *read_c89_line(FILE *file, int *out_len); /* Añadida en refactorizacion C89 para leer linea a linea en lugar de getline() */
int             read_map(FILE *file, t_map *map);       /* Lee el mapa desde un archivo, valida y lo almacena. Recibe un puntero a archivo y un puntero a mapa. */
void    solve_bsq(t_map *map);                  /* Resuelve el problema del cuadrado mas grande, recibiendo un puntero a mapa */
void    print_map(t_map *map);                  /* Imprime el mapa, recibiendo un puntero a mapa */
int             process_file(const char *filename);     /* Procesa un archivo, recibiendo el nombre del archivo como cadena de caracteres */

#endif
