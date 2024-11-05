/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:18:29 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:18:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_get_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_eat);
	philo->last_eat = ft_my_watch();
	pthread_mutex_unlock(&philo->mut_last_eat);
}

void	ft_get_num_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_num_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->mut_num_meals);
}

uint64_t	ft_get_die(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_die_t);
	time = data->die_time;
	pthread_mutex_unlock(&data->mut_die_t);
	return (time);
}

uint64_t	ft_get_eat(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_eat_t);
	time = data->eat_time;
	pthread_mutex_unlock(&data->mut_eat_t);
	return (time);
}

uint64_t	ft_get_last_eat(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->mut_last_eat);
	time = philo->last_eat;
	pthread_mutex_unlock(&philo->mut_last_eat);
	return (time);
}