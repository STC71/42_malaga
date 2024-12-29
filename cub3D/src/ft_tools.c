/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:08:45 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:08:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_split_map(t_data *info, char *map)
{
	int	res;

	res = 0;
	if (ft_check_extra(map))
		res = 1;
	if (res == 1)
	{
		free(map);
		return (FAILURE);
	}
	info->map.map = ft_split(map, '\n');
	free(map);
	if (!info->map.map)
	{
		printf(RED"Failed in ft_split at ft_split_map function.\n"RESET);
		return (FAILURE);
	}
	info->map.map_line = ft_split_len(info->map.map);
	return (SUCCESS);
}

/*	This function checks for errors in the map and, if there are no errors, 
	splits the map into lines and stores the result in the t_data structure. It
	initializes res and calls ft_check_extra to check for unwanted extra lines,
	and handles errors appropriately. If it does not find errors, it calls
	ft_split to split the map into lines and stores the number of lines in
	map_line. Finally, it returns SUCCESS if there are no errors, or FAILURE if
	there are errors. This helps to ensure that the map is processed correctly
	and does not contain errors.	*/

int	ft_split_line(char ***c, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		printf(RED"Failed reading the line.\n"RESET);
		return (FAILURE);
	}
	line = ft_del_nl(line);
	*c = ft_split(line, ' ');
	if (!c)
	{
		printf(RED"Failed in ft_split.\n"RESET);
		free(line);
		return (FAILURE);
	}
	free(line);
	return (SUCCESS);
}

/*	This function reads a line from a file, removes the \n, splits the line into
	words using a space as a delimiter, and stores the result in an array of
	strings. If the line is NULL, an error message is printed and FAILURE is
	returned.	*/

char	*ft_trim_str(char *s1, char *set)
{
	char	*new;

	new = ft_strtrim(s1, set);
	if (s1)
		free(s1);
	return (new);
}

/*	This function trims the specified characters from a string and frees the
	memory of the original string safely. It calls ft_strtrim to trim the
	characters from s1 using set as a reference, frees the memory of s1 if it is
	not null, and returns the new trimmed string. This helps to avoid memory
	leaks when working with dynamically allocated strings and ensures that the
	original string is freed correctly.	*/

void	ft_new_fd(t_data *info, int i, int *fd)
{
	int			j;
	int			k;
	char		*line;

	k = 0;
	j = ft_missing_num(info);
	if (j != 0)
	{
		close(*fd);
		*fd = open(info->file, O_RDONLY);
		if (*fd < 0)
		{
			printf(RED"Failed to open the map file."RESET);
			return ;
		}
		while (k <= i - j)
		{
			line = get_next_line(*fd);
			if (line && ft_strcmp(line, "\n"))
				k++;
			free(line);
		}
	}
}

/*	This function reopens the map file and adjusts the fd to point to the
	correct position, in case there are missing identifiers in the map config
	file. It initializes variables, checks for missing identifiers, closes and
	reopens the file if necessary, and adjusts the position in the file by
	reading lines until reaching the correct position. This ensures that the
	map file is read correctly, even if identifiers are missing.	*/
