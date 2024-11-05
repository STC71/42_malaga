/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:22:03 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:22:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_keep_or_not(t_data *data)
{
	bool	keep;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep);
}

bool	ft_has_eaten(t_data *value, t_philo *philo)
{
	bool	res;

	res = false;
	if (ft_times_eating(philo) >= value->nb_meals)
		res = true;
	return (res);
}

bool	ft_rip(t_philo *philo)
{
	bool		res;
	t_data		*data;

	data = philo->data;
	res = false;
	if (ft_my_watch() - ft_get_last_eat(philo) > ft_get_die(data)
		&& ft_how_are_you(philo) != EATING)
	{
		ft_status(philo, DIE);
		res = true;
	}
	return (res);
}

bool	ft_num_meals(t_data *value)
{
	if (value->nb_meals > 0)
		return (true);
	return (false);
}
