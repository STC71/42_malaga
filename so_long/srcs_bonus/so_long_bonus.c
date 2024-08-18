/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 09:34:29 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 09:34:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

char	**ft_status_map(t_init *game)
{
	t_map	*tmp;
	char	**status;
	int		i;

	i = 0;
	tmp = game->map;
	status = malloc(sizeof(char *) * (game->size.y + 1));
	if (!status)
		return (NULL);
	while (game->map)
	{
		status[i] = ft_strdup(game->map->map);
		if (!status[i])
		{
			ft_free_status(status, i);
			return (NULL);
		}
		i++;
		game->map = game->map->next;
	}
	game->map = tmp;
	status[i] = NULL;
	return (status);
}

void	ft_key_press(struct mlx_key_data key_data, void *date)
{
	t_init	*game;

	game = date;
	game = ft_find_ship(game);
	if (key_data.key == MLX_KEY_UP && ft_key_check(game) == 1)
		ft_move_ship_up(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_DOWN && ft_key_check(game) == 2)
		ft_move_ship_down(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_LEFT && ft_key_check(game) == 3)
		ft_move_ship_left(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_RIGHT && ft_key_check(game) == 4)
		ft_move_ship_right(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_ESCAPE && ft_key_check(game) == 5)
	{
		mlx_close_window(game->mlx);
		return ;
	}
}

int	ft_map(t_init **game)
{
	t_init	*tmp;

	tmp = *game;
	tmp->map = ft_map_init(tmp);
	if (!tmp->map)
	{
		free(tmp);
		return (1);
	}
	tmp->size.x = ft_map_x(tmp->map);
	tmp->size.y = ft_map_y(tmp->map);
	tmp->status_a = ft_status_map(tmp);
	if (!tmp->status_a)
	{
		ft_free_all(tmp, 2);
		return (FAILURE);
	}
	tmp->status_b = ft_status_map(tmp);
	if (!tmp->status_b)
	{
		ft_free_all(tmp, 1);
		return (FAILURE);
	}
	*game = tmp;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	system("clear");
	if (argc != 2)
	{
		ft_map_error(ERR_INIT);
		return (1);
	}
	if (argc == 2)
	{
		if (ft_check_ber(argv[1]) == FAILURE)
		{
			ft_map_error(ERR_FILE);
			return (FAILURE);
		}
		i = ft_start_map(argv[1]);
		if (i == 1)
			return (FAILURE);
	}
	ft_game_over_();
	return (SUCCESS);
}
