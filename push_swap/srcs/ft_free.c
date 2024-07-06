/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-06 12:59:28 by sternero          #+#    #+#             */
/*   Updated: 2024-07-06 12:59:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    ft_free(t_stack **stack)
{
    t_stack	*tmp;

    if (*stack == NULL)
        return ;
    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
    *stack = NULL;
}

void    ft_free_all(t_stack **stack_a, t_stack **stack_b)
{
    ft_free(stack_a);
    ft_free(stack_b);
}
/*The free() function deallocates the memory allocation for the stack pointed 
to by stack. If stack is a NULL pointer, no operation is performed.
The function free_all() frees the memory of both stacks.*/