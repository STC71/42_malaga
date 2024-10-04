/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:28 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;
	size_t	copy_len;

	dst_len = (size_t)ft_strlen((char *)dst);
	src_len = (size_t)ft_strlen((char *)src);
	total_len = dst_len + src_len;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	copy_len = dstsize - dst_len - 1;
	if (copy_len < src_len)
		src_len = copy_len;
	if (src_len > 0)
	{
		ft_memcpy(dst + dst_len, src, src_len);
		dst[dst_len + src_len] = '\0';
	}
	return (total_len);
}

/*strlcat() appends string src to the end of dst.  It will append at most 
    dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, 
    unless dstsize is 0 or the original dst string was longer than dstsize
    (in practice this should not happen as it means that either dstsize 
    is incorrect or that dst is not a*/