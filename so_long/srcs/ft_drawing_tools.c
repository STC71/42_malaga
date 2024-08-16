/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 08:05:56 by sternero          #+#    #+#             */
/*   Updated: 2024-08-07 08:05:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_map	*ft_add_line(char *line)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map = ft_strdup(line);
	if (!new->map)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	ft_last_line(t_init *game, t_map *new)
{
	t_map	*last;

	last = game->map;
	if (!last)
		game->map = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	ft_drawing_map(t_init *game)
{
	t_coord	coord;
	int		j;
	int		i;

	j = 0;
	while (j < game->size.y)
	{
		i = 0;
		while (game->status_a[j][i] != '\n' && game->status_a[j][i] != '\0')
		{
			coord.x = i;
			coord.y = j;
			ft_drawing_imgs(game, game->status_a[j][i], coord);
			i++;
		}
		j++;
	}
	ft_drawing_ship(game, game->ship);
}

void	ft_drawing_imgs(t_init *game, char img, t_coord p)
{
	if (img == '1' && game->imgs.wall != NULL)
		mlx_image_to_window(game->mlx, game->imgs.wall, p.x * 64, p.y * 64);
	if (img != '1' && game->imgs.ocean != NULL)
		mlx_image_to_window(game->mlx, game->imgs.ocean, p.x * 64, p.y * 64);
	if (img == 'P')
	{
		ft_drawing_ship(game, p);
		return ;
	}
	if (img == 'C' && game->imgs.collec != NULL)
		mlx_image_to_window(game->mlx, game->imgs.collec, p.x * 64, p.y * 64);
	if (img == 'E' && game->imgs.exit_c != NULL)
		mlx_image_to_window(game->mlx, game->imgs.exit_c, p.x * 64, p.y * 64);
}

void	ft_drawing_ship(t_init *game, t_coord p)
{
	if (game->course == 'U' && game->counter > 0)
		ft_move_ship_up(game, p, game->counter);
	else if (game->course == 'D' && game->counter > 0)
		ft_move_ship_down(game, p, game->counter);
	else if (game->course == 'R' && game->counter > 0)
		ft_move_ship_right(game, p, game->counter);
	else if (game->course == 'L' && game->counter > 0)
		ft_move_ship_left(game, p, game->counter);
	else
		mlx_image_to_window(game->mlx, game->imgs.ship, p.x * 64, p.y * 64);
}
