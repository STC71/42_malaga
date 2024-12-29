/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:13:24 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:13:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

/*	This function prints an error message when an invalid character is found in
	the map. It takes a pointer to an array of strings that contains the map, 
	the line number, and the column number as arguments. It prints the invalid
	character and the line and column number where it was found.	*/

void	ft_error_border(int line, int flag)
{
	if (flag == 1)
	{
		printf(RED"The left side of the map is open.\n"RESET);
		printf("Error at line: ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	if (flag == 2)
	{
		printf(RED"The right side of the map is opebn.\n"RESET);
		printf("Error at line: ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
}

/*	This function prints an error message when the side walls of a row in the 
	map are not closed. It takes the line number and a flag as arguments. If 
	the flag is 1, it prints an error message indicating that the left side of
	the map is not closed. If the flag is 2, it prints an error message
	indicating that the right side of the map is not closed.	*/

void	ft_error_bad_spc(int line, int i)
{
	printf(RED"Invalid space"RESET" in line: ");
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(".\n", 2);
}

/*	This function prints an error message when an invalid space is found in the
	map. It takes the line number and the column number as arguments. It prints
	the line and column number where the invalid space was found.	*/

void	ft_error_rgb_num(char **rgb, int i, int j, int line)
{
	printf(RED"Bad argument:\n" RESET);
	ft_putchar_fd(rgb[i][j], 2);
	ft_putstr_fd("\" in line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(". \n", 2);
}

/*	This function prints an error message when an invalid RGB value is found in
	the map. It takes a pointer to an array of strings that contains the RGB
	values, the line number, and the column number as arguments. It prints the
	invalid character and the line number where it was found.	*/
