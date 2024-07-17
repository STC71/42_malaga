/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-06 13:13:48 by sternero          #+#    #+#             */
/*   Updated: 2024-07-06 13:13:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack    *ft_new_stack(int value)
{
    t_stack	*stack_b;

    stack_b = (t_stack *)malloc(sizeof(t_stack));
    if (!stack_b)
        ft_error(1);
    stack_b->value = value;
    stack_b->next = NULL;
    return (stack_b);
}

int   ft_count_neg(t_stack **stack_a)
{
    t_stack *tmp;
    int     count;

    count = 0;
    tmp = *stack_a;
    while (tmp)
    {
        if (tmp->value < 0)
            count++;
        tmp = tmp->next;
    }
    return (count);
}

void    ft_b_to_a(t_stack **stack_a, t_stack **stack_b)
{
    while (ft_stack_len(*stack_b) > 0)
        pa(stack_a, stack_b, 1);
    ft_free(stack_b);
}

void    ft_be_good(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp_a; 
    t_stack *tmp_b;
    int value;
    int index;
    int pos;

    ft_add_pos(stack_a, stack_b);
    tmp_a = *stack_a;
    tmp_b = *stack_b;
    ft_printf ("\nstack_a\n");
    while (tmp_a)
    {
        value = tmp_a->value;
        index = tmp_a->index;
        pos = tmp_a->pos;
        ft_printf ("value del stack_a: %d - index del stack_a: %d - pos del stack_a: %d - target del stack_a: %d\n", value, index, pos, tmp_a->target); 
        tmp_a = tmp_a->next;
    }
    ft_printf ("\nstack_b\n");
    while (tmp_b)
    {
        value = tmp_b->value;
        index = tmp_b->index;
        pos = tmp_b->pos;
        ft_printf ("value del stack_b: %d - index del stack_b: %d - pos del stack_b: %d - target del stack_b: %d\n", value, index, pos, tmp_b->target);
        tmp_b = tmp_b->next;
    }
    ft_free(&tmp_a);
}

int     ft_abs(int a)
{
    if (a < 0)
        return (a * -1);
    return (a);
}

