/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tfree.c                                         :+:      :+:    :+:   */
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
        tmp = (*stack)->next; // tmp is a pointer to the next element of the stack.
        free(*stack); // free the memory of the stack.
        *stack = tmp; // the stack is now the next element.
    }
    *stack = NULL; // the stack is now NULL.
    free(tmp); // free the memory of the pointer tmp.
}

void    ft_free_all(t_stack **stack_a, t_stack **stack_b)
{
    ft_free(stack_a);
    ft_free(stack_b);
}
/*The free() function deallocates the memory allocation for the stack pointed 
to by stack. If stack is a NULL pointer, no operation is performed.
The function free_all() frees the memory of both stacks.*/