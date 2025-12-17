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

static void	post_wait_cleanup(char **command_args, t_shell *shell,
	int status_of_process)
{
	if (WIFEXITED(status_of_process))
		shell->g_status = WEXITSTATUS(status_of_process);
	else if (WIFSIGNALED(status_of_process))
		shell->g_status = 128 + WTERMSIG(status_of_process);
	if (shell->fdin > 2)
		close(shell->fdin);
	if (shell->fdout > 2)
		close(shell->fdout);
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[exec] freeing %p\n", (void *)command_args);
	unregister_orphan_alloc(shell, command_args);
	ft_str_free(command_args);
}

void	execute_child_proces(char *path, char **exc, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	ft_str_free(exc);
	exit(shell->g_status);
}

static int	fill_args(char **matrix, t_cmd **commands, int i)
{
	int	k;

	k = 0;
	while (commands[i]->args && commands[i]->args[k])
	{
		matrix[k + 1] = ft_strdup(commands[i]->args[k]);
		if (!matrix[k + 1])
		{
			while (k >= 0)
				free(matrix[k--]);
			return (-1);
		}
		k++;
	}
	return (k);
}

char	**create_matrix_cmd_and_args(t_cmd **commands, int i)
{
	char	**matrix;
	int		j;
	int		k;

	j = 0;
	while (commands[i]->args && commands[i]->args[j])
		j++;
	matrix = calloc(j + 2, sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[0] = ft_strdup(commands[i]->cmd);
	if (!matrix[0])
	{
		free(matrix);
		return (NULL);
	}
	k = fill_args(matrix, commands, i);
	if (k < 0)
	{
		free(matrix);
		return (NULL);
	}
	matrix[k + 1] = NULL;
	return (matrix);
}

/* create_matrix_cmd_and_args: create argv matrix for execve */
void	exec_bin_cmd(char *cmd_path, t_cmd **commands, t_shell *shell, int i)
{
	pid_t	child_id;
	int		status_of_process;
	char	**command_args;
	char	*cmd0;

	command_args = prepare_command_args(commands, i, shell);
	if (!command_args)
		return ;
	cmd0 = "(null)";
	if (command_args && command_args[0])
		cmd0 = command_args[0];
	print_exec_debug(command_args, cmd0);
	child_id = fork();
	if (child_id == 0)
		execute_child_proces(cmd_path, command_args, shell);
	if (child_id > 0)
		close_child_fdout(shell);
	if (child_id == -1)
	{
		handle_fork_failure(command_args, shell);
		return ;
	}
	waitpid(child_id, &status_of_process, 0);
	post_wait_cleanup(command_args, shell, status_of_process);
}

/* execute_bin_cmd: execute a binary command in a child process */
