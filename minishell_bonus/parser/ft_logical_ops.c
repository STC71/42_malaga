/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_logical_op(char c1, char c2)
{
	if (c1 == '&' && c2 == '&')
		return (1);
	if (c1 == '|' && c2 == '|')
		return (1);
	return (0);
}

int	ft_has_logical_ops(char *prompt)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && ft_is_logical_op(prompt[i], prompt[i + 1]))
			return (1);
		if (!in_quotes && prompt[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

t_ast	*ft_create_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[alloc] ft_create_ast_node: node=%p type=%d\n",
			(void *)node, (int)type);
	node->type = type;
	node->cmds = NULL;
	node->left = NULL;
	node->right = NULL;
	node->raw_cmd = NULL;
	return (node);
}

void	ft_free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[free] ft_free_ast: node=%p type=%d\n",
			(void *)node, (int)node->type);
	if (node->left)
		ft_free_ast(node->left);
	if (node->right)
		ft_free_ast(node->right);
	if (node->raw_cmd)
		free(node->raw_cmd);
	if (node->cmds)
	{
		i = 0;
		while (node->cmds[i])
			free(node->cmds[i++]);
		free(node->cmds);
	}
	free(node);
}
