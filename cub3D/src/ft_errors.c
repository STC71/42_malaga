/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:05:50 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:05:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_bad_letter(char **map, int line, int i)
{
	printf(RED"Bad character "RESET"\"");
	ft_putchar_fd(map[line][i], 2);
	ft_putstr_fd("\" in map at line ", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	ft_error_border(int line, int flag)
{
	if (flag == 1)
	{
		printf(RED"The left side of the map is not closed.\n"RESET);
		printf("Error at line: ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	if (flag == 2)
	{
		printf(RED"The right side of the map is not closed.\n"RESET);
		printf("Error at line: ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
}

void	ft_error_bad_spc(int line, int i)
{
	printf(RED"Invalid space"RESET" in line: ");
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	ft_error_rgb_num(char **rgb, int i, int j, int line)
{
	printf(RED"Bad argument:\n" RESET);
	ft_putchar_fd(rgb[i][j], 2);
	ft_putstr_fd("\" in line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(". \n", 2);
}
