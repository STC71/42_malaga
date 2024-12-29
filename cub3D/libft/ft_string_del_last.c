/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_del_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 14:13:48 by sternero          #+#    #+#             */
/*   Updated: 2024-10-13 14:13:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_string_del_last(char **str)
{
	char	**new;
	int		len;
	int		i;

	len = ft_string_len(str);
	new = ft_calloc(len, sizeof(char *));
	i = 0;
	while (i < len - 1)
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	ft_string_free(str);
	return (new);
}

/*	The ft_string_del_last() function deletes the last element of a string array
	Parameters:
		- str: the string array to delete the last element.
	Return value:
		The new string array without the last element.*/