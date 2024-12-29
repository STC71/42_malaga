/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-18 14:26:51 by sternero          #+#    #+#             */
/*   Updated: 2024-12-18 14:26:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_safe(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (new);
}

/*	This function concatenates two strings and frees the memory of the original
	strings safely. It calls ft_strjoin to concatenate s1 and s2, frees the 
	memory of s1 and s2 if they are not null, and returns the new concatenated 
	string. 
	This helps to avoid memory leaks when working with dynamically allocated
	strings and ensures that the original strings are freed correctly.	*/