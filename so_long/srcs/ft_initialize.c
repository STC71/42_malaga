/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 12:19:59 by sternero          #+#    #+#             */
/*   Updated: 2024-08-07 12:19:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_init	*ft_initialize_game(t_init *init)
{
	init->mlx = NULL;	
	init->path = NULL;
	init->map = NULL;
	init->status_a = NULL;
	init->status_b = 0;
	init->ship.x = 0;
	init->ship.y = 0;
	init->size.x = 0;	
	init->size.y = 0;
	init->moves = 0;
	init->counter = 0;
	init->collec = 0;
	init->flag = 0;	
	return (init);
}

int	ft_start_map(char *path)
{
	t_init	*game;

	game = ft_calloc(sizeof(t_init), 1);
	if (!game)
		return (FAILURE);
	game = ft_initialize_game(game);
	game->path = path;
	if (ft_map(&game) == 1)
		return (FAILURE);
	game = ft_find_ship(game);
	game = ft_flood(game);
	game->status_b = ft_free_status(game->status_b, game->size.y);
	if (ft_check_failed(game, ft_count_obj(game->map)) == FAILURE)
	{
		ft_free_all(game, 1);
		return (FAILURE);
	}
	ft_mlx_init(game);
	ft_free_all(game, 0);
	return (SUCCESS);
}

t_map	*ft_map_init(t_init *game)
{
	char	*line;
	int		fd;

	fd = open(game->path, O_RDONLY);
	if (fd < 0)
	{
		ft_map_error("The map was not found or cannot be opened.\n");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_check_empty_line(game, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map);
}

/*
The function ft_initialize_init() initializes the variables of the game.
The function receives a pointer to the structure t_init and returns a pointer 
to the structure t_init. It initializes the variables of the game to NULL or 0.
It returns the pointer to the structure t_init.
*/






// void	ft_initialize(t_vars *vars, char *route)
// {
// 	vars->start_found = 0;
// 	vars->moves = 0;
// 	vars->map.route = route;
//     vars->collectibles = 0;
//     vars->map.collectibles_possible = 0;
// 	vars->collected = 0;
// 	vars->won = FALSE;
// 	vars->exit_found = 0;
// 	vars->map.exit_possible = FALSE;
// 	vars->exit_unlocked = FALSE;
// }

// void	ft_initialize_map(t_vars *vars, t_point *pos)
// {
// 	vars->map.fd = open(vars->map.route, O_RDONLY);
// 	vars->map.grid = malloc(vars->map.g_height * sizeof(char *));
// 	vars->map.tiles = malloc(vars->map.g_height * sizeof(t_tile *));
// 	pos->x = 0;
// 	pos->y = 0;
// }

