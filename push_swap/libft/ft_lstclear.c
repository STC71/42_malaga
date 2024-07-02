/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-18 08:28:31 by sternero          #+#    #+#             */
/*   Updated: 2024/04/18 19:47:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		del((*lst)-> content);
		free(*lst);
		*lst = tmp;
	}
}
/*Delete and free the given 'lst' node and all consecutive of that node, using
	the function 'del' and free(3). In the end, the pointer to the list must 
	be NULL. Parameters lst: The address of a pointer to a node. del: a 
	function pointer used to delete the content of a node.*/
