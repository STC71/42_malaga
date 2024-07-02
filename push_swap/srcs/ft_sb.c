/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:44:11 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:44:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sb(t_stack **stack_b, int print)
{
    t_stack	*tmp;

    if (!*stack_b || !(*stack_b)->next)
        return ;
    tmp = *stack_b;
    *stack_b = tmp->next;
    tmp->next = (*stack_b)->next;
    (*stack_b)->next = tmp;
    if (print)
        ft_printf("sb\n");
}

/*
Swap the first two elements of the 'stack b'.

stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/