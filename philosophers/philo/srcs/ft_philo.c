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

int     main (int argc, char **argv)
{
    if (argc > 1)
    {
        ft_check_args(argc, argv);
    }
    //printf("\n");
    return (0);
}

/*  The main function is the entry point of the program. It checks if the number 
    of arguments is correct and if the arguments are valid. If the arguments are 
    not valid, it prints an error message. */