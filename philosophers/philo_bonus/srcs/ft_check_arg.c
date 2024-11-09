/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 16:07:45 by sternero          #+#    #+#             */
/*   Updated: 2024-11-08 16:07:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_argv_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (ERROR_INPUT);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_check_args(int c, char **v)
{
	if (c < 5 || c > 6 || ft_argv_num(c, v) != 0 || ft_error_argv(c, v))
		return (ERROR_INPUT);
	return (SUCCESS);
}
