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

int	ft_pipe_redir(char c, t_pipe_red *val, char *prompt, int *in)
{
	if (c == '|')
	{
		if (val->pipe == 1 || !ft_check_pipe_in(prompt))
			return (SUCCESS);
		ft_check_red_or_pipe(val, 1); 
	}
	else if (c == '<' || c == '>')
	{
		if (val->red == 1 || !ft_check_pipe_n_red_mixes(prompt, in))
			return (SUCCESS);
		ft_check_red_or_pipe(val, 2); 
	}
	else
		ft_check_red_or_pipe(val, 3);
	return (FAILURE);
}

/*	ft_pip_redir() function is used to handle pipes and redirections. If there 
	is a pipe, it will check that the pipes are allowed and the redirections are
	well opened and closed. If there is a redirection, it will check that the 
	combination	of pipes and redirections is correct. */

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

/*	ft_len_word() function is used to calculate the length of a word within the
	prompt, starting at pos and ending when it finds a space, "|", "<" or ">".*/

void	ft_no_spc_entry(char **new, char *old)
{
	char	*aux;

	aux = ft_strjoin(new[ft_string_len(new) - 1], old);
	free(new[ft_string_len(new) - 1]);
	new[ft_string_len(new) - 1] = aux;
}

/*	ft_no_spc_entry() function is used to join the last two strings in the array
	new. This is necessary when there is no space between the strings. */

void	ft_action_pipe_redir(t_pipe_red *val)
{
	val->pipe = 0;
	val->red = 0;
}

/*	ft_action_pipe_redir() function is used to initialize the structure with the
	values of the pipes and redirections. */

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

/*	ft_shell_split() function is used to split the prompt into words. It is used
	by the ft_action_prompt() function to split the prompt into words. */
