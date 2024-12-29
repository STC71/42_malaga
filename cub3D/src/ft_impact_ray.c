/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:06:12 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:06:12 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_ray(t_data *info)
{
	int		i;
	double	angle;
	double	fov;

	fov = FOV * M_PI / 180;
	angle = info->player.angle * M_PI / 180;
	i = 0;
	while (i < WIDTH)
	{
		info->player.ray[i].angle = angle - (fov / 2) \
			+ ((fov / WIDTH) * i);
		info->player.ray[i].angle_ret = info->player.ray[i].angle;
		if (info->player.ray[i].angle < 0)
			info->player.ray[i].angle += 2 * M_PI;
		i++;
	}
}

/*	This function initializes the rays that are shot from the player's position,
	calculating their angles based on the player's Field of View (FOV). In 
	simple terms, the Field of View (FOV) in a video game determines how wide
	the player's viewing angle is within the game. It's like looking through a
	window: a wider FOV allows you to see more things around you, while a
	narrower one limits your vision. In this case, the FOV is 60 degrees, which
	means the player can see 60 degrees to their left and 60 degrees to their
	right. This prepares the rays to be used in the collision detection with the
	walls (ft_search_wall) and the rendering in the game.	*/

void	ft_impact_ver(t_ray *ray)
{
	if (ray->ray_dir_x > 0 && ray->ray_dir_y >= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_y) * 1920;
	}
	else if (ray->ray_dir_x <= 0 && ray->ray_dir_y > 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_y) * 1920;
	}
	else if (ray->ray_dir_x >= 0 && ray->ray_dir_y < 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_y) * 1920;
	}
	else if (ray->ray_dir_x < 0 && ray->ray_dir_y <= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_y) * 1920;
	}
}

/*	This function calculates the vertical impact of the ray in terms of pixels
	in the screen width. It uses the ray direction and the impact position to
	determine this position, which is used to render correctly the ray impact in
	the game screen.	*/

void	ft_impact_hor(t_ray *ray)
{
	if (ray->ray_dir_x > 0 && ray->ray_dir_y >= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_x) * 1920;
	}
	else if (ray->ray_dir_x <= 0 && ray->ray_dir_y > 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_x) * 1920;
	}
	else if (ray->ray_dir_x >= 0 && ray->ray_dir_y < 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_x) * 1920;
	}
	else if (ray->ray_dir_x < 0 && ray->ray_dir_y <= 0)
	{
		ray->pixel_width_impact = (ray->hit - ray->map_x) * 1920;
	}
}

/*	This function calculates the horizontal impact of the ray in terms of pixels
	in the screen width. It uses the ray direction and the impact position to
	determine this position, which is used to render correctly the ray impact in
	the game screen.	*/
