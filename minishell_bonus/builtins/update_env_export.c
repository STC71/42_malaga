/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:04:54 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 10:41:17 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env_err2(t_shell *shell, int env_err, char *command)
{
	int	i;

	i = 0;
	shell->g_status = 1;
	if (env_err == 0)
		env_err0(command, i);
	else if (env_err == -3)
	{
		if (command[1] != '\0')
			env_err = -2;
		else
			env_err3();
	}
	else if (env_err == -1)
		env_err1(command, i);
	else if (env_err == -2)
		env_err2(command, i);
}

/*  ft_print_env_err2 function is used to write an error message to the 
	standard output when the export command receives an invalid identifier. 
	It takes the command and the index of the invalid character as arguments. 
	It then writes the error message to the standard output.*/

int	check_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]))
		return (0);
	if (env[i] == '=')
		return (-3);
	while (env[i])
	{
		if (env[i] == '=')
		{
			if (env[i + 1] == '=' && env[i + 2] != '\0')
				return (-2);
		}
		i++;
	}
	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			return (-1);
		i++;
	}
	return (1);
}

/*  check_env function is used to check the export command for invalid 
	identifiers. It takes the command as an argument and checks for the 
	following conditions:
	- If the first character is a digit, it returns 0.
	- If the first character is an equal sign, it returns -3.
	- If the command contains a character that is not a letter, digit, or 
		underscore, it returns -1.
	- If the command contains an equal sign followed by a character that is 
		not a null character, it returns -2.
	Otherwise, it returns 1.*/

void	ft_print_env2(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		write(shell->fdout, "declare -x ", 11);
		write(shell->fdout, shell->env[i], ft_strlen(shell->env[i]));
		write(shell->fdout, "\n", 1);
		i++;
	}
}

/*  ft_print_env2 function is used to print all the environment variables 
	to the standard output. It takes the shell as an argument and then 
	iterates over the environment variables, writing each one to the standard 
	output.*/

void	ft_update_env_export(t_shell *shell, char **commands)
{
	int	i;

	if (commands[0] == 0)
		ft_print_env2(shell);
	else
	{
		i = 0;
		while (commands[i] != NULL)
		{
			if (check_env(commands[i]) > 0)
				ft_update_env(commands[i], shell);
			else
				ft_print_env_err2(shell, check_env(commands[i]), commands[i]);
			i++;
		}
	}
}

/*  ft_update_env_export function is used to update the environment variables 
	with the export command. It takes the shell and the commands as arguments. 
	If there are no commands, it prints all the environment variables. 
	Otherwise, it iterates over the commands and updates the environment 
	variables. If a command is invalid, it writes an error message to the 
	standard output.*/