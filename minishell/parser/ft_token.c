/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 12:46:08 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 12:46:08 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ft_top_split(char *str)
{
    char    **top;
    int     i;
    int     j;

    i = 0;
    j = 0;
    top = (char **)malloc(sizeof(char *) * (ft_count_top(str) + 1));
    if (!top)
        return (NULL);
    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else
        {
            top[j] = ft_process_word(str, &i);
            j++;
        }
    }
    top[j] = NULL;
    return (top);
}

char    *ft_process_tokens(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_word(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != ' ')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

char    ft_tokenize_vector(char *vector, int *pos)
{
    char    *out;
    char    *tmp;
    char    *txt;

    out = NULL;
    while (vector[*pos] && vector[*pos] != ' ' && vector[*pos] != '>'
        && vector[*pos] != '<' && vector[*pos] != '|')
    {
        if (vector[*pos] == '\'')
            txt = ft_process_single(vector, pos);
        else if (vector[*pos] == '\"')
            txt = ft_process_double(vector, pos);
        else
            txt = ft_extract_token(vector, (*pos)++, 1);
        tmp = ft_strjoin(out, txt);
        free(out);
        free(txt);
        out = tmp;
    }
        return (out);
}

void    ft_env_var(t_minishell *minishell, char **var)
{
    t_var	**list_var;
	int		i;
	char	*status;

	list_var = ft_init_env(var);
	status = ft_itoa(minishell->status);
	i = 0;
	while (minishell->full_cmd[i])
	{
		if (minishell->full_cmd[i][0] != '\'')
			ft_do_command(&minishell->full_cmd[i], list_var, status);
		i++;
	}
	ft_restore_dolar(minishell->full_cmd);
	free(status);
	i = 0;
	while (minishell->full_cmd[i] != NULL)
	{
		ft_remove_quotes(minishell->full_cmd[i]);
		i++;
	}
	ft_free_envs(list_var); // revisar nombres de funciones ********************
}

/* The ft_top_split() function splits a string into an array of strings. It 
    takes one argument: a string. It used to split the input into tokens, and
    returns an array of strings. */

/* The process_tokens() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. */

/* The ft_tokenize_vector() function processes the tokens in the vector. It 
    takes two arguments: a string and a pointer to an index. In the while loop,
    it checks if the character in the string is a space, a redirection character,
    or a pipe character. If the character is a single quote or a double quote,
    it calls the ft_process_single() or ft_process_double() function to extract
    the word. If the character is a token, it calls the ft_process_token()
    function to extract the word. */

/* The ft_env_var() function processes the environment variables. It takes two
    arguments: a pointer to a t_minishell structure and an array of strings. 
    It uses a t_var structure to store the environment variables in a linked
    list. ft_init_env() is used to initialize the list, ft_do_command() is used
    to execute the commands, ft_restore_dolar() is used to restore the $ symbol,
    ft_remove_quotes() is used to remove quotes from the strings, and
    ft_free_envs() is used to free the memory allocated for the list. */