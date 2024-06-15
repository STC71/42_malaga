/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-07 09:09:47 by sternero          #+#    #+#             */
/*   Updated: 2024-06-07 09:09:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_screen(int pid)
{
	system("clear");
	ft_printf("* * WELLCOME TO MINITALK BONUS SERVER * *\n");
	ft_printf("*              by sternero              *\n");
	ft_printf("*         from 42 Málaga (2024)         *\n");
	ft_printf("* * * * * * * * * * * * * * * * * * * * *\n");
	ft_printf("\n>>>         PID number: %d       <<<\n", pid);
	ft_printf("\n>>> waiting for messages, please wait <<<\n");
	ft_printf("\n>>>   ... or press ctrl + c to exit   <<<\n\n");
}

void	ft_btoa(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void)context;
	if (sig == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		if (i == 0)
			kill(info->si_pid, SIGUSR2);
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	act;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error\n");
		return (1);
	}
	pid = getpid();
	system("clear");
	ft_screen(pid);
	act.sa_sigaction = ft_btoa;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
	return (0);
}
