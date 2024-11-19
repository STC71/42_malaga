/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 12:00:37 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 12:00:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Manejar los pipes y la redirecciones (sino tiene comillas)*/
int	ft_pipe_redir(char c, t_pipe_red *val, char *prompt, int *in)
{
	if (c == '|')
	{
		if (val->pipe == 1 || !ft_check_pipe_in(prompt))
			// si hay una pipe y está en la primera posición
			return (SUCCESS);
		ft_check_red_or_pipe(val, 1); 
			// marca en la estrcutura q hay una pipe
	}
	else if (c == '<' || c == '>')
	{
		if (val->red == 1 || !ft_check_pipe_n_red_mixes(prompt, in))
			// si hay redirecciónes y las mezclas son incorrectas
			return (SUCCESS);
		ft_check_red_or_pipe(val, 2); 
			// marca en la estrcutura q hay una redirección
	}
	else // si no hay ni pipe ni redirección
		ft_check_red_or_pipe(val, 3);
			// marca en la estrcutura q no hay ni pipe ni redirección
	return (FAILURE);
}

/*
	Calcula la longuitud de una palabra dentro de prompt, empezando en pos y
	terminando cuando encuentre un espacio, "|", "<" o ">".
	NO SE USA. ¿¿¿¿...????
*/
int	ft_len_word(char *prompt, int i)
{
	int	len;

	len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '|'
		&& prompt[i] != '<' && prompt[i] != '>')
	{
		len++;
		i++;
	}
	return (len);
}

// NO SE USA ¿¿¿...??? 
void	ft_no_spc_entry(char **new, char *old)
{
	char	*aux;

	aux = ft_strjoin(new[ft_string_len(new) - 1], old);
	free(new[ft_string_len(new) - 1]);
	new[ft_string_len(new) - 1] = aux;
}

/* Inicializa a 0 la estructura val para controlar los pipes y redicrecciones (red).
No se usa. ¿¿¿¿...???? */

void	ft_action_pipe_redir(t_pipe_red *val)
{
	val->pipe = 0;
	val->red = 0;
}

/*
	Nuestro ft_shell_split: separamos el prompt por grupos de string.
*/
char	**ft_shell_split(char *prompt)
{
	int		i;
	char	*tmp;
	char	**new;

	i = 0;
	new = NULL;
	while (prompt[i])
	{
		while (prompt[i] == ' ')
			i++;
		if (!prompt[i])
			break ;
		tmp = ft_token_director(prompt, &i);
		if (!new)
			new = ft_string_new(tmp);
		else
			new = ft_string_add(new, tmp);
		free(tmp);
	}
	return (new);
}
