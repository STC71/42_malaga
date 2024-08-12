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

void	ft_drawing_background(t_vars *vars)
{
	t_point	ini;
	t_point	end;

	ini.x = 0;
	ini.y = 0;
	end.x = vars->map.g_width * SIZE;
	end.y = vars->map.g_height * SIZE;
	while (ini.y < end.y)
	{
		while (ini.x < end.x)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->floor.img, \
			ini.x, ini.y);
			ini.x += SIZE;
		}
		ini.x = 0;
		ini.y += SIZE;
	}
}

void	ft_drawing_map(t_vars *vars)
{
	t_point	s;

	s.x = 0;
	s.y = 0;
	while (s.y < vars->map.g_height * SIZE)
	{
		while (s.x < vars->map.g_width * SIZE)
		{
			if (vars->map.grid[s.y / SIZE][s.x / SIZE] == FLOOR)
				put_sp(vars, s, FLOOR);
			else if (vars->map.grid[s.y / SIZE][s.x / SIZE] == WALL)
				put_sp(vars, s, WALL);				
			else if (vars->map.grid[s.y / SIZE][s.x / SIZE] == PLAYER)
				put_sp(vars, s, PLAYER);			
			else if (vars->map.grid[s.y / SIZE][s.x / SIZE] == COLLECT)
				put_sp(vars, s, COLLECT);
			else if (vars->map.grid[s.y / SIZE][s.x / SIZE] == EXIT)
				put_sp(vars, s, EXIT);
			s.x += SIZE;
		}
		s.x = 0;
		s.y += SIZE;
	}
}

void	ft_drawing_image(t_vars *vars, t_point coo, char img)
{
	if (img == FLOOR)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->floor.img, \
			coo.x, coo.y);
	else if (img == WALL)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall.img, \
			coo.x, coo.y);
	else if (img == PLAYER)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player.img, \
			coo.x, coo.y);
	else if (img == COLLECT)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->collect.img, \
			coo.x, coo.y);
	else if (img == EXIT)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->exit.img, \
			coo.x, coo.y);
}


void	ft_drawing_gamer(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player.img, \
		vars->gamer.pos.x * SIZE, vars->gamer.pos.y * SIZE);
}

void	ft_drawing_movements(t_vars *vars)
{
	int	hun;
	int	ten;
	int	uni;

	hun = (vars->moves / 100);
	ten = (vars->moves / 10) % 10;
	uni = ((vars->moves % 100) % 10);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[hun].img, \
		0 * SIZE + 10, 10);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[ten].img, \
		1 * SIZE + 10, 10);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->nbrs[uni].img, \
		2 * SIZE + 10, 10);
}

/*
The drawing_background() function draws the background of the map.
It takes a pointer to a t_vars structure as a parameter.
It initializes two t_point structures, ini and end, to store the initial and
final coordinates of the background.
It sets the x and y coordinates of the initial point to 0.
It sets the x and y coordinates of the end point to the width of the map 
multiplied by the size of the tiles.
It then enters a while loop that runs as long as the y coordinate of the initial
point is less than the y coordinate of the end point.
It enters a nested while loop that runs as long as the x coordinate of the
initial point is less than the x coordinate of the end point.
It draws the floor image at the x and y coordinates of the initial point.
It increments the x coordinate of the initial point by the size of the tiles.
It resets the x coordinate of the initial point to 0 and increments the y
coordinate of the initial point by the size of the tiles.

The drawing_map() function draws the map on the screen.
It takes a pointer to a t_vars structure as a parameter.
It initializes a t_point structure, s, to store the x and y coordinates of the
tiles. It sets the x and y coordinates of the structure to 0.
It enters a while loop that runs as long as the y coordinate of the structure is
less than the height of the map multiplied by the size of the tiles.
It enters a nested while loop that runs as long as the x coordinate of the
structure is less than the width of the map multiplied by the size of the tiles.
It checks the type of the tile at the x and y coordinates of the structure. If
it is a floor tile, it calls the put_sp() function with the floor image as a
parameter. If it is a wall tile, it calls the put_sp() function with the wall
image as a parameter. If it is a player tile, it calls the put_sp() function
with the player image as a parameter. If it is a collectible tile, it calls the
put_sp() function with the collectible image as a parameter. If it is an exit
tile, it calls the put_sp() function with the exit image as a parameter.
It increments the x coordinate of the structure by the size of the tiles.
It resets the x coordinate of the structure to 0 and increments the y coordinate
of the structure by the size of the tiles.

The drawing_image() function draws an image on the screen.
It takes a pointer to a t_vars structure and a t_point structure as parameters.
It also takes a character representing the type of the image to draw.
It uses the mlx_put_image_to_window() function to draw the image at the x and y
coordinates of the t_point structure. The image is selected based on the type of
the image. If the type is a floor tile, it draws the floor image. If the type is
a wall tile, it draws the wall image. If the type is a player tile, it draws the
player image. If the type is a collectible tile, it draws the collectible image.
If the type is an exit tile, it draws the exit image.

The drawing_gamer() function draws the player on the map.
It takes a pointer to a t_vars structure as a parameter.
It uses the mlx_put_image_to_window() function to draw the player image at the
x and y coordinates of the player position multiplied by the size of the tiles.
It uses to draw the specified image at the specified coordinates.

The drawing_movements() function draws the number of movements on the screen.
It takes a pointer to a t_vars structure as a parameter. It initializes three
integers, hun, ten, and uni, to store the hundreds, tens, and units digits of the
number of movements. It calculates the hundreds digit by dividing the number of
movements by 100. It calculates the tens digit by dividing the number of
movements by 10 and taking the remainder when divided by 10. It calculates the
units digit by taking the remainder of the number of movements when divided by
10. It uses the mlx_put_image_to_window() function to draw the hundreds digit
image at the x and y coordinates of the screen. It uses the mlx_put_image_to_window()
function to draw the tens digit image at the x and y coordinates of the screen.
It uses the mlx_put_image_to_window() function to draw the units digit image at
the x and y coordinates of the screen.
*/