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

#include "../includes/philo_bonus.h"

int	ft_writing(t_data *data, char *msg)
{
	sem_wait(data->print_sem);
	if (ft_everyone_ok())
	{
		sem_post(data->print_sem);
		return (1);
	}
	printf("%lu %d %s\n", ft_my_watch() - ft_get_start(data),
		data->philo.id, msg);
	sem_post(data->print_sem);
	return (0);
}

void	ft_instruction(void)
{
	printf(BDBLUE"\n\n");
	printf("█████ █  █ ███ █    ████       ███  ████ █   █ █  █ ████\n");
	printf("█   █ █  █  █  █    █  █       █  █ █  █ ██  █ █  █ █   \n");
	printf("█████ ████  █  █    █  █       ███  █  █ █ █ █ █  █ ████\n");
	printf("█     █  █  █  █    █  █       █  █ █  █ █  ██ █  █    █\n");
	printf("█     █  █ ███ ████ ████       ███  ████ █   █ ████ ████\n\n");
	printf(RESET"                 by sternero(nov.2024)              \n\n");
	printf(BDYELLOW "\tRemember, 😡 you must enter...\n\n" RESET);
	printf("./philo_bonus +\n");
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
	printf(BDRED"😵‍💫 Don't be confused"RESET);
	printf("... and enjoy the experience. 🤪\n\n");
}
