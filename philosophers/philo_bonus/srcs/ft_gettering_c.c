/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 23:19:38 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 23:19:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	ft_get_start(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}

uint64_t	ft_get_sleep(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_sleep_t);
	time = data->sleep_time;
	pthread_mutex_unlock(&data->mut_sleep_t);
	return (time);
}
