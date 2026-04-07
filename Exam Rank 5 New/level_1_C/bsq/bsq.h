#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_Y 100
#define MAX_X 200

typedef struct {
    int rows, cols;
    char empty, obstacle, full;
    char map[MAX_Y][MAX_X];
} t_map;

int     min3(int a, int b, int c);
char    *read_c89_line(FILE *file, int *out_len);
int     read_map(FILE *file, t_map *map);
void    solve_bsq(t_map *map);
void    print_map(t_map *map);
int     process_file(const char *filename);

#endif

/* 
 * Refactorizacion C89: 
 * - Eliminada la macro _POSIX para el estandar ANSI C puro.
 * - Solo se utilizan bibliotecas puras (C89/C90).
 */
