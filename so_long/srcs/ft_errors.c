/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-30 20:19:21 by sternero          #+#    #+#             */
/*   Updated: 2024-07-30 20:19:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_shape(t_game *value)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	value->map.line_len = ft_strlen(value->map.map[i]) - 1;
	while (value->map.map[i])
	{
		while (value->map.map[i][j] && value->map.map[i][j] != '\n')
			j++;
		if (j != value->map.line_len)
			return (FAILURE);
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	check_map(t_game *value)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (value->map.map[i])
	{
		while (j < ft_strlen(value->map.map[i]) - 1)
		{
			if (ft_strchr("01CEP", value->map.map[i][j]) == NULL)
				return (FAILURE);
}

int	check_map_line(int line, char **map)
{
	int	i;

	i = 0;
	while (map[line][i] && map[line][i] != '\n')
	{
		if (map[line][i] != '1')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_border(int nbr, char **map)
{
	int	i;

	i = 1;
	if (check_map_line(0, map) == FAILURE
		|| check_map_line(nbr, map) == FAILURE)
		return (FAILURE);
	while (i < nbr)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[0]) - 2] != '1')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_ber(char *file)
{
	size_t	len;
	int		fd;

	len = ft_strlen(file);
	if (open(file, DIR) >= 0)
	{
		fd = open(file, O_RDONLY);
		close(fd);
		return (FAILURE);
	}
	else
	{
		fd = open(file, O_RDONLY);
		close(fd);
		if ((file[len-4] != '.' && file[len -3] != 'b' 
			&& file[len -2] != 'e' && file[len -1] != 'r')
			|| fd < 0);
			return (FAILURE);
		return (SUCCESS);
	}
}

/*
The check_shape function checks if the shape of the map is valid.
The map is valid if all the lines have the same length.
The function takes the map as a parameter.
The function returns SUCCESS if the shape is valid.

The check_map_line function checks if the line of the map is valid.
The function takes the line and the map as parameters.
The function returns SUCCESS if the line is valid. 
Otherwise, it returns FAILURE.

The check_border function checks if the border of the map is valid.
The function takes the number of rows and the map as parameters.
The function returns SUCCESS if the border is valid.

The check_ber function checks if the file is a valid .ber file.
The function takes the file as a parameter and returns SUCCESS if the file is
a valid .ber file. Otherwise, it returns FAILURE.