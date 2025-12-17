/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/02 19:17:50 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_exit_toomany_err(t_shell *shell)
{
	write(STDERR_FILENO, "exit: too many arguments\n", 26);
	shell->g_status = 1;
}

/*	write_exit_toomany_err function is used to write an error message to the 
	standard output when the exit command receives too many arguments.*/

void	write_numeric_err(t_shell *shell, char **command)
{
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, command[0], ft_strlen(command[0]));
	write(STDERR_FILENO, ": numeric argument required\n", 29);
	shell->g_status = 1;
}

/*	write_numeric_err function is used to write an error message to the standard
	output when the exit command receives a non-numeric argument.*/

void	write_pwd_err(t_shell *shell)
{
	write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

/*	write_pwd_err function is used to write an error message to the standard 
	output when the pwd command fails to retrieve the current working directory.
	
	The difereneces between the functions are:
	- write_exit_toomany_err writes "exit: too many arguments\n" to the standard
		output.
	- write_numeric_err writes "exit: ", the command[0], ": numeric argument 
		required\n" to the standard output.
	- write_pwd_err writes "pwd: error retrieving current directory: ", 
		strerror(errno), "\n" to the standard output.*/
