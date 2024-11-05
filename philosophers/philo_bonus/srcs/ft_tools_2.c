/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 23:38:29 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 23:38:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_num_philos(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->mut_nb_philos);
	i = data->nb_philos;
	pthread_mutex_unlock(&data->mut_nb_philos);
	return (i);
}

void	ft_game_over(t_data *value)
{
	int		i;
	int		j;
	t_philo	*philos;

	i = -1;
	j = ft_num_philos(value);
	philos = value->philos;
	while (++i < j)
		ft_status(&philos[i], DIE);
}

void	ft_keep_flag(t_data *value, bool now)
{
	pthread_mutex_lock(&value->mut_keep_iter);
	value->keep_iterating = now;
	pthread_mutex_unlock(&value->mut_keep_iter);
}

void	ft_status(t_philo *philo, t_state status)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DIE)
		philo->state = status;
	pthread_mutex_unlock(&philo->mut_state);
}

/*
void	print_nb_meals_had(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mut_print);
	printf("Philo %d ate %d times\n", philo->id, philo->meals);
	pthread_mutex_unlock(&data->mut_print);
}
*/

/*
void	wait_until(uint64_t wakeup_time)
{
	int			margin;
	uint64_t	time;

	margin = 5;
	while (1)
	{
		time = ft_my_watch();
		if (wakeup_time <= time + margin)
		{
			while (wakeup_time > time)
				time = ft_my_watch();
			break ;
		}
		else
		{
			usleep(1000 * (wakeup_time - time - margin));
		}
	}
}
*/

/*
void	print_mut(t_data *data, char *msg)
{
	pthread_mutex_lock(&data->mut_print);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->mut_print);
}
*/