/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:02:18 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:02:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				num;
	const unsigned char	*str1;
	const unsigned char	*str2;

	num = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (num < n)
	{
		if (str1[num] != str2[num])
			return (str1[num] - str2[num]);
		num++;
	}
	return (0);
}
/*The memcmp() function returns zero if the two strings are identical, 
	otherwise returns the difference between the first two differing bytes
	(treated as unsigned char values, so that `\200' is greater than `\0',
	for example). Zero-length strings are always identical.  
	This behavior is not required by C and portable code should only 
	depend on the sign of the returned value.*/