/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:09:00 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:09:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_get_imgs_info(t_data *info, int *res, int *fd)
{
	if (*fd < 0)
	{
		printf(RED"Failed to open the map file."RESET);
		*res = 1;
		return (*res);
	}
	if (ft_get_walls(info, fd, res))
	{
		*res = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function opens the map configuration file and gets the information of
	the wall textures. If the file cannot be opened, an error message is printed
	and res is set to 1.	*/

int	ft_get_walls(t_data *info, int *fd, int *res)
{
	char	**split_line;
	int		i;
	int		j;

	split_line = NULL;
	i = 0;
	j = 0;
	while (i < 6)
	{
		if (ft_split_line(&split_line, *fd))
			return (FAILURE);
		j++;
		if (ft_check_text(info, split_line, &i, j))
			*res = 1;
	}
	ft_missing_id(info, fd, i);
	return (SUCCESS);
}

/*	This function reads and processes the lines of the map configuration file to
	obtain the paths of the wall textures. It checks and stores these paths in
	the t_data structure. If an error occurs during the process, it returns
	FAILURE.	*/

double	ft_size_wall(t_ray *ray)
{
	double	size;

	if (ray->hyp_distance < ray->ver_distance)
		size = (WIDTH / ray->hyp_distance);
	else
		size = (WIDTH / ray->ver_distance);
	return (size);
}

/*	This function calculates the size of the wall based on the distance of the
	ray to the wall. It takes a pointer to a t_ray structure as an argument. It
	initializes the variable size. If the hypotenuse distance of the ray is less
	than the vertical distance of the ray, the size is calculated as the width
	of the window divided by the hypotenuse distance of the ray. Otherwise, the
	size is calculated as the width of the window divided by the vertical
	distance of the ray. Finally, it returns the size of the wall. This helps to
	calculate the size of the wall correctly based on the distance of the ray to
	the wall.	*/

void	ft_load_imgs(t_data *info)
{
	info->textures.no_texture = mlx_load_png(info->textures.no_path);
	if (!info->textures.no_texture)
	{
		printf(RED"Failed to load png for NO\n"RESET);
		exit(FAILURE);
	}
	info->textures.so_texture = mlx_load_png(info->textures.so_path);
	if (!info->textures.so_texture)
	{
		printf(RED"Failed to load png for SO\n"RESET);
		exit(FAILURE);
	}
	info->textures.ea_texture = mlx_load_png(info->textures.ea_path);
	if (!info->textures.ea_texture)
	{
		printf(RED"Failed to load png for EA\n"RESET);
		exit(FAILURE);
	}
	info->textures.we_texture = mlx_load_png(info->textures.we_path);
	if (!info->textures.we_texture)
	{
		printf(RED"Failed to load png for WE\n"RESET);
		exit(FAILURE);
	}
}

/*	This function loads the textures of the walls. It takes a pointer to a
	t_data structure as an argument. It loads the textures of the walls using
	the mlx_load_png function. If the textures are not loaded correctly, it
	prints an error message and exits the program. This helps to load the
	textures of the walls correctly.	*/
