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

t_stack	*ft_new_stack(int value)
{
	t_stack	*stack_b;

	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_b)
		ft_error(1);
	stack_b->value = value;
	stack_b->next = NULL;
	return (stack_b);
}

int	ft_count_neg(t_stack **stack_a)
{
	t_stack	*tmp;
	int		count;

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

void	ft_b_to_a(t_stack **stack_a, t_stack **stack_b)
{
	while (ft_stack_len(*stack_b) > 0)
		pa(stack_a, stack_b, 1);
	ft_free(stack_b);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

void	ft_error(int i)
{
	if (i < 1)
		ft_printf("Error\n");
	exit(1);
}

/*
The *ft_new_stack function creates a new stack with the given value.
The ft_count_neg function counts the number of negative values in the stack.
The ft_b_to_a function moves all values from stack b to stack a.
The ft_abs function returns the absolute value of a given integer.
The ft_error function prints "Error" when the value of i is less than 1.
*/