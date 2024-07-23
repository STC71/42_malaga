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
		if ((*stack_a)->index <= max)
			pb(stack_a, stack_b, 1);
		else
			ra(stack_a, 1);
		// else if ((ft_find_last(stack_a) < (*stack_a)->index) 
		// && (ft_find_last(stack_b) > (*stack_b)->index))
		// 	rrr(stack_a, stack_b, 1);
		// else if ((*stack_a)->next->index < (*stack_a)->index 
		// && (*stack_b)->next->index > (*stack_b)->index)
		// 	rr(stack_a, stack_b, 1);
		// else if ((*stack_a)->next->index < (*stack_a)->index 
		// && (*stack_b)->next->index < (*stack_b)->index)
		// 	ra(stack_a, 1);
		// else if ((*stack_a)->next->index > (*stack_a)->index 
		// && (*stack_b)->next->index < (*stack_b)->index)
		// 	rb(stack_a, 1);
		// else if ((ft_find_last(stack_a) < (*stack_a)->index) 
		// && (ft_find_last(stack_b) > (*stack_b)->index))
		// 	rra(stack_a, 1);
		// // else if ((ft_find_last(stack_b) < (*stack_b)->index) 
		// // && (ft_find_last(stack_a) > (*stack_a)->index))
		// // 	rrb(stack_a, 1);
		// else if ((*stack_a)->next->index > (*stack_a)->index)
		// 	sa(stack_a, 1);
		// else if ((*stack_b)->next->index > (*stack_b)->index)
		// 	sb(stack_b, 1);
		// else if(((*stack_a)->next->index < (*stack_a)->index) 
		// && ((*stack_b)->next->index < (*stack_b)->index))
		// 	ss(stack_a, stack_b, 1);
	}
	while ((ft_stack_len(*stack_a) >= 1))
		pb(stack_a, stack_b, 1);
	ft_sort_end(stack_a, stack_b);
	// if (i--)
	// {
	// 	while (i--)
	// 	{
	// 		pb(stack_a, stack_b, 1);

	// 		// if ((*stack_b)->index < (*stack_b)->next->index 
	// 		// && ft_stack_len(*stack_b) > 1 && max > 100)
	// 		// 	rb(stack_b, 1);
	// 	}
	// 	ft_sort_end(stack_a, stack_b);
	// }
}

void	ft_sort_end(t_stack **stack_a, t_stack **stack_b)
{
	ft_sort_min(stack_a); // To find the minimum index in the stack
	while (*stack_b)
	{
		ft_find_pos_target(stack_a, stack_b); // To find the value of the target
		ft_get_cost(stack_a, stack_b); // To find the cost of the target
		ft_cheap_sort(stack_a, stack_b); // To find the cheapest way to sort the stack
	}
	if(!be_sorted(*stack_a)) 
		shifte_change(stack_a); // To find the cheapest way to sort the stack
	//while (*stack_a) // No es necesario!!!
	//{
	// 	ft_printf("stack_a: %d\n", (*stack_a)->value);
	// 	stack_a = &(*stack_a)->next;
	// }
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

// void    ft_sort_big(t_stack **stack_a, t_stack **stack_b)
// {
//     int     i;
//     int     j;
//     int     num;
//     int     max_bits;
//     int     total_elements;
//     int     pushed_elements;

//     total_elements = ft_stack_len(*stack_a);
//     max_bits = 0;
//     while ((total_elements - 1) >> max_bits != 0)
//         ++max_bits; 
//     i = 0;
//     while (i < max_bits)
//     {
//         j = 0;
//         pushed_elements = 0;
//         while (j < total_elements)
//         {
//             num = (*stack_a)->index;
//             if (((num >> i) & 1) == 1)
//                 ra(stack_a, 1);
//             else
//             {
//                 pb(stack_a, stack_b, 1);
//                 pushed_elements++;
//             }
//             j++;
//         }
//         while (pushed_elements > 0)
//         {
//             pa(stack_a, stack_b, 1);
//             pushed_elements--;
//         }
//         i++;
//     }
// }


/*
The ft_sort_big function is the main function for sorting a big stack. 
It first calculates the number of bits needed to represent the maximum 
index in the stack. Then, it iterates over each bit, shifting the numbers 
in the stack to the right position. The ra and pb functions are used to 
move the numbers to the right position, and the pa function is used to 
move the numbers back to the original stack. This process is repeated for 
each bit, resulting in a sorted stack.
The funtion finish using pa to move the numbers back to the original stack.
*/

