/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-08 09:15:22 by sternero          #+#    #+#             */
/*   Updated: 2024-08-08 09:15:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_key_press(struct mlx_key_data key_data, void *param)
{
	t_init	*game;

	game = param;
	game = ft_find_ship(game);
	if (key_data.key == MLX_KEY_UP && key_check(game) == 1)
		ft_go_up(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_DOWN && key_check(game) == 2)
		ft_go_down(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_LEFT && key_check(game) == 3)
		ft_go_left(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_RIGHT && key_check(game) == 4)
		ft_go_right(game, game->ship.y, game->ship.x);
	if (key_data.key == MLX_KEY_ESCAPE && key_check(game) == 5)
	{
		mlx_close_window(game->mlx);
		return ;
	}
}

void	ft_go_right(t_init *game, int y, int x)
{
	t_coord	p;
	
	p.x = x;
	p.y = y;
	if (game->status_a[y][x + 1] == 'C')
		game->collec++;
	else if (game->status_a[y][x + 1] == 'E' && game->collec == game->collec)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	else if (game->status_a[y][x + 1] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y][x + 1] = 'P';
	game->counter++;
	game->course = 'R';
	game->walking = true;
	ft_printf("Moves: %d\n", game->moves);
	hook_images(game, game->status_a[y][x], p);
	p.x++;
	game->walking = false;
	hook_images(game, game->status_a[y][x + 1], p);
}

void	ft_go_left(t_init *game, int y, int x)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	if (game->status_a[y][x - 1] == 'C')
		game->collec++;
	else if (game->status_a[y][x - 1] == 'E' && game->collec == game->collec)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	else if (game->status_a[y][x - 1] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y][x - 1] = 'P';
	game->counter++;
	game->course = 'L';
	game->walking = true;
	ft_printf("Moves: %d\n", game->moves);
	hook_images(game, game->status_a[y][x], p);
	p.x--;
	game->walking = false;
	hook_images(game, game->status_a[y][x - 1], p);
}

void	ft_go_up(t_init *game, int y, int x)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	if (game->status_a[y - 1][x] == 'C')
		game->collec++;
	else if (game->status_a[y - 1][x] == 'E' && game->collec == game->collec)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	else if (game->status_a[y - 1][x] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y - 1][x] = 'P';
	game->counter++;
	game->course = 'U';
	game->walking = true;
	ft_printf("Moves: %d\n", game->moves);
	hook_images(game, game->status_a[y][x], p);
	p.y--;
	game->walking = false;
	hook_images(game, game->status_a[y - 1][x], p);
}

void	ft_go_down(t_init *game, int y, int x)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	if (game->status_a[y + 1][x] == 'C')
		game->collec++;
	else if (game->status_a[y + 1][x] == 'E' && game->collec == game->collec)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	else if (game->status_a[y + 1][x] == 'E')
		return ;
	game->moves++;
	game->status_a[y][x] = '0';
	game->status_a[y + 1][x] = 'P';
	game->counter++;
	game->course = 'D';
	game->walking = true;
	ft_printf("Moves: %d\n", game->moves);
	hook_images(game, game->status_a[y][x], p);
	p.y++;
	game->walking = false;
	hook_images(game, game->status_a[y + 1][x], p);
}



// int	ft_press_key(int key, t_vars *vars)
// {
// 	if (key == ESC)
// 		ft_end_game(vars);
// 	else if (key == RIGHT && !vars->won)
// 		ft_init_moves(vars, (t_coord	{vars->gamer.pos.x + 1, \
// 			vars->gamer.pos.y});
// 	else if (key == LEFT && !vars->won)
// 		ft_init_moves(vars, (t_coord	{vars->gamer.pos.x - 1, \
// 			vars->gamer.pos.y});
// 	else if (key == UP && !vars->won)
// 		ft_init_moves(vars, (t_coord	{vars->gamer.pos.x, \
// 			vars->gamer.pos.y - 1});
// 	else if (key == DOWN && !vars->won)
// 		ft_init_moves(vars, (t_coord	{vars->gamer.pos.x, \
// 			vars->gamer.pos.y + 1});
// 	return (SUCCESS);
// }

// void	ft_check_moves(t_coord	p, t_vars *vars)
// {
// 	size_t	w;
// 	size_t	h;

// 	w = vars->map.g_width;
// 	h = vars->map.g_height;
// 	if (vars->map.grid[p.y][p.x] == WALL || \
// 		vars->map.tiles[p.y][p.x].v == 1 || p.x < 0 || p.y < 0 || p.x > w || \
// 		p.y > h)
// 		return ;
// 	vars->map.tiles[p.y][p.x].v = 1;
// 	if (vars->map.grid[p.y][p.x] == EXIT)
// 		vars->map.exit_possible = 1;
// 	if (vars->map.grid[p.y][p.x] == COLLECT)
// 		vars->map.collectibles_possible++;
// 	ft_check_moves((t_coord	{p.x - 1, p.y}, vars);
// 	ft_check_moves((t_coord	{p.x + 1, p.y}, vars);
// 	ft_check_moves((t_coord	{p.x, p.y - 1}, vars);
// 	ft_check_moves((t_coord	{p.x, p.y + 1}, vars);
// 	return ;
// }

// void	ft_init_moves(t_vars *vars, t_coord	new)
// {
// 	ft_printf("Number of moves: %d\n", ++vars->moves);
// 	if (new.x < vars->map.g_width && new.y < vars->map.g_height)
// 	{
// 		if (vars->map.grid[new.y][new.x] == COLLECT)
// 		{
// 			vars->collected++;
// 			vars->map.grid[new.y][new.x] = FLOOR;
// 			if (vars->collected == vars->collectibles)
// 				vars->exit_unlocked = 1;
// 			vars->gamer.pos = new;
// 		}
// 		else if (vars->map.grid[new.y][new.x] == EXIT && vars->exit_unlocked)
// 		{
// 			vars->gamer.pos = new;
// 			vars->won = 1;
// 		}
// 		else if (vars->map.grid[new.y][new.x] != WALL)
// 			vars->gamer.pos = new;
// 	}
// }

// int	ft_init_rendering(t_vars *vars)
// {
// 	ft_drawing_background(vars);
// 	if (!vars->won)
// 	{
// 		ft_drawing_map(vars);
// 		ft_drawing_ship(vars);
// 		ft_drawing_movements(vars);
// 	}
// 	else
// 	{
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->you_win.img, 0, 0);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[\
// 			(vars->moves / 100)].img, 1 * SIZE + 10, 3 * SIZE + 10);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[\
// 			(vars->moves / 10) % 10].img, 2 * SIZE + 10, 3 * SIZE + 10);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[\
// 			(vars->moves % 100) % 10].img, 3 * SIZE + 10, 3 * SIZE + 10);
// 	}
// 	return (0);
// }

// /*
// The ft_check_moves() function checks if the new position is a wall or if the
// new position has been visited. If the new position is a wall or has been
// visited, the function returns. If the new position is not a wall or has not
// been visited, the function marks the new position as visited. If the new
// position is an exit, the function sets the exit_possible variable to 1. If the
// new position is a collectible, the function increments the collectibles_possible
// variable by 1. The function then calls itself recursively for the new position
// to the left, right, up, and down. It is used to check if the exit is reachable, 
// to count the number of collectibles, and to check if the new position is valid.

// The game_moves() function increments the number of moves by 1 and prints the 
// number of moves. It then checks if the new position is within the map limits.
// If the new position is within the map limits, the function checks if the new
// position is a collectible. If the new position is a collectible, the function
// increments the number of collected collectibles by 1, changes the collectible
// to a floor, and checks if the number of collected collectibles is equal to the
// number of collectibles. If the number of collected collectibles is equal to the
// number of collectibles, the function unlocks the exit. If the new position is
// an exit and the exit is unlocked, the function moves the ship to the new
// position and sets the won variable to 1. If the new position is not a wall, the
// function moves the ship to the new position.

// The game_rendering() function draws the background. If the ship has not won,
// the function draws the map, the ship, and the number of moves. If the ship
// has won, the function draws the victory image, and the number of moves.
// */