#include "life.h"

int main(int argc, char *argv[]) {
    if (argc != 4) { return 1; }

    int ancho = atoi(argv[1]), alto = atoi(argv[2]), iter = atoi(argv[3]);
    int tab[alto][ancho], siguiente[alto][ancho], hor = 0, ver = 0, pen = 0;
    char c;

    for (int i = 0; i < alto; i++)
        for (int j = 0; j < ancho; j++) { tab[i][j] = 0; }

    while (read(0, &c, 1) == 1) {
        if (c == 'w' && ver > 0) { ver--; }
        else if (c == 's' && ver < alto - 1) { ver++; }
        else if (c == 'a' && hor > 0) { hor--; }
        else if (c == 'd' && hor < ancho - 1) { hor++; }
        else if (c == 'x') { pen = !pen; }
        if (pen) { tab[ver][hor] = 1; }
    }

    for (int generacion = 0; generacion < iter; generacion++) {
        for (int fila = 0; fila < alto; fila++) {
            for (int columna = 0; columna < ancho; columna++) {
                int vivas = 0;
                for (int vfila = -1; vfila <= 1; vfila++)
                    for (int vcolumna = -1; vcolumna <= 1; vcolumna++)
                        if ((vfila || vcolumna)
                            && fila + vfila >= 0
                            && fila + vfila < alto
                            && columna + vcolumna >= 0
                            && columna + vcolumna < ancho)
                            vivas += tab[fila + vfila][columna + vcolumna];
                siguiente[fila][columna] = (tab[fila][columna] && (vivas == 2 || vivas == 3))
                                  || (!tab[fila][columna] && vivas == 3);
            }
        }
        for (int i = 0; i < alto; i++)
            for (int j = 0; j < ancho; j++)
                tab[i][j] = siguiente[i][j];
    }
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) { putchar(tab[i][j] ? 'O' : ' '); }
        putchar('\n');
    }
    return 0;
}