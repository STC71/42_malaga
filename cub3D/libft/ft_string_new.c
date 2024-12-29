/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 14:23:44 by sternero          #+#    #+#             */
/*   Updated: 2024-10-13 14:23:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_string_new(char *str)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[0] = ft_strdup(str);
	if (!new[0])
	{
		free(new);
		return (NULL);
	}
	new[1] = NULL;
	return (new);
}
