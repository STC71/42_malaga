/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_n_think.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:16:30 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:16:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

bool	ft_num_meals(t_data *data)
{
	if (data->meals_num > 0)
		return (true);
	return (false);
}

bool	ft_has_eaten(t_data *data)
{
	if (ft_num_meals(data) == false)
		return (false);
	if (data->meals_num <= data->philo.meals)
	{
		ft_status(data, FULL);
		return (true);
	}
	return (false);
}

int	ft_eating(t_data *data)
{
	if (ft_get_forks(data))
		return (FAILURE);
	ft_get_last_meal(data);
	ft_status(data, EATING);
	if (ft_writing(data, EAT))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	ft_sleeping_for_eating(data);
	ft_drop_forks(data);
	data->philo.meals++;
	if (ft_has_eaten(data))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_thinking(t_data *data)
{
	if (ft_writing(data, THINK))
		return (1);
	return (0);
}

uint64_t	ft_get_last_eat(t_data *data)
{
	uint64_t	time;

	sem_wait(data->philo.philo_sem);
	time = data->philo.last_eat;
	sem_post(data->philo.philo_sem);
	return (time);
}
