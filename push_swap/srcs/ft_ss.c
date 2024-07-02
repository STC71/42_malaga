/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:48:22 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:48:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 1);
    sb(stack_b, 1);
    if (print)
        ft_printf("ss\n");
}

/*
Swap the first two elements of the 'stack a' and 'stack b'.

stack_a: the address of a pointer to the first node of the list 'a'.
stack_b: the address of a pointer to the first node of the list 'b'.
print: 1 to print the operation, 0 to not print it.
*/
