/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 18:13:40 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 18:13:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;
	char	*res;
	size_t	n1;
	size_t	last;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	n1 = 0;
	while (n1 < len_s1 && ft_strchr(set, s1[n1]) != (void *)0)
		n1++;
	last = len_s1;
	while (last > n1 && ft_strchr(set, s1[last - 1]) != (void *)0)
		last--;
	len = last - n1;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1 + n1, len + 1);
	return (res);
}
/*Remove all characters from the string 'set' from the beginning and 
	the end of 's1', until find a character not belonging to 'set'. The
	resulting string is returned with a reservation of malloc, or 'NULL'.*/
