/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 12:54:44 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 12:54:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_parse_input(t_minishell *minishell)
{
    char    *input;
    char    **tokens;
    int     i;

    input = readline(SHELL_PROMPT);
    if (!input)
        return ;
    add_history(input);
    tokens = ft_top_split(input);
    i = 0;
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }
    free(input);
    free(tokens);
}

/* The ft_parse_input() function reads the input from the user, parses it into
    tokens, and prints the tokens to the screen. It takes a pointer to a 
    t_minishell structure as an argument. */
