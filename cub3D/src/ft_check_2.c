/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:03:47 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:03:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_imgs(char **c, int i)
{
	int	flag;

	flag = 0;
	if (ft_check_cardinal(c, i))
		flag = 1;
	if (ft_check_path(c, i))
		flag = 1;
	if (ft_check_bad_argument(c, i))
		flag = 1;
	if (ft_check_file(c[0], c[1], i))
		flag = 1;
	if (ft_check_colors(c, i))
		flag = 1;
	if (ft_check_colors_num(c, i))
		flag = 1;
	return (flag);
}

/*	This function checks a series of conditions to ensure that the input related
	to an image is valid. If any of the conditions fail, the function sets the
	flag variable to 1 to indicate that there was an error.
	- The ft_check_cardinal function checks if the first element of the string
		array c is a valid identifier.
	- The ft_check_path function checks if the second element of the string 
		array c is a valid path.
	- The ft_check_bad_argument function checks if there is an extra argument in
		the string array c.
	- The ft_check_file function checks if the texture file can be opened in
		read-only mode.
	- The ft_check_colors function checks if the RGB values are valid.
	- The ft_check_colors_num function checks if there is a correct number of
		RGB values.	*/

int	ft_check_cardinal(char **c, int line)
{
	(void)line;
	if (ft_strcmp(c[0], "NO") && ft_strcmp(c[0], "SO")
		&& ft_strcmp(c[0], "WE") && ft_strcmp(c[0], "EA")
		&& ft_strcmp(c[0], "F") && ft_strcmp(c[0], "C"))
	{
		printf(RED"Invalid identifier\n"RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the identifier is valid. It takes the string array c
	and the line number i as arguments. If the first element of the string array
	c is not "NO", "SO", "WE", "EA", "F", or "C", the function prints an error
	message and returns FAILURE. This ensures that the identifier is valid.	*/

int	ft_check_path(char **c, int i)
{
	if (!c[1])
	{
		printf(RED"Bad texture format in line: %d", i);
		printf("\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the path is valid. It takes the string array c and
	the line number i as arguments. If the second element of the string array c
	is NULL, the function prints an error message and returns FAILURE. This
	ensures that the path is not empty and has the correct format.	*/

int	ft_check_bad_argument(char **c, int i)
{
	(void)i;
	if (c && c[2] && ft_strcmp(c[0], "C")
		&& ft_strcmp(c[0], "F") && c[0][0] != '1')
	{
		printf(RED"Extra argument in file\n"RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the argument is valid. It takes the string array c
	and the line number i as arguments. If the string array c has more than 2
	elements and the first element is not "C" or "F", the function prints an
	error message and returns FAILURE. If the first element is not "C" or "F" 
	and the first character of the first element is not '1', the function prints
	an error message and returns FAILURE. If the argument is valid, the function
	returns SUCCESS. This ensures that the argument is valid and has the correct
	format and not extra arguments.	*/

int	ft_check_map_closed(t_data *info)
{
	int	res;

	res = 0;
	if (ft_check_sides(info->map.map))
		res = 1;
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the map is closed. It takes the t_data structure
	info as an argument. The function calls the ft_check_side function to check
	if the map is closed. If the map is not closed, the function returns FAILURE
	If the map is closed, the function returns SUCCESS. This ensures that the 
	map is closed and has no leaks.	*/