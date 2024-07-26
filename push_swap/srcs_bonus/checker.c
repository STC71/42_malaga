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

#include "../includes/checker.h"

int	ft_operations(t_stack **stack_a, t_stack **stack_b, char *operation)
{
	if (!ft_strncmp(operation, "sa\n", 3))
		sa(stack_a, 0);
	else if (!ft_strncmp(operation, "sb\n", 3))
		sb(stack_b, 0);
	else if (!ft_strncmp(operation, "ss\n", 3))
		ss(stack_a, stack_b, 0);
	else if (!ft_strncmp(operation, "pa\n", 3))
		pa(stack_a, stack_b, 0);
	else if (!ft_strncmp(operation, "pb\n", 3))
		pb(stack_a, stack_b, 0);
	else if (!ft_strncmp(operation, "ra\n", 3))
		ra(stack_a, 0);
	else if (!ft_strncmp(operation, "rb\n", 3))
		rb(stack_b, 0);
	else if (!ft_strncmp(operation, "rr\n", 3))
		rr(stack_a, stack_b, 0);
	else if (!ft_strncmp(operation, "rra\n", 4))
		rra(stack_a, 0);
	else if (!ft_strncmp(operation, "rrb\n", 4))
		rrb(stack_b, 0);
	else if (!ft_strncmp(operation, "rrr\n", 4))
		rrr(stack_a, stack_b, 0);
	else
		ft_printf("Error\n");
	return (1);
}

void	ft_be_duplicated(t_stack *stack_a)
{
	t_stack	*tmp;

	if (stack_a == NULL)
		ft_error(0);
	while (stack_a->next != NULL)
	{
		tmp = stack_a -> next;
		while (tmp != NULL)
		{
			if (stack_a->value == tmp->value)
				ft_error(0);
			tmp = tmp->next;
		}
		stack_a = stack_a->next;
	}
}

int	be_sorted(t_stack *stack_a)
{
	t_stack	*tmp;

	if (stack_a == NULL)
		return (1);
	tmp = stack_a;
	while (tmp->next != NULL)
	{
		if (tmp->value < tmp->next->value)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}

void	ft_include(t_stack **stack_a, int argc, char **argv)
{
	t_stack	*tmp;	
	int		i;

	tmp = NULL;
	i = argc - 1;
	while (i > 0)
	{
		be_nbr(argv[i]);
		tmp = ft_checker_stacknew(ft_atoi(argv[i]));
		tmp->next = *stack_a;
		*stack_a = tmp;
		i--;
	}
	ft_be_duplicated(*stack_a);
	if (be_sorted(*stack_a))
		return ;
}

int	main(int argc, char **argv)
{
	char	*operation;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc <= 1)
		return (0);
	ft_include(&stack_a, argc, argv);
	while (1)
	{
		operation = get_next_line(STDIN_FILENO);
		if (!operation)
			break ;
		if (ft_operations(&stack_a, &stack_b, operation) == 0)
			ft_free_all(&stack_a, &stack_b);
		free(operation);
	}
	if ((stack_a) && (stack_b == NULL) && (be_sorted(stack_a)))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_free_all(&stack_a, &stack_b);
	return (0);
}
