/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:07:30 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:07:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

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
	first = ((HEIGHT / 2) - (size / 2));
	if (first < 0)
	{
		pixel = -first;
		first = 0;
	}
	while (i < HEIGHT)
	{
		if (i > first && i < HEIGHT - 1)
		{
			color = ft_color_wall(info, ray, (i - first + pixel) / size);
			mlx_put_pixel(info->walls, x, i, color);
		}
		i++;
	}
}

/*	This function paints a column of the wall. It initializes the variables i,
	first, pixel, size, and color. It calculates the size of the wall and the
	first pixel to draw. It iterates over the pixels of the column and paints
	the wall. If the pixel is within the range of the wall, it calculates the
	color of the pixel and paints it.	*/

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
}

/*	This function adds the color of the ceiling and the floor to the t_data
	structure. It takes a pointer to a t_data structure and a string array as
	arguments. It checks if the first element of the string array is valid and
	if the second element is valid. If the first element is "C", it stores the
	color of the ceiling in the c_color of the t_data structure. If the first
	element is "F", it stores the color of the floor in the f_color of the
	t_data structure. This helps to add the color of the ceiling and the floor
	to the t_data structure correctly.	*/

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
