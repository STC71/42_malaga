/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tsort_big.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-06 13:26:28 by sternero          #+#    #+#             */
/*   Updated: 2024-07-06 13:26:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int    ft_pos_min(t_stack **stack_a, int pos)
{
    t_stack *tmp;
    int     post;

    if (!stack_a || !*stack_a)
        return (-1);
    post = pos;
    tmp = *stack_a;
    int min = tmp->value;
    while (tmp)
    {
        if ((tmp->value < min))
        {
            min = tmp->value;
            post = pos;
        }
        tmp = tmp->next;
        pos++;
    }
    return (post);
}

void    ft_sort_min(t_stack **stack_a, t_stack **stack_b)
{
    int pos;

    while (*stack_a)
    {
        pos = ft_pos_min(stack_a, 0);
        while (pos != 0)
        {
            ra(stack_a, 1);
            pos--;
        }
        pb(stack_a, stack_b, 1);
    }
    while (*stack_b)
        pa(stack_a, stack_b, 1);
}

void   ft_sort_max(t_stack **stack_a, t_stack **stack_b)
{
    int pos;

    while (*stack_a)
    {
        pos = ft_pos_min(stack_a, 0);
        while (pos != 0)
        {
            ra(stack_a, 1);
            pos--;
        }
        pb(stack_a, stack_b, 1);
    }
    while (*stack_b)
        pa(stack_a, stack_b, 1);
}

void    ft_sort_big(t_stack **stack_a, t_stack **stack_b)
{
    int pos;

    while (*stack_a)
    {
        pos = ft_pos_min(stack_a, 0);
        while (pos != 0)
        {
            ra(stack_a, 1);
            pos--;
        }
        pb(stack_a, stack_b, 1);
        ft_sort_big(stack_a, stack_b);
    }
    while (*stack_b)
        pa(stack_a, stack_b, 1);
}

/*
The sort_big() function sorts a stack of any size by using the push_swap algorithm.
The pos_min() function returns the position of the smallest number in the stack.

The sort_big() function sorts the stack by pushing the smallest number to stack_b and 
then sorting stack_a recursively.
*/

