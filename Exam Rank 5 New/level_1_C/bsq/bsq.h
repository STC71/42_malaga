# pragma once

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_map
{
	int	rows;
	int	cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**map;
}	t_map;

