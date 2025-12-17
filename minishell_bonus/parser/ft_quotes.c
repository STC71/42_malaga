/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 09:54:16 by sternero          #+#    #+#             */
/*   Updated: 2024-10-18 09:54:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_double_quotes(int val)
{
	if (val == NO_QUOTE)
		return (DQ_OPEN);
	else if (val == DQ_OPEN)
		return (NO_QUOTE);
	else
		return (val);
}

/*	ft_check_double_quotes() function is used to check if the quote character is
	a double quote and update the state accordingly. */

int	ft_check_single_quotes(int val)
{
	if (val == NO_QUOTE)
		return (SQ_OPEN);
	else if (val == SQ_OPEN)
		return (NO_QUOTE);
	else
		return (val);
}

/*	ft_check_single_quotes() function is used to check if the quote character is
	a single quote and update the state accordingly. */

int	ft_check_quotes(char quotes, int old)
{
	int	new;

	new = old;
	if (quotes == '\"')
		new = ft_check_double_quotes(old);
	else if (quotes == '\'')
		new = ft_check_single_quotes(old);
	return (new);
}

/*	ft_check_quotes() function is used to check if the quote character is a 
	single or double quote and update the state accordingly. */

int	ft_quotes_state(char c, int state)
{
	return (ft_check_quotes(c, state));
}

/*	ft_quotes_state() function is used to update the state of the quotes. */

void	ft_del_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				str[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

/*	ft_del_quotes() function is used to delete the quotes, single or double, 
	from a string where they are. */
