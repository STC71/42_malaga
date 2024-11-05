/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 08:12:09 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 08:12:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		main(int argc, char **argv)
{
	if (ft_check_args(argc, argv) != 0)
	{
		ft_instruction();
		return (INPUT_ERROR);
	}
	if (ft_init_philos(argc, argv) != 0)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

void	*ft_the_core(void *philo)
{
	t_philo	*value;

	value = (t_philo *) philo;
	ft_get_last_meal(value);
	if (value->id % 2 == 0)
		ft_delay(value->data->eat_time - 10);
	while (ft_how_are_you(value) != DIE)
	{
		if (ft_eating(value) != 0)
			break;
		if (ft_thinking(value) != 0)
			break;
		if (ft_sleeping(value) != 0)
			break;			
		if (ft_how_are_you(value) == DIE)
			break;
	}
	return (NULL);
}

int	ft_only_one(t_philo *philo)
{
	ft_get_fork_l(philo);
	ft_delay(ft_get_die(philo->data));
	ft_status(philo, DIE);
	return (1);
}

void	*ft_the_watchdog(void *phi_value)
{
	int		i;
	int		j;
	t_data	*value;
		
	i = -1;
	value = (t_data *)phi_value;	
	j = ft_num_philos(value);

	while (++i < j && ft_keep_or_not(value))
	{
		usleep(1000);
		if (ft_has_eaten(value, &value->philos[i]) == false)
			i = -1;
	}
	if (ft_keep_or_not(value) == true)
	{
		ft_keep_flag(value, false);
		ft_game_over(value);
	}
	return (NULL);
}

int	ft_sincro(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = ft_num_philos(data);
	if (pthread_join(data->monit_all_alive, NULL))
		return (FAILURE);
	if (ft_num_meals(data) == true
		&& pthread_join(data->monit_all_full, NULL))
		return (FAILURE);
	while (++i < j)
	{
		if (pthread_join(data->philo_ths[i], NULL))
			return (FAILURE);
	}
	return (SUCCESS);
}
