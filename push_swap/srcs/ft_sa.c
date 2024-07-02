/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:42:40 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:42:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_stack **stack_a, int print)
{
    t_stack	*tmp;

    if (!*stack_a || !(*stack_a)->next)
        return ;
    tmp = *stack_a;
    *stack_a = tmp->next;
    tmp->next = (*stack_a)->next;
    (*stack_a)->next = tmp;
    if (print)
        ft_printf("sa\n");
}

/*
Swap the first two elements of the 'stack a'.

stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/
