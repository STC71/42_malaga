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
} // reserva memoria para los argumentos de un comando.

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
} // reserva memoria para las redirecciones de entrada de un comando.

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
} // reserva memoria para las redirecciones de salida de un comando.

void	ft_mem_cmds(t_cmd **cmds, char **split)
{
	int	i;
	int	cmd_n;

	i = 0;
	cmd_n = ft_pipes_nbr(split);
	while (i < cmd_n)
	{
		cmds[i] = ft_calloc(1, sizeof(t_cmd));
		cmds[i]->cmd = NULL;
		ft_mem_args(cmds[i], split);
		ft_mem_in(cmds[i], split);
		ft_mem_out(cmds[i], split);
		i++;
	}
} // reserva memoria para los comandos.