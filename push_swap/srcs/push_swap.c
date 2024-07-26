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

void	be_nbr(char *str)
{
	long	nbr;
	int		neg;

	nbr = 0;
	neg = 0;
	if (*str == '-' || *str == '+')
	{
		neg = (*str == '-');
		str++;
	}
	if (!*str)
		ft_error(0);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			ft_error(0);
		if (*str == '+')
			str++;
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	if (neg)
		nbr = -nbr;
	if (nbr > INT_MAX || nbr < INT_MIN)
		ft_error(0);
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

t_stack	*ft_stacknew(int value)
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

int	main(int argc, char *argv[])
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_stack		*tmp;
	int			i;

	if (argc <= 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	tmp = NULL;
	i = argc - 1;
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

/*
The be_nbr function checks if the given string is a valid number. It calls 
the ft_error function if the string is not a valid number.

The ft_be_duplicated function checks if there are any duplicate values 
in the stack. It calls the ft_error function if there are any duplicates.

The be_sorted function checks if the stack is already sorted. It returns 1
if the stack is sorted, otherwise it returns 0.

The ft_stacknew function creates a new stack with the given value.

The main function takes the arguments from the command line and creates
a stack with the given values. It then checks if the stack is sorted, and
calls the ft_sort function to sort the stack. Finally, it frees the memory
used by the stacks.
*/