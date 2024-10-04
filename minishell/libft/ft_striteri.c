/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 10:01:06 by sternero          #+#    #+#             */
/*   Updated: 2024-04-16 10:01:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	nbr;

	nbr = 0;
	if (s == NULL || f == NULL)
		return ;
	while (*s)
	{
		f(nbr++, s++);
	}
}
/*Applies the function f to each character of the string passed as argument, 
    and passing its index as first argument. Each character is passed by 
    address to f to be modified if necessary.*/
