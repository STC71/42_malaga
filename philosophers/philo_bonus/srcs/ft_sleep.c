/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 08:32:19 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 08:32:19 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_sleeping_for_eating(t_data *data)
{
	ft_delay(data->eat_time);
}

/* 	This code makes a philosopher wait for a specific amount of time before it 
	starts eating. The waiting time is determined by the 'eat_time' value stored
	in the 'data' structure."
	Essentially, this function simulates the time a philosopher takes to finish 
	eating.	*/

int	ft_sleeping(t_data *data)
{
	ft_status(data, SLEEPING);
	if (ft_writing(data, SLEEP))
		return (FAILURE);
	ft_delay(data->sleep_time);
	return (SUCCESS);
}

/* 	This code simulates a philosopher sleeping. It first marks the philosopher's
	status as 'sleeping'. Then, it writes a message to indicate that the 
	philosopher is now sleeping. Next, it pauses the program for a specific 
	amount of time (the philosopher's sleep time). Finally, it returns a value 
	to indicate if there were any issues during the sleeping process. */
