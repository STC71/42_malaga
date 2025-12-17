/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_ops_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_op_at_pos(char *prompt, int i, int *semicolon_pos)
{
	if (prompt[i] == '|' && prompt[i + 1] == '|')
		return (i);
	if (prompt[i] == '&' && prompt[i + 1] == '&')
		return (i);
	if (prompt[i] == ';' && *semicolon_pos == -1)
		*semicolon_pos = i;
	return (-1);
}

static void	ft_update_quote_paren(char c, int *in_quotes, int *paren_level)
{
	if (c == '\'' || c == '\"')
		*in_quotes = !(*in_quotes);
	if (!(*in_quotes) && c == '(')
		(*paren_level)++;
	if (!(*in_quotes) && c == ')')
		(*paren_level)--;
}

int	ft_find_logical_op(char *prompt)
{
	int	i;
	int	in_quotes;
	int	paren_level;
	int	semicolon_pos;
	int	result;

	i = 0;
	in_quotes = 0;
	paren_level = 0;
	semicolon_pos = -1;
	while (prompt[i])
	{
		ft_update_quote_paren(prompt[i], &in_quotes, &paren_level);
		if (!in_quotes && paren_level == 0)
		{
			result = ft_check_op_at_pos(prompt, i, &semicolon_pos);
			if (result != -1)
				return (result);
		}
		i++;
	}
	return (semicolon_pos);
}
