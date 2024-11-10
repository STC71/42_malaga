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

#include "../includes/philo_bonus.h"

void	ft_free_sem(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
}

/* 	This code cleans up the semaphores used for synchronization in the dining 
	philosophers problem. It closes the semaphore used to control access to 
	forks and the semaphore used to control printing to the console. 
	Why is this important?
	By closing the semaphores at the end of the program, we ensure that the 
	system resources are properly released. If we don't close the semaphores, 
	they might continue to consume system resources even after the program has 
	finished running. This could lead to resource leaks and other problems. */
