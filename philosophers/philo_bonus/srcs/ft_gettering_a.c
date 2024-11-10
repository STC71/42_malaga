/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:18:29 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:18:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

uint64_t	ft_get_start(t_data *data)
{
	return (data->start_time);
}

/* 	This code gets the starting time of the simulation.	 */

void	ft_get_last_meal(t_data *data)
{
	sem_wait(data->philo.philo_sem);
	data->philo.last_eat = ft_my_watch();
	sem_post(data->philo.philo_sem);
}

/* 	This code updates the time of the last meal for a specific philosopher. 
	It does this by first making sure only one philosopher can update this 
	information at a time (using a semaphore), then recording the current time, 
	and finally allowing other philosophers to access this information. */
