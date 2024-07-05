/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:05:51 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:05:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	sub_len;
	char	*s2;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen((char *)s);
	if (start >= len_s)
		return (ft_strdup(""));
	sub_len = len;
	if (start + sub_len > len_s)
		sub_len = len_s - start;
	s2 = (char *)malloc((sub_len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s + start, sub_len + 1);
	s2[sub_len] = '\0';
	return (s2);
}

/*Reserve (with malloc(3)) and return a substring of the string 's'.
The substring starts from the index 'start' and has a maximum length 'len'.*/