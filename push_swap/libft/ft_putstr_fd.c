/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 10:48:33 by sternero          #+#    #+#             */
/*   Updated: 2024-04-16 10:48:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	num;

	num = 0;
	while (s[num] != '\0')
	{
		ft_putchar_fd(s[num], fd);
		num++;
	}
}
/*Outputs the string s to the given file descriptor.*/