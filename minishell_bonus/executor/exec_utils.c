/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@local>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/29 12:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_fork_failure(char **command_args, t_shell *shell)
{
	shell->g_status = 1;
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[error] fork failed free %p\n",
			(void *)command_args);
	unregister_orphan_alloc(shell, command_args);
	ft_str_free(command_args);
}

char	**prepare_command_args(t_cmd **commands, int i, t_shell *shell)
{
	char	**command_args;

	command_args = create_matrix_cmd_and_args(commands, i);
	if (!command_args)
		shell->g_status = 1;
	return (command_args);
}

void	print_exec_debug(char **command_args, char *cmd0)
{
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[exec] cmd_args=%p cmd=%s\n",
			(void *)command_args, cmd0);
}

void	close_child_fdout(t_shell *shell)
{
	if (shell->fdout > 2)
		close(shell->fdout);
}
