/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:43 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	cp;

	src_len = 0;
	cp = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize != 0)
	{
		while (cp < (dstsize - 1) && src[cp] != '\0')
		{
			dst[cp] = src[cp];
			cp++;
		}
		dst[cp] = '\0';
	}
	return (src_len);
}

/*strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
    NUL-terminating the result if dstsize is not 0.*/