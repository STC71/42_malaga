/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:02:29 by sternero          #+#    #+#             */
/*   Updated: 2024/04/18 19:53:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			len;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	len = 0;
	while (len < n)
	{
		dst1[len] = src1[len];
		len++;
	}
	return (dst1);
}
/*The memcpy() function copies n bytes from memory area src to memory area dst.
    If dst and src overlap, behavior is undefined.  Applications in which dst
    and src might overlap should use memmove(3) instead.*/
