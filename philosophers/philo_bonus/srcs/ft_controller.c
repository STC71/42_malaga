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

#include "../includes/philo_bonus.h"

void	*ft_cerberus(void *data_p)
{
	t_data	*data;

	data = (t_data *)data_p;
	while (ft_suspend(ft_how_are_you(data)) == false)
	{
		if (ft_everyone_ok())
			return (ft_status(data, FINISHED), NULL);
		if (ft_rip(data))
		{
			sem_wait(data->print_sem);
			if (ft_rip(data) && ft_everyone_ok() == false)
			{
				ft_status(data, DIE);
				ft_philo_dep();
				printf("%lu %d %s\n", ft_my_watch() - ft_get_start(data),
					data->philo.id, DIED);
				sem_post(data->print_sem);
				break ;
			}
			sem_post(data->print_sem);
		}
		usleep(1000);
	}
	return (NULL);
}
