/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_cmd_node(t_ast *node, t_shell *shell)
{
	int	status;

	if (node->raw_cmd)
		status = ft_execute_simple_cmd(node->raw_cmd, shell);
	else if (node->cmds)
	{
		execute(node->cmds, shell);
		status = shell->g_status;
	}
	else
		status = 0;
	return (status);
}

/*	ft_execute_cmd_node() executes NODE_CMD type node
	Returns: exit status of the command */

int	ft_execute_simple_cmd(char *cmd_str, t_shell *shell)
{
	char	*old_prompt;
	t_ast	*old_ast;
	int		status;

	old_prompt = shell->prompt;
	old_ast = shell->ast;
	shell->prompt = ft_strdup(cmd_str);
	if (!shell->prompt)
		return (1);
	ft_action_prompt(shell, shell->prompt);
	if (shell->parse_error == 0)
		execute(shell->cmds, shell);
	status = shell->g_status;
	free(shell->prompt);
	shell->prompt = old_prompt;
	shell->ast = old_ast;
	return (status);
}

/*	ft_execute_simple_cmd() executes a single command string through
	the normal minishell execution pipeline. Returns exit status. */
