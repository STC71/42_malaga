/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 08:50:28 by sternero          #+#    #+#             */
/*   Updated: 2024-04-16 08:50:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*str;
	unsigned int	nbr;

	nbr = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen((char *)s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[nbr] != '\0')
	{
		str[nbr] = f(nbr, s[nbr]);
		nbr++;
	}
	str[nbr] = '\0';
	return (str);
}

/*To each character of the string 's', apply the function 'f' giving as 
	parameters the index of each character inside 's' and the character
	itself. Generate a new string with the result of successive use
	of 'f'. Parameters -> s: The string to iterate, f: The function to 
	apply on each character. Return value: the string created after the
	correct use of 'f' over each character or NULL if memory reservation
	fails.*/