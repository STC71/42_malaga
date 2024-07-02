/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:55:40 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:55:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_chr(int chr)
{
	write (1, &chr, 1);
	return (1);
}

/*
int	main()
{
	ft_write_chr('5');
	return (0);
}
*/
// must print: 5
// must return: 1

/* The funtion print a character to the standard output. And return 1*/