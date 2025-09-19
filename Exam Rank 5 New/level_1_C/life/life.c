#include "life.h"

int main(int argc, char *argv[])
{
	if (argc != 4) { return 1; }
	int		w = atoi(argv[1]), h = atoi(argv[2]), iter = atoi(argv[3]);
	int		board[h][w], next[h][w], x = 0, y = 0, pen = 0;
	char	c;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) { board[i][j] = 0; }
	while (read(0, &c, 1) == 1) {
		if (c == 'w' && y > 0) { y--; }
		else if (c == 's' && y < h - 1) { y++; }
		else if (c == 'a' && x > 0) { x--; }
		else if (c == 'd' && x < w - 1) { x++; }
		else if (c == 'x') { pen = !pen; }
		if (pen) { board[y][x] = 1; }
	}
	for (int t = 0; t < iter; t++) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int alive = 0;
				for (int di = -1; di <= 1; di++)
					for (int dj = -1; dj <= 1; dj++)
						if ((di || dj) && i + di >= 0 && i + di < h && j + dj >= 0 && j + dj < w)
							alive += board[i + di][j + dj];
				next[i][j] = (board[i][j] && (alive == 2 || alive == 3)) || (!board[i][j] && alive == 3);
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) { board[i][j] = next[i][j]; }
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) { putchar(board[i][j] ? 'O' : ' '); }
		putchar('\n');
	}
	return 0;
}
