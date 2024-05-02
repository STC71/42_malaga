/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:03:48 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:03:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)

{
	int	n;

	n = 0;
	while (str[n] != '\0')
	{
		if (str[n] == (char)c)
		{
			return ((char *)(str + n));
		}
		n++;
	}
	if (str[n] == (char)c)
	{
		return ((char *)(str + n));
	}
	return (NULL);
}
/*The functions strchr() and strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.*/