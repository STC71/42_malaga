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

/* 	This code checks if the user gave the correct number and type of arguments 
	when starting the program. It makes sure there are exactly 5 numbers after 
	the program name and that these numbers are within specific limits. If any 
	number is wrong, it tells the program to stop.	*/

t_state	ft_how_are_you(t_data *data)
{
	t_state	state;

	sem_wait(data->philo.philo_sem);
	state = data->philo.state;
	sem_post(data->philo.philo_sem);
	return (state);
}

/* 	This code checks a philosopher's current status (like eating, sleeping, or 
	thinking). It does this by safely looking at the philosopher's information 
	and then returning the current status.
	Imagine a group of friends at a dinner table. This code is like a waiter 
	asking a friend, "Are you eating, sleeping, or talking right now?" 
	The waiter makes sure to only ask one friend at a time to avoid confusion.
 */

bool	ft_everyone_ok(void)
{
	sem_t	*death;

	death = sem_open("/death", 0, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}

/* 	This code checks if everyone is alive in the simulation. It does this by 
	trying to access a shared semaphore called 'death'. If it can't access this 
	semaphore, it means someone has died, so it returns false. Otherwise, if it 
	can access it, it means everyone is still alive, so it returns true.	*/

void	ft_philo_dep(void)
{
	sem_open("/death", O_CREAT, 0644, 0);
}

/* 	This code creates a new semaphore named 'death'. A semaphore is like a 
	digital flag that can be raised or lowered. In this case, the 'death' 
	semaphore is used to signal when a philosopher has died. Creating it at the 
	beginning prepares the program to track deaths.	 */

bool	ft_rip(t_data *data)
{
	if (ft_how_are_you(data) != EATING
		&& ft_my_watch() - ft_get_last_eat(data) > data->die_time)
		return (true);
	return (false);
}

/* 	Checks if a philosopher has died. This function looks at a philosopher's 
	current state and how long it's been since they last ate. If they haven't 
	eaten in a long time and aren't currently eating, it returns 'true' (meaning
	they're dead), otherwise, it returns 'false'." 
	In essence, this code is a watchdog that determines if a philosopher has 
	starved to death in the simulation. */