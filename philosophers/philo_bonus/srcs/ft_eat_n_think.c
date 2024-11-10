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

#include "../includes/philo_bonus.h"

bool	ft_num_meals(t_data *data)
{
	if (data->meals_num > 0)
		return (true);
	return (false);
}

/* 	This code checks if a philosopher has eaten the required number of meals. 
	If the number of meals eaten is greater than zero, it returns 'true' 
	(meaning they've eaten enough). Otherwise, it returns 'false' (meaning they 
	haven't eaten enough).
	In simpler terms: This part of the code is like asking, 
	"Has this philosopher eaten enough yet?" 
	The answer is either "yes" (true) or "no" (false).	*/

bool	ft_has_eaten(t_data *data)
{
	if (ft_num_meals(data) == false)
		return (false);
	if (data->meals_num <= data->philo.meals)
	{
		ft_status(data, FULL);
		return (true);
	}
	return (false);
}

/* 	This code checks if a philosopher has eaten enough meals. It counts how many
	meals a philosopher has eaten and compares it to the required number of 
	meals. If the philosopher has eaten enough, it sets the philosopher's status
	to 'full' and returns 'true' to indicate that the philosopher is finished 
	eating. This function helps to determine when a philosopher should stop 
	eating and move on to the next phase of their cycle.	*/

int	ft_eating(t_data *data)
{
	if (ft_get_forks(data))
		return (FAILURE);
	ft_get_last_meal(data);
	ft_status(data, EATING);
	if (ft_writing(data, EAT))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	ft_sleeping_for_eating(data);
	ft_drop_forks(data);
	data->philo.meals++;
	if (ft_has_eaten(data))
		return (FAILURE);
	return (SUCCESS);
}

/* 	This function simulates a philosopher eating. It tries to get both forks, 
	updates the last meal time, sets the philosopher's status to 'eating', and 
	writes a message to a log. If there's an issue with writing to the log, the 
	philosopher drops the forks and fails. After eating for a specified time, 
	the philosopher drops the forks, increments the meal count, and checks if 
	they've eaten enough times. If so the function fails, otherwise it succeeds.
 */

int	ft_thinking(t_data *data)
{
	if (ft_writing(data, THINK))
		return (FAILURE);
	return (SUCCESS);
}

/*	This code simulates a philosopher thinking. It first tries to print a 
	message to indicate that the philosopher is thinking. If there's an error 
	during this process, it returns a failure; otherwise, it returns success. */

uint64_t	ft_get_last_eat(t_data *data)
{
	uint64_t	time;

	sem_wait(data->philo.philo_sem);
	time = data->philo.last_eat;
	sem_post(data->philo.philo_sem);
	return (time);
}

/* 	This code safely reads the last time a philosopher ate. It uses a semaphore 
	to protect shared data, ensuring only one philosopher can access and update 
	the last_eat time at a time. This prevents race conditions and ensures 
	accurate data. 	*/
