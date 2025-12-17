/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 18:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 18:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_ast_parsing(t_shell *shell)
{
	int	has_parens;
	int	has_ops;

	has_parens = ft_has_parentheses(shell->prompt);
	has_ops = ft_has_logical_ops(shell->prompt);
	if (has_ops)
	{
		shell->ast = ft_parse_logical_expr(shell->prompt, shell);
		if (shell->ast)
			return (1);
	}
	if (has_parens && !has_ops)
	{
		shell->ast = ft_parse_parentheses(shell->prompt, shell);
		if (shell->ast)
			return (1);
	}
	return (0);
}

/*	ft_handle_ast_parsing() function checks if the prompt has parentheses or
	logical operators and parses them accordingly. Returns 1 if AST was created,
	0 otherwise. */

void	ft_execute_command(t_shell *shell)
{
	if (shell->ast)
	{
		shell->g_status = ft_execute_ast(shell->ast, shell);
		ft_free_ast(shell->ast);
		shell->ast = NULL;
	}
	else
	{
		ft_expand_wildcards_all(shell);
		execute(shell->cmds, shell);
	}
}

/*	ft_execute_command() function executes the command stored in the shell
	structure. If there is an AST, it executes it, otherwise it expands
	wildcards and executes the normal command. */

void	ft_process_line(t_shell *shell, char *line)
{
	add_history(line);
	ft_action_prompt(shell, line);
	if (shell->parse_error == 0)
		ft_execute_command(shell);
}

/*	ft_process_line() function processes a valid line: adds it to history,
	parses the prompt, and executes the command if there are no parse errors. */
