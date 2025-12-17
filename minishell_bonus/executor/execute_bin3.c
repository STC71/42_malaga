/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:00 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/25 13:11:00 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_in_path(t_cmd **commands, t_shell *shell, int i,
		char **bin_paths)
{
	int	j;

	j = 0;
	while (bin_paths[j])
	{
		shell->cmd_path = join_binpath_andcmd(commands[i]->cmd, bin_paths[j++]);
		if (shell->cmd_path != NULL)
			break ;
	}
	if (shell->cmd_path != NULL)
	{
		ft_str_free(bin_paths);
		exec_bin_cmd(shell->cmd_path, commands, shell, i);
		free(shell->cmd_path);
	}
	else
	{
		ft_str_free(bin_paths);
		exec_bin_cmd(commands[i]->cmd, commands, shell, i);
	}
	shell->cmd_path = NULL;
}

/*  search_in_path() function searches for the command in the PATH directories
	and executes it if found. */
