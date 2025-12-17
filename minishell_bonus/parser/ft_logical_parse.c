/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_ast	*ft_parse_parenthesis_cmd(char *trimmed, int len)
{
	t_ast	*node;
	char	*content;

	content = ft_substr(trimmed, 1, len - 2);
	if (!content)
		return (NULL);
	if (ft_has_logical_ops(content))
	{
		node = ft_parse_logical_expr(content, NULL);
		free(content);
		return (node);
	}
	node = ft_create_ast_node(NODE_SUBSHELL);
	if (node)
		node->raw_cmd = content;
	else
		free(content);
	return (node);
}

static t_ast	*ft_parse_simple_cmd(char *prompt)
{
	t_ast	*node;
	char	*trimmed;
	int		len;

	trimmed = prompt;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t'))
		len--;
	if (len > 2 && trimmed[0] == '(' && trimmed[len - 1] == ')')
		return (ft_parse_parenthesis_cmd(trimmed, len));
	node = ft_create_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->raw_cmd = ft_strdup(prompt);
	return (node);
}

static t_ast	*ft_create_op_node(char *prompt, int op_pos)
{
	if (prompt[op_pos] == '&')
		return (ft_create_ast_node(NODE_AND));
	else if (prompt[op_pos] == '|')
		return (ft_create_ast_node(NODE_OR));
	else
		return (ft_create_ast_node(NODE_SEQ));
}

static int	ft_parse_children(t_ast *node, char *left, char *right,
		t_shell *shell)
{
	node->left = ft_parse_logical_expr(left, shell);
	node->right = ft_parse_logical_expr(right, shell);
	if (!node->left || !node->right)
		return (0);
	return (1);
}

t_ast	*ft_parse_logical_expr(char *prompt, t_shell *shell)
{
	t_ast		*node;
	int			op_pos;
	char		*left;
	char		*right;

	if (!prompt || !*prompt)
		return (NULL);
	op_pos = ft_find_logical_op(prompt);
	if (op_pos == -1)
		return (ft_parse_simple_cmd(prompt));
	node = ft_create_op_node(prompt, op_pos);
	if (!node)
		return (NULL);
	left = ft_extract_left_cmd(prompt, op_pos);
	right = ft_extract_right_cmd(prompt, op_pos);
	if (!left || !right || !ft_parse_children(node, left, right, shell))
	{
		free(left);
		free(right);
		ft_free_ast(node);
		return (NULL);
	}
	free(left);
	free(right);
	return (node);
}
