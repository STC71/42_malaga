/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 11:47:37 by sternero          #+#    #+#             */
/*   Updated: 2024-09-23 11:47:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// ------- ft_check.c ------------------------------------------------------- //

int     ft_print_error(int error);
// ft_print_error() prints an error message according to the error number.
// the error number is passed as an argument, and are defined in the philo.h

void    ft_check_args(int argc, char **argv);
// ft_check_args() checks the number of arguments and the values of the 
// arguments passed to the program. If the arguments are not valid, it calls
// ft_print_error() with the corresponding error number.

// ------- ft_tools.c ------------------------------------------------------- //

int     ft_atoi_pro(char *c);
int     ft_atoi(const char *str);
// ft_atoi and ft_atoi_pro are used to convert a string to an integer.

// ------- philo.c -------------------------------------------------------------



// main function is the entry point of the program. It checks the number of
// arguments and the values of the arguments passed to the program. If the
// arguments are not valid, it calls ft_check_args() with the corresponding
// error number. 

#endif