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

int     ft_check_quotes(char *str, int i)
{
    if (str[i] == '"')
        return (DQ_OPEN);
    if (str[i] == '\'')
        return (SQ_OPEN);
    return (NO_QUOTE);
}

int     ft_chck_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

int     ft_check_redirection(char *str, int i)
{
    if (str[i] == '>')
        return (1);
    if (str[i] == '<')
        return (2);
    return (0);
}

/* The ft_check_quotes() function checks if a character is a quote. It takes two
    arguments: a string and an index. It returns DQ_OPEN if the character is a
    double quote, SQ_OPEN if the character is a single quote, and NO_QUOTE if 
    the character is not a quote.*/

/* The ft_chck_pipe() function checks if a string contains a pipe character. It
    takes one argument: a string. It returns 1 if the string contains a pipe
    character, and 0 if the string does not contain a pipe character. */

/* The ft_check_redirection() function checks if a character is a redirection
    character. It takes two arguments: a string and an index. It returns 1 if
    the character is a '>', 2 if the character is a '<', and 0 if the character
    is not a redirection character. */
