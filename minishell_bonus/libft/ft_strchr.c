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

/* The function strchr() locates the first occurrence of c (converted to a
	char) in the string pointed to by s. The terminating null character is
	considered to be part of the string; therefore if c is `\0', the functions
	locate the terminating `\0'. */

char	*ft_strchr(const char *s, int c)
{
	char	*s1;
	char	c1;
	size_t	cont;

	s1 = (char *)s;
	c1 = (char)c;
	cont = 0;
	while (s1[cont] != '\0')
	{
		if (s1[cont] == c1)
			return (&s1[cont]);
		cont++;
	}
	if (c1 == '\0')
		return (&s1[cont]);
	return (NULL);
}

/* char	*ft_strchr(const char *str, int c)

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
} */

/*The functions strchr() and strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.*/