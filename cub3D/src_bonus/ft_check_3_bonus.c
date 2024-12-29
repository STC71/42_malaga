/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:11:16 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:11:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_check_pos_player(t_data *info, char **map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				c = map[i][j];
				info->player.pos_x = j + 0.5;
				info->player.pos_y = i + 0.5;
				info->player.map_x = j;
				info->player.map_y = i;
			}
			j++;
		}
		i++;
	}
	ft_get_ang(info, c);
	ft_init_ray(info);
}

/*	This function searches for the initial player position in the map, sets the
	player's coordinates and the direction they are facing.
	It takes a pointer to a t_data structure that contains the game information
	and a pointer to an array of strings that contains the map.
	The variables i and j are declared to iterate over the map and the variable
	c is declared to store the character representing the player's initial
	direction (N, S, W, E). A loop is used to iterate over each row of the map.
	Inside the loop, it is checked if the current cell (map[i][j]) contains (N,
	S, W, E). These cells represent the player's initial position and direction.
	If one of these cells is found, the character is stored in the variable c 
	and the player's coordinates and the cell they are in are set in the
	info->player structure. The ft_get_ang function is called to set the 
	player's facing direction and the ft_init_ray function is called to
	initialize the rays.
	The + 0.5 is added to the player's coordinates to place the player in the
	center of the cell.	In a cell 1 x 1 the center of the cell is (0.5, 0.5)  */

int	ft_check_end_file(char **map, int end)
{
	int	i;

	i = 0;
	while (map[end - 1][i])
	{
		if (map[end - 1][i] != ' ' && map[end - 1][i] != '1')
		{
			printf(RED"Invalid character in the last line of the map\n"RESET);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/*	This function checks if the last line of a map contains only valid 
	characters, specifically spaces and 1. If it finds an invalid character, 
	it prints an error message and returns FAILURE.	*/

int	ft_check_spaces(char **map)
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
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				res = ft_check_spaces_map(map, i, j, res);
				res = ft_check_spaces_map_2(map, i, j, res);
			}
			j++;
		}
		i++;
	}
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if there are spaces around a specified cell in a map.
	If it finds a space, it prints an error message and sets the flag (res) 
	to 1. The function checks if the current cell is not in the first row 
	(i != 0) and if the upper cell (map[i - 1][j]) is a space. If so, it prints
	an error message and sets the flag (res) to 1. The function also checks if
	the current cell is not in the last row (i != ft_split_len(map)) and if the
	lower cell (map[i + 1][j]) is a space. If so, it prints an error message and
	sets the flag (res) to 1.	*/

int	ft_check_spaces_map_2(char **map, int i, int j, int res)
{
	if (j != 0)
	{
		if (map[i][j - 1] == ' ')
		{
			ft_error_bad_spc(i, j - 1);
			res = 1;
		}
	}
	if ((size_t)j != ft_strlen(map[i]))
	{
		if (map[i][j + 1] == ' ')
		{
			ft_error_bad_spc(i, j + 1);
			res = 1;
		}
	}
	return (res);
}

/*	This function checks if there are spaces to the left or right of a specified
	cell in a map. If it finds a space, it prints an error message and sets the
	flag (res) to 1.
	The function checks if the current cell is not in the first column (j != 0)
	and if the cell to the left (map[i][j - 1]) is a space. If so, it prints an
	error message and sets the flag (res) to 1.
	The function also checks if the current cell is not in the last column
	(j != ft_strlen(map[i])) and if the cell to the right (map[i][j + 1]) is a
	space. If so, it prints an error message and sets the flag (res) to 1.	*/

int	ft_check_spaces_map(char **map, int i, int j, int res)
{
	if (i != 0)
	{
		if (map[i - 1][j] == ' ')
		{
			ft_error_bad_spc(i - 1, j);
			res = 1;
		}
	}
	if (i != ft_split_len(map))
	{
		if (map[i + 1][j] == ' ')
		{
			ft_error_bad_spc(i + 1, j);
			res = 1;
		}
	}
	return (res);
}

/*	This function checks if there are spaces to the left or right of a specified
	cell in a map. If it finds a space, it prints an error message and sets the
	flag (res) to 1.
	The function checks if the current cell is not in the first row (i != 0) and
	if the upper cell (map[i - 1][j]) is a space. If so, it prints an error
	message and sets the flag (res) to 1.
	The function also checks if the current cell is not in the last row
	(i != ft_split_len(map)) and if the lower cell (map[i + 1][j]) is a space.
	If so, it prints an error message and sets the flag (res) to 1.	*/