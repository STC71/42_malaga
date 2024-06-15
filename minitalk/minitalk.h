/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-05 08:48:09 by sternero          #+#    #+#             */
/*   Updated: 2024-06-05 08:48:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

void	ft_btoa(int sig);
int		ft_atoi(const char *str);
void	ft_atob(int pid, char c);

#endif

/* 
This is the header file for the minitalk project. It includes the 
necessary libraries and the prototypes of the functions.

unistd.h: for write()
stdlib.h: for malloc()
signal.h: for signal()
sys/types.h: for pid_t
libft.h: for my own library functions
ft_printf.h: for my own ft_printf() function

The functions are:
- ft_btoa(): converts a byte to an ASCII character
- ft_atoi(): converts a string to an integer
- ft_atob(): converts an ASCII character to a byte
*/