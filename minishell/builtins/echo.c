/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 12:36:23 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **args, t_shell *shell)
{
	int	i;
	int	j;
	int	new_line;

	i = 0;
	j = 1;
	new_line = 1;
	if (!args[i])
	{
		write(shell->fdout, "\n", 1);
		return ;
	}
	if (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n' && args[i])
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
			{
				while (args[i])
				{
					write(shell->fdout, args[i], ft_strlen(args[i]));
					if (args[i + 1] && args[i][0] != '\0')
						write(shell->fdout, " ", 1);
					i++;
					if (new_line)
						write(shell->fdout, "\n", 1);
				}
				return ;
			}
			new_line = 0;
			i++;
		}
	}
	while (args[i])
	{
		write(shell->fdout, args[i], ft_strlen(args[i]));
		if (args[i + 1] && args[i][0] != '\0')
			write(shell->fdout, " ", 1);
		i++;
	}
	if (new_line)
		write(shell->fdout, "\n", 1);
}

/*	ft_echo function is used to write arguments to the standard output. 
	It takes the arguments and the shell structure as arguments. 
	It then writes the arguments to the standard output, separated by a space. 
	If the -n option is present, it does not write a newline character at 
		the end.*/