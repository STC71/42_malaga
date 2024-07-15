/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcheap_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 14:50:14 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 14:50:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void 	ft_cheap_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		a_cost;
	int		b_cost;
	int		cheap;

	tmp = *stack_b;
	cheap = INT_MAX;
	while (tmp)
	{
		if (abs(tmp->a_cost - tmp->b_cost) < cheap)
		{
			cheap = abs(tmp->a_cost - tmp->b_cost);
			a_cost = tmp->a_cost;
			b_cost = tmp->b_cost;
		}
		tmp = tmp->next;
	}
	ft_moves(stack_a, stack_b, a_cost, b_cost);
}

void	ft_get_cost(t_stack **stack_a, t_stack **stack_b)
{
	//t_stack		*tmp_a;
	t_stack		*tmp_b;
	int			len_a;
	int			len_b;

	//tmp_a = *stack_a;
	tmp_b = *stack_b;
	len_a = ft_stack_len(*stack_a);
	len_b = ft_stack_len(*stack_b);
	while (tmp_b)
	{
		tmp_b->b_cost = tmp_b->pos;
		if (tmp_b->pos > len_b / 2)
			tmp_b->b_cost = (len_b - tmp_b->pos) * -1;
		tmp_b->a_cost = tmp_b->target;
		if (tmp_b->target > len_a / 2)
			tmp_b->a_cost = (len_a - tmp_b->target) * -1;
		tmp_b = tmp_b->next;
	}
}

void	ft_moves(t_stack **a, t_stack **b, int a_cost, int b_cost)
{
	if (a_cost < 0 && b_cost < 0)
		rrr_rev(a, b, &a_cost, &b_cost);
	else if (a_cost > 0 && b_cost > 0)
		rr_rot(a, b, &a_cost, &b_cost);
	a_rot(a, &a_cost);
	b_rot(b, &b_cost);
	pa(a, b, 1);
}

/*
The ft_cheap_sort() function is used to sort the stack in the cheapest way 
	possible. With this function, we can sort the stack in the most efficient
	way possible.

The ft_get_cost() function is used to get the cost of the moves for each
	element in the stack. With this function, we can determine the cost of
	moving each element in the stack.

The ft_moves() function is used to move the elements in the stack to the
	appropriate position. With this function, we can move the elements in the
	stack to the correct position.
	And the ft_moves() function is called by the ft_cheap_sort() function to
	move the elements in the stack to the correct position.
*/