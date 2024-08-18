/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 11:48:54 by sternero          #+#    #+#             */
/*   Updated: 2024-08-07 11:48:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_failed(t_init *game, t_cell objects)
{
	int	x;

	x = SUCCESS;
	if (ft_check_obj_nbr(objects) == FAILURE)
		x = FAILURE;
	if (ft_check_obj(game->cell, objects) == FAILURE)
		x = FAILURE;
	if (ft_check_form(game) == FAILURE)
		x = FAILURE;
	if (ft_check_borders(game) == FAILURE)
		x = FAILURE;
	if (x == FAILURE)
	{
		(ft_map_error(ERR_GENERAL));
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_check_ber(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if ((file[len - 4] != '.' || file[len - 3] != 'b'
			|| file[len -2] != 'e' || file[len -1] != 'r'))
		return (FAILURE);
	return (SUCCESS);
}

void	ft_check_empty_line(t_init *game, char *line)
{
	t_map	*new;

	if (line[0] == '\n')
	{
		ft_map_error(ERR_LINE);
		free(line);
		exit(FAILURE);
	}
	new = ft_add_line(line);
	ft_last_line(game, new);
	free(line);
}

t_init	**ft_check_cell(t_init	**game, char check)
{
	if (check == 'C')
	{
		(*game)->cell.collec++;
		(*game)->collec++;
	}
	if (check == 'P')
		(*game)->cell.ship++;
	if (check == 'E')
		(*game)->cell.exit++;
	return (game);
}

int	ft_key_check(t_init *game)
{
	if (game->status_a[game->ship.y - 1][game->ship.x] != '1'
		&& mlx_is_key_down(game->mlx, MLX_KEY_UP))
		return (1);
	if (game->status_a[game->ship.y + 1][game->ship.x] != '1'
		&& mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		return (2);
	if (game->status_a[game->ship.y][game->ship.x - 1] != '1'
		&& mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		return (3);
	if (game->status_a[game->ship.y][game->ship.x + 1] != '1'
		&& mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		return (4);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		return (5);
	return (0);
}
