/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:10:37 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:10:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_hipo_cal(t_ray *ray)
{
	if (ray->flag == 0 && ray->ray_dir_x > 0)
		ray->hyp_distance = sqrt(pow((ray->map_x - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 0 && ray->ray_dir_x < 0)
		ray->hyp_distance = sqrt(pow(((ray->map_x + 1) - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 1 && ray->ray_dir_y > 0)
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow((ray->map_y - ray->pos_y), 2));
	else
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow(((ray->map_y + 1) - ray->pos_y), 2));
}

/*	This function calculates the distance (hypotenuse) between the player's
	position and the ray impact point with the wall. It uses the ray direction
	and the impact point coordinates to determine the distance, which is used to
	calculate the real distance between the player and the wall.	*/

void	ft_get_player_to_wall(t_data *info, t_ray *ray)
{
	if (ray->ray_dir_x > 0)
		ray->side_dist_x = (info->player.map_x + \
			ray->step_x - info->player.pos_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (info->player.pos_x - \
			info->player.map_x) * ray->delta_dist_x;
	if (ray->ray_dir_y > 0)
		ray->side_dist_y = (info->player.map_y + \
			ray->step_y - info->player.pos_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (info->player.pos_y - \
			info->player.map_y) * ray->delta_dist_y;
}

/*	This function calculates the initial distances from the player's position to
	the first intersection with a grid line of the map in the x and y 
	directions. It uses the ray direction and the player's position to determine
	these distances, which are then used in the DDA algorithm (ft_search_wall)
	to find the first wall the ray encounters.	*/

void	ft_vert_cal(t_data *info, t_ray *ray)
{
	double	angle;
	double	player;	

	player = info->player.angle * (M_PI / 180);
	angle = fabs(ray->angle_ret - player);
	if (angle > M_PI)
		angle = 2 * M_PI - angle;
	ray->ver_distance = ray->hyp_distance * cos(angle);
	if (ray->ver_distance < 0.0001)
		ray->ver_distance = 9999999999999.0;
}

/*	This function calculates the vertical distance between the player and the
	ray impact point with the wall. This distance is used to render the walls
	correctly on the screen. The function converts the player angle from degrees
	to radians. It calculates the absolute difference between the ray angle and
	the player angle. If the difference is greater than PI, it adjusts to get
	the shortest angle. It calculates the vertical distance using the hypotenuse
	distance and the cosine of the angle. If the vertical distance is less than
	0.0001, it adjusts to avoid precision problems due to possible divisions by 
	0.	
	The conversion of the angle from degrees to radians is necessary because the
	trigonometric functions in C, such as sin(), cos(), and tan(), use angles in
	radians. The difference between degrees and radians is that: while degrees
	are a unit of measure that divides a circle into 360 equal parts, radians
	are a unit of measure based on the arc length of a circle (a complete circle
	has 2 * PI radians).	*/

void	ft_get_ang(t_data *info, char dir)
{
	if (dir == 'E')
		info->player.angle = 0;
	if (dir == 'S')
		info->player.angle = 90;
	if (dir == 'W')
		info->player.angle = 180;
	if (dir == 'N')
		info->player.angle = 270;
}

/*	This function sets the player's angle based on the provided cardinal
	direction (N, S, E, W). It checks the value of dir and adjusts the player's
	angle accordingly, allowing the player to be correctly oriented in the game
	map.
	        N (270°)
		       |
	W (180°) --+-- E (0°)
		       |
		    S (90°)
	The specified values are due to the way angles are handled in the coordinate
	system used in the game, which is common in graphics and trigonometry. 
	Angles are measured clockwise from the positive x-axis, with 0° pointing
	east, 90° south, 180° west, and 270° north.	*/

void	ft_get_size_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map->map)
		return ;
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) > j)
			j = ft_strlen(map->map[i]);
		i++;
	}
	map->map_size_x = j;
	map->map_size_y = i;
}

/*	This function calculates the size of the map. It takes a pointer to a t_map
	structure as an argument. The variables i and j are declared to iterate over
	the map and store the size of the map. If the map is NULL, the function
	returns. The function iterates over the map and calculates the length of the
	longest line in the map. It then stores the size of the map in the 
	map_size_x and map_size_y variables.	*/
