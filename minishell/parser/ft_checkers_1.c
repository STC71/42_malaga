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

/* ft_check_pipe_n_red_mixes() function is used to check if the combination of
	pipes and redirections is correct. This is necessary to avoid errors in the
	parsing. For example, if there is a pipe, there cannot be a redirection, and
	if there is a redirection, there cannot be a pipe. */

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

/*	ft_check_last() function is used to check that the last valid character is
	neither a pipe nor a redirection. This is important to avoid errors in the
	parsing. */

int	ft_check_red_and_pipe(char *prompt)
{
	int			i;
	int			state;
	t_pipe_red	val;

	i = 0;
	state = NO_QUOTE;
	ft_action_pipe_redir(&val);
	while (prompt[i])
	{
		state = ft_quotes_state(prompt[i], state);
		if (state == NO_QUOTE)
		{
			if (ft_pipe_redir(prompt[i], &val, prompt, &i) == 0)
				return (0);
		}
		i++;
	}
	return (ft_check_last(prompt));
}

/*	ft_check_red_and_pipe() function is used to check that the pipes are allowed
	and the redirections are well opened and closed. This is necessary to avoid
	errors in the parsing. */

int	ft_check_pipe_in(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] == ' ' || prompt[i] == '\t')
		i++;
	if (prompt[i] == '|')
		return (0);
	return (1);
}

/*	ft_check_pipe_in() function is used to check that there is no pipe in the
	first valid character. This is necessary to avoid errors in the parsing. */

void	ft_check_red_or_pipe(t_pipe_red *val, int i)
{
	if (i == 1)
	{
		val->pipe = 1;
		val->red = 0;
	}
	else if (i == 2)
	{
		val->pipe = 0;
		val->red = 1;
	}
	else if (i == 3)
	{
		val->pipe = 0;
		val->red = 0;
	}
}

/*	ft_check_red_or_pipe() function is used to change the state of the pipes and
	redirections. For example, if there is a pipe, the pipe flag will be set to 
	1, and the redirection flag will be set to 0. */
