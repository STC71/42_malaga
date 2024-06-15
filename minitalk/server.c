/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-07 09:09:47 by sternero          #+#    #+#             */
/*   Updated: 2024-06-07 09:09:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_btoa(int sig)
{
	static int	bit;
	static int	i;

	if (sig == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error\n");
		return (1);
	}
	pid = getpid();
	system("clear");
	ft_printf("* * *  WELLCOME TO MINITALK SERVER  * * *\n");
	ft_printf("*              by sternero              *\n");
	ft_printf("*         from 42 Málaga (2024)         *\n");
	ft_printf("* * * * * * * * * * * * * * * * * * * * *\n");
	ft_printf("\n>>>         PID number: %d       <<<\n", pid);
	ft_printf("\n>>> waiting for messages, please wait <<<\n");
	ft_printf("\n>>>   ... or press ctrl + c to exit   <<<\n\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_btoa);
		signal(SIGUSR2, ft_btoa);
		pause ();
	}
	return (0);
}
