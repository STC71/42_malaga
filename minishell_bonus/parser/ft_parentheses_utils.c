/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_matching_paren(char *str, int start)
{
	int	i;
	int	level;
	int	in_quotes;

	i = start + 1;
	level = 1;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == '(')
			level++;
		if (!in_quotes && str[i] == ')')
		{
			level--;
			if (level == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*ft_extract_subshell(char *prompt, int *i)
{
	int		end;
	int		len;
	char	*sub;

	end = ft_find_matching_paren(prompt, *i);
	if (end == -1)
		return (NULL);
	len = end - *i - 1;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, prompt + *i + 1, len + 1);
	*i = end;
	return (sub);
}

static int	ft_count_open(char *str)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == '(')
			count++;
		i++;
	}
	return (count);
}

static int	ft_count_close(char *str)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == ')')
			count++;
		i++;
	}
	return (count);
}

int	ft_check_parentheses(char *prompt)
{
	if (ft_count_open(prompt) != ft_count_close(prompt))
		return (0);
	return (1);
}
