/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 10:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-23 10:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_execute_and(t_ast *node, t_shell *shell)
{
	int	left_status;
	int	right_status;

	left_status = ft_execute_ast(node->left, shell);
	if (left_status == 0)
	{
		right_status = ft_execute_ast(node->right, shell);
		return (right_status);
	}
	return (left_status);
}

/*	ft_execute_and() executes && operator: right side only if left succeeds
	Returns: right status if left succeeded, left status otherwise */

static int	ft_execute_or(t_ast *node, t_shell *shell)
{
	int	left_status;
	int	right_status;

	left_status = ft_execute_ast(node->left, shell);
	if (left_status != 0)
	{
		right_status = ft_execute_ast(node->right, shell);
		return (right_status);
	}
	return (left_status);
}

/*	ft_execute_or() executes || operator: right side only if left fails
	Returns: left status if left succeeded, right status otherwise */

static int	ft_execute_seq(t_ast *node, t_shell *shell)
{
	int	right_status;

	ft_execute_ast(node->left, shell);
	right_status = ft_execute_ast(node->right, shell);
	return (right_status);
}

/*	ft_execute_seq() executes ; operator: both commands run sequentially
	Returns: exit status of second command (last executed) */

int	ft_execute_ast(t_ast *node, t_shell *shell)
{
	int	status;

	if (!node)
		return (1);
	if (node->type == NODE_AND)
		status = ft_execute_and(node, shell);
	else if (node->type == NODE_OR)
		status = ft_execute_or(node, shell);
	else if (node->type == NODE_SEQ)
		status = ft_execute_seq(node, shell);
	else if (node->type == NODE_CMD)
		status = ft_execute_cmd_node(node, shell);
	else if (node->type == NODE_SUBSHELL)
		status = ft_execute_simple_cmd(node->raw_cmd, shell);
	else
		status = 0;
	shell->g_status = status;
	return (status);
}

/*	ft_execute_ast() recursively executes AST from root node
	Handles: NODE_AND, NODE_OR, NODE_SEQ, NODE_CMD, NODE_SUBSHELL
	Returns: exit status of the command tree */
