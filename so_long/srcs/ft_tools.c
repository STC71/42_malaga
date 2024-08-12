/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-30 20:19:21 by sternero          #+#    #+#             */
/*   Updated: 2024-07-30 20:19:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_error(char *str)
{
	ft_printf("\n\n%s", SLOW_BLINK);
	ft_printf("%s╔═╗ ╦═╗ ╦═╗ ╔═╗ ╦═╗\n", RED);
	ft_printf("%s║╣  ╠╦╝ ╠╦╝ ║ ║ ╠╦╝\n", RED);
	ft_printf("%s╚═╝ ╩╚═ ╩╚═ ╚═╝ ╩╚═%s\n", RED, RESET);
	ft_printf("%s\n", RESET);
	ft_printf("%s\n", str);
	exit(FAILURE);
}

void	ft_game_over_(void)
{
	ft_printf("\n\n%s", SLOW_BLINK);
	ft_printf("%s╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╦╔═╗╦═╗\n", RED);
	ft_printf("%s║ ╦╠═╣║║║║╣   ║ ║╚╗╔╝║╣ ╠╦╝\n", YELLOW);
	ft_printf("%s╚═╝╩ ╩╩ ╩╚═╝  ╚═╝ ╚╝ ╚═╝╩╚═%s\n", RED, RESET);
	ft_printf("%s\n\n", RESET);
}








size_t	ft_lenth(char *str)
{
	size_t	n;

	n = 0;
	while (str[n] && str[n] != '\n')
		n++;
	return (n);
}

int	ft_invalid_character(int l)
{
	if (l != FLOOR && l != WALL && l != PLAYER && l != COLLECT && l != EXIT)
		return (FAILURE);
	return (SUCCESS);
}

// void	ft_allocate_memory(t_vars *vars, t_point g_pos)
// {
// 		vars->map.grid[g_pos.y] = malloc((vars->map.g_width - 1) \
// 			* sizeof(char));
// 		vars->map.tiles[g_pos.y] = malloc((vars->map.g_width - 1) \
// 			* sizeof(t_tile));
// }

// int	ft_end_game(t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	exit(0);
// }

// /*
// The ft_map_error() function prints an error message and exits the program.
// It takes a string as a parameter, which is the error message to be printed.
// Print in red the word "Error" and reset the color. Print the error message.
// Then exit the program with a status of 1 (1: failure).

// The ft_lenth() function calculates the length of a string. Receives a string
// as a parameter. It initializes a variable n to 0. While the character in the
// string is not null and different from the newline character, it increments
// the variable n. Returns the length of the string.

// The ft_invalid_character() function checks if the character is valid. Receives
// an integer as a parameter. If the integer is different from the valid characters
// (FLOOR, WALL, PLAYER, COLLECT, EXIT), it returns FAILURE. Otherwise, it returns
// SUCCESS.

// The ft_allocate_memory() function allocates memory for the map. Receives a 
// pointer to a t_vars structure and a t_point structure as parameters. It 
// allocates memory for the grid and tiles of the map. It allocates memory for the
// grid of the map. It allocates memory for the tiles of the map.

// The ft_end_game() function ends the game. Receives a pointer to a t_vars 
// structure as a parameter. It destroys the window and exits the program.
// */