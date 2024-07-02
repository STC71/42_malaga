/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pa.c                                            :+:      :+:    :+:   */
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

    if (!*stack_b)
        return ;
    tmp = *stack_b;
    *stack_b = tmp->next;
    *stack_a = tmp;
    if (print)
        ft_printf("pa\n");
}

/*
Push the first element of the 'stack b' to the top of the 'stack a'.

tmp: temporary pointer to the first element of the 'stack b'.

*stack_b = tmp->next: the second element of the 'stack b' becomes 
    the first element.

*stack_a = tmp: the first element of the 'stack b' becomes the
    first element of the 'stack a'.

print: 1 to print the operation, 0 to not print it.
*/