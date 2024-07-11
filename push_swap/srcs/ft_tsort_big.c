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
    int tmp;
    int len = ft_stack_len(*stack_a);

    if (len <= 1)
        return;
    ft_find_min(stack_a);
    tmp = (*stack_a)->index;
    while (*stack_a != NULL && (*stack_a)->index <= tmp)
        ra(stack_a, 0);
    while (*stack_b != NULL && (*stack_b)->index > tmp)
        rb(stack_b, 0);
    while (*stack_a!= NULL && *stack_b != NULL) 
    {
        if ((*stack_a)->index <= tmp && (*stack_b)->index > tmp) 
        {
            if ((*stack_a)->next != NULL && (*stack_a)->next->index <= tmp)
                sa(stack_a, 0);
            else
                pa(stack_a, stack_b, 0);
            if ((*stack_b)->next != NULL && (*stack_b)->next->index > tmp)
                sb(stack_b, 0);
            else
                pb(stack_a, stack_b, 0);
        } 
        else 
        {
            rra(stack_a, 0);
            rrb(stack_b, 0);
        }
    }
    ft_sort_min(stack_a, stack_b);
    ft_sort_min(stack_b, stack_a);
    while (*stack_b != NULL)
        pa(stack_a, stack_b, 0);
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
        pos = ft_find_pos_min(stack_a, ft_find_min(stack_a));
        if (pos >= ft_stack_len(*stack_a) / 2)
            while (pos++ <= ft_stack_len(*stack_a))
                rra(stack_a, 1);
        else
            while (pos--)
                ra(stack_a, 1);
        pb(stack_a, stack_b, 1);
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

