/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 11:48:54 by sternero          #+#    #+#             */
/*   Updated: 2024-08-07 11:48:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_ber(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if ((file[len-4] != '.' && file[len -3] != 'b' 
		&& file[len -2] != 'e' && file[len -1] != 'r'))
		return (FAILURE);
	return (SUCCESS);
}

void	ft_check_empty_line(t_init game, char *line)
{
	t_map	*line;

	if (line[0] == '\n')
	{
		ft_map_error("Empty line has been detected in the file.\n");
		free(line);
		exit(FAILURE);
	}
	new_line = list_map_line(line); // ***** VOY POR AQUÍ *****
	map_add_back(game, new_line);
	free(line);
}



// int	ft_check_border(t_vars *vars)
// {
// 	size_t	y;
// 	size_t	x;

// 	y = 0;
// 	x = 0;
// 	while (x < vars->map.g_width)
// 	{
// 		if (vars->map.grid[y][x] != WALL)
// 			return (FAILURE);
// 		else if (vars->map.grid[vars->map.g_height - 1][x] != WALL)
// 			return (FAILURE);
// 		x++;
// 	}
// 	x = 0;
// 	while (y < vars->map.g_height)
// 	{
// 		if (vars->map.grid[y][x] != WALL)
// 			return (FAILURE);
// 		else if (vars->map.grid[y][vars->map.g_width - 1] != WALL)
// 			return (FAILURE);
// 		y++;
// 	}
// 	return (SUCCESS);
// }

// void	ft_check_map(t_vars *vars)
// {
// 	if (vars->start_found <= 0)
// 		ft_error("Missing starting position on the map.");	
// 	if (vars->start_found > 1)
// 		ft_error("There can be only one starting position.");	
// 	if (vars->collectibles <= 0)
// 		ft_error("No collectibles found on the map.");
// 	if (vars->map.collectibles_possible != vars->collectibles)
// 		ft_error("No access to all collectibles on the map.");
// 	if (vars->exit_found <= 0)
// 		ft_error("No exit found on map.");
// 	if (vars->exit_found > 1)
// 		ft_error("There can only be one way out.");	
// 	if (!vars->map.exit_possible)
// 		ft_error("The exit is not accessible.");
// }

// void	ft_check_elements(t_vars *vars, char c, t_point pos)
// {
// 	if (c == PLAYER)
// 	{
// 		vars->start_found++;
// 		vars->gamer.pos = pos;
// 		vars->gamer.start_pos = pos;
// 	}
// 	else if (vars->map.grid[pos.y][pos.x] == COLLECT)
// 		vars->collectibles++;
// 	else if (vars->map.grid[pos.y][pos.x] == EXIT)
// 		vars->exit_found++;
// }

// /*
// The check_ber() function checks if the file is a valid .ber file.
// It takes a string as a parameter and returns SUCCESS if the file is a valid 
// .ber file, otherwise it returns FAILURE.

// The check_border() function checks the border of the map. It receives a pointer
// to the structure t_vars. The function initializes the y and x variables to 0.
// The function checks if the first row and the last row of the map are walls. If
// the first row and the last row of the map are not walls, the function returns
// FAILURE. The function checks if the first column and the last column of the map
// are walls. If the first column and the last column of the map are not walls, the
// function returns FAILURE. If everything is correct, the function returns SUCCESS.

// The check_map() function checks the map. If the start_found variable is less
// than or equal to 0, the function calls the ft_error() function with the
// message "Missing starting position on the map.". If the start_found variable
// is greater than 1, the function calls the ft_error() function with the
// message "There can be only one starting position.". If the collectibles
// variable is less than or equal to 0, the function calls the ft_error()
// function with the message "No collectibles found on the map.". If the
// collectibles variable is different from the collectibles_possible variable,
// the function calls the ft_error() function with the message "No access
// to all collectibles on the map.". If the exit_found variable is less than or
// equal to 0, the function calls the ft_error() function with the message
// "No exit found on map.". If the exit_found variable is greater than 1, the
// function calls the ft_error() function with the message "There can only
// be one way out.". If the exit_possible variable is 0, the function calls the
// ft_error() function with the message "The exit is not accessible.".

// The check_elements() function checks the elements of the map. It receives
// a pointer to the structure t_vars, a character, and a point. If the character
// is PLAYER, the function increments the start_found variable, assigns the
// position of the player to the position received, and assigns the position of
// the player to the start_pos variable. If the character is EXIT, the function
// increments the exit_found variable. If the character is COLLECT, the function
// increments the collectibles variable.
// */
