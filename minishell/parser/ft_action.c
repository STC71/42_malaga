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
    minishell->full_cmd = super_split(minishell->prompt); //no implementada ****
    if (minishell->prompt[ft_strlen(minishell->prompt) - 1] == ' ')
        minishell->full_cmd = ft_remove_last(minishell->full_cmd);
    expand_env_var(minishell, minishell->env);    //no implementada ************
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
    // función pendiente de implementar ****************************************
    minishell->split_cmd = ft_matrixdup(minishell->split_cmd);
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
