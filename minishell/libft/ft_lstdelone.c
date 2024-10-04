/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-18 08:15:04 by sternero          #+#    #+#             */
/*   Updated: 2024-04-18 08:15:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
}
/*Takes an 'lst' node as a parameter and releases the memory of the content 
	using the 'del' function given as a parameter, in addition to releasing 
	the node. The 'next' memory should not be freed. Parameters lst: the 
	node to release. del: a pointer to the function used to release the 
	content of the node.*/