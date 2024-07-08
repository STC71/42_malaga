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
    if (print)
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
    if (print)
        ft_printf("rb\n");
}

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 0);
    rb(stack_b, 0);
    if (print)
        ft_printf("rr\n");
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