/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:15:14 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:15:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_first_pixel(double size, int *pixel)
{
	int	first;

	first = ((HEIGHT / 2) - (size / 2));
	if (first < 0)
	{
		*pixel = -first;
		first = 0;
	}
	return (first);
}

/*	This function calculates the first pixel to paint in the window. It takes
	the size of the wall and a pointer to an integer as arguments. It calculates
	the first pixel to paint in the window. If the first pixel is less than 0, 
	it adjusts the pixel and the first pixel to 0. Finally, it returns the first
	pixel.	*/

void	ft_paint_column(t_data *info, t_ray *ray, int x)
{
	int			i;
	int			first;
	int			pixel;
	double		size;
	uint32_t	color;

	i = 0;
	pixel = 0;
	size = ft_size_wall(ray);
	first = ft_first_pixel(size, &pixel);
	while (i++ < HEIGHT)
	{
		if (i > first && i < HEIGHT - 1)
		{
			if (ray->door_flag != 1)
				color = ft_color_wall(info, ray, (i - first + pixel) / size);
			else
				color = ft_color_door(info, ray, (i - first + pixel) / size);
			mlx_put_pixel(info->walls, x, i, color);
		}
	}
}

/*	This function paints a column of the wall in the window. It takes a pointer
	to a t_data structure, a pointer to a t_ray structure, and an integer x as
	arguments. It initializes the variables i, first, and pixel. It calculates
	the size of the wall and the first pixel to paint. It iterates over pixels
	of the window and paints the wall. If the pixel is within the range of the
	wall, it calculates the color of the pixel and paints it in the window. If
	the door flag is set, it calculates the color of the door and paints it in
	the window. Finally, it returns nothing.	*/

int	ft_paint(t_data *info)
{
	int	w;
	int	h;

	w = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			if (h < HEIGHT / 2)
				mlx_put_pixel(info->background, w, h++, info->textures.c_color);
			else
				mlx_put_pixel(info->background, w, h++, info->textures.f_color);
		}
		w++;
	}
	return (SUCCESS);
}

/*	This function paints the ceiling and the floor of the window. It initializes
	the variables w and h to iterate over the pixels of the window. It iterates
	over the pixels of the window and paints the ceiling and the floor of the
	window. If the pixel is above the middle of the window, it paints the 
	ceiling with the color of the ceiling. If the pixel is below the middle of
	the window, it paints the floor with the color of the floor. Finally, it
	returns SUCCESS.	*/

void	ft_add_text_path_2(t_data *info, char **c)
{
	if (c[0] && c[1] && !ft_strcmp(c[0], "C"))
	{
		info->textures.c_color = ft_rgb_get(c);
		info->textures.c_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "F"))
	{
		info->textures.f_color = ft_rgb_get(c);
		info->textures.f_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "DO"))
	{
		info->textures.do_path = ft_strdup(c[1]);
		info->textures.do_flag = 1;
	}
}

/*	This function adds the color of the ceiling and the floor to the t_data
	structure. It takes a pointer to a t_data structure and a string array as
	arguments. It checks if the first element of the string array is valid and
	if the second element is valid. If the first element is "C", it stores the
	color of the ceiling in the c_color of the t_data structure. If the first
	element is "F", it stores the color of the floor in the f_color of the
	t_data structure. If the first element is "DO", it stores the path of the
	door texture in the do_path of the t_data structure. This helps to add the
	color of the ceiling and the floor to the t_data structure correctly.	*/

void	ft_add_text_path(t_data *info, char **c)
{
	if (c[0] && c[1] && !ft_strcmp(c[0], "NO"))
	{
		info->textures.no_path = ft_strdup(c[1]);
		info->textures.no_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "SO"))
	{
		info->textures.so_path = ft_strdup(c[1]);
		info->textures.so_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "EA"))
	{
		info->textures.ea_path = ft_strdup(c[1]);
		info->textures.ea_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "WE"))
	{
		info->textures.we_path = ft_strdup(c[1]);
		info->textures.we_flag = 1;
	}
	ft_add_text_path_2(info, c);
}

/*	This function adds the texture paths to the t_data structure. It takes a
	pointer to a t_data structure and a string array as arguments. It checks if
	the first element of the string array is valid and if the second element is
	valid. If the first element is "NO", it stores the second element in the
	NO texture path of the t_data structure. If the first element is "SO", it
	stores the second element in the SO texture path of the t_data structure. If
	the first element is "EA", it stores the second element in the EA texture
	path of the t_data structure. If the first element is "WE", it stores the
	second element in the WE texture path of the t_data structure. If the first
	element is "C", it stores the color of the ceiling in the c_color of the
	t_data structure. If the first element is "F", it stores the color of the
	floor in the f_color of the t_data structure. This helps to add the texture
	paths to the t_data structure correctly.	*/
