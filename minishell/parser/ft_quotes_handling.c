/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 13:24:11 by sternero          #+#    #+#             */
/*   Updated: 2024-10-18 13:24:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Procesa la parte de un array que está encerrada entre comillas dobles.
*/
char	*ft_handles_double_quotes(char *prompt, int *i)
{
	int		j;
	int		count;
	char	*tmp;

	j = 0;
	count = 0;
	tmp = ft_calloc(ft_strlen(prompt) - *i + 1, sizeof(char));
	while (prompt[*i] && count < 2)
	{
		if (prompt[*i] == '\"')
			count++;
		tmp[j++] = prompt[*i];
		(*i)++;
	}
	return (tmp);
}

/*
	Procesa la parte de un array que está encerrada entre comillas simples.
*/
char	*ft_handles_single_quotes(char *prompt, int *i)
{
	int		j;
	int		count;
	char	*tmp;

	j = 0;
	count = 0;
	tmp = ft_calloc(ft_strlen(prompt) - *i + 1, sizeof(char));
	while (prompt[*i] && count < 2)
	{
		if (prompt[*i] == '\'')
			count++;
		if (prompt[*i] == '$')
			tmp[j++] = (char)1;
		else
			tmp[j++] = prompt[*i];
		(*i)++;
	}
	return (tmp);
}

