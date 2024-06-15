/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:04 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen((char *)s1) + 1;
	s2 = (char *)malloc(len * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy (s2, s1, len);
	return (s2);
}
/*The strdup() function allocates sufficient memory for a copy of the string s1,
	does the copy, and returns a pointer to it.*/