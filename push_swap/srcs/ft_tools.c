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
/*
void    ft_get_index(t_stack **stack_a)
{
    t_stack *tmp;
    t_stack *tmp2;
    int     index;

    tmp2 = *stack_a;
    while (tmp2 != NULL)
    {
        index = 0;
        tmp = tmp2;
        while (tmp)
        {
            if (tmp->value > (tmp2)->value)
                index++;
            tmp = tmp->next;
        }
        (tmp2)->index = index;
        tmp2 = (tmp2)->next;
    }
}
*/
/*
The new_stack() function allocates sufficient memory for a new stack, 
does the copy, and returns a pointer to it.
*/

/*
The count_neg() function counts the number of negative numbers in the stack,
and returns the count.
*/

/*
The get_index() function assigns an index to each element of the stack.
The order of index is the same as the order of the elements in the stack.
*/
