/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:58:24 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:58:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_stack **stack_a, int print)
{
    t_stack	*tmp;
    t_stack	*last;

    if (!*stack_a || !(*stack_a)->next)
        return ;
    tmp = *stack_a;
    *stack_a = tmp->next;
    last = *stack_a;
    while (last->next)
        last = last->next;
    last->next = tmp;
    tmp->next = NULL;
    if (print)
        ft_printf("ra\n");
}

/*
Rotate the 'stack a' up by one.
The first element becomes the last one.

stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/