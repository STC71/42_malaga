/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-18 09:15:56 by sternero          #+#    #+#             */
/*   Updated: 2024/04/18 19:52:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	current = lst;
	while (current)
	{
		temp = ft_lstnew(f(current->content));
		if (!temp)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, temp);
		current = current->next;
	}
	return (new_list);
}

/*Iterates the list 'lst' and applies the function 'f' to it content of each 
    node. Create a resulting list of the correct and successive application of 
    the function 'f' over each node. The 'del' function is used to delete the 
    contents of a node, if you do lack. Parameters lst: a pointer to a node.
    f: the address of a pointer to a function used in the iteration of each 
    list element. del: a function pointer used to delete the contents of a 
    node, if necessary.*/
