/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:05:29 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:05:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;
	int			num;

	last = NULL;
	num = 0;
	while (str[num] != '\0')
	{
		if (str[num] == (char)c)
			last = str + num;
		num++;
	}
	if (str[num] == (char)c)
		last = str + num;
	return ((char *)last);
}

/*The functions strchr() and strrchr() return a pointer to the located
	 character, or NULL if the character does not appear in the string.*/