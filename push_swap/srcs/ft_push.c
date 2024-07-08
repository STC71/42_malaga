/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:51:05 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:51:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack	*tmp;

    tmp = NULL;
    if (!*stack_b)
        return ;
    tmp = *stack_b; 
    *stack_b = (*stack_b)->next;
    *stack_a = tmp;
    if (print)
        ft_printf("pa\n");
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack	*tmp;

    tmp = NULL;
    if (!*stack_a)
        return ;
    tmp = *stack_a;
    *stack_a = (*stack_a)->next;
    *stack_b = tmp;
    if (print)
        ft_printf("pb\n");
}

/*
Push the first element of the 'stack b' to the top of the 'stack a'.
t_stack *tmp: a pointer to the first element of the 'stack b'.
if (!*stack_b): if the 'stack b' is empty, return.
tmp = *stack_b: the first element of the 'stack b' is now the first
    element of the 'stack b' in the pointer tmp.
*stack_b = tmp->next: the first element of the 'stack b' is now the
    second element.
print: 1 to print the operation, 0 to not print it.
*/

/*
Push the first element of the 'stack a' to the top of the 'stack b'.
t_stack *tmp: a pointer to the first element of the 'stack a'.
if (!*stack_a): if the 'stack a' is empty, return.
tmp = *stack_a: the first element of the 'stack a' is now the first
    element of the 'stack a' in the pointer tmp.
*stack_a = tmp->next: the first element of the 'stack a' is now the
    second element.
print: 1 to print the operation, 0 to not print it.
*/