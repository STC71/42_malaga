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

/*	The function ft_init_values() initializes the values of the data structure. 
	It receives a data structure, the number of arguments, and the arguments. 
	If the number of arguments is 6, it assigns the number of meals to the data 
	structure. Otherwise, it assigns -1 if the number of meals is not specified.
	-1 means that the number of meals is not specified. It assigns the eating
	time, the dying time, the sleeping time, the number of full philosophers,
	the number of philosophers, and the flag to keep iterating. It initializes
	the mutexes of the eating time, the dying time, the sleeping time, the flag
	to keep iterating, the number of philosophers, the print, and the start 
	time.
	Finally, it returns the result of the function ft_malloc() that allocates
	memories for the program. */

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

/*	The function ft_init_threads() initializes the threads of the philosophers.
	It receives a data structure as an argument. It initializes the start time 
	of the data structure. It creates the threads of the philosophers. If the 
	creation of the thread fails, it returns a failure message. It creates the 
	thread that monitors if all the philosophers are alive. If the creation of 
	the thread fails, it returns a failure message. If the number of meals is 
	true, it creates the thread that monitors if all the philosophers have eaten
	If the creation of the thread fails, it returns a failure message. Finally, 
	it returns a success message if everything is correct. */

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

/*	The function ft_init_philos() initializes the philosophers. It receives the 
	number of arguments and the arguments. It creates a data structure. If the 
	initialization of the values of the data structure fails, it returns a malloc
	error. It initializes the data of the philosophers. It initializes the forks.
	It initializes the threads of the philosophers. It waits for the threads to 
	finish. Finally, it frees all the memories allocated for the program. */

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

/*	The function ft_init_philos_data() initializes the data of the philosophers.
	It receives a data structure as an argument. 
	It initializes the philosophers, the id, the number of meals, the state, 
	and the mutexes of the state, the number of meals, and the last meal. 
	ft_get_last_meal() initializes the last meal of the philosopher. 
	Finally, it returns a success message. */

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

/*	The function ft_init_forks() initializes the forks of the philosophers. It 
	receives a data structure as an argument. It initializes the forks of the 
	philosophers. It initializes the left fork of the philosopher and the 
	right fork of the first philosopher, the right fork of the philosopher is 
	the left fork of the previous philosopher. Finally, it returns a success if
	everything is correct. */
