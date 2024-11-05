/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 12:40:50 by sternero          #+#    #+#             */
/*   Updated: 2024-10-31 12:40:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_values(t_data *data, int argc, char **argv)
{
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	data->eat_time = (uint64_t) ft_atoi(argv[3]);
	data->die_time = (uint64_t) ft_atoi(argv[2]);
	data->sleep_time = (uint64_t) ft_atoi(argv[4]);
	data->nb_full_p = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->keep_iterating = true;
	pthread_mutex_init(&data->mut_eat_t, NULL);
	pthread_mutex_init(&data->mut_die_t, NULL);	
	pthread_mutex_init(&data->mut_sleep_t, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_nb_philos, NULL);
	pthread_mutex_init(&data->mut_print, NULL);	
	pthread_mutex_init(&data->mut_start_time, NULL);
	return (ft_malloc(data));
}

int	ft_init_threads(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = ft_num_philos(data);
	data->start_time = ft_my_watch();
	while (++i < j)
	{
		if (pthread_create(&data->philo_ths[i], NULL,
				&ft_the_core, &data->philos[i]))
			return (FAILURE);
	}
	if (pthread_create(&data->monit_all_alive, NULL,
			&ft_are_you_dead, data))
		return (FAILURE);
	if (ft_num_meals(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
			&ft_the_watchdog, data))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_init_philos(int argc, char **argv)
{
	t_data	values;

	if (ft_init_values(&values, argc, argv) != 0)
		return (MALLOC_ERROR);
	ft_init_philos_data(&values);
	ft_init_forks(&values);
	ft_init_threads(&values);
	ft_sincro(&values);
	ft_free_all(&values);
	return (SUCCESS);
}

int	ft_init_philos_data(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].state = OFF;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_num_meals, NULL);
		pthread_mutex_init(&philos[i].mut_last_eat, NULL);
		ft_get_last_meal(&philos[i]);
	}
	return (SUCCESS);
}

int	ft_init_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philos[0].fork_l = &data->forks[0];
	philos[0].fork_r = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		philos[i].fork_l = &data->forks[i];
		philos[i].fork_r = &data->forks[i - 1];
	}
	return (SUCCESS);
}
