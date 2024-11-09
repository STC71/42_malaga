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

#include "../includes/philo_bonus.h"

void	ft_sleeping_for_eating(t_data *data)
{
	ft_delay(data->eat_time);
}

int	ft_sleeping(t_data *data)
{
	ft_status(data, SLEEPING);
	if (ft_writing(data, SLEEP))
		return (1);
	ft_delay(data->sleep_time);
	return (0);
}
