/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:03:29 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:03:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*let;

	let = (unsigned char *)dest;
	while (len > 0)
	{
		*let++ = (unsigned char)c;
		len--;
	}
	return (dest);
}
/*The memset() function writes len bytes of value c (converted to an unsigned
	char) to the string b. The memset() function returns its first argument*/