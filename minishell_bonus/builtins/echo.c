/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/24 11:07:57 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Writes each argument to the shell output, separated by spaces.
** Adds a newline at the end if new_line is true.
** Used by echo to print arguments. Uses write (system call) and ft_strlen.
*/
void	ft_write_newline(char **args, t_shell *shell, int i, int new_line)
{
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

/*
** Implements the echo builtin. Prints arguments to the shell output.
** Handles the -n option to suppress newline. Calls ft_write_newline to print.
** Uses write (system call) and ft_strlen. Only prints newline if -n is not 
	present.
*/
void	ft_echo(char **args, t_shell *shell)
{
	int	i;
	int	j;
	int	new_line;

	i = 0;
	new_line = 1;
	if (!args[i])
	{
		write(shell->fdout, "\n", 1);
		return ;
	}
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	ft_write_newline(args, shell, i, new_line);
}
