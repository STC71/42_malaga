/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 09:25:27 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 09:25:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_mem_args(t_cmd *cmds, char **split)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (split[i] && strcmp(split[i], "|") != 0)
	{
		if (i > 0)
		{
			if (strcmp(split[i], ">") == 0 || strcmp(split[i], ">>") == 0
				|| strcmp(split[i], "<") == 0)
			{
				i += 2;
			}
			else
			{
				arg++;
				i++;
			}
		}
		else
			i++;
	}
	cmds->args = ft_calloc(arg + 1, sizeof(char *));
}

/*	ft_mem_args() function is used to reserve memory for the arguments of a 
	command. */

void	ft_mem_in(t_cmd *cmds, char **split)
{
	int	i;
	int	in;

	i = 0;
	in = 0;
	while (split[i] && strcmp(split[i], "|") != 0)
	{
		if (strcmp(split[i], "<") == 0 || strcmp(split[i], "<<") == 0)
		{
			in++;
			i++;
			if (split[i])
			{
				in++;
				i++;
			}
		}
		else
			i++;
	}
	cmds->incmd = ft_calloc(in + 1, sizeof(char *));
}

/*	ft_mem_in() function is used to reserve memory for the input redirections 
	of a command. */

void	ft_mem_out(t_cmd *cmds, char **split)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (split[i] && strcmp(split[i], "|") != 0)
	{
		if (strcmp(split[i], ">") == 0 || strcmp(split[i], ">>") == 0)
		{
			out++;
			i++;
			if (split[i])
			{
				out++;
				i++;
			}
		}
		else
			i++;
	}
	cmds->outcmd = ft_calloc(out + 1, sizeof(char *));
}

/*	ft_mem_out() function is used to reserve memory for the output redirections
	of a command. */

void	ft_mem_cmds(t_cmd **cmds, char **split)
{
	int	i;
	int	cmd_n;
	int	pos;

	i = 0;
	cmd_n = ft_pipes_nbr(split);
	pos = 0;
	while (i < cmd_n)
	{
		cmds[i] = ft_calloc(1, sizeof(t_cmd));
		cmds[i]->cmd = NULL;
		ft_mem_args(cmds[i], split + pos);
		ft_mem_in(cmds[i], split + pos);
		ft_mem_out(cmds[i], split + pos);
		while (split[pos] && strcmp(split[pos], "|") != 0)
			pos++;
		if (split[pos] && strcmp(split[pos], "|") == 0)
			pos++;
		i++;
	}
}

/*	ft_mem_cmds() function is used to reserve memory for the commands. */
