/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 13:59:24 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 13:59:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
/*The calloc() function contiguously allocates enough space for count objects 
 	that are size bytes of memory each and returns a pointer to the allocated
	memory.  The allocated memory is filled with bytes of value zero. This 
	function return a pointer to allocated memory.*/