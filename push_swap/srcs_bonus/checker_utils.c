/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-25 16:28:03 by sternero          #+#    #+#             */
/*   Updated: 2024-07-25 16:28:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

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

t_stack	*ft_checker_stacknew(int value)
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

/*
The be_nbr function is used to check if the string is a number.

The ft_checker_stacknew function is used to create a new stack.
*/