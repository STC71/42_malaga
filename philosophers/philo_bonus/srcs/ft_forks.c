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

#include "../includes/philo_bonus.h"

int	ft_drop_forks(t_data *data)
{
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	return (SUCCESS);
}

int	ft_get_forks(t_data *data)
{
	sem_wait(data->forks_sem);
	if (ft_writing(data, TAKE_FORKS))
	{
		sem_post(data->forks_sem);
		return (FAILURE);
	}
	if (data->philos_num == 1)
		return (FAILURE);
	sem_wait(data->forks_sem);
	if (ft_suspend(ft_how_are_you(data)))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	if (ft_writing(data, TAKE_FORKS))
	{
		ft_drop_forks(data);
		return (FAILURE);
	}
	return (SUCCESS);
}
