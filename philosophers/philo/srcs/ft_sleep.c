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

#include "../includes/philo.h"

int	ft_sleeping(t_philo *philo)
{
	ft_status(philo, SLEEPING);
	if (ft_how_are_you(philo) == DIE)
		return (FAILURE);
	ft_writing(philo->data, philo->id, SLEEP);
	ft_delay(ft_get_sleep(philo->data));
	return (SUCCESS);
}

/*	The function ft_sleeping() is a function that is called when the philosopher
	is sleeping. It receives a philosopher as an argument. It changes the state 
	of the philosopher to sleeping. If the philosopher is dead, it returns a 
	failure message. Else, it writes the message that the philosopher is 
	sleeping, sleeps for the sleeping time, and returns a success message. */

void	ft_sleep_for_eating(t_philo *philo)
{
	ft_delay(ft_get_eat(philo->data));
}

/*	The function ft_sleep_for_eating() sleeps for the eating time of the 
	philosopher. It receives a philosopher as an argument. It delays the eating 
	time of the philosopher. */
