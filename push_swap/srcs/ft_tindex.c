/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tindex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-11 11:25:50 by sternero          #+#    #+#             */
/*   Updated: 2024-07-11 11:25:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack *copy_stack(t_stack *original) 
{
    t_stack *copy;
    t_stack *last;
    t_stack *temp;

    copy = NULL;
    last = NULL;
    while (original) 
    {
        temp = malloc(sizeof(t_stack));
        if (!temp)
            ft_error(1);
        temp->value = original->value;
        temp->next = NULL;
        if (last)
            last->next = temp;
        else
            copy = temp;
        last = temp;
        original = original->next;
    }
    return copy;
}

void sort_list(t_stack **list)
{
    t_stack *temp;
    t_stack *temp2;
    int aux;

    if (!list || !*list)
        return ;
    temp = *list;
    while (temp && temp->next)
    {
        temp2 = temp->next;
        while (temp2)
        {
            if (temp->value > temp2->value)
            {
                aux = temp->value;
                temp->value = temp2->value;
                temp2->value = aux;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}

int find_index(t_stack *sorted_list, int value) 
{
    int index;
    
    index = 1;
    while (sorted_list)
    {
        if (sorted_list->value == value)
            return index;
        index++;
        sorted_list = sorted_list->next;
    }
    return -1;
}

void ft_get_index(t_stack **stack_a)
{
    t_stack *copy; 
    t_stack *original;
 
    copy = copy_stack(*stack_a);
    sort_list(&copy);
    original = *stack_a;
    while (original)
    {
        original->index = find_index(copy, original->value);
        original = original->next;
    }
    while (copy)
    {
        t_stack *tmp = copy;
        copy = copy->next;
        free(tmp);
    }
}

/*
This functions finds the index of the target in the stack_a,
and assigns it with the values imputs.
*/

/*
The function *copy_stack creates a copy of the stack_a anb returns it.
The function sort_list sorts the stack_a in ascending order.
The function find_index finds the index of the target in the stack_a.
The function ft_get_index assigns the index of the target in the stack_a.
*/