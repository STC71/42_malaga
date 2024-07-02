/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 20:02:53 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 20:02:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 0);
    rb(stack_b, 0);
    if (print)
        ft_printf("rr\n");
}

/*
Rotate the 'stack a' and 'stack b' up by one.
The first element of each stack becomes the last one.

stack_a: the address of a pointer to the first node of the list 'a'.
stack_b: the address of a pointer to the first node of the list 'b'.
print: 1 to print the operation, 0 to not print it.
*/