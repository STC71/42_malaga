/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 20:05:04 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 20:05:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rrb(t_stack **stack_b, int print)
{
    t_stack	*tmp;
    t_stack	*last;

    if (!*stack_b || !(*stack_b)->next)
        return ;
    tmp = *stack_b;
    last = tmp;
    while (last->next->next)
        last = last->next;
    last->next->next = tmp;
    *stack_b = last->next;
    last->next = NULL;
    if (print)
        ft_printf("rrb\n");
}

/*
Rotate the 'stack b' down by one.
The last element becomes the first one.

stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/