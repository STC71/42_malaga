/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec_builtins.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:07:50 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 14:08:22 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	choose_builtin(t_shell *shell, t_cmd **commands, int i)
{
	char	*builtin;

	builtin = commands[i]->cmd;
	if (!ft_strcmp(builtin, "echo"))
		ft_echo(commands[i]->args, shell);
	else if (!ft_strcmp(builtin, "cd"))
		ft_cd(commands[i]->args, shell);
	else if (!ft_strcmp(builtin, "env"))
		ft_print_env(shell, commands[i]->args);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(commands[i]->args, shell);
	else if (!ft_strcmp(builtin, "export"))
		ft_update_env_export(shell, commands[i]->args);
	else if (!ft_strcmp(builtin, "unset"))
		ft_delete_env_unset(commands[i]->args, shell);
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd(shell);
}

/*  choose_builtin() function is called in the main function, it will execute
	the builtin command that is passed as an argument. */

int	check_if_is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "pwd"))
		return (1);
	return (0);
}

/*  check_if_is_builtin() function is called in the main function, in the case 
	that the command is a builtin, it will return 1, otherwise it will 
	return 0. */
