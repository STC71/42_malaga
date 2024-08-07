/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 20:03:58 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 20:03:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_stack **stack_a, int print)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	last = *stack_a;
	while (last->next->next)
		last = last->next;
	tmp = last->next;
	last->next = NULL;
	tmp->next = *stack_a;
	*stack_a = tmp;
	if (print == 1)
		ft_printf("rra\n");
}

void	rrb(t_stack **stack_b, int print)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	last = *stack_b;
	while (last->next->next)
		last = last->next;
	tmp = last->next;
	last->next = NULL;
	tmp->next = *stack_b;
	*stack_b = tmp;
	if (print == 1)
		ft_printf("rrb\n");
}

void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	if (print == 1)
		ft_printf("rrr\n");
}

void	rrr_rot(t_stack **s_a, t_stack **s_b, int *a_cost, int *b_cost)
{
	while (*a_cost < 0 && *b_cost < 0)
	{
		(*a_cost)++;
		(*b_cost)++;
		rrr(s_a, s_b, 1);
	}
}

void	b_rot(t_stack **stack_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			(*cost)--;
			rb(stack_b, 1);
		}
		else if (*cost < 0)
		{
			(*cost)++;
			rrb(stack_b, 1);
		}
	}
}

/*
The rra funtion rotates the stack a down by one.
The rrb function rotates the stack b down by one.
The rrr function rotates both stacks down by one.
The rrr_rot function rotates both stacks down by one until the cost is 0.
The b_rot function rotates the stack b down by one until the cost is 0.
*/