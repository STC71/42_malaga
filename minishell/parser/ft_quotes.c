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

int     ft_check_quotes(char *str, int i)
{
    int     out;

    out = i;
    if (str[i] == '\'')
        out = ft_using_single(str);
    if (str[i] == '\"')
        out = ft_using_double(str);
    return (out);
}

int     ft_using_single(char *str)
{
    if (str == NO_QUOTE)
        return (SQ_OPEN);
    else if (str == SQ_OPEN)
        return (NO_QUOTE);
    else
        return (str);
}

int     ft_using_double(char *str)
{
    if (str == NO_QUOTE)
        return (DQ_OPEN);
    else if (str == DQ_OPEN)
        return (NO_QUOTE);
    else
        return (str);
}

/* The ft_check_quotes() function checks if a character is a quote. It used to
    gestionate the quotes in the command. It takes two arguments: a string and 
    an index. It returns DQ_OPEN if the character is a double quote, SQ_OPEN if 
    the character is a single quote, and NO_QUOTE if the character is not a 
    quote. For it is used the following functions: 
    ft_using_single() and ft_using_double(). */

/* The ft_using_single() function checks if a character is a single quote. It 
    takes one argument: a string. It returns SQ_OPEN if the character is a 
    single quote, NO_QUOTE if the character is not a quote, and the character 
    if the character is a double quote. */

/* The ft_using_double() function checks if a character is a double quote. It 
    takes one argument: a string. It returns DQ_OPEN if the character is a 
    double quote, NO_QUOTE if the character is not a quote, and the character 
    if the character is a single quote. */

/* Thats functions are necessary to determine the quotes in the command. */
