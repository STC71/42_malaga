/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 08:15:44 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 08:15:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// ------------------------- External libraries ----------------------------- //

# include <fcntl.h>
/*  O_CREAT to create a file if it doesn't exist.
    O_RDWR to open the file for reading and writing.
    O_TRUNC to truncate the file to zero bytes. */
# include <pthread.h>
/*  pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, 
    pthread_mutex_unlock, pthread_mutex_destroy */
# include <semaphore.h>      /* sem_open, sem_close, sem_post, sem_wait */
# include <stdbool.h>        /* bool, true, false */
# include <stdint.h>         /* uint64_t, uint32_t, uint16_t, uint8_t */
# include <stdio.h>          /* printf, NULL... */ 
# include <stdlib.h>         /* malloc, free, exit */
# include <string.h>         /* strerror */
# include <sys/time.h>       /* gettimeofday */
# include <sys/wait.h>       /* waitpid */ 
# include <unistd.h>         /* usleep, write, fork, execve... */

// ------------------------- Own libraries --------------------------------- //

# include "structures.h"                /* Structures */
# include "colors.h"                    /* colors */
# include "messages.h"                  /* Messages */
# include "functions.h"                 /* Functions */

#endif