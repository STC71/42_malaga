/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-05 08:48:09 by sternero          #+#    #+#             */
/*   Updated: 2024-06-05 08:48:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/select.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

// =======================================================
// To fix the visibility of the sigaction structure
// =======================================================
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

#endif

/* 
This is the header file for the minitalk project. It includes the 
necessary libraries and the prototypes of the functions.

unistd.h: for write()
*/
