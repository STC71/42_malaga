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

int     ft_num_pipe(char *str)
{
    int i;
    int n_pipe;

    i = 0;
    n_pipe = 0;
    while (str[i])
    {
        if (str[i] == '|')
            n_pipe++;
        i++;
    }
    return (n_pipe);
}

/* The ft_chck_pipe() function checks if a string contains a pipe character. It
    takes one argument: a string. It returns 1 if the string contains a pipe
    character, and 0 if the string does not contain a pipe character. */

/* The ft_check_redirection() function checks if a character is a redirection
    character. It takes two arguments: a string and an index. It returns 1 if
    the character is a '>', 2 if the character is a '<', and 0 if the character
    is not a redirection character. */

/* The ft_num_pipe() function counts the number of pipe characters in a string.
    It takes one argument: a string. It returns the number of pipe characters in
    the string. */
