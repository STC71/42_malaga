/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:05:04 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:05:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*	This function compares the values of s1 and s2 and returns an integer
	greater than, equal to, or less than 0, according as the string s1 is
	greater than, equal to, or less than the string s2. The comparison is
	done using unsigned characters, so that '\200' is greater than '\0'.*/