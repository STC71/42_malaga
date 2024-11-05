/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 22:57:27 by sternero          #+#    #+#             */
/*   Updated: 2024-11-01 22:57:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_writing(t_data *data, int id, char *src)
{
	uint64_t	i;

	i = ft_my_watch() - ft_get_start(data);
	pthread_mutex_lock(&data->mut_print);
	if (ft_keep_or_not(data))
		printf("%lu %d %s\n", i, id, src);
	pthread_mutex_unlock(&data->mut_print);
}

/*	The function ft_writing() writes the message of the philosopher. It receives
	a data structure, the id of the philosopher, and the message. It gets the 
	current time, locks the mutex of the print, writes the message of the 
	philosopher, and unlocks the mutex of the print. */

void	ft_instruction(void)
{
	printf(BDBLUE"\n\n");
	printf("█████ █  █ █ █    ████ ████ ████ ████ █  █ ████ ████ ████\n");
	printf("█   █ █  █ █ █    █  █ █    █  █ █  █ █  █ █    █  █ █   \n");
	printf("█████ ████ █ █    █  █ ████ █  █ ████ ████ ████ ███  ████\n");
	printf("█     █  █ █ █    █  █    █ █  █ █    █  █ █    █  █    █\n");
	printf("█     █  █ █ ████ ████ ████ ████ █    █  █ ████ █  █ ████\n\n");
	printf(RESET"                   by sternero(nov.2024)\n\n");
	printf(BDYELLOW "\tRemember, 😡 you must enter...\n\n" RESET);
	printf("./philo +\n");
	printf("number of philosophers (must be a number between 1 and 200) +\n");
	printf("time to die (must be a number greater than 60 ms.) +\n");
	printf("time to eat (must be a number greater than 60 ms.) +\n");
	printf("time to sleep (must be a number greater than 60 ms.) +\n\n");
	printf(BDGREEN"😳 Optionally "RESET);
	printf(": the number of times each phyllo must eat.\n\n");
	printf(BDBLUE"\tNow let's see an example:\t"RESET);
	printf("./philo 4 800 200 200 5\n\n");
	printf("This will create 4 philosophers, ");
	printf("each with a time to die 😭 of 800 ms,\n");
	printf("a time to eat 🤤 of 200 ms, a time to sleep 🥱 of 200 ms,\n");
	printf("and each philosopher must eat 5 times.\n\n");
	printf(BDRED"😵‍💫 Don't be confused"RESET"... and ");
	printf("enjoy the experience. 🤪\n\n");
}

/*	The function ft_instruction() prints the instructions of the program when 
	the arguments are incorrect or without arguments. */
