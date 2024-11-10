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

#include "../includes/philo_bonus.h"

void	ft_delay_even(t_data *data)
{
	if (data->philo.id % 2 == 0)
		ft_delay(data->eat_time - 10);
}

/* 	This code checks if a philosopher has an even number ID. If so, it makes the
	philosopher wait for a short time before starting to eat. This is done to 
	prevent all philosophers from grabbing forks at the same time and causing a 
	deadlocK.	*/

bool	ft_suspend(t_state	state)
{
	if (state == DIE || state == FULL || state == FINISHED)
		return (true);
	return (false);
}

/* 	In simpler terms, this function acts as a "stop signal" for the philosopher.
	If the philosopher is dead, full, or the simulation is over, it tells the 
	philosopher to stop what it's doing.	*/

void	ft_status(t_data *data, t_state state)
{
	sem_wait(data->philo.philo_sem);
	data->philo.state = state;
	sem_post(data->philo.philo_sem);
}

/* 	This code updates a philosopher's current state (like eating, sleeping, or 
	thinking) using a semaphore to ensure only one philosopher can change their 
	state at a time.	*/

void	ft_delay(uint64_t sleep_time)
{
	uint64_t	start;

	start = ft_my_watch();
	while ((ft_my_watch() - start) < sleep_time)
		usleep(500);
}

/* 	This code makes the program pause for a specific amount of time. It does 
	this by repeatedly checking how much time has passed and then pausing for a 
	very short time (500 microseconds) until the desired time is reached.
	In essence, this function creates a custom delay by continuously checking 
	the time and pausing until the specified delay is over.	 */

uint64_t	ft_my_watch(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (SUCCESS);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

/* 	This code snippet measures time in milliseconds.
	It does this by:
	Getting the current time: It uses a system call to get the current time, 
		including seconds and microseconds.
	Converting to milliseconds: It converts the seconds to milliseconds and 
		adds the milliseconds part, giving you the total time in milliseconds.
	In simpler terms, it's like a stopwatch that tells you how many milliseconds
	have passed since a specific starting point. */
