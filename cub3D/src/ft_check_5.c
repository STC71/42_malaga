/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:04:43 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:04:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_cub_ext(char *file, int *i)
{
	char	*c;

	if (!file)
		return (FAILURE);
	c = ft_strrchr(file, '.');
	if (!c || ft_strlen(c) != 4 || ft_strcmp(c, ".cub"))
	{
		printf(RED"Bad extension"RESET" must be .cub\n");
		*i = 1;
	}
	return (*i);
}

/*	This function checks if the file extension is correct. It takes a pointer to
	a string that contains the file name and a pointer to an integer as 
	arguments. The variable c is declared to store the file extension. If the 
	file name is NULL, the function returns 1. The ft_strrchr function is called
	to find the last occurrence of '.' in the file name. If the file extension
	is not found or the length of the extension is not 4 characters or the
	extension is not ".cub", an error message is printed and the flag (i) is set
	to 1. The function returns the flag (i).	*/

int	ft_check_first_last(t_data *info, char **map)
{
	int	res;

	res = 0;
	if (ft_check_start_file(map))
		res = 1;
	if (ft_check_end_file(map, info->map.map_line))
		res = 1;
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the first and last lines of the map contain only
	valid characters. It takes a pointer to a t_data structure that contains the
	game information and a pointer to an array of strings that contains the map
	as arguments. The variables i and res are declared to iterate over the map
	and store the result of the checks. It calls the ft_check_start_file
	function to check if the first line of the map contains only valid 
	characters. If the ft_check_start_file function returns FAILURE, the res 
	variable is set to 1. The function calls the ft_check_end_file function to
	check if the last line of the map contains only valid characters. If the
	ft_check_end_file function returns FAILURE, the res variable is set to 1.
	If the res variable is 1, the function returns FAILURE. 
	If the res variable is 0, the function returns SUCCESS.	*/

int	ft_check_wrongs(char c)
{
	if (c != 'N' && c != 'S' && c != 'W'
		&& c != 'E' && c != ' ' && c != '1'
		&& c != '0' && c != '\n')
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the character is valid. It takes a character as an
	argument. If the character is not 'N', 'S', 'W', 'E', ' ', '1', '0', or 
	'\n', the function returns FAILURE. If the character is valid, the function
	returns SUCCESS.	*/

int	ft_check_inside(char **map)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_check_wrongs(map[i][j]))
			{
				ft_bad_letter(map, i, j);
				res = 1;
			}
			j++;
		}
		i++;
	}
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the map contains invalid characters. It takes a
	pointer to an array of strings that contains the map as an argument. The
	variables i and j are declared to iterate over the map. A loop is used to
	iterate over each row of the map. Inside the loop, another loop is used to
	iterate over each cell of the map. If the current cell contains an invalid
	character, an error message is printed and the flag (res) is set to 1. 
	If the flag (res) is 1, the function returns FAILURE. If the flag (res) 
	is 0, the function returns SUCCESS.	*/

int	ft_check_extra(char *map)
{
	int	i;

	i = 0;
	if (!map || !map[i] || map[i] == '\n')
	{
		printf(RED"The map is missing.\n"RESET);
		return (FAILURE);
	}
	while (map[i])
	{
		if (map[i] == '\n')
		{
			i++;
			while (map[i] != '\0' && map[i] == ' ')
				i++;
			if (map[i] == '\n')
			{
				printf(RED"Extra line in map.\n"RESET);
				return (FAILURE);
			}
		}
		if (map[i] != '\0')
			i++;
	}
	return (SUCCESS);
}

/*	This function checks for unwanted extra lines in the map. It initializes a
	variable i to iterate over the characters of the map string, checks if the
	map is missing, and uses a loop to iterate over each character of the map.
	If it finds an unwanted extra line, it prints an error message and returns
	FAILURE. If it does not find extra lines, it returns SUCCESS. This helps to
	ensure that the map does not contain unwanted extra lines.	*/
