/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 17:17:18 by sternero          #+#    #+#             */
/*   Updated: 2024-07-15 17:17:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_add_pos(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		pos_a;
	int		pos_b;

	pos_a = 0;
	tmp_a = *stack_a;
	while (tmp_a)
	{
		tmp_a->pos = pos_a;
		tmp_a = tmp_a->next;
		pos_a++;
	}
	tmp_b = *stack_b;
	pos_b = 0;
	while (tmp_b)
	{
		tmp_b->pos = pos_b;
		tmp_b = tmp_b->next;
		pos_b++;
	}
	ft_free_all(&tmp_a, &tmp_b);
}

void	ft_find_pos_target(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_b;
	int		pos_b;

	tmp_b = *stack_b;
	ft_pos_target(stack_a);
	ft_pos_target(stack_b);
	pos_b = 0;
	while (tmp_b)
	{
		pos_b = ft_target(stack_a, tmp_b->index, INT_MAX, pos_b);
		tmp_b->target = pos_b;
		tmp_b = tmp_b->next;
	}
	ft_free(&tmp_b);
}

int	ft_target(t_stack **stack_a, int index, int target, int pos)
{
	t_stack	*tmp_a;

	tmp_a = *stack_a;
	while (tmp_a)
	{
		if (tmp_a->index > index && tmp_a->index < target)
		{
			target = tmp_a->index;
			pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	if (target != INT_MAX)
		return (pos);
	tmp_a = *stack_a;
	while (tmp_a)
	{
		if (tmp_a->index < target)
		{
			target = tmp_a->index;
			pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (pos);
}

void	ft_pos_target(t_stack **stack)
{
	t_stack	*tmp;
	int		pos;

	tmp = *stack;
	pos = 0;
	while (tmp)
	{
		tmp->pos = pos;
		tmp = tmp->next;
		pos++;
	}
}

/*
The ft_add_pos function is used to add the position of each element 
in the stack. 

The function ft_find_pos_target is used to find the target position 
of each element in the stack. 

The ft_target function is used to find the target position of an 
element in the stack. 

The ft_pos_target function is used to add the position of each element 
in the stack.
*/
