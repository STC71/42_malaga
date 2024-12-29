/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:12:59 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:12:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

bool	ft_check_door(t_data *info)
{
	int	check_x;
	int	check_x2;
	int	check_y;
	int	check_y2;

	check_x = (int)floor((info->player.pos_x + 0.25));
	check_x2 = (int)floor((info->player.pos_x - 0.25));
	check_y = (int)floor((info->player.pos_y + 0.25));
	check_y2 = (int)floor((info->player.pos_y - 0.25));
	if (info->map.map[check_y][check_x] == 'C')
		return (false);
	if (info->map.map[check_y2][check_x] == 'C')
		return (false);
	if (info->map.map[check_y][check_x2] == 'C')
		return (false);
	if (info->map.map[check_y2][check_x2] == 'C')
		return (false);
	return (true);
}

/*	This function is used to check if the player is near a door on the game
	map. To do this, the coordinates of the points adjacent to the player are
	calculated and it is verified if any of these points is in a position where
	there is a door. floor is used to round down the calculated coordinates,
	obtaining the position on the map grid. After this, it is verified if any of
	the points adjacent to the player is in a position where there is a door. If
	any of the points adjacent to the player is in a position where there is a
	door, the function will return false, indicating that the player is not near
	a door. Otherwise, the function will return true, indicating that the player
	is not near a door. */

void	ft_door(t_data *info)
{
	t_ray		door_ray;

	if (!ft_check_door(info))
		return ;
	door_ray.angle = info->player.angle * (M_PI / 180);
	ft_init_values_ray(info, &door_ray);
	ft_get_player_to_wall(info, &door_ray);
	ft_search_wall(info, &door_ray);
	if (door_ray.flag == 0)
		door_ray.hit = door_ray.pos_y + \
			(door_ray.perp_wall_dist * door_ray.ray_dir_y);
	else
		door_ray.hit = door_ray.pos_x + \
			(door_ray.perp_wall_dist * door_ray.ray_dir_x);
	if (door_ray.flag == 0)
		ft_impact_ver(&door_ray);
	else
		ft_impact_hor(&door_ray);
	ft_hipo_cal(&door_ray);
	if (info->map.map[door_ray.map_y][door_ray.map_x] == 'D' \
		&& door_ray.hyp_distance <= 1)
		info->map.map[door_ray.map_y][door_ray.map_x] = 'C';
	else if (info->map.map[door_ray.map_y][door_ray.map_x] \
		== 'C' && door_ray.hyp_distance <= 1)
		info->map.map[door_ray.map_y][door_ray.map_x] = 'D';
}

/*	This function handles the opening and closing of doors in the game. First,
	it is checked if the player is near a door on the game map with the function
	ft_check_door. If the player is not near a door, the function ends. If the
	player is near a door, a t_ray structure called door_ray is created and its
	values are initialized with the function ft_init_values_ray. Then, the
	direction of the door ray is calculated with the function
	ft_get_player_to_wall. Next, the wall is searched with the function
	ft_search_wall. The impact point of the door is calculated with the
	function ft_impact_ver or ft_impact_hor, depending on whether the door is
	vertical or horizontal. The hypotenuse distance is calculated with the
	function ft_hipo_cal. If the impact point of the door is at a distance less
	than or equal to 1, the door is opened or closed on the game map and the
	value of the corresponding cell is updated. */

void	ft_dda(t_data *info, t_ray *ray)
{
	while (info->map.map[ray->map_y][ray->map_x] != '1' &&
		info->map.map[ray->map_y][ray->map_x] != 'D')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			if (info->map.map[ray->map_y][ray->map_x] == 'C')
				info->prev_map_x = ray->map_x;
			ray->map_x += ray->step_x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			if (info->map.map[ray->map_y][ray->map_x] == 'C')
				info->prev_map_y = ray->map_y;
			ray->map_y += ray->step_y;
			ray->flag = 1;
		}
		if (info->map.map[ray->map_y][ray->map_x] == 'D')
			ray->door_flag = 1;
	}
}

/*	This function implements the Digital Differential Analyzer (DDA) algorithm
	to calculate the intersection of a ray with the walls of the map. The DDA
	algorithm is a rasterization algorithm used to transform lines into pixels
	in a two-dimensional plane. In this case, the DDA algorithm is used to
	calculate the intersection of a ray with the walls of the map. The DDA
	algorithm is implemented with a while loop that runs while the ray has not
	impacted with a wall or a door. In each iteration of the loop, the distance
	to the next side in x and y is calculated and the position of the ray on the
	map is updated. If the ray impacts with a door, the door flag in the ray
	structure is updated. Suppose the player casts a ray in a specific direction
	to detect if there is a wall or a door in that direction. The DDA algorithm
	will initialize the DDA loop to advance the ray through the map, determine
	if the ray should advance in the x or y direction, based on the distances
	side_dist_x and side_dist_y, and then update these distances, as well as the
	map_x and map_y positions of the ray. In the case that the ray encounters a
	closed door (D), it will set ray->door_flag to 1. The loop will continue
	until the ray encounters a wall (1) or a door (D).
	The Digital Differential Analyzer (DDA) algorithm is a method used to draw
	lines in computer graphics. In the context of a raycasting game, the DDA
	algorithm is used to calculate the intersection of a ray with the cells of
	the map, identifying walls and doors. */
