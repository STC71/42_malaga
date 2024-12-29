/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:12:41 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:12:41 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

unsigned int	ft_rgb_get(char **c)
{
	unsigned int	rgb;

	if (ft_split_len(c) == 2)
	{
		rgb = ft_rgb_to_hex_split(c);
		if (rgb == 1)
			rgb = 255;
	}
	if (ft_split_len(c) == 4)
	{
		rgb = ft_rgb_to_hex(c);
		if (rgb == 1)
			rgb = 255;
	}
	return (rgb);
}

/*	This function converts RGB values provided in a string to a hexadecimal 
	value. It checks the length of the string c to determine the input format
	and calls ft_rgb_to_hex_split if the length is 2 or ft_rgb_to_hex if the
	length is 4. If the function returns 1, the value 255 is assigned to avoid
	returning the value 1, which is used to indicate an error. Finally, the
	function returns the hexadecimal value.	*/

unsigned int	ft_rgb_to_hex_split(char **c)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	hex;
	char			**rgb;

	rgb = ft_split(c[1], ',');
	if (!rgb)
	{
		printf(RED"Failed in ft_split process.\n"RESET);
		return (FAILURE);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_split_free(rgb);
	if (r > 255 || r < 1 || g > 255 || g < 1 || b > 255 || b < 1)
	{
		ft_error_color(c, r, g, b);
		return (FAILURE);
	}
	hex = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (hex);
}

/*	This function converts RGB values to a hexadecimal value. It takes the R, G,
	and B values from the string array c and converts them to integers. It then
	checks if the values are in the correct range (0-255) and converts them to a
	hexadecimal value. If the values are out of range, it prints an error 
	message and returns FAILURE.
	Inside the function, the values of the red(r), green(g), blue(b) components,
	and the alpha channel(0xFF) are combined into a single hexadecimal value. 
	This represents the color in a 32-bit space, with 8 bits for each color
	component and 8 bits for the alpha channel.
	r << 24: Shifts the value of r 24 bits to the left, placing the 8 most
	significant bits in the correct position (bits 24-31).
	g << 16: Shifts the value of g 16 bits to the left, placing the 8 most
	significant bits in the correct position (bits 16-23).
	b << 8: Shifts the value of b 8 bits to the left, placing the 8 most
	significant bits in the correct position (bits 8-15).
	0xFF: Represents the alpha channel, which is set to 0xFF (255) to make the
	color fully opaque.
	The diference between this function and ft_rgb_to_hex is that this function
	uses a string array with the RGB values separated by commas, while the other
	function uses a string array with the RGB values separated by spaces.	*/

unsigned int	ft_rgb_to_hex(char **c)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	hex;

	if (!c || !c[0] || !c[1] || !c[2] || !c[3])
		return (FAILURE);
	r = ft_atoi(c[1]);
	g = ft_atoi(c[2]);
	b = ft_atoi(c[3]);
	if (r > 255 || r < 1 || g > 255 || g < 1 || b > 255 || b < 1)
	{
		ft_error_color(c, r, g, b);
		return (FAILURE);
	}
	hex = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (hex);
}

/*	This function converts RGB values to a hexadecimal value. It takes the R, G,
	and B values from the string array c and converts them to integers. It then
	checks if the values are in the correct range (0-255) and converts them to a
	hexadecimal value. If the values are out of range, it prints an error 
	message and returns FAILURE.
	Inside the function, the values of the red(r), green(g), blue(b) components,
	and the alpha channel(0xFF) are combined into a single hexadecimal value. 
	This represents the color in a 32-bit space, with 8 bits for each color
	component and 8 bits for the alpha channel.
	r << 24: Shifts the value of r 24 bits to the left, placing the 8 most
	significant bits in the correct position (bits 24-31).
	g << 16: Shifts the value of g 16 bits to the left, placing the 8 most
	significant bits in the correct position (bits 16-23).
	b << 8: Shifts the value of b 8 bits to the left, placing the 8 most
	significant bits in the correct position (bits 8-15).
	0xFF: Represents the alpha channel, which is set to 0xFF (255) to make the
	color fully opaque.
	The diference between this function and ft_rgb_to_hex_split is that this
	function uses a string array with the RGB values separated by spaces, while
	the other function uses a string array with the RGB values separated by
	commas.	*/

uint32_t	ft_get_color(double x, double size, mlx_texture_t *txt)
{
	unsigned int	i;
	uint32_t		index;
	uint8_t			rgba[4];

	i = 0;
	if (!txt || !txt->pixels || x >= 1 || size >= 1)
		return (0);
	index = ((uint32_t)(txt->height * size) * txt->width
			+ (uint32_t)(txt->width * x)) * txt->bytes_per_pixel;
	while (i < 4)
	{
		rgba[i] = txt->pixels[index + i];
		i++;
	}
	return (ft_rgba(rgba));
}

/*	This function gets the color of a pixel of a texture based on the provided
	coordinates. It checks if the texture and the parameters are valid,
	calculates the index of the pixel in the texture, gets the RGBA values of
	the pixel, and packs the RGBA values into a single value that is returned.
	This helps to ensure that the color of the pixel of the texture is obtained
	correctly based on the provided coordinates.	*/

uint32_t	ft_color_wall(t_data *info, t_ray *ray, double size)
{
	uint32_t	c;

	if (ray->flag == 0)
	{
		if (ray->ray_dir_x > 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.ea_texture);
		if (ray->ray_dir_x < 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.we_texture);
		return (c);
	}
	else if (ray->flag == 1)
	{
		if (ray->ray_dir_y > 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.so_texture);
		if (ray->ray_dir_y < 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.no_texture);
		return (c);
	}
	return (0x33333388);
}

/*	This function gets the color of a pixel of the wall texture based on the
	direction of the ray that hits the wall. It checks if the ray hits a wall in
	the x or y axis, and calls the ft_get_color function to get e color of
	the pixel of the wall texture. It returns the color of the pixel obtained or
	a default color (0x33333388 color: dark gray) if no condition is met. This
	helps to get the color of the pixel of the wall texture correctly based on
	the direction of the ray that hits the wall.	*/
