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

#include "../includes/philo_bonus.h"

int     ft_print_error(int error)
{
    if (error == 1)
        printf(RED ERROR_ARGS_1"\n" RESET);
    if (error == 2)
        printf(RED ERROR_ARGS_2"\n" RESET);
    if (error == 3)
        printf(RED ERROR_ARGS_3"\n" RESET);
    if (error == 4)
        printf(RED ERROR_ARGS_4"\n" RESET);
    if (error == 5)
        printf(RED ERROR_ARGS_5"\n" RESET);
    if (error == 6)
        printf(RED ERROR_ARGS_6"\n" RESET);
    return FAILURE;
}


void     ft_check_args(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        ft_print_error(1);
    if (ft_atoi(argv[1]) < 2)
        ft_print_error(2);
    if (ft_atoi(argv[2]) < 60)
        ft_print_error(3);
    if (ft_atoi(argv[3]) < 60)
        ft_print_error(4);
    if (ft_atoi(argv[4]) < 60)
        ft_print_error(5);
    if (argc == 6 && ft_atoi(argv[5]) < 1)
        ft_print_error(6);
}
