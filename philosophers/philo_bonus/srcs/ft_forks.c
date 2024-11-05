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

#include "../includes/philo.h"

void	ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	ft_drop_fork_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
}

void	ft_drop_fork_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_r);
}

