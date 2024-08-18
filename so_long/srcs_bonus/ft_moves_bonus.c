/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-08 09:15:22 by sternero          #+#    #+#             */
/*   Updated: 2024-08-08 09:15:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_moves_win(t_init *game)
{
	char	*counter;

	mlx_image_to_window(game->mlx, game->imgs.wall, 64, 1);
	counter = ft_itoa(game->moves);
	mlx_put_string(game->mlx, "Moves: ", 20, 20);
	mlx_put_string(game->mlx, counter, 85, 20);
}

void	ft_move_ship_right(t_init *game, int y, int x)
{
	t_coord	coord;

	coord.y = y;
	coord.x = x;
	if (game->status_a[y][x + 1] == 'C')
		game->c++;
	else if ((game->status_a[y][x + 1] == 'E' && game->c == game->collec)
		|| game->status_a[y][x + 1] == 'X')
		ft_the_end(game);
	else if (game->status_a[y][x + 1] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y][x + 1] = 'P';
	game->counter++;
	game->course = 'R';
	game->walking = true;
	ft_moves_win(game);
	ft_printf("Total moves: %s%d\n%s", RED, game->moves, RESET);
	ft_drawing_imgs(game, game->status_a[y][x], coord);
	coord.x++;
	game->walking = false;
	ft_drawing_imgs(game, game->status_a[y][x + 1], coord);
}

void	ft_move_ship_left(t_init *game, int y, int x)
{
	t_coord	coord;

	coord.y = y;
	coord.x = x;
	if (game->status_a[y][x - 1] == 'C')
		game->c++;
	else if ((game->status_a[y][x - 1] == 'E' && game->c == game->collec)
		|| game->status_a[y][x - 1] == 'X')
		ft_the_end(game);
	else if (game->status_a[y][x - 1] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y][x - 1] = 'P';
	game->counter++;
	game->course = 'L';
	game->walking = true;
	ft_moves_win(game);
	ft_printf("Total moves: %s%d\n%s", RED, game->moves, RESET);
	ft_drawing_imgs(game, game->status_a[y][x], coord);
	coord.x--;
	game->walking = false;
	ft_drawing_imgs(game, game->status_a[y][x - 1], coord);
}

void	ft_move_ship_up(t_init *game, int y, int x)
{
	t_coord	coord;

	coord.y = y;
	coord.x = x;
	if (game->status_a[y - 1][x] == 'C')
		game->c++;
	else if ((game->status_a[y - 1][x] == 'E' && game->c == game->collec)
		|| game->status_a[y - 1][x] == 'X')
		ft_the_end(game);
	else if (game->status_a[y - 1][x] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y - 1][x] = 'P';
	game->counter++;
	game->course = 'U';
	game->walking = true;
	ft_moves_win(game);
	ft_printf("Total moves: %s%d\n%s", RED, game->moves, RESET);
	ft_drawing_imgs(game, game->status_a[y][x], coord);
	coord.y--;
	game->walking = false;
	ft_drawing_imgs(game, game->status_a[y - 1][x], coord);
}

void	ft_move_ship_down(t_init *game, int y, int x)
{
	t_coord	coord;

	coord.y = y;
	coord.x = x;
	if (game->status_a[y + 1][x] == 'C')
		game->c++;
	else if ((game->status_a[y + 1][x] == 'E' && game->c == game->collec)
		|| game->status_a[y + 1][x] == 'X')
		ft_the_end(game);
	else if (game->status_a[y + 1][x] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y + 1][x] = 'P';
	game->counter++;
	game->course = 'D';
	game->walking = true;
	ft_moves_win(game);
	ft_printf("Total moves: %s%d\n%s", RED, game->moves, RESET);
	ft_drawing_imgs(game, game->status_a[y][x], coord);
	coord.y++;
	game->walking = false;
	ft_drawing_imgs(game, game->status_a[y + 1][x], coord);
}
