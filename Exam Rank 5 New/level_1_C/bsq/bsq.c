#include "bsq.h"

int	ft_is_printable(char c) { return (c >= 32 && c <= 126); }

int	ft_atoi_custom(const char *str, int len) {
	int res = 0, i;
	if (len <= 0) return (-1);
	for (i = 0; i < len; i++) {
		if (str[i] < '0' || str[i] > '9') return (-1);
		res = res * 10 + (str[i] - '0');
	}
	return (res);
}

void	free_map(t_map *map) {
	int i;
	if (map->map) {
		for (i = 0; i < map->rows; i++) { if (map->map[i]) free(map->map[i]); }
		free(map->map); map->map = NULL;
	}
}

int	parse_first_line(FILE *file, t_map *map) {
	char *line = NULL; size_t len = 0; long read_bytes;
	read_bytes = getline(&line, &len, file);
	if (read_bytes <= 0 || !line) { free(line); return (0); }
	if (line[read_bytes - 1] == '\n') line[--read_bytes] = '\0';
	if (read_bytes < 4) { free(line); return (0); }
	map->full = line[read_bytes - 1]; map->obstacle = line[read_bytes - 2]; map->empty = line[read_bytes - 3];
	if (!ft_is_printable(map->full) || !ft_is_printable(map->obstacle) || !ft_is_printable(map->empty)) return (free(line), 0);
	if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) return (free(line), 0);
	map->rows = ft_atoi_custom(line, read_bytes - 3); free(line);
	return (map->rows > 0);
}

int	read_map_content(FILE *file, t_map *map) {
	char *line = NULL; size_t len = 0; long r_bytes; int i, j;
	map->map = calloc(map->rows, sizeof(char *));
	if (!map->map) return (0);
	for (i = 0; i < map->rows; i++) {
		line = NULL; len = 0; r_bytes = getline(&line, &len, file);
		if (r_bytes <= 0 || !line) return (free(line), 0);
		if (line[r_bytes - 1] == '\n') line[--r_bytes] = '\0';
		if (i == 0) { map->cols = r_bytes; if (map->cols == 0) return (free(line), 0); }
		else if (r_bytes != map->cols) return (free(line), 0);
		map->map[i] = malloc(map->cols + 1);
		if (!map->map[i]) return (free(line), 0);
		for (j = 0; j < map->cols; j++) {
			if (line[j] != map->empty && line[j] != map->obstacle) return (free(line), 0);
			map->map[i][j] = line[j];
		}
		map->map[i][map->cols] = '\0'; free(line);
	}
	return (1);
}

int	min3_func(int a, int b, int c) { int min = a; if (b < min) min = b; if (c < min) min = c; return min; }

void	solve_and_print(t_map *map) {
	int **dp, max_sz = 0, max_i = 0, max_j = 0, i, j;
	dp = calloc(map->rows, sizeof(int *)); if (!dp) return ;
	for (i = 0; i < map->rows; i++) { dp[i] = calloc(map->cols, sizeof(int)); if (!dp[i]) return ; }
	for (i = 0; i < map->rows; i++) {
		for (j = 0; j < map->cols; j++) {
			if (map->map[i][j] == map->obstacle) dp[i][j] = 0;
			else if (i == 0 || j == 0) dp[i][j] = 1;
			else dp[i][j] = 1 + min3_func(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
			if (dp[i][j] > max_sz) { max_sz = dp[i][j]; max_i = i; max_j = j; }
		}
	}
	for (i = max_i - max_sz + 1; i <= max_i; i++) {
		for (j = max_j - max_sz + 1; j <= max_j; j++) map->map[i][j] = map->full;
	}
	for (i = 0; i < map->rows; i++) { fputs(map->map[i], stdout); fputs("\n", stdout); }
	for (i = 0; i < map->rows; i++) { free(dp[i]); }
	free(dp);
}

void	process_file(FILE *f) {
	t_map map_data = {0, 0, 0, 0, 0, NULL};
	if (!parse_first_line(f, &map_data) || !read_map_content(f, &map_data)) fprintf(stderr, "map error\n");
	else solve_and_print(&map_data);
	free_map(&map_data);
}

int	main(int argc, char **argv) {
	FILE *f; int i;
	if (argc == 1) process_file(stdin);
	else {
		for (i = 1; i < argc; i++) {
			f = fopen(argv[i], "r");
			if (!f) fprintf(stderr, "map error\n");
			else { process_file(f); fclose(f); }
		}
	}
	return (0);
}
