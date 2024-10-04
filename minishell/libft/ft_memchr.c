/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:02:09 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:02:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	let;
	size_t	num;

	str = (char *)s;
	let = (char)c;
	num = 0;
	while (num < n)
	{
		if (str[num] == let)
			return ((void *)(str + num));
		num++;
	}
	return (0);
}
/*The memchr() function returns a pointer to the byte located, 
	or NULL if no such byte exists within n bytes.*/