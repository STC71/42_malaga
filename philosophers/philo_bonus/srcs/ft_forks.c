/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 23:27:51 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 23:27:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_drop_forks(t_data *data)
{
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	return (SUCCESS);
}

/*	Imagine the forks as tickets to a ride. When a philosopher is done eating, 
	they give back their two tickets (forks) to the ticket booth (semaphore), 
	allowing other philosophers to take them.
	Why is this important?
	By releasing the forks, the philosopher allows other hungry philosophers to 
	start eating. This helps prevent deadlocks, where all philosophers are 
	waiting for forks that someone else is holding.	*/

int	ft_get_forks(t_data *data)
{
	sem_wait(data->forks_sem);
	if (ft_writing(data, TAKE_FORKS))
	{
		sem_post(data->forks_sem);
		return (FAILURE);
	}
	if (data->philos_num == 1)
		return (FAILURE);
	sem_wait(data->forks_sem);
	if (ft_suspend(ft_how_are_you(data)))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	if (ft_writing(data, TAKE_FORKS))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* 	This code section is responsible for a philosopher trying to pick up two 
	forks to eat.
	Acquires a "lock" on the forks: This prevents multiple philosophers from 
		grabbing forks simultaneously.
	Checks if the philosopher should stop eating: If a termination condition is 
		met, the philosopher drops the fork and returns failure.
	Acquires the second fork: If the first attempt was successful, the 
		philosopher tries to grab the second fork.
	Checks for termination again: If the philosopher should stop, it drops both 
		forks.
	Returns success if both forks are acquired.
	In simpler terms:
	This part of the code makes sure a philosopher can only start eating when it
	has both forks. It also checks if the philosopher needs to stop eating for 
	any reason (like a time limit or a global stop signal). 	*/
