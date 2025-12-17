/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_has_parentheses(char *prompt)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && (prompt[i] == '(' || prompt[i] == ')'))
			return (1);
		i++;
	}
	return (0);
}

static t_ast	*ft_parse_subshell_content(char *content, t_shell *shell)
{
	t_ast	*node;

	if (ft_has_logical_ops(content))
		return (ft_parse_logical_expr(content, shell));
	node = ft_create_ast_node(NODE_SUBSHELL);
	if (!node)
		return (NULL);
	node->raw_cmd = ft_strdup(content);
	if (!node->raw_cmd)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

static int	ft_find_first_paren(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && prompt[i] != '(')
		i++;
	if (prompt[i] == '(')
		return (i);
	return (-1);
}

t_ast	*ft_parse_parentheses(char *prompt, t_shell *shell)
{
	int			i;
	char		*content;
	t_ast		*node;

	if (!ft_has_parentheses(prompt) || !ft_check_parentheses(prompt))
	{
		if (ft_has_parentheses(prompt))
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		return (NULL);
	}
	i = ft_find_first_paren(prompt);
	if (i == -1)
		return (NULL);
	content = ft_extract_subshell(prompt, &i);
	if (!content)
		return (NULL);
	node = ft_parse_subshell_content(content, shell);
	free(content);
	return (node);
}
