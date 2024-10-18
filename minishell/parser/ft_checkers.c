/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 15:42:43 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 15:42:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_check_cmd(t_minishell *minishell)
{
    int     i;
    int     j;

    i = 0;
    j = NO_QUOTE;
    while (minishell->prompt[i])
    {
        if (minishell->prompt[i] == '\"' ||  minishell->prompt[i] == '\'')  
            j = ft_check_quotes(minishell->prompt, j);
        i++;
    }
    if (ft_chek_first_pipe(minishell->prompt) == 0)
        return (0);
    else
        return (ft_validating_pipes(minishell->prompt));
}

int     ft_chek_first_pipe (char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

int     ft_check_last_pipe (char *str)
{
    int     i;

    i = ft_strlen(str) - 1;
    while (i >= 0)
    {
        if (str[i] == '|')
            return (1);
        i--;
    }
    return (0);
}

int     ft_check_mixes(char *str, int *i)
{
    if (str[*i] == '>') 
    {
        if (str[*i + 1] == '>')
            return (2);
        else
            return (1);
    }
    if (str[*i] == '<')
    {
        if (str[*i + 1] == '<')
            return (4);
        else
            return (3);
    }
    while (str[*i] == ' ' || str[*i] == '\t')
        (*i)++;
    if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
        return (0);
    return (-1);
}

int     ft_validating_pipes(char *str)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '|')
            j++;
        i++;
    }
    if (j == 0)
        return (0);
    return (1);
}

/* The ft_check_cmd() function checks if a command is valid. It is valid if it
    contains valid pipe characters. It takes a pointer to a t_minishell structure
    as an argument. It returns 1 if the command is valid, and 0 if the command is
    not valid. */

/* The ft_chck_first_pipe() function checks if a string contains a pipe character
    at the beginning. It takes one argument: a string. It returns 1 if the string
    contains a pipe character at the beginning, and 0 if the string does not
    contain a pipe character at the beginning. */

/* The ft_check_last_pipe() function checks if a string contains a pipe character   
    at the end. It takes one argument: a string. It returns 1 if the string
    contains a pipe character at the end, and 0 if the string does not contain a
    pipe character at the end. */

/* The ft_check_mixes() function checks if a string contains valid pipe characters.
    It takes two arguments: a string and a pointer to an integer. It returns 0 if
    the string contains valid pipe characters, 1 if the string contains a single
    right pipe character, 2 if the string contains a double right pipe character,
    3 if the string contains a single left pipe character, 4 if the string contains
    a double left pipe character, and -1 if the string does not contain valid pipe
    characters. After checking for valid pipe characters, the function skips any
    whitespace characters or tabs. Finaly it checks if the string contains a pipe
    character. */ 

/* The ft_validating_pipes() function checks if a string contains valid pipe
    characters. It takes one argument: a string. It returns 1 if the string
    contains valid pipe characters, and 0 if the string does not contain valid
    pipe characters. */