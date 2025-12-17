/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:05 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 14:37:38 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_oldpwd(t_shell *shell, int i)
{
	if (shell->oldpwd != NULL && ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("OLDPWD=", shell->oldpwd);
	}
}

/*  reset_oldpwd() function is used to reset the OLDPWD environment variable to 
	the previous position. */

void	reset_old_pwd_and_lastcmd(t_shell *shell, t_cmd **commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		reset_oldpwd(shell, i);
		if (ft_strncmp(shell->env[i], "_=", 2) == 0)
		{
			if (commands[0]->args && commands[0]->args[0] != NULL)
			{
				while (commands[0]->args[j] != NULL)
					j++;
				free(shell->env[i]);
				shell->env[i] = ft_strjoin("_=", commands[0]->args[j - 1]);
			}
			else if (commands[0]->cmd != NULL)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strjoin("_=", commands[0]->cmd);
			}
		}
		i++;
	}
}

/*  reset_old_pwd_and_lastcmd() function is used to reset the OLDPWD and "_" 
	environment variables to the previous position. If the last command executed
	had arguments, only the last argument will be shown (neither the command nor
	the intermediate args), and if it didn't have args, only the command will be
	shown. */

void	check_if_builtin(t_cmd **commands, t_shell *shell, int i)
{
	shell->g_status = 0;
	if (commands[i]->cmd && check_if_is_builtin(commands[i]->cmd) == 1)
		choose_builtin(shell, commands, i);
	else if (commands[i]->cmd)
		execute_bin_cmd_main(commands, shell, i);
}

/*  check_if_builtin() functión checks if the command is a builtin or a system
	command (bin). If it is a builtin, it will execute the command, otherwise
	it will execute the system command. */

void	config_pipe(t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		write(STDERR_FILENO, "pipe: error creating pipe\n", 27);
		shell->exec_signal = 1;
		shell->g_status = 1;
	}
	else
	{
		shell->fdnextin = fd[0];
		shell->fdout = fd[1];
	}
}

/*  config_pipe() function is used to create a pipe and save the file
	descriptors	in the structure. It is important to create a pipe to
	communicate the	commands. */

void	execute(t_cmd **commands, t_shell *shell)
{
	int	i;

	i = 0;
	save_fds(shell);
	while (commands[i] != NULL)
	{
		shell->fdnextin = -1;
		if (commands[i + 1] != NULL)
			config_pipe(shell);
		else
			shell->fdout = STDOUT_FILENO;
		choose_redirections(commands[i]->incmd, shell);
		choose_redirections(commands[i]->outcmd, shell);
		if (commands[i]->cmd != NULL && shell->exec_signal == 0)
			check_if_builtin(commands, shell, i);
		if (shell->fdout > 2)
		{
			close(shell->fdout);
			shell->fdout = -1;
		}
		shell->fdin = shell->fdnextin;
		i++;
	}
	reset_old_pwd_and_lastcmd(shell, commands);
	reset_redirections(shell);
}

/*  execute() function is used to execute the commands. It saves the file 
	descriptors, configures the pipes, checks the redirections, checks if the 
	command is a builtin or a system command, and resets the redirections. */
