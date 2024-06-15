/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-05 09:11:33 by sternero          #+#    #+#             */
/*   Updated: 2024-06-05 09:11:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_atob(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

void	confirm_msg(int signal)
{
	if (signal == 1)
		ft_printf(">>> Message sent <<<\n");
	else if (signal == SIGUSR2)
		ft_printf(">>> ERROR <<<\n");
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_atob(pid, argv[2][i]);
			i++;
		}
		signal(SIGUSR2, confirm_msg);
		confirm_msg(1);
		ft_atob(pid, '\n');
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
