/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:11:28 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:11:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_check_sides(char **map)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (map[i])
	{
		if (ft_check_left_file(map[i]))
		{
			ft_error_border(i + 1, 1);
			res = 1;
		}
		if (ft_check_right_file(map[i]))
		{
			ft_error_border(i + 1, 2);
			res = 1;
		}
		i++;
	}
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the side walls of each row in the map are closed 
	with '1'. If it finds a row where the side wall is not closed it prints an
	error message and returns FAILURE.	*/

int	ft_check_left_file(char *c)
{
	int	i;

	i = 0;
	while (c[i] == ' ')
		i++;
	if (c[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the left side of a row in the map is closed. It
	takes a pointer to a string that contains the row as an argument. 
	The variable i is declared to iterate over the row. A loop is used to iterate
	over the row from left to right. Inside the loop, the variable i is 
	incremented until it finds a character different from a space. If the 
	character is not '1', the function returns FAILURE. 
	If the character is '1', the function returns SUCCESS.	*/

int	ft_check_right_file(char *c)
{
	int	i;

	i = ft_strlen(c);
	i--;
	while (c[i] == ' ')
		i--;
	if (c[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the right side of a row in the map is closed. It
	takes a pointer to a string that contains the row as an argument. 
	The variable i is declared to iterate over the row. The variable i is set
	to the length of the row minus 1. A loop is used to iterate over the row 
	from right to left. Inside the loop, the variable i is decremented until
	it finds a character different from a space. If the character is not '1',
	the function returns FAILURE. 
	If the character is '1', the function returns SUCCESS.	*/

int	ft_check_start_file(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != ' ' && map[0][i] != '1')
		{
			printf(RED"Invalid character in the first line.\n"RESET);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/*	This function checks if the first line of a map contains only valid 
	characters, specifically spaces and 1. If it finds an invalid character, 
	it prints an error message and returns FAILURE.	*/

int	ft_check_text(t_data *info, char **c, int *i, int line)
{
	if (!c[0])
	{
		ft_split_free(c);
		return (SUCCESS);
	}
	if (ft_check_imgs(c, line))
	{
		ft_add_text_path(info, c);
		ft_split_free(c);
		*i += 1;
		return (FAILURE);
	}
	ft_add_text_path(info, c);
	if (ft_strcmp(c[0], "DO"))
		*i += 1;
	ft_split_free(c);
	return (SUCCESS);
}

/*	This function checks and processes an input line related to textures in the
	map configuration file. It checks if the line is empty, calls ft_check_imgs
	to check if the line contains valid information about textures, and handles
	errors appropriately. If the line is valid, it adds the texture path to the
	info structure. Finally, it frees the memory of c, increments the index i,
	and returns the result. This helps to ensure that the texture paths are
	processed and stored correctly.	*/
