/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-15 18:14:17 by sternero          #+#    #+#             */
/*   Updated: 2024-10-15 18:14:17 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_free_cmd(t_cmd *cmd)
{
    free(cmd->cmd);
    ft_free_vector(cmd->args);
    ft_free_vector(cmd->cmd_in);
    ft_free_vector(cmd->cmd_out);
    free(cmd);
}

void    ft_free_vector(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

/* The ft_free_cmd() function frees the memory allocated for a t_cmd 
    structure. It takes one argument: a pointer to a t_cmd structure, and
    call the ft_free_vector() function to free the memory allocated for the
    arguments, the input redirection command, and the output redirection
    command. */

/* The ft_free_vector() function frees the memory allocated for an array of
    strings. It takes one argument: an array of strings. The function frees
    the memory allocated for each string in the array and then frees the
    memory allocated for the array. */

