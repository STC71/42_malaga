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
	int		max;

	max = (ft_stack_len(*stack_a) / 2);
	while (ft_stack_len(*stack_a) >= max + 1)
	{
		if ((*stack_a)->index <= max + 1)
			pb(stack_a, stack_b, 1);
		else
			ra(stack_a, 1);
	}
	while ((ft_stack_len(*stack_a) >= 1))
		pb(stack_a, stack_b, 1);
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

/*
The function ft_pos_min() returns the position of the minimum value 
in the stack.

The function ft_sort_max() sorts the stack_a by moving the index (values). 
It gets the half maximum values of the stack_a and moves them to the stack_b.
After that, the follows the same process with the rest of the values.
Finally, it call the function ft_sort_end() to sort the stack_b and return 
sorted all the values to the stack_a.

The function ft_sort_end() call the function ft_sort_min() to sort the stack_a.
Then, it calls the function ft_sort_min() to sort the stack_a. It go in a loop 
until the stack_b is not empty. It calls the function ft_find_pos_target() to 
find the position of the target in the stack_a, and stores it in the target
variable of the stack_b. Then, it calls the function ft_get_cost() to find the
position of the target in the stack_a, and stores it in the target variable of
the stack_b. Finally, it calls the function ft_cheap_sort() to sort the cheapest
move to sort the stack_a and stack_b.

The function ft_moves() moves the stack_a to the top of the stack_b. It gets the
cheapest move to sort the stack_a and stack_b depending on the cost of the moves.
*/
