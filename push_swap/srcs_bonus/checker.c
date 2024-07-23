/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-16 13:21:36 by sternero          #+#    #+#             */
/*   Updated: 2024-06-16 13:21:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int		ft_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*tmp;

	if (!stack_a)
		return (0);
	tmp = stack_a;
	while (tmp->next)
	{
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		ft_double(t_stack *stack_a)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (!stack_a)
		return (0);
	tmp = stack_a;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->value == tmp2->value)
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		ft_check(t_stack *stack_a, t_stack *stack_b)
{
	if (ft_sort(stack_a, stack_b) && !stack_b)
	{
		ft_printf("OK\n");
		return (1);
	}
	else
	{
		ft_printf("KO\n");
		return (0);
	}
}
