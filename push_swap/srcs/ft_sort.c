/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-24 17:13:18 by sternero          #+#    #+#             */
/*   Updated: 2024-06-24 17:13:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int    ft_stack_len(t_stack *stack)
{
    t_stack *tmp;
    int stack_len;

    tmp = stack;
    stack_len = 0;
    while (tmp)
    {
        stack_len++;
        tmp = tmp->next;
    }
    return (stack_len);
}

void    ft_sort(t_stack **stack_a, t_stack **stack_b)
{
    int stack_len;

    stack_len = ft_stack_len(*stack_a);
    ft_printf("stack_len: %d\n", stack_len); // stack_len is the length of the stack
    if (stack_len < 2)
        ft_error(0);
    else if (stack_len == 2 && be_sorted(*stack_a) == 0)
        sa(stack_a, 1);
    else if (stack_len == 3 && be_sorted(*stack_a) == 0)
        ft_sort_three(stack_a);
    else if ((stack_len == 4 || stack_len == 5) && be_sorted(*stack_a) == 0)
        ft_sort_five(stack_a, stack_b);
    //else if (stack_len > 5
    //    ft_sort_many(stack_a, stack_b, stack_len);
}
void    ft_sort_three(t_stack **stack)
{
    if ((*stack)->value > (*stack)->next->value 
        && (*stack)->value < (*stack)->next->next->value)
    {
        sa(stack, 1);
        ft_printf("option 1\n"); // 
    }
    else if ((*stack)->value > (*stack)->next->value 
        && (*stack)->value > (*stack)->next->next->value)
    {
        sa(stack, 1);
        rra(stack, 1);
        ft_printf("option 2\n"); // swap the first two elements and rotate the stack to the right
    }
    else if ((*stack)->value > (*stack)->next->value 
        && (*stack)->value > (*stack)->next->next->value)
    {
        ra(stack, 1);
        ft_printf("option 3\n"); // rotate the stack to the left
    }
    else if ((*stack)->value < (*stack)->next->value 
        && (*stack)->value < (*stack)->next->next->value)
    {
        sa(stack, 1);
        ra(stack, 1);
        ft_printf("option 4\n"); // swap the first two elements and rotate the stack to the left
    }
    else if ((*stack)->value < (*stack)->next->value 
        && (*stack)->value > (*stack)->next->next->value)
        rra(stack, 1);
    ft_printf("option 5\n"); // rotate the stack to the right
}

void    ft_sort_five(t_stack **stack_a, t_stack **stack_b)
{
    int len;

    len = ft_stack_len(*stack_a);
    while ((*stack_a)->value != ft_find_max(stack_a))
    {
        if (ft_find_pos_max(stack_a, ft_find_max(stack_a)) < len / 2)
            ra(stack_a, 1);
        rra(stack_a, 1);
    }
    pb(stack_a, stack_b, 1); //push max to stack b
    while ((*stack_a)->value != ft_find_min(stack_a))
    {
        if (ft_find_pos_min(stack_a, ft_find_min(stack_a)) < len / 2)
            ra(stack_a, 1);
        rra(stack_a, 1);
    }
    pb(stack_a, stack_b, 1); //push min to stack b
    ft_sort_three(stack_a); //sort the remaining three values
    while (*stack_b)
        pa(stack_a, stack_b, 1); //push the values back to stack a
    rra(stack_a, 1); //rotate the stack to the right
}

/*
This file contains the functions that sort the stack. 
The functions are used to sort the stack in ascending order. 

ft_stack_len: This function calculates the length of the stack.
It takes the address of the stack as a parameter and returns 
the length of the stack.

ft_sort: This function sorts the stack.
It takes the address of the stack as a parameter and returns nothing.
It calculates the length of the stack and calls the appropriate 
sorting function.

ft_sort_three: This function sorts the stack with three elements.
It takes the address of the stack as a parameter and returns nothing.
It compares the elements of the stack and sorts them in ascending order.

ft_sort_five: This function sorts the stack with four or five elements.
It takes the address of the stack and the address of the second stack 
as parameters and returns nothing.
It calculates the length of the stack and sorts the stack 
with four or five elements.

All calls the appropriate functions to sort the stack with three,
four or five elements.
*/