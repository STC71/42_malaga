/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 08:15:44 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 08:15:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>       
/* pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, 
    pthread_mutex_unlock, pthread_mutex_destroy */
# include <stdbool.h>       /* bool, true, false */
# include <stdint.h>        /* uint64_t, uint32_t, uint16_t, uint8_t */
# include <stdio.h>         /* NULL... */ 
# include <stdlib.h>        /* malloc, free, exit */
# include <string.h>        /* strerror */
# include <sys/time.h>  
# include <unistd.h>        /* usleep, write, fork, execve... */

# include "../libft/libft.h"            /* ft_atoi, ft_strlen, ft_strjoin... */
# include "../ft_printf/ft_printf.h"    /* ft_printf */
# include "colors.h"                    /* colors */
# include "functions.h"                 /* Functions */
# include "messages.h"                  /* Messages */

# define FAILURE 1
# define SUCCESS 0

#endif