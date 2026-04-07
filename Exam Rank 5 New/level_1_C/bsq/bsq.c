#include "bsq.h"

int     min3(int a, int b, int c) { return (a <= b && a <= c) ? a : (b <= a && b <= c) ? b : c; }

char *read_c89_line(FILE *file, int *out_len) {
    int capacity = 128, len = 0, c;
    char *buffer = malloc(capacity); if (!buffer) return NULL;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') break;
        buffer[len++] = (char)c;
        if (len >= capacity - 1) {
            char *new_buf; capacity *= 2; new_buf = malloc(capacity);
            if (!new_buf) { free(buffer); return NULL; }
            memcpy(new_buf, buffer, len); free(buffer); buffer = new_buf;
        }
    }
    if (len == 0 && c == EOF) { free(buffer); return NULL; }
    buffer[len] = '\0'; if (out_len) *out_len = len; return buffer;
}

int     read_map(FILE *file, t_map *map) {
    char *line; int read_bytes, i, j;
    if (fscanf(file, "%d %c %c %c\n", &map->rows, &map->empty, &map->obstacle, &map->full) != 4 || map->rows < 1) {return (0); }
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) { return (0); }
    for (i = 0; i < map->rows; i++) {
                line = read_c89_line(file, &read_bytes);
                if (!line) { return (0); }
                if (i == 0) { map->cols = read_bytes; }
                if (read_bytes != map->cols || read_bytes == 0) { free(line); return (0); }
                for (j = 0; j < read_bytes; j++) {
                    if (line[j] != map->empty && line[j] != map->obstacle) { free(line); return (0); }
                    map->map[i][j] = line[j];
                }
                free(line);
            }
            return (1);
        }
        
void    solve_bsq(t_map *map) {
    int dp[MAX_Y][MAX_X]; int max = 0, max_i = 0, max_j = 0, i, j;
        for (i = 0; i < MAX_Y; i++) { for (j = 0; j < MAX_X; j++) { dp[i][j] = 0; } }
        for (i = 0; i < map->rows; i++) {
                for (j = 0; j < map->cols; j++) {
                        if (map->map[i][j] == map->obstacle) { dp[i][j] = 0; }
                        else if (i == 0 || j == 0) { dp[i][j] = 1; }
                        else { dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]); }
                        if (dp[i][j] > max) { max = dp[i][j]; max_i = i; max_j = j; }
                    }
        }
        for (i = max_i - max + 1; i <= max_i; i++)
        for (j = max_j - max + 1; j <= max_j; j++) { map->map[i][j] = map->full; }
    }
    
    void    print_map(t_map *map) {
        int i, j;
        for (i = 0; i < map->rows; i++) {
                for (j = 0; j < map->cols; j++) { printf("%c", map->map[i][j]); }
                printf("\n");
        }
}

int     process_file(const char *filename) {
    FILE *f; t_map m; memset(&m, 0, sizeof(t_map)); f = filename ? fopen(filename, "r") : stdin;
    if (!f) { printf("Error: cannot open file\n"); return (1); }
    if (!read_map(f, &m)) {
        printf("Error: invalid map\n");
        if (filename) { fclose(f); }
        return (1);
    }
        solve_bsq(&m); print_map(&m);
        if (filename) { fclose(f); }
        return (0);
    }
    
    int     main(int argc, char *argv[]) {
        if (argc == 1) { process_file(NULL); }
        else if(argc == 2) { process_file(argv[1]); }
        else { printf("Error: to many arguments.\n"); return 1; }
        return 0;
    }
    
    /* 
     * Refactorizacion C89:
     * - Se elimina el uso de getline y ssize_t (extensiones POSIX).
     * - Las variables se declaran al inicio de los bloques funcionales en lugar de dentro de for() o a la mitad del codigo.
     */