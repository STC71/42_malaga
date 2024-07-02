/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 20:01:06 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 20:01:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rb(t_stack **stack_b, int print)
{
    t_stack	*tmp;
    t_stack	*last;

    if (!*stack_b || !(*stack_b)->next)
        return ;
    tmp = *stack_b;
    last = *stack_b;
    while (last->next)
        last = last->next;
    *stack_b = tmp->next;
    tmp->next = NULL;
    last->next = tmp;
    if (print)
        ft_printf("rb\n");
}

/*
Rotate the 'stack b' up by one.
The first element becomes the last one.

stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/