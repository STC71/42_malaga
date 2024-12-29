/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-17 10:55:59 by sternero          #+#    #+#             */
/*   Updated: 2024-04-17 10:55:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		nbr;

	nbr = 0;
	while (lst != (void *)0)
	{
		lst = lst->next;
		nbr++;
	}
	return (nbr);
}
/*Counts the number of nodes in a list. 
	lst parameters: the beginning of the list. 
	Return value: The length of the list.*/