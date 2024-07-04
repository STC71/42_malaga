/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-16 13:14:36 by sternero          #+#    #+#             */
/*   Updated: 2024-06-16 13:14:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_error(int i)
{
	if (i == 1)
		ft_printf("Error: invalid character,\n");
	if (i == 2)
		ft_printf("Error: number out of range,\n");
	if (i == 3)
		ft_printf("Error: duplicated number,\n");
	ft_printf("       try again please...\n");
	exit(1);
}

void	be_nbr(char *str)
{
	if (!str || !ft_isdigit(*str))
		ft_error(1);
	if ((*str == '-' || *str == '+' || *str == ' ') && !ft_isdigit(*str++))
		ft_error(1);
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) <= -2147483648)
		ft_error(2);
}

void	ft_be_duplicated(t_stack *stack_a)
{
	t_stack	*tmp;

	if (stack_a == NULL)
		ft_error(0);
	while (stack_a->next != NULL)
	{
		tmp = stack_a->next;
		while (tmp != NULL)
		{
			if (stack_a->value == tmp->value)
				ft_error(3);
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
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
t_stack		*ft_stacknew(int value)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->value = value;
	new->next = NULL;
	return (new);
}

int main (int argc, char *argv[])
{
	t_stack		*stack_a;
	int		i;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	i = 1;
	while (argv[i])
		stack_a = ft_stacknew(ft_atoi(argv[i++]));
	ft_be_duplicated(stack_a);
	if (be_sorted(stack_a))
		return (0);
	ft_sort(stack_a, NULL);
	return (0);
}

/*
ft_error: print an error message and return 1.
be_nbr: check if the string is a number.
be_duplicated: check if the number is duplicated.
be_sorted: check if the list is sorted.
main: check the arguments, create the list and sort it.
*/