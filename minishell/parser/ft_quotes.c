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

/* Cambiamos el chequeo de las comillas dobles (dq : doble quote). */
int	ft_check_double_quotes(int val)
{
	if (val == NO_QUOTE)
		return (DQ_OPEN);
	else if (val == DQ_OPEN)
		return (NO_QUOTE);
	else
		return (val);
}

/* Cambiamos el chequeo de las comillas simples (sq = simple quote). */
int	ft_check_single_quotes(int val)
{
	if (val == NO_QUOTE)
		return (SQ_OPEN);
	else if (val == SQ_OPEN)
		return (NO_QUOTE);
	else
		return (val);
}

/* verifica si el carácter quote es una comilla simple o doble y actualiza 
   el estado en consecuencia. */
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

/* Actualiza el estado de las comillas */
int	ft_quotes_state(char c, int state)
{
	return (ft_check_quotes(c, state));
}

/*
	Borra las comillas, simples o dobles, de un string (str)
	y da lo mismo donde esten.
*/
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
