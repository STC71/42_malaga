/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 17:17:18 by sternero          #+#    #+#             */
/*   Updated: 2024-07-15 17:17:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    ft_add_pos(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp_a;
    t_stack *tmp_b;
    int     pos_a;
    int     pos_b;

    pos_a = ft_stack_len(*stack_a);
    tmp_a = *stack_a;
    while (tmp_a)
    {
        tmp_a->pos = pos_a;
        tmp_a = tmp_a->next;
        pos_a--;
    }
    tmp_b = *stack_b;
    pos_b = ft_stack_len(*stack_b);
    while (tmp_b)
    {
        tmp_b->pos = pos_b;
        tmp_b = tmp_b->next;
        pos_b--;
    }
    ft_free_all(&tmp_a, &tmp_b);
}

/*
The function ft_add_pos() assigns the position of each element in the stack. 
It takes two arguments: a pointer to a pointer to a t_stack structure and a 
pointer to a pointer to a t_stack structure. 
The function assigns the position of each element in the stack by iterating 
through the stack and assigning the position of each element in the stack. 
The function then frees the memory allocated for the temporary variables 
tmp_a and tmp_b using the ft_free_all() function.
*/