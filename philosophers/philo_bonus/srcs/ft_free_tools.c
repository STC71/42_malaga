/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-26 09:14:04 by sternero          #+#    #+#             */
/*   Updated: 2024-09-26 09:14:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	leaks(void)
{
	system("leaks philo");
}

/*	The leaks function is used to check for memory leaks. After the program has
	been compiled you can run for example: "./philo 4 800 200 200 5 leaks" or 
	"./philo leaks" and the program will run with the leaks function. If there
	are memory leaks, the program will show you where they are. If there are no
	memory leaks, the program will run without any output. */

void	ft_free_all(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = ft_num_philos(data);
	while (++i < j)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_state);
		pthread_mutex_destroy(&data->philos[i].mut_num_meals);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat);
	}
	pthread_mutex_destroy(&data->mut_die_t);
	pthread_mutex_destroy(&data->mut_eat_t);
	pthread_mutex_destroy(&data->mut_sleep_t);
	pthread_mutex_destroy(&data->mut_nb_philos);
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_keep_iter);
	pthread_mutex_destroy(&data->mut_start_time);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}

int	ft_malloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
		return (free(data->philos), MALLOC_ERROR);
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_ths == NULL)
		return (free(data->philos), free(data->forks), MALLOC_ERROR);
	return (SUCCESS);
}
