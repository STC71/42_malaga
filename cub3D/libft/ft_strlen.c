/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:04:53 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:04:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	num;

	num = 0;
	while (str[num])
		num++;
	return (num);
}

/*The strlen() function returns the number of characters that precede the
     terminating NUL character.*/