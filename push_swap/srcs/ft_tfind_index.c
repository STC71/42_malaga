/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tfind_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-12 17:36:48 by sternero          #+#    #+#             */
/*   Updated: 2024-07-12 17:36:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_find_index_up(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    
    tmp = *stack_a;
    int index = 1;

    while (tmp)
    {
        if (tmp->index >= min && tmp->index <= max)
            return index;
        tmp = tmp->next;
        index++;
    }
    return -1;
}

int ft_find_index_down(t_stack **stack_a, int min, int max)
{
    t_stack *tmp;
    int reverse;
    
    reverse = 0;
    if (!stack_a || !*stack_a)
        return -1;
    tmp = *stack_a;
    while (tmp != NULL)
    {
        if (tmp->index >= min && tmp->index <= max)
            return reverse;
        tmp = tmp->next;
        reverse++;
    }
    return -1;
}

void 	ft_cheap_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		a_cost;
	int		b_cost;
	int		cheap;
	int		current_cost;

	tmp = *stack_b;
	cheap = INT_MAX;
	while (tmp)
    {
        current_cost = ft_abs(tmp->a_cost) + ft_abs(tmp->b_cost);
        if (current_cost < cheap)
        {
            cheap = current_cost;
            a_cost = tmp->a_cost;
            b_cost = tmp->b_cost;
        }
        tmp = tmp->next;
    }
	ft_moves(stack_a, stack_b, a_cost, b_cost);
}

void	ft_get_cost(t_stack **stack_a, t_stack **stack_b)
{
	//t_stack		*tmp_a;
	t_stack		*tmp_b;
	int			len_a;
	int			len_b;

	//tmp_a = *stack_a;
	tmp_b = *stack_b;
	len_a = ft_stack_len(*stack_a);
	len_b = ft_stack_len(*stack_b);
	while (tmp_b)
	{
		tmp_b->b_cost = tmp_b->pos;
		if (tmp_b->pos > len_b / 2)
			tmp_b->b_cost = (len_b - tmp_b->pos) * -1;
		tmp_b->a_cost = tmp_b->target;
		if (tmp_b->target > len_a / 2)
			tmp_b->a_cost = (len_a - tmp_b->target) * -1;
		tmp_b = tmp_b->next;
	}
}

/*
This functions finds the position of the target in the stack_a, 
and stores it in the target variable of the stack_b
*/

/*
The function ft_find_index_up finds the index of the target in 
the stack_a, and stores it in the target variable of the stack_b.
It returns the index of the target in the stack_a.
*/

/*
The function ft_find_index_down finds the index of the target in
the stack_a, and stores it in the target variable of the stack_b.
It returns the index of the target in the stack_a.
*/

/*
The function ft_cheap_sort finds the cheapest move to sort the 
stack_a, and stack_b, and executes it. It uses the ft_moves function
to execute the move.
*/

/*
The function ft_get_cost calculates the cost of each move in the 
stack_b. It stores the cost in the a_cost and b_cost variables of
the stack_b.
*/
