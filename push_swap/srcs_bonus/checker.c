/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-16 13:21:36 by sternero          #+#    #+#             */
/*   Updated: 2024-06-16 13:21:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_check(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	tmp = *stack_a;
	while (tmp->next)
	{
		if (tmp->index > tmp->next->index)
		{
			ft_free(&tmp);
			ft_free_all(stack_a, stack_b);
			ft_printf("KO\n");
			exit(0);
		}
		tmp = tmp->next;
	}
	ft_free(&tmp);
	if (*stack_b)
	{
		ft_free_all(stack_a, stack_b);
		ft_printf("KO\n");
		exit(0);
	}
	ft_free_all(stack_a, stack_b);
	ft_printf("OK\n");
}

int		main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**tab;
	int		i;

	if (ac < 2)
		return (0);
	i = 0;
	tab = ft_strsplit(av[1], ' ');
	stack_a = NULL;
	stack_b = NULL;
	while (tab[i])
	{
		ft_add_stack(&stack_a, ft_atoi(tab[i]));
		i++;
	}
	ft_free_tab(tab);
	while (get_next_line(0, &tab) > 0)
	{
		ft_do_op(tab, &stack_a, &stack_b);
		ft_free_tab(tab);
	}
	ft_check(&stack_a, &stack_b);
	return (0);
}