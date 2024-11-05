/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 09:11:36 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 09:11:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_args(int c, char **v)
{
	if (c < 5 || c > 6 || ft_argv_num(c, v) != 0 || ft_error_argv(c, v))
		return (INPUT_ERROR);
	return (SUCCESS);
}

/* The function ft_check_args() checks the arguments: if the number of arguments
   is less than 5 or more than 6, or if the arguments are not numbers, or if the
   arguments are less than 60, it returns an error. Otherwise, it returns a 
   success message. */

int	ft_error_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (INPUT_ERROR);
	if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200)
		return (INPUT_ERROR);
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (INPUT_ERROR);
	}
	return (SUCCESS);
}

/* The function ft_error_argv() checks the arguments: if the number of 
   philosophers is less than 1 or more than 200, or if the time to die, 
   the time to eat, or the time to sleep is less than 60, it returns an 
   error. Otherwise, it returns a success message. */

int	ft_argv_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (INPUT_ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/* The function ft_argv_num() checks the arguments: if the arguments are not 
   numbers, it returns an error. Otherwise, it returns a success message. */

t_state	ft_how_are_you(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

/* The function ft_how_are_you() checks the state of the philosopher. 
   It receives a philosopher as an argument. It locks the mutex of the 
   state of the philosopher, gets the state of the philosopher and unlocks 
   the mutex of the state of the philosopher. Finally, it returns the state 
   of the philosopher. */

void	*ft_are_you_dead(void *data)
{
	int		i;
	int		j;
	t_data	*value;
	t_philo	*philos;

	i = -1;
	value = (t_data *)data;
	philos = value->philos;
	j = ft_num_philos(value);
	while (++i < j && ft_keep_or_not(value))
	{
		if (ft_rip(&philos[i]) && ft_keep_or_not(value))
		{
			ft_writing(value, philos[i].id, DIED);
			ft_keep_flag(value, false);
			ft_game_over(value);
			break ;
		}
		if (i == j - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

/* The function ft_are_you_dead() checks if the philosopher is dead. It receives
   a data structure as an argument. It checks if the philosopher is dead. If the
   philosopher is dead, it prints the message of the philosopher's death, 
   changes the flag of the data structure to false, and calls the function game 
   over to end the program. Finally, if the philosopher is not dead, it returns 
   NULL. */
