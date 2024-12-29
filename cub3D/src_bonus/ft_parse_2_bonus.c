/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:15:52 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:15:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_get_map(t_data *info, int fd)
{
	char	*line;
	char	*map;

	line = NULL;
	map = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		printf(RED"Failed reading map line.\n"RESET);
		return (FAILURE);
	}
	map = ft_new_str(line, fd);
	if (!map)
		return (FAILURE);
	map = ft_trim_str(map, "\n");
	if (!map)
	{
		printf(RED"Failed in ft_trim_str process.\n"RESET);
		return (FAILURE);
	}
	if (ft_split_map(info, map))
		return (FAILURE);
	return (SUCCESS);
}

/*	This function reads the content of a map file, processes it, and stores it
	in the t_data structure. It initializes the variables line and map, and
	calls the get_next_line function to read the first line of the file. If the
	get_next_line function returns NULL, it prints an error message and returns
	FAILURE. It calls the ft_new_str function to read all the lines of the file
	and concatenate them into one string. If the ft_new_str function returns
	NULL, it returns FAILURE. It calls the ft_trim_str function to remove the \n
	from the map string. If the ft_trim_str function returns NULL, it prints an
	error message and returns FAILURE. It calls the ft_split_map function to
	split the map string into lines and store the result in the t_data
	structure. If the ft_split_map function returns FAILURE, it returns FAILURE.
	If everything is done correctly, it returns SUCCESS.	*/

char	*ft_new_str(char *c, int fd)
{
	char	*map;

	map = NULL;
	while (c)
	{
		if (!c)
		{
			printf(RED"Failed reading map line.\n"RESET);
			return (NULL);
		}
		map = ft_strjoin_safe(map, c);
		if (!map)
		{
			printf(RED"Failed in ft_strjoin_safe process.\n"RESET);
			return (NULL);
		}
		c = get_next_line(fd);
	}
	return (map);
}

/*	This function reads all the lines of a map file and concatenates them into
	one. If an error occurs during the process, an error message is printed and
	NULL is returned. If everything is done correctly, it returns the map string
	that contains all the lines of the map file concatenated. This helps to
	process the content of the map file efficiently and safely.	*/

int	ft_players_count(char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

/*	This function counts the number of players in the map. It takes a pointer to
	an array of strings that contains the map as an argument. The variables i, j
	and k are declared to iterate over the map and count the number of players.
	A loop is used to iterate over each row of the map. Inside the loop, another
	loop is used to iterate over each cell of the map. If the current cell
	contains (N, S, W, E), the variable k is incremented. After iterating over
	the entire map, the function returns the number of players.	*/

int	ft_players_num(char **map)
{
	int	i;

	i = ft_players_count(map);
	if (i == 0)
	{
		printf(RED"Missing player in map.\n"RESET);
		return (FAILURE);
	}
	if (i > 1)
	{
		printf(RED"Too many players in map."RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	This function checks if the number of players in the map is correct.
	First, the function ft_players_count is called to count the number of
	players in the map. If the number of players is 0, an error message is
	printed and FAILURE is returned. If the number of players is greater than 1,
	an error message is printed and FAILURE is returned. If the number of 
	players is correct, SUCCESS is returned.	*/

void	ft_door_ident(t_data *info)
{
	if (info->textures.do_flag != 1)
	{
		printf("Detected door in map and, ");
		printf(RED"but \"DO\" "RESET"identifier is missing\n");
		info->textures.do_error = 1;
		return ;
	}
}

/*	This function checks if there is a door in the map and if the "DO"
	identifier is missing. It takes a pointer to a t_data structure that
	contains the game information as an argument. If the door flag is not set,
	an error message is printed and the door error flag is set to 1. This helps
	to identify if there is a door in the map and if the "DO" identifier is
	missing.	*/
