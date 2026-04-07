#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_Y 100
#define MAX_X 200

typedef struct {
    int rows, cols;
    char empty, obstacle, full;
    char map[MAX_Y][MAX_X];
} t_map;

int		min3(int a, int b, int c);
int		read_map(FILE *file, t_map *map);
void	solve_bsq(t_map *map);
void	print_map(t_map *map);
int		process_file(const char *filename);
