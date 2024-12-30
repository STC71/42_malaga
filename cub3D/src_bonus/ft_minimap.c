/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:14:32 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:14:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_minimap(t_data *info)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < 320)
	{
		x = 0;
		while (x < 420)
		{
			if (ft_check_point(x++, y))
				mlx_put_pixel(info->walls, x, y, 0x00FF0088);
			else if (ft_check_wall(info, x++, y, '1'))
				mlx_put_pixel(info->walls, x, y, 0xFF00FF88);
			else if (ft_check_wall(info, x++, y, 'D'))
				mlx_put_pixel(info->walls, x, y, 0x0000FF88);
			else if (ft_check_wall(info, x++, y, 'C'))
				mlx_put_pixel(info->walls, x, y, 0x0000FF66);
		}
		y++;
	}
	while (i < 1920)
		ft_printer_ray(info, &info->player.ray[i++]);
}

/*	This function draws a minimap on the image info->walls and draws the 
	player's rays (the rays are the lines drawn on the screen to represent the
	walls). First, the variables i, x, y are initialized to 0 that will contain
	the index of the rays and the x and y coordinates of the minimap. Then, the
	rows of the minimap are traversed with a while loop that runs while y is
	less than 320 (320 is the height of the minimap). Inside this loop, the
	columns of the minimap are traversed with another while loop that runs while
	x is less than 420 (420 is the width of the minimap). In each iteration of
	this loop, it is checked if the point (x, y) is inside the circle that
	represents the player in the minimap with the function ft_check_point. If
	the point is inside the circle, it is painted green with the function
	mlx_put_pixel. If the point is not inside the circle, it is checked if the
	point is on a wall with the function ft_check_wall. If the point is on a
	wall, it is painted purple. If the point is not on a wall, it is checked if
	the point is on a door with the function ft_check_wall. If the point is on a
	door, it is painted blue. If the point is not on a door, it is checked if
	the point is on a colectable with the function ft_check_wall. If the point
	is on a colectable (not enabled) it is painted dark blue. After painting the
	minimap, the player's rays are traversed with a while loop that runs while i
	is less than 1920 (1920 is the number of player's rays, this amount
	corresponds to the horizontal resolution of the screen). In each iteration
	of this loop, the function ft_printer_ray is called to draw the ray on the
	image info->walls.	*/

bool	ft_check_point(int x, int y)
{
	int	cx;
	int	cy;
	int	r;

	cx = 160;
	cy = 160;
	r = 16;
	if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
		return (true);
	return (false);
}

/*	This function checks if the point received as an argument is inside the
	minimap. The center of the minimap is at the coordinates (160, 160), and the
	radius is 16. 
	16 is the radius of the circle that represents the player in the minimap.
	Radius is the distance from the center of the circle to any point on the
	circumference.
	If the point is inside the circle, the function returns true.
	Otherwise, it returns false.	*/

void	ft_printer_ray(t_data *info, t_ray *ray)
{
	double	x;
	double	y;	

	x = 160;
	y = 160;
	while (ft_check_point((int)(y), (int)(x)))
	{
		mlx_put_pixel(info->walls, (int)x, (int)y, 0xFF000088);
		x += ray->ray_dir_x;
		y += ray->ray_dir_y;
	}
}

/*	This function draws a ray on the image info->walls. First, the variables x,
	y are initialized to 160 that will contain the x and y coordinates of the
	ray. Then, the points of the ray are traversed with a while loop that runs
	while the function check_point returns true. Inside this loop, the point (x,
	y) is painted red with the function mlx_put_pixel. Then, the coordinates x,
	y of the ray are incremented with the x and y components of the ray
	direction. This function is useful to visually represent the player's rays
	on the minimap, showing the direction in which the player is looking and
	helping to visualize the game environment.	*/

bool	ft_check_wall(t_data *info, int x, int y, char c)
{
	double		map_x;
	double		map_y;

	map_x = (info->player.pos_x - 2.5) + ((double)x / 64);
	map_y = (info->player.pos_y - 2.5) + ((double)y / 64);
	if (map_x < 0 || map_y < 0)
		return (false);
	if (map_x >= info->map.map_size_x || map_y >= info->map.map_size_y)
		return (false);
	if (info->map.map[(int)map_y][(int)map_x] == c)
		return (true);
	return (false);
}

/*	This function checks if the point (x, y) is on a wall of the map. The
	function receives the game information and the x and y coordinates of the
	point to check. The x and y coordinates of the point are converted to map
	coordinates with the formula:
		map_x = (info->player.pos_x - 2.5) + ((double)x / 64);
		map_y = (info->player.pos_y - 2.5) + ((double)y / 64);
	The map coordinates are calculated by subtracting 2.5 from the player's
	coordinates and dividing the x and y coordinates by 64. The division by 64
	is done to scale the minimap to the size of the map. If the map coordinates
	are less than 0 or greater than the size of the map, the function returns
	false. If the point is on a wall, the function returns true. Otherwise, the
	function returns false.
	info->player.pos_x and y represent the player's position on the game map.
	Subtracting 2.5 from these coordinates adjusts the player's position to
	center the minimap around him. The value 2.5 is chosen because the minimap
	shows an area of 5 x 5 units of the game map around the player.
	By subtracting 2.5, it ensures that the player is in the center of the
	minimap with 2.5 units of the map visible on each side of the player. As for
	the scaling of the minimap, the division by 64 is done so that the minimap
	has the same size as the game map. The size of the minimap is 320 x 420
	pixels, and the size of the game map is 20 x 20 units. Therefore, each unit
	of the game map is represented with 16 pixels in the minimap. This allows
	the minimap to represent a portion of the game map at a smaller scale.	*/
