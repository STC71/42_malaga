/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 11:41:46 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 11:41:46 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int     ft_moves(char *moves)
{
    if (!ft_strcmp(moves, "sa"))
        return (1);
    if (!ft_strcmp(moves, "sb"))
        return (2);
    if (!ft_strcmp(moves, "ss"))
        return (3);
    if (!ft_strcmp(moves, "pa"))
        return (4);
    if (!ft_strcmp(moves, "pb"))
        return (5);
    if (!ft_strcmp(moves, "ra"))
        return (6);
    if (!ft_strcmp(moves, "rb"))
        return (7);
    if (!ft_strcmp(moves, "rr"))
        return (8);
    if (!ft_strcmp(moves, "rra"))
        return (9);
    if (!ft_strcmp(moves, "rrb"))
        return (10);
    if (!ft_strcmp(moves, "rrr"))
        return (11);
    else
        return (0);
}

int     ft_made(t_stack **stack_a, t_stack **stack_b, int made)
{
    if (made == 1)
        return (sa(stack_a, 1));
    if (made == 2)
        return (sb(stack_b, 1));
    if (made == 3)
        return (ss(stack_a, stack_b, 1));
    if (made == 4)
        return (pa(stack_a, stack_b, 1));
    if (made == 5)
        return (pb(stack_a, stack_b, 1));
    if (made == 6)
        return (ra(stack_a, 1));
    if (made == 7)
        return (rb(stack_b, 1));
    if (made == 8)
        return (rr(stack_a, stack_b, 1));
    if (made == 9)
        return (rra(stack_a, 1));
    if (made == 10) 
        return (rrb(stack_b, 1));
    if (made == 11) 
        return (rrr(stack_a, stack_b, 1));  
    return (0);
}

int     ft_read_made(t_stack **stack_a, t_stack **stack_b)
{
    int     made;
    int     bad;
    char    *moves;

    made = 0;
    bad = 0;
    while (made != 0)
    {
        bad = get_next_line(0, &moves);
        if (bad == 0)
            break ;
        made = ft_moves(moves);
        if (made == 0)
        {
            free(moves);
            return (0);
        }
        if (ft_made(stack_a, stack_b, made) == 0)
        {
            free(moves);
            return (0);
        }
        free(moves);
    }
}