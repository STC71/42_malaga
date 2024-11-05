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

int		ft_sleeping(t_philo *philo)
{
	ft_status(philo, SLEEPING);
	if (ft_how_are_you(philo) == DIE)
		return (FAILURE);
	ft_writing(philo->data, philo->id, SLEEP);
	ft_delay(ft_get_sleep(philo->data));
	return (SUCCESS);
}

void	ft_sleep_for_eating(t_philo *philo)
{
	ft_delay(ft_get_eat(philo->data));
}

