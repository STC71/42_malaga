/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:56:11 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/24 10:42:03 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_err_isdirectory(DIR *dir)
{
	write(STDERR_FILENO, ": is a directory", 16);
	closedir(dir);
}

void	execute_child_proces(char *path, char **exc, t_shell *shell)
{
	if (shell->fdin > 2)
	{
		dup2(shell->fdin, STDIN_FILENO);
		close(shell->fdin);
	}
	if (shell->fdout > 2)
	{
		dup2(shell->fdout, STDOUT_FILENO);
		close(shell->fdout);
	}
	if (ft_strchr(path, '/') != NULL)
		execve(path, exc, shell->env);
	shell->g_status = write_bin_error(path, shell);
	exit(shell->g_status);
}

/*  execute_child_proces() function is used to execute the command in the child
	process. It checks that the fdin, out have been set and sets them as the
	standard output and input, then closes them. Then it checks that the path
	contains a "/" and executes it and exits the child process with EXIT.
	The function is necessary to execute the command in the child process. */

char	**create_matrix_cmd_and_args(t_cmd **commands, int i)
{
	char	**matrix;
	int		j;

	j = 0;
	while (commands[i]->args[j] != NULL && commands[i]->args != NULL)
		j++;
	matrix = calloc(j + 1, sizeof(char *));
	j = 0;
	matrix[j] = ft_strdup(commands[i]->cmd);
	j++;
	if (commands[i]->args != NULL)
	{
		while (commands[i]->args[j - 1] != NULL && commands[i]->args != NULL)
		{
			matrix[j] = ft_strdup(commands[i]->args[j - 1]);
			j++;
		}
	}
	matrix[j] = NULL;
	return (matrix);
}

/*  create_matrix_cmd_and_args() function is used to create a matrix that 
	contains the command and its arguments to be used in a child process.
	It is used by the execute_bin_cmd() function to execute the command in the
	child process. */

void	exec_bin_cmd(char *cmd_path, t_cmd **commands, t_shell *shell, int i)
{
	pid_t	child_id;
	int		status_of_process;
	char	**command_args;

	command_args = create_matrix_cmd_and_args(commands, i);
	child_id = fork();
	if (child_id == 0)
		execute_child_proces(cmd_path, command_args, shell);
	waitpid(child_id, &status_of_process, 0);
	shell->g_status = status_of_process;
	if (shell->fdin > 2)
		close(shell->fdin);
	if (shell->fdout > 2)
		close(shell->fdout);
	if (shell->g_status == 32512 || shell->g_status == 32256)
		shell->g_status /= 256;
	ft_str_free(command_args);
}

/*  execute_bin_cmd() function is used to execute the command bin with the full
	path or with the command only if the path does not exist. It does it in a
	child process. Then it checks if the fdin and out are > 2 (0, 1, 2 correspond
	to stdin, stdout and stderror), that is, if they have been set manually. If
	so, it closes them. */
