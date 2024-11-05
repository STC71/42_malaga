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

/*	The function ft_drop_fork() drops the forks of the philosopher. It receives
	a philosopher as an argument. It unlocks the mutex of the left fork and the
	mutex of the right fork. */

void	ft_drop_fork_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
}

/*	The function ft_drop_fork_l() drops the left fork of the philosopher. It 
	receives a philosopher as an argument. It unlocks the mutex of the left 
	fork. It used by the function ft_drop_fork(). */

void	ft_drop_fork_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_r);
}

/*	The function ft_drop_fork_r() drops the right fork of the philosopher. It
	receives a philosopher as an argument. It unlocks the mutex of the right 
	fork. It used by the function ft_drop_fork(). */
