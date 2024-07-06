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

/*The new_stack() function allocates sufficient memory for a new stack, 
does the copy, and returns a pointer to it.*/