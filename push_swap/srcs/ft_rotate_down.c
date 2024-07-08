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
    tmp = *stack_b;
    last = tmp;
    while (last->next->next)
        last = last->next;
    last->next->next = tmp;
    *stack_b = last->next;
    last->next = NULL;
    if (print)
        ft_printf("rrb\n");
}

void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 0);
    rb(stack_b, 0);
    if (print)
        ft_printf("rrr\n");
}

/*rra
Rotate the 'stack a' down by one.
The last element becomes the first one.
stack_a: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*rrb
Rotate the 'stack b' down by one.
The last element becomes the first one.
stack_b: the address of a pointer to the first node of the list.
print: 1 to print the operation, 0 to not print it.
*/

/*rrr
Reverse rotate the 'stack a' and 'stack b' down by one.
The last element of each stack becomes the first one.
stack_a: the address of a pointer to the first node of the list 'a'.
stack_b: the address of a pointer to the first node of the list 'b'.
print: 1 to print the operation, 0 to not print it.
*/