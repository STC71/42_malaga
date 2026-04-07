/* 
 * Refactorizacion C89:
 * - Se elimina el uso de getline y ssize_t (extensiones POSIX) agregando en su lugar read_c89_line iterando un array.
 * - Las variables se declaran obligatoriamente despues de la apertura de cualquier llave { y no despues de llamadas de codigo.
 * - Se elimina la instanciacion de variables dentro de los bloques for().
 */

#include "bsq_comentado.h"   /* Incluye la cabecera del modulo con las definiciones necesarias */

/* Este programa resuelve el problema del Biggest Square (BSQ) usando programacion dinamica.
   Lee un mapa desde archivo o stdin, valida los datos y encuentra el mayor cuadrado sin obstaculos. */

int min3(int a, int b, int c) {
        /* Devuelve el menor de tres valores, usado para calcular el tamaño maximo de cuadrado en cada celda */
        if (a <= b && a <= c) return (a);
        if (b <= a && b <= c) return (b);
        return (c);
}
/* Se usa en el algoritmo de programacion dinamica (solve_bsq) para determinar el tamaño del
   cuadrado mas grande posible en una posicion dada. */

/*
 * read_c89_line() - Lee una linea entera de archivo
 * Reemplazo de getline de C99 posix respetando ANSI C 89 puro de la libreria standar.
 * Asignara una memoria incial de 128 bytes, y reservara dinamicamente mas de ser necesario al leer la linea y un out_len
 */
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


int read_map(FILE *file, t_map *map) {
        char *line; int read_bytes, i, j; /* Puntero a cadena y Guardara la longitud de la linea leida. Contadores declarados al inicio segun C89 */

        /* fscanf() lee exactamente 4 valores obligatorios: un digito de iteraciones y 3 caracteres de config */
        if (fscanf(file, "%d %c %c %c\n", &map->rows, &map->empty, &map->obstacle, &map->full) != 4 || map->rows < 1) return (0);
        
        /* Verifica que los caracteres para celdas vacias, obstaculos y llenas sean distintos entre si. */
        if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) return (0);

        for (i = 0; i < map->rows; i++) {
                /* Se lee una linea del archivo y se almacena en 'line' con longitud en read_bytes (usando nuestra read_line) */
                line = read_c89_line(file, &read_bytes); if (!line) return (0);
                /* En la primera linea, guarda el numero de columnas basado en la longitud de la linea. */
                if (i == 0) map->cols = read_bytes;
                /* Si alguna fila tiene diferente cantidad de columnas o es vacia, devolvemos error. */
                if (read_bytes != map->cols || read_bytes == 0) { free(line); return (0); }
                /* Recorremos cada caracter de la linea validando que sean caracteres del mapa correctos */
                for (j = 0; j < read_bytes; j++) {
                        if (line[j] != map->empty && line[j] != map->obstacle) { free(line); return (0); }
                        /* Guardamos el caracter en la matriz del mapa (maxima limitacion es const MAX) */
                        map->map[i][j] = line[j];
                }
                free(line); /* Liberamos la memoria de la linea custom extraida */
        }
        return (1);
}

void solve_bsq(t_map *map)
{
        int dp[MAX_Y][MAX_X]; int max = 0, max_i = 0, max_j = 0, i, j;
        
        /* Inicializamos a 0 toda la matriz (en C89 no podriamos haber hecho = {0} tan facil dentro la validacion cruzada por bug en arrays multi gcc muy antiguo, preferible iterar) */
        for (i = 0; i < MAX_Y; i++) { for (j = 0; j < MAX_X; j++) { dp[i][j] = 0; } }

        /* Recorremos cada celda del mapa. Cada celda dp[i][j] almacenara el tamaño del mayor cuadrado */
        for (i = 0; i < map->rows; i++) {
                for (j = 0; j < map->cols; j++) {
                        if (map->map[i][j] == map->obstacle) dp[i][j] = 0;
                        else if (i == 0 || j == 0) dp[i][j] = 1;
                        else dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
                                
                        /* Actualizamos el maximo */
                        if (dp[i][j] > max) { max = dp[i][j]; max_i = i; max_j = j; }
                }
        }
        /* Marcamos el cuadrado usando character full */
        for (i = max_i - max + 1; i <= max_i; i++)
                for (j = max_j - max + 1; j <= max_j; j++) map->map[i][j] = map->full;
}

void print_map(t_map *map)
{
        int i, j; /* En C89 hay que declararlo al principio del bloque */
        for (i = 0; i < map->rows; i++) {
                for (j = 0; j < map->cols; j++) printf("%c", map->map[i][j]);           
                printf("\n");
        }
}

int process_file(const char *filename)
{
        FILE *f; t_map m; /* Segun standar C89, inicializamos aqui arriba y procesamos despues. */
        
        memset(&m, 0, sizeof(t_map)); f = filename ? fopen(filename, "r") : stdin;
        
        if (!f) { printf("Error: cannot open file\n"); return (1); }
        if (!read_map(f, &m)) { printf("Error: invalid map\n"); if (filename) fclose(f); return (1); }
        solve_bsq(&m); print_map(&m);
        if (filename) fclose(f);
        return (0);
}

int main(int argc, char *argv[]) {
    /* Process de C89 estandar */
    if (argc == 1) { process_file(NULL); }
    else if(argc == 2) { process_file(argv[1]); }
    else { printf("Error: to many arguments.\n"); return 1; }
    return 0;
}
