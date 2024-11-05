/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 09:11:36 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 09:11:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_args(int c, char **v)
{
	if (c < 5 || c > 6 || ft_argv_num(c, v) != 0 || ft_error_argv(c, v))
		return (INPUT_ERROR);
	return (SUCCESS);
}

int	ft_error_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (INPUT_ERROR);
	if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200)
		return (INPUT_ERROR);
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (INPUT_ERROR);
	}
	return (SUCCESS);
}

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
				return (INPUT_ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

t_state	ft_how_are_you(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

void	*ft_are_you_dead(void *data)
{
	int		i;
	int		j;
	t_data	*value;
	t_philo	*philos;

	i = -1;
	value = (t_data *)data;
	philos = value->philos;
	j = ft_num_philos(value);
	while (++i < j && ft_keep_or_not(value))
	{
		if (ft_rip(&philos[i]) && ft_keep_or_not(value))
		{
			ft_writing(value, philos[i].id, DIED);
			ft_keep_flag(value, false);
			ft_game_over(value);
			break ;
		}
		if (i == j - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

