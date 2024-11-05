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

/*	The function ft_num_philos() gets the number of philosophers. It receives a 
	data structure as an argument. It locks the mutex of the number of 
	philosophers, gets the number of philosophers, and unlocks the mutex of the 
	number of philosophers. Finally, it returns the number of philosophers. */

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

/*	The function ft_game_over() changes the state of the philosophers to die. 
	It receives a data structure as an argument. It gets the number of 
	philosophers, the philosophers, and changes the state of the philosophers 
	to die. */

void	ft_keep_flag(t_data *value, bool now)
{
	pthread_mutex_lock(&value->mut_keep_iter);
	value->keep_iterating = now;
	pthread_mutex_unlock(&value->mut_keep_iter);
}

/*	The function ft_keep_flag() changes the flag of the data structure to keep 
	running. It receives a data structure and a boolean as arguments. It locks 
	the mutex of the flag to keep iterating, changes the flag to keep iterating, 
	and unlocks the mutex of the flag to keep iterating. It is used to stop the
	program when a philosopher dies. */

void	ft_status(t_philo *philo, t_state status)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DIE)
		philo->state = status;
	pthread_mutex_unlock(&philo->mut_state);
}

/*	The function ft_status() changes the state of the philosopher. It receives a
	philosopher and a state as arguments. It locks the mutex of the state of the
	philosopher, changes the state of the philosopher, and unlocks the mutex of
	the state of the philosopher. It is used when the philosopher is eating,
	thinking, or sleeping. */

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