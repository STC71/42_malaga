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

void	ft_parse_cmd(char **split_cmd, int *i, t_cmd *cmd_struct)
{
	int	arg;
	int	in;
	int	out;

	arg = 0;
	in = 0;
	out = 0;
	while (split_cmd[*i] && strcmp(split_cmd[*i], "|") != 0)
	{
		if (ft_strcmp(split_cmd[*i], "<") == 0
			|| ft_strcmp(split_cmd[*i], "<<") == 0)
			ft_handles_in_redir(split_cmd, i, cmd_struct, &in);
		else if (ft_strcmp(split_cmd[*i], ">") == 0
			|| ft_strcmp(split_cmd[*i], ">>") == 0)
			ft_handles_out_redir(split_cmd, i, cmd_struct, &out);
		else
		{
			if (cmd_struct->cmd == NULL)
				cmd_struct->cmd = ft_strdup(split_cmd[*i]);
			else
				cmd_struct->args[arg++] = ft_strdup(split_cmd[*i]);
			(*i)++;
		}
	}
}

/*	ft_parse_cmd() function is used to parse the command and store it in the 
	cmd_struct structure. When the command is parsed, it is stored in the
	cmd_struct structure. */

void	ft_parse_split(t_shell *shell)
{
	int		i;
	int		cmd;
	int		pipe;
	t_cmd	**cmds;

	i = 0;
	cmd = 0;
	pipe = ft_pipes_nbr(shell->split_cmd);
	cmds = ft_calloc(pipe + 1, sizeof(t_cmd *));
	ft_mem_cmds(cmds, shell->split_cmd);
	while (shell->split_cmd[i])
	{
		ft_parse_cmd(shell->split_cmd, &i, cmds[cmd]);
		if (shell->split_cmd[i] && strcmp(shell->split_cmd[i], "|") == 0)
			i++;
		cmd++;
	}
	i = 0;
	if (shell->cmds)
	{
		while (shell->cmds[i])
			ft_free_commands(shell->cmds[i++]);
		free(shell->cmds);
	}
	shell->cmds = cmds;
}

/*	ft_parse_split() function is used to parse the split_cmd and store it in the
	cmds structure. When the split_cmd is parsed, it is stored in the cmds 
	structure. */
