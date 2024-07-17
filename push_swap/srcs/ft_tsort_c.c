/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tsort_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 14:15:58 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 14:15:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_min(t_stack **stack)
{
	int		max;

	if (be_sorted(*stack))
		return ;
	max = ft_hi_index(*stack);
	if ((*stack)->index == max)
		ra(stack, 1);
	else if ((*stack)->next->index == max)
		rra(stack, 1);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack, 1);
}

void	shifte_change(t_stack **stack_a)
{
	int	low_pos;
	int	len;

	len = ft_stack_len(*stack_a);
	low_pos = ft_low_index(stack_a);
	if (low_pos > len / 2)
	{
		while (low_pos < len)
		{
			rra(stack_a, 1);
			low_pos++;
		}
	}
	else
	{
		while (low_pos > 0)
		{
			ra(stack_a, 1);
			low_pos--;
		}
	}
}

int	ft_low_index(t_stack **stack)
{
	t_stack	*tmp;
	int		low_index;
	int		low_pos;

	tmp = *stack;
	low_index = INT_MAX;
	ft_pos_target(stack);
	low_pos = tmp->pos;
	while (tmp)
	{
		if (tmp->index < low_index)
		{
			low_index = tmp->index;
			low_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (low_pos);
}

int	ft_hi_index(t_stack *stack)
{
	int		index;

	index = stack->index;
	while (stack)
	{
		if (stack->index > index)
			index = stack->index;
		stack = stack->next;
	}
	return (index);
}