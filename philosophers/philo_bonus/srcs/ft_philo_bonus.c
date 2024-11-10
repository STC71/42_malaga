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

#include "../includes/philo_bonus.h"

int	ft_run_all(t_data *data, int id)
{
	if (ft_philo_struct(data, id))
		exit(1);
	ft_delay_even(data);
	if (pthread_create(&data->watchdog, NULL, &ft_cerberus, data))
		return (ERROR_THREAD);
	while (true)
	{
		if (ft_eating(data) || ft_suspend(ft_how_are_you(data))
			|| ft_sleeping(data) || ft_suspend(ft_how_are_you(data))
			|| ft_thinking(data))
			break ;
	}
	if (pthread_join(data->watchdog, NULL))
		exit(FAILURE);
	sem_close(data->philo.philo_sem);
	exit(SUCCESS);
}

/* 	This code starts a philosopher's life cycle. It initializes the philosopher,
	delays if needed, creates a watchdog thread to monitor the philosopher, and 
	then repeatedly makes the philosopher eat, sleep, and think until a 
	termination condition is met. Finally, it joins the watchdog thread and 
	cleans up resources.	*/

int	ft_philo_struct(t_data *data, int id)
{
	char	*sem_name;

	sem_name = ft_init_sem_name(id);
	if (sem_name == NULL)
		exit(ERROR_MALLOC);
	sem_unlink(sem_name);
	data->philo.philo_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(sem_name);
	data->philo.id = id;
	ft_get_last_meal(data);
	return (SUCCESS);
}

/* 	This code sets up a philosopher's information. It creates a unique name for 
	a semaphore, which is used for synchronization. Then, it initializes the 
	philosopher's ID and other necessary data. Finally, it records the time of 
	the philosopher's last meal.	*/

int	main(int argc, char **argv)
{
	if (ft_check_args(argc, argv) != 0)
	{
		ft_instruction();
		return (ERROR_INPUT);
	}
	ft_init_philo(argc, argv);
	return (SUCCESS);
}

/* 	This code starts the dining philosophers simulation. It first checks if the 
	command-line arguments are correct. If they are, it initializes the 
	simulation, setting up all the necessary data structures and starting the 
	philosopher processes.	*/
