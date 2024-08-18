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
	init->c = 0;
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
		ft_map_error(ERR_MAP);
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

void	ft_init_txts(t_init *game)
{
	game->txts.wall = mlx_load_png("./imgs/wall.png");
	game->txts.ocean = mlx_load_png("./imgs/ocean.png");
	game->txts.ship = mlx_load_png("./imgs/ship.png");
	game->txts.ship_u = mlx_load_png("./imgs/ship_U.png");
	game->txts.ship_d = mlx_load_png("./imgs/ship_D.png");
	game->txts.ship_l = mlx_load_png("./imgs/ship_L.png");
	game->txts.ship_r = mlx_load_png("./imgs/ship_R.png");
	game->txts.shark = mlx_load_png("./imgs/shark.png");
	game->txts.collec = mlx_load_png("./imgs/collec.png");
	game->txts.exit_c = mlx_load_png("./imgs/exit_c.png");
	game->txts.exit_o = mlx_load_png("./imgs/exit_o.png");
	if (!game->txts.wall || !game->txts.ocean || !game->txts.ship
		|| !game->txts.ship_u || !game->txts.ship_d
		|| !game->txts.ship_l || !game->txts.ship_r
		|| !game->txts.shark || !game->txts.collec
		|| !game->txts.exit_c || !game->txts.exit_o)
	{
		ft_map_error("The textures could not be loaded..\n");
		ft_free_all(game, 1);
		exit(FAILURE);
	}
}

void	ft_init_imgs(t_init *game)
{
	game->imgs.wall = mlx_texture_to_image(game->mlx, game->txts.wall);
	game->imgs.ocean = mlx_texture_to_image(game->mlx, game->txts.ocean);
	game->imgs.ship = mlx_texture_to_image(game->mlx, game->txts.ship);
	game->imgs.ship_d = mlx_texture_to_image(game->mlx, game->txts.ship_d);
	game->imgs.ship_l = mlx_texture_to_image(game->mlx, game->txts.ship_l);
	game->imgs.ship_r = mlx_texture_to_image(game->mlx, game->txts.ship_r);
	game->imgs.ship_u = mlx_texture_to_image(game->mlx, game->txts.ship_u);
	game->imgs.shark = mlx_texture_to_image(game->mlx, game->txts.shark);
	game->imgs.collec = mlx_texture_to_image(game->mlx, game->txts.collec);
	game->imgs.exit_c = mlx_texture_to_image(game->mlx, game->txts.exit_c);
	game->imgs.exit_o = mlx_texture_to_image(game->mlx, game->txts.exit_o);
}
