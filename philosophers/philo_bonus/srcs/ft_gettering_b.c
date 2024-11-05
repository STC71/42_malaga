/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:18:48 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:18:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_get_fork_l(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_l);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

int	ft_get_fork_r(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_r);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

int	get_forks(t_philo *philo)
{
	if (ft_num_philos(philo->data) == 1)
		return (ft_only_one(philo));
	if (ft_get_fork_r(philo) != 0)
		return (FAILURE);
	if (ft_get_fork_l(philo) != 0)
	{
		ft_drop_fork_r(philo);
		return (FAILURE);
	}
	return (SUCCESS);
}
