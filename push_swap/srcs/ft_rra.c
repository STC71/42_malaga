/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rra.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 20:03:58 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 20:03:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_stack **stack_a, int print)
{
    t_stack	*tmp;
    t_stack	*last;

    if (!*stack_a || !(*stack_a)->next)
        return ;
    last = *stack_a;
    while (last->next->next)
        last = last->next;
    tmp = last->next;
    last->next = NULL;
    tmp->next = *stack_a;
    *stack_a = tmp;
    if (print)
        ft_printf("rra\n");
}

/*
Rotate the 'stack a' down by one.
The last element becomes the first one.

stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/