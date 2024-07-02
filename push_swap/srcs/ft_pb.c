/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:55:55 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:55:55 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack	*tmp;

    if (!*stack_a)
        return ;
    tmp = *stack_a;
    *stack_a = tmp->next;
    *stack_b = tmp;
    if (print)
        ft_printf("pb\n");
}

/*
Push the first element of the 'stack a' to the top of the 'stack b'.

tmp: temporary pointer to the first element of the 'stack a'.

*stack_a = tmp->next: the second element of the 'stack a' becomes 
    the first element.

*stack_b = tmp: the first element of the 'stack a' becomes the 
    first element of the 'stack b'.

print: 1 to print the operation, 0 to not print it.
*/