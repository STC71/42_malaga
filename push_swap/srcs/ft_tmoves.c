/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmoves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-20 15:28:25 by sternero          #+#    #+#             */
/*   Updated: 2024-07-20 15:28:25 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_move_a(t_stack **stack_a, t_stack **stack_b, int pos, int i)
{
	if (i == 1)
	{
		while (pos++ < ft_stack_len(*stack_a))
			if (*stack_b)
			{
				if ((*stack_b)->index < ft_find_last(*stack_b) 
				&& (*stack_a)->index > ft_find_last(*stack_a))
					rrr(stack_a, stack_b, 1);
				else
					rra(stack_a, 1);
			}
			else
				rra(stack_a, 1);				
	}
	else if (i == 0)	
		while (pos-- >= 1)
			ra(stack_a, 1);
}

void	ft_select_a(t_stack **stack_a, t_stack **stack_b)
{
	int			pos_a;
	int			pos_b;
	int			i;
	int			len;

	i = 0;
    len = ft_stack_len(*stack_a) / 110;
	while (i++ <= len)
	{
		pos_a = ft_find_pos_min(stack_a, i);
		if (pos_a <= len)
			break;
	}
	i = ft_stack_len(*stack_a) + 1;
	while (i-- >= (ft_stack_len(*stack_a) - len))
	{
		pos_b = ft_find_pos_min(stack_a, i);
		if (pos_b <= len)
			break;
	}
	if (pos_a < ft_stack_len(*stack_a) - pos_b)
		ft_move_a(stack_a, stack_b, pos_a, 0);
	else
		ft_move_a(stack_a, stack_b, pos_b, 1);
}
