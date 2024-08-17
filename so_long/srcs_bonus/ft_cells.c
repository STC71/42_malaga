/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cells_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-15 08:47:06 by sternero          #+#    #+#             */
/*   Updated: 2024-08-15 08:47:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

t_init	**ft_fill(char **stat, t_coord size, t_coord now, t_init **game)
{
	if (now.y < 0 || now.y >= size.y || now.x < 0 || now.x >= size.x
		|| stat[now.y][now.x] == '1' || stat[now.y][now.x] == 'F')
		return (game);
	if (stat[now.y][now.x] == 'E')
	{
		stat[now.y][now.x] = 'F';
		(*game)->cell.exit++;
		return (game);
	}
	game = ft_check_cell(game, stat[now.y][now.x]);
	stat[now.y][now.x] = 'F';
	game = ft_fill(stat, size, (t_coord){now.x - 1, now.y}, game);
	game = ft_fill(stat, size, (t_coord){now.x + 1, now.y}, game);
	game = ft_fill(stat, size, (t_coord){now.x, now.y - 1}, game);
	game = ft_fill(stat, size, (t_coord){now.x, now.y + 1}, game);
	return (game);
}

t_init	*ft_flood(t_init *game)
{
	game->cell.ship = 0;
	game->cell.collec = 0;
	game->cell.exit = 0;
	game = *ft_fill(game->status_b, game->size, game->ship, &game);
	return (game);
}
