/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 11:50:34 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 11:50:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_token_director(char *prompt, int *i)
{
	if (prompt[*i] == '|')
		return (ft_handles_pipe(prompt, i));
	else if (prompt[*i] == '<')
		return (ft_handles_redir_in(prompt, i));
	else if (prompt[*i] == '>')
		return (ft_handles_redir_out(prompt, i));
	else
		return (ft_handles_characters(prompt, i));
}

/*
	Procesa una parte de caracteres que sean pipes consecutivos.
*/
char	*ft_handles_pipe(char *prompt, int *i)
{
	char	*tmp;
	int		j;
	int		len;

	j = *i;
	len = 0;
	while (prompt[j] == '|')
	{
		len++;
		j++;
	}
	tmp = ft_substr(prompt, *i, len);
	*i += len;
	return (tmp);
}

/*
	Procesa una parte de caracteres que sean "<" consecutivos.
*/
char	*ft_handles_redir_in(char *prompt, int *i)
{
	char	*tmp;
	int		j;
	int		len;

	j = *i;
	len = 0;
	while (prompt[j] == '<')
	{
		len++;
		j++;
	}
	tmp = ft_substr(prompt, *i, len);
	*i += len;
	return (tmp);
}

/*
	Procesa una parte de caracteres que sean ">" consecutivos.
*/
char	*ft_handles_redir_out(char *prompt, int *i)
{
	char	*tmp;
	int		j;
	int		len;

	j = *i;
	len = 0;
	while (prompt[j] == '>')
	{
		len++;
		j++;
	}
	tmp = ft_substr(prompt, *i, len);
	*i += len;
	return (tmp);
}

/*
	Procesa una subcadena de caracteres "normales" consecutivos.
*/
char	*ft_handles_characters(char *prompt, int *i)
{
	char	*c;
	char	*tmp;
	char	*res;

	res = ft_strdup("");
	while (prompt[*i] && prompt[*i] != ' ' && prompt[*i] != '|'
		&& prompt[*i] != '<' && prompt[*i] != '>')
	{
		if (prompt[*i] == '\"')
			c = ft_handles_double_quotes(prompt, i);
		else if (prompt[*i] == '\'')
			c = ft_handles_single_quotes(prompt, i);
		else
			c = ft_substr(prompt, (*i)++, 1);
		tmp = ft_strjoin(res, c);
		free(res);
		free(c);
		res = tmp;
	}
	return (res);
}
