/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-19 19:42:40 by sternero          #+#    #+#             */
/*   Updated: 2024-06-19 19:42:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_stack **stack_a, int print)
{
	t_stack	*tmp;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	*stack_a = tmp->next;
	tmp->next = (*stack_a)->next;
	(*stack_a)->next = tmp;
	if (print == 1)
		ft_printf("sa\n");
}

void	sb(t_stack **stack_b, int print)
{
	t_stack	*tmp;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	*stack_b = tmp->next;
	tmp->next = (*stack_b)->next;
	(*stack_b)->next = tmp;
	if (print == 1)
		ft_printf("sb\n");
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	if (print)
		ft_printf("ss\n");
}

/*sa
Swap the first two elements of the 'stack a'.
stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*sb
Swap the first two elements of the 'stack b'.
stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*ss
Swap the first two elements of the 'stack a' and 'stack b'.
stack_a: the address of a pointer to the first node of the list 'a'.
stack_b: the address of a pointer to the first node of the list 'b'.
print: 1 to print the operation, 0 to not print it.
*/
