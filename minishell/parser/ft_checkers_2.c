/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 15:42:43 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 15:42:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Comprueba que no haya espacios ni tabuladores, sino devuelve 1(error)*/
int		ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	ft_check_cmd(t_shell *shell)
{
	int	i;
	int	state;

	i = 0;
	state = NO_QUOTE;
		// empieza estableciendo el estado de las comillas en 0 (sin comillas).
	while (shell->prompt[i])
	{
		if (shell->prompt[i] == '\"' || shell->prompt[i] == '\'')
			state = ft_check_quotes(shell->prompt[i], state);
				// compruebe si el carácter quote es una comilla simple o doble 
				// y actualiza el estado en consecuencia ( 0 , 1 o 2).
		i++;
	}
	if (ft_check_pipe_in(shell->prompt) == 0)
		return (SUCCESS);
	else
		return (ft_check_red_and_pipe(shell->prompt));
			// comprueba Que las pipes sean las permitidas y las redirecciones 
			// esten bien abiertas y cerradas 
} // comprueba que no haya pipes ni redirecciones en la primera posición.