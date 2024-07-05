/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:05:04 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:05:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	num;

	num = 0;
	if (n == 0)
		return (0);
	while (num < n && (s1[num] || s2[num]))
	{
		if (s1[num] != s2[num])
			return ((unsigned char)s1[num] - (unsigned char)s2[num]);
		num++;
	}
	return (0);
}
/*The strcmp() and strncmp() functions return an integer greater than, 
	equal to, or less than 0, according as the string s1 is greater than, 
	equal to, or less than the string s2.  
	The comparison is done using unsigned characters, so that `\200' is 
	greater than `\0'.*/