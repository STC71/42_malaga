/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 23:38:29 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 23:38:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_delay_even(t_data *data)
{
	if (data->philo.id % 2 == 0)
		ft_delay(data->eat_time - 10);
}

bool	ft_suspend(t_state	state)
{
	if (state == DIE || state == FULL || state == FINISHED)
		return (true);
	return (false);
}

void	ft_status(t_data *data, t_state state)
{
	sem_wait(data->philo.philo_sem);
	data->philo.state = state;
	sem_post(data->philo.philo_sem);
}

void	ft_delay(uint64_t sleep_time)
{
	uint64_t	start;

	start = ft_my_watch();
	while ((ft_my_watch() - start) < sleep_time)
		usleep(500);
}

uint64_t	ft_my_watch(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
