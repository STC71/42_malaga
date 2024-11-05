/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 08:12:09 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 08:12:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
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

/* The main function is the entry point of the program. It checks the arguments:
   if the number of arguments is less than 5 or more than 6, or if the arguments
   are not numbers, or if the arguments are less than 60, it calls the function
   to print the instructions and returns an error. Afer, it calls the function
   to initialize the philosophers; if the initialization fails, it returns an
   error. Finally, it returns a success message if everything is correct. */

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
			break ;
		if (ft_thinking(value) != 0)
			break ;
		if (ft_sleeping(value) != 0)
			break ;
		if (ft_how_are_you(value) == DIE)
			break ;
	}
	return (NULL);
}

/* The function ft_the_core() is very important function of the philosopher. 
   It receives a philosopher as an argument. It gets the last meal time of the 
   philosopher. If the number of the philosopher is even, it delays the eating
   time by 10 ms. While the philosopher is alive, it checks if the philosopher
   is eating, thinking, or sleeping and if the philosopher is dead. If eating,
   thinking, or sleeping fails, or the philosopher is dead, it breaks the loop.
   Finally, it returns NULL. */	

int	ft_only_one(t_philo *philo)
{
	ft_get_fork_l(philo);
	ft_delay(ft_get_die(philo->data));
	ft_status(philo, DIE);
	return (FAILURE);
}

/* The function ft_only_one() is a function that is called when there is only 
   one philosopher. It receives a philosopher as an argument. It gets the left
   fork of the philosopher but does not get the right fork, because there is no
   right fork. It delays the time to die of the philosopher and changes the
   state of the philosopher to dead. Finally, it returns a failure message. */

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

/* The function ft_the_watchdog() is a function that is called when there is 
   more than one philosopher. It receives a data structure as an argument. 
   While the philosophers are alive, it checks if the philosophers have eaten. 
   If a philosopher has not eaten, it resets the counter of the philosopher. 
   If all the philosophers have eaten, it changes the flag of the data structure 
   to false and calls the function game over to print the message. Finally, it
   returns NULL. */

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

/* The function ft_sincro() is a function that is called when the philosophers
   have finished eating. It receives a data structure as an argument. It waits 
   for the thread that monitors if all the philosophers are alive. 
   If the number of meals is true, it waits for the thread that monitors if 
   all the philosophers have eaten. 
   Finally, it waits for all the threads of the philosophers and returns a 
   success message if everything is correct. */
