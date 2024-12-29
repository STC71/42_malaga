/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:04 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + 1;
	new = malloc(len);
	if (!new)
		return (NULL);
	if (n < len)
		len = n + 1;
	ft_strlcpy(new, s1, len);
	new[len - 1] = '\0';
	return (new);
}
