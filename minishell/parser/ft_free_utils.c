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
    ft_free_strd(cmd->args);
    ft_free_strd(cmd->cmd_in);
    ft_free_strd(cmd->cmd_out);
    free(cmd);
}

