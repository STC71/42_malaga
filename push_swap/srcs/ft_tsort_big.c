/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tsort_big.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-06 13:26:28 by sternero          #+#    #+#             */
/*   Updated: 2024-07-06 13:26:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int    ft_pos_min(t_stack **stack_a, int pos)
{
	t_stack *tmp;
	int     post;

	if (!stack_a || !*stack_a)
		return (-1);
	post = pos;
	tmp = *stack_a;
	int min = tmp->value;
	while (tmp)
	{
		if ((tmp->value < min))
		{
			min = tmp->value;
			post = pos;
		}
		tmp = tmp->next;
		pos++;
	}
	return (post);
}

void    ft_sort_max(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	//int		mid;

	i = ft_stack_len(*stack_a);
	while (i > 3)
	{	
		//if (i % 2 == 0)
			//mid = i / 2;
		//else
			//mid = (i + 1) / 2;
		//mid = (i + 1) / 2;
		if ((*stack_a)->index <= ft_find_last(*stack_a))
		{
			pb(stack_a, stack_b, 1);
			//ft_printf("i: %d\n", i);
			i--;
		}
		else if ((*stack_a)->next->index <= ft_find_last(*stack_a))
		 	ra(stack_a, 1);
		else if ((*stack_a)->index > ft_find_last(*stack_a))
		 	rra(stack_a, 1);
	}
	if (!be_sorted(*stack_a))
		ft_sort_three(stack_a);
	ft_sort_end(stack_a, stack_b);
}

void	ft_sort_end(t_stack **stack_a, t_stack **stack_b)
{
	ft_sort_min(stack_a);
	while (*stack_b)
	{
		ft_find_pos_target(stack_a, stack_b);
		ft_get_cost(stack_a, stack_b);
		ft_cheap_sort(stack_a, stack_b);
	}
	if(!be_sorted(*stack_a)) 
		shifte_change(stack_a);
}

void	ft_moves(t_stack **stack_a, t_stack **stack_b, int a_cost, int b_cost)
{
	if (a_cost < 0 && b_cost < 0)
		rrr_rot(stack_a, stack_b, &a_cost, &b_cost);
	else if (a_cost > 0 && b_cost > 0)
		rr_rot(stack_a, stack_b, &a_cost, &b_cost);
	a_rot(stack_a, &a_cost);
	b_rot(stack_b, &b_cost);
	pa(stack_a, stack_b, 1);
}

void    ft_sort_big(t_stack **stack_a, t_stack **stack_b)
{
	int pos; 

	while (*stack_a)
	{
		pos = ft_find_pos_min(stack_a, ft_find_min(stack_a));
		if (pos >= ft_stack_len(*stack_a) / 2)
			while (pos++ <= ft_stack_len(*stack_a))
				rra(stack_a, 1);
		else
			while (pos--)
				ra(stack_a, 1);
		pb(stack_a, stack_b, 1);
	}
	ft_b_to_a(stack_a, stack_b);
}

/*
The sort_big() function sorts a stack of any size by using the push_swap algorithm.
The pos_min() function returns the position of the smallest number in the stack.

The sort_big() function sorts the stack by pushing the smallest number to stack_b and 
then sorting stack_a recursively.
*/

