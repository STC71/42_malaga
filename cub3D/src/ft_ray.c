/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:08:20 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:08:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_values_ray(t_data *info, t_ray *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = info->player.map_x;
	ray->map_y = info->player.map_y;
	ray->pos_x = info->player.pos_x;
	ray->pos_y = info->player.pos_y;
	ray->ray_dir_x = cos(ray->angle);
	ray->ray_dir_y = sin(ray->angle);
	ray->delta_dist_x = 1 / fabs(ray->ray_dir_x);
	ray->delta_dist_y = 1 / fabs(ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	ray->flag = 0;
}

/*	This function initializes the ray variables (t_ray) based on the player
	information (t_data). It calculates the ray direction in x and y, the delta
	distances, the initial ray position, and the steps in x and y. This prepares
	the ray to be used in the collision detection algorithm with the walls
	(ft_search_wall) and the rendering in the game.	*/

void	ft_shoot_ray(t_data *info, t_player *player)
{
	int	i;

	ft_init_ray(info);
	i = 0;
	while (i < WIDTH)
	{
		ft_get_impact_ray(info, &player->ray[i]);
		ft_paint_column(info, &player->ray[i], i);
		i++;
	}
}

/*	This function is in charge of shooting rays from the player's position to
	detect collisions with the walls and render the wall columns on the screen.
	The function receives the info structure that contains all the game
	information and the player structure that contains the player information.
	The function initializes the rays and iterates over all the shot rays. For
	each ray, the function finds the impact point with the wall and renders the
	wall column on the screen.	*/

void	ft_get_impact_ray(t_data *info, t_ray *ray)
{
	ft_init_values_ray(info, ray);
	ft_get_player_to_wall(info, ray);
	ft_search_wall(info, ray);
	if (ray->flag == 0)
		ray->hit = ray->pos_y + (ray->perp_wall_dist * ray->ray_dir_y);
	else
		ray->hit = ray->pos_x + (ray->perp_wall_dist * ray->ray_dir_x);
	if (ray->flag == 0)
		ft_impact_ver(ray);
	else
		ft_impact_hor(ray);
	ft_hipo_cal(ray);
	ft_vert_cal(info, ray);
}

/*	This function is in charge of finding the impact point of a ray with a wall.
	It receives the data structure that contains all the game information and 
	the ray structure that contains the ray information. The function 
	initializes the ray variables and calculates the ray direction. 
	It calculates the distance between the player and the wall in the x and y
	axes. It iterates over the map until it finds a wall. It calculates the
	perpendicular distance between the player and the wall. It calculates the
	ray impact point with the wall. It calculates the hypotenuse between the
	player and the wall. Finally, it calculates the vertical distance between 
	the player and the wall to render the wall column on the screen.	*/

void	ft_search_wall(t_data *info, t_ray *ray)
{
	while (info->map.map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->flag = 1;
		}
	}
	if (ray->flag == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}

/*	The function is in charge of finding the impact point of a ray with a wall,
	using the DDA (Digital Differential Analyzer) algorithm. It receives the
	data structure that contains all the game information and the ray structure
	that contains the ray information. The function uses a while loop to iterate
	over the map until it finds a wall. In each iteration, it determines in
	which direction to move (horizontal or vertical) and updates the side
	distances. If the side distance in x is less than the side distance in y, it
	updates the side distance in x and moves in x. If the side distance in y is
	less than the side distance in x, it updates the side distance in y and 
	moves in y. When it finds a wall, it calculates the perpendicular distance
	between the player and the wall. If the ray flag is 0, it calculates the
	perpendicular distance in x. If the ray flag is 1, it calculates the
	perpendicular distance in y.	*/