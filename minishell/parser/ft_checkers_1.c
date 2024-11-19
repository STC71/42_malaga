/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 15:42:43 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 15:42:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Comprobamos que las combinaciones de pipes y redirecciones son correctas. */
int	ft_check_pipe_n_red_mixes(char *prompt, int *pos)
{
	if (prompt[*pos] == '<')
	{
		if (prompt[*pos + 1] == '<' || prompt[*pos + 1] == '>')
			*pos += 2;
		else
			*pos += 1;
	}
	else if (prompt[*pos] == '>')
	{
		if (prompt[*pos + 1] == '>')
			*pos += 2;
		else
			*pos += 1;
	}
	while (prompt[*pos] == ' ' || prompt[*pos] == '\t')
		*pos += 1;
	if (prompt[*pos] == '<' || prompt[*pos] == '>' || prompt[*pos] == '|')
		return (0);
	return (1);
}

/* Verificamos que el ultimo caracter valido no sea ni "|" ni "<" ni ">". */
int	ft_check_last(char *prompt)
{
	int	i;

	if (ft_strlen(prompt) > 0)
		i = ft_strlen(prompt) - 1;
	else
		i = 0;
	while (i >= 0 && (prompt[i] == ' ' || prompt[i] == '\t'))
		i--;
	if (prompt[i] && (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>'))
		return (0);
	return (1);
}

/* Comprueba q las pipes sean las permitidas y las redirecciones
estén bien abiertas y cerradas */
int	ft_check_red_and_pipe(char *prompt)
{
	int			i;
	int			state;
	t_pipe_red	val;

	i = 0;
	state = NO_QUOTE; // (0)
	ft_action_pipe_redir(&val);
		// Inicializa la estructura para controlar los pipes y redicrecciones (red).
	while (prompt[i])
	{
		state = ft_quotes_state(prompt[i], state);
			// actualiza el estado de las comillas (quote) revisando todo el prompt.
		if (state == NO_QUOTE) // si no tiene comillas (NO_QUOTE)
		{
			if (ft_pipe_redir(prompt[i], &val, prompt, &i) == 0)
				// si devuelve 0 es q hay un error en las pipes o redirecciones
				return (0);
		}
		i++;
	}
	return (ft_check_last(prompt));
		// verifica q el último carácter no sea una pipe o redirección.
}

/* Comprobamos que no haya un pipe en el primer caracter valido */
int	ft_check_pipe_in(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] == ' ' || prompt[i] == '\t')
		// salta los espacios y tabuladores
		i++;
	if (prompt[i] == '|') 
		// si el primer caracter es un pipe
		return (0);
	return (1);
}

/* Va cambiando el estado de los pipes y redireciones.*/
void	ft_check_red_or_pipe(t_pipe_red *val, int i)
{
	if (i == 1) // si flag = 1 es q hay una pipe
	{
		val->pipe = 1;
		val->red = 0;
	}
	else if (i == 2) // si flag = 2 es q hay una redirección
	{
		val->pipe = 0;
		val->red = 1;
	}
	else if (i == 3) // si flag = 3 es q no hay ni pipe ni redirección
	{
		val->pipe = 0;
		val->red = 0;
	}
}
