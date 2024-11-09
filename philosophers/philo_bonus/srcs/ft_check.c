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

#include "../includes/philo_bonus.h"

int	ft_error_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (ERROR_INPUT);
	if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200)
		return (ERROR_INPUT);
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (ERROR_INPUT);
	}
	return (SUCCESS);
}

t_state	ft_how_are_you(t_data *data)
{
	t_state	state;

	sem_wait(data->philo.philo_sem);
	state = data->philo.state;
	sem_post(data->philo.philo_sem);
	return (state);
}

bool	ft_everyone_ok(void)
{
	sem_t	*death;

	death = sem_open("/death", 0, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}

void	ft_philo_dep(void)
{
	sem_open("/death", O_CREAT, 0644, 0);
}

bool	ft_rip(t_data *data)
{
	if (ft_how_are_you(data) != EATING
		&& ft_my_watch() - ft_get_last_eat(data) > data->die_time)
		return (true);
	return (false);
}
