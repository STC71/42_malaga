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
	if (i >= 0)
		ft_printf("Error\n");
	exit(1);
}

void	be_nbr(char *str)
{
	char	*tmp;

	tmp = str;
	if (str == NULL)
		ft_error(0);
	
	while (*str)
	{
		if (*str == '"')
			exit(1);
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			ft_error(1);
		str++;
	}
	if (ft_atoi(tmp) > INT_MAX || ft_atoi(tmp) < INT_MIN)
		ft_error(2);
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
		return (1); //If the list is empty, it is sorted.
	tmp = stack_a;
	while (tmp->next != NULL)
	{
		if (tmp->value < tmp->next->value)
			tmp = tmp->next;
		else
			return (0); //If the list is not sorted, return 0.
	}
	return (1); //If the list is sorted, return 1.
}
t_stack		*ft_stacknew(int value)
{
	t_stack	*new;
	new = 0;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->value = value;
	new->next = NULL;
	return (new);
}

int main (int argc, char *argv[])
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_stack		*tmp;
	int		i;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	tmp = NULL;
	i = argc - 1;
	//ft_printf ("\033c"); // Is this line necessary?
	while (i > 0)
	{
		be_nbr(argv[i]);
		tmp = ft_stacknew(ft_atoi(argv[i]));
		tmp->next = stack_a;
		stack_a = tmp;
		i--;
	}
	ft_be_duplicated(stack_a);
	if (be_sorted(stack_a))
		return (0);
	ft_sort(&stack_a, &stack_b);
	ft_free_all(&stack_a, &stack_b);
	return (0);
}




// void	ft_control(char *argv[])
// {
// 	argv = ft_split(argv, " ");
// }
/*
ft_error: print an error message and return 1.
be_nbr: check if the string is a number.
be_duplicated: check if the number is duplicated.
be_sorted: check if the list is sorted.
main: check the arguments, create the list and sort it.
*/