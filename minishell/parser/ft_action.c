/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 15:22:38 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 15:22:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_parse_input(t_minishell *minishell)
{
    minishell->full_cmd = ft_shell_split(minishell->prompt);
    if (minishell->prompt[ft_strlen(minishell->prompt) - 1] == ' ')
        minishell->full_cmd = ft_remove_last(minishell->full_cmd);
    ft_env_var(minishell, minishell->env);
}

void    ft_action_parse(t_minishell *minishell, char *line)
{
    minishell->prompt = line;
    minishell->error_parse = 0;
    ft_spc_remove(minishell->prompt);
    if (ft_check_cmd(minishell))
    {
        ft_printf("Error: invalid command\n");
        minishell->error_parse = EXIT_FAILURE;
        minishell->prompt = NULL;
        return ;
    }
    ft_parse_input(minishell);
    minishell->split_cmd = ft_copy_mtx(minishell->split_cmd);
    ft_free_vector(minishell->full_cmd);
    ft_free_vector(minishell->split_cmd);
}

void    ft_spc_remove(char *spaces)
{
    int     rmv;

    if (!spaces)
        return ;
    rmv = ft_strlen(spaces);
    while (rmv > 0 && spaces[rmv - 1] == ' ')
    {
        rmv--;
    }
    spaces[rmv] = '\0';
}

/* The ft_parse_input() function is used to parse the input from the user. It
   takes one argument: a pointer to a t_minishell structure. It calls the
   ft_shell_split() function to split the input, the ft_remove_last() function
   to remove the last element of the matrix of strings, and the ft_env_var()
   function to substitute the environment variables. */

/* The ft_action_parse() function processes the input from the user. It takes
   two arguments: a pointer to a t_minishell structure and a string. It calls
   the ft_spc_remove() function to remove the spaces from the input, the
   ft_check_cmd() function to check if the command is valid, the ft_parse_
   input() function to parse the input, the ft_copy_mtx() function to copy the
   matrix of strings, and the ft_free_vector() function to free the memory
   allocated for the matrix of strings. */

/* The ft_spc_remove() function removes the spaces from the input. It takes one
    argument: a string that contains the input, and using a while loop, it
    removes the spaces from the end of the string. */