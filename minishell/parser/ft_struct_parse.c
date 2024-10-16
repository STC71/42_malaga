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

void    ft_parse_command(char **cmd_break, int *i, t_cmd *struct_command)
{
    int     n_args;
    int     n_in;
    int     n_out;

    n_args = 0;
    n_in = 0;
    n_out = 0;

    while (cmd_break[*i] && strcmp(cmd_break[*i], "|") != 0)
    {
        if (strcmp(cmd_break[*i], ">") == 0 || strcmp(cmd_break[*i], ">>") == 0)
            ft_handling_inside(cmd_break, i, struct_command, &n_out);
        else if (strcmp(cmd_break[*i], "<") == 0 
            || strcmp(cmd_break[*i], "<<") == 0)
            ft_handling_inside(cmd_break, i, struct_command, &n_in);
        else
        {
            if (struct_command->cmd == NULL)
                struct_command->cmd = ft_strdup(cmd_break[*i]);
            else
                struct_command->args[n_args++] = ft_strdup(cmd_break[*i]);
            (*i)++;
        }
    }
}

/* The ft_parse_input() function reads the input from the user, parses it into
    tokens, and prints the tokens to the screen. It takes a pointer to a 
    t_minishell structure as an argument. */

/* The ft_parse_command() function parses the command into tokens. It takes 
    three arguments: an array of strings, a pointer to an index, and a pointer
    to a t_cmd structure. It uses the array of strings to parse the command into
    tokens, the index to keep track of the current token, and the t_cmd 
    structure to store the tokens. */
