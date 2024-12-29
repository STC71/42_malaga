/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:05:04 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:05:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_colors(char **c, int i)
{
	(void)i;
	if (ft_strcmp(c[0], "C") && ft_strcmp(c[0], "F"))
		return (SUCCESS);
	if (ft_split_len(c) == 2 && ft_check_comma(c) == 2)
		return (SUCCESS);
	else if (ft_split_len(c) == 4 && ft_check_comma(c) == 2)
		return (SUCCESS);
	else
	{
		if (ft_check_comma(c) != 2)
			printf(RED"Bad rgb format"RESET);
		if (ft_split_len(c) != 2 && ft_split_len(c) != 4)
			printf(RED"Bad rgb format"RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the color format is correct. It verifies if the
	number of commas is correct and if the number of arguments is either 2 or 4.
	If the format is incorrect, it prints an error message and returns FAILURE.
	Otherwise, it returns SUCCESS.	*/

void	ft_error_color(char **path, int r, int g, int b)
{
	printf(RED"Bad rgb value\n"RESET);
	ft_putstr_fd(path[0], 2);
	ft_putstr_fd(". ", 2);
	if (r > 255 || r < 0)
	{
		ft_putstr_fd("r = ", 2);
		ft_putnbr_fd(r, 2);
		ft_putstr_fd(". ", 2);
	}
	if (g > 255 || g < 0)
	{
		ft_putstr_fd("g = ", 2);
		ft_putnbr_fd(g, 2);
		ft_putstr_fd(". ", 2);
	}
	if (b > 255 || b < 0)
	{
		ft_putstr_fd("b = ", 2);
		ft_putnbr_fd(b, 2);
		ft_putstr_fd(".", 2);
	}
	ft_putstr_fd("\n", 2);
}

/*	This function prints an error message when the color values are invalid.
	It checks if the color values are greater than 255 or less than 0, printing
	an error message for each value that is out of range.	*/

int	ft_check_colors_num(char **c, int line)
{
	int	flag;
	int	i;
	int	j;

	i = 1;
	flag = 0;
	if (ft_strcmp(c[0], "F") && ft_strcmp(c[0], "C"))
		return (SUCCESS);
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			if (!ft_isdigit(c[i][j]) && c[i][j] != ',')
			{
				ft_error_rgb_num(c, i, j, line);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the color arguments are valid. It iterates through
	the provided string array c, checking each character to see if it is a digit
	or a comma. If it finds a character that is not a digit or a comma, it 
	prints an error message and returns FAILURE. 
	Otherwise, it returns SUCCESS.	*/

uint32_t	ft_rgba(uint8_t pixels[4])
{
	uint32_t	c;

	c = 0;
	c |= ((uint32_t)pixels[0] << 24);
	c |= ((uint32_t)pixels[1] << 16);
	c |= ((uint32_t)pixels[2] << 8);
	c |= pixels[3];
	return (c);
}

/*	This function packs the RGBA values of a pixel into a single value. It
	takes an array of 4 uint8_t values as an argument. It initializes a uint32_t
	variable c and packs the RGBA values into c. It shifts the values of the
	pixels array to the left by 24, 16, 8, and 0 bits, and then ORs the values
	together to pack them into c. Finally, it returns the packed value c (color)
	This helps to pack the RGBA values of a pixel into a single value.	*/
