/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:14 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	return (res);
}

/*Reserve (with malloc(3)) and return a new string, formed by the 
	concatenation of 's1' and 's2'. 
	's1': the first string.
	's2': the string to add to 's1'.
	Return: the new string 'res' or 'NULL' if memory reservation fails.*/