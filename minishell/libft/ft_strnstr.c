/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:05:17 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:05:17 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	char	*hay;
	char	*nee;

	nlen = ft_strlen((char *)needle);
	hay = (char *)haystack;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*hay != '\0' && len >= nlen)
	{
		nee = (char *)needle;
		if (*hay == *nee && ft_strncmp(hay, nee, nlen) == 0)
			return (hay);
		hay++;
		len--;
	}
	return (NULL);
}
/*If needle is an empty string, haystack is returned; if needle occurs
	nowhere in haystack, NULL is returned; otherwise a pointer to the first
	character of the first occurrence of needle is returned.*/