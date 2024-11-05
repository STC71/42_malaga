/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_n_think.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:16:30 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:16:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_times_eating(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->mut_num_meals);
	res = philo->meals;
	pthread_mutex_unlock(&philo->mut_num_meals);
	return (res);
}

/*	The function ft_times_eating() gets the number of times the philosopher has
	eaten. It receives a philosopher as an argument. It locks the mutex of the 
	number of meals, gets the number of meals, and unlocks the mutex of the 
	number of meals. Finally, it returns the number of meals. */

int	ft_eating(t_philo *philo)
{
	if (get_forks(philo) != 0)
		return (FAILURE);
	ft_status(philo, EATING);
	ft_writing(philo->data, philo->id, EAT);
	ft_get_last_meal(philo);
	ft_sleep_for_eating(philo);
	ft_get_num_meals(philo);
	ft_drop_fork(philo);
	return (SUCCESS);
}

/*	The function ft_eating() is a function that is called when the philosopher 
	is eating. It receives a philosopher as an argument. If the philosopher 
	cannot get the forks, it returns a failure message. Else, it changes the
	state of the philosopher to eating, writes the message that the philosopher
	is eating, gets the last meal time of the philosopher, sleeps for the eating
	time, gets the number of meals of the philosopher, and drops the fork. 
	Finally, it returns a success message. */

int	ft_thinking(t_philo *philo)
{
	ft_status(philo, THINKING);
	if (ft_how_are_you(philo) == DIE)
		return (1);
	ft_writing(philo->data, philo->id, THINK);
	return (SUCCESS);
}

/*	The function ft_thinking() is a function that is called when the philosopher
	is thinking. It receives a philosopher as an argument. It changes the state 
	of the philosopher to thinking. If the philosopher is dead, it returns 1. 
	Else, it writes the message that the philosopher is thinking. Finally, it 
	returns a success message. */
