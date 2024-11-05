/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 23:19:38 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 23:19:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	ft_get_start(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}

/*	The function ft_get_start() gets the start time of the program. It receives 
	a data structure as an argument. It locks the mutex of the start time, gets 
	the start time, and unlocks the mutex of the start time. Finally, it returns 
	the start time. */

uint64_t	ft_get_sleep(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_sleep_t);
	time = data->sleep_time;
	pthread_mutex_unlock(&data->mut_sleep_t);
	return (time);
}

/*	The function ft_get_sleep() gets the time to sleep of the philosopher. 
	It receives a data structure as an argument. It locks the mutex of the 
	sleeping time, gets the sleeping time, and unlocks the mutex of the sleeping 
	time. Finally, it returns the sleeping time. */
