/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:58:24 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:58:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_stack **stack_a, int print)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	*stack_a = tmp->next;
	last = *stack_a;
	while (last->next)
		last = last->next;
	last->next = tmp;
	tmp->next = NULL;
	if (print == 1)
		ft_printf("ra\n");
}

void	rb(t_stack **stack_b, int print)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	last = *stack_b;
	while (last->next)
		last = last->next;
	*stack_b = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
	if (print == 1)
		ft_printf("rb\n");
}

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	if (print)
		ft_printf("rr\n");
}

void    rr_rot(t_stack **s_a, t_stack **s_b, int *a_cost, int *b_cost)
{
	while (*a_cost > 0 && *b_cost > 0)
	{
		
		(*a_cost)--;
		(*b_cost)--;
		rr(s_a, s_b, 1);
	}
}

void	a_rot(t_stack **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			(*cost)--;
			ra(stack_a, 1);
		}
		else if (*cost < 0)
		{
			(*cost)++;
			rra(stack_a, 1);
		}
	}
}



/*ra
Rotate the 'stack a' up by one.
The first element becomes the last one.
stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*rb
Rotate the 'stack b' up by one.
The first element becomes the last one.
stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*rr
Rotate the 'stack a' and 'stack b' up by one.
The first element of each stack becomes the last one.
stack_a: the address of a pointer to the first node of the list 'a'.
stack_b: the address of a pointer to the first node of the list 'b'.
print: 1 to print the operation, 0 to not print it.
*/

/*rr_rot
Rotate the 'stack a' and 'stack b' up by one.
The first element of each stack becomes the last one.
s_a: the address of a pointer to the first node of the list 'a'.
s_b: the address of a pointer to the first node of the list 'b'.
a_cost: the number of rotations to perform on 'stack a'.
b_cost: the number of rotations to perform on 'stack b'.
print: 1 to print the operation, 0 to not print it.
*/

/*a_rot
Rotate the 'stack a' up by the number of rotations in 'cost'.
stack_a: the address of a pointer to the first node of the list 'a'.
cost: the number of rotations to perform on 'stack a'.
print: 1 to print the operation, 0 to not print it.
*/