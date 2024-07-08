/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-27 09:49:11 by sternero          #+#    #+#             */
/*   Updated: 2024-06-27 09:49:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int    ft_find_min(t_stack **stack)
{
    t_stack *tmp;
    int min;

    tmp = *stack;
    min = tmp->value;
    while (tmp)
    {
        if (tmp->value < min)
            min = tmp->value;
        tmp = tmp->next;
    }
    return (min);
}

int    ft_find_max(t_stack **stack)
{
    t_stack *tmp;
    int max;

    tmp = *stack;
    max = tmp->value;
    while (tmp)
    {
        if (tmp->value > max)
            max = tmp->value;
        tmp = tmp->next;
    }
    return (max);
}

int    ft_find_pos_min(t_stack **stack, int min)
{
    t_stack *tmp;
    int pos_min;

    tmp = *stack;
    pos_min = 0;
    while (tmp)
    {
        if (tmp->value == min)
            return (pos_min);
        tmp = tmp->next;
        pos_min++;
    }
    return (pos_min);
}

int    ft_find_pos_max(t_stack **stack, int max)
{
    t_stack *tmp;
    int pos_max;

    tmp = *stack;
    pos_max = 0;
    while (tmp)
    {
        if (tmp->value == max)
            return (pos_max);
        tmp = tmp->next;
        pos_max++;
    }
    return (pos_max);
}

/*
ft_find_min() returns the minimum value of the stack.
ft_find_max() returns the maximum value of the stack.
ft_find_pos_min() returns the position of the minimum value of the stack.
ft_find_pos_max() returns the position of the maximum value of the stack.
*/