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

void	    pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack	*tmp;

    if (*stack_b == NULL)
        return ;
    tmp = (*stack_b)->next;
    (*stack_b)->next = *stack_a;
    *stack_a = *stack_b;
    *stack_b = tmp;
    if (print)
        ft_printf("pa\n");
}

void	    pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack	*tmp;

    if (*stack_a == NULL)
        return ;
    tmp = (*stack_a)->next;
    (*stack_a)->next = *stack_b;
    *stack_b = *stack_a;
    *stack_a = tmp;
    if (print)
        ft_printf("pb\n");
}

/*
The pa funtion takes the first element of the stack b and puts it at the 
top of the stack a. 

The pb function does the opposite.
*/