/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-30 20:19:21 by sternero          #+#    #+#             */
/*   Updated: 2024-07-30 20:19:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_map_error(char *str)
{
	ft_printf("\n%s", SLOW_BLINK);
	ft_printf("%s╔═╗ ╦═╗ ╦═╗ ╔═╗ ╦═╗\n", RED);
	ft_printf("%s║╣  ╠╦╝ ╠╦╝ ║ ║ ╠╦╝\n", RED);
	ft_printf("%s╚═╝ ╩╚═ ╩╚═ ╚═╝ ╩╚═%s\n", RED, RESET);
	ft_printf("%s\n", RESET);
	ft_printf("%s\n", str);
	exit(FAILURE);
}

int	ft_map_x(t_map *width)
{
	int	x;

	x = 0;
	while (width->map[x] != '\n')
		x++;
	return (x);
}

int	ft_map_y(t_map *height)
{
	int	y;

	y = 0;
	while (height)
	{
		y++;
		height = height->next;
	}
	return (y);
}

void	ft_game_over_(void)
{
	ft_printf("\n%s", SLOW_BLINK);
	ft_printf("%s╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╦╔═╗╦═╗\n", DARK_BLUE);
	ft_printf("%s║ ╦╠═╣║║║║╣   ║ ║╚╗╔╝║╣ ╠╦╝\n", DARK_YELLOW);
	ft_printf("%s╚═╝╩ ╩╩ ╩╚═╝  ╚═╝ ╚╝ ╚═╝╩╚═\n", DARK_BLUE);
	ft_printf("%s\n", RESET);
}

