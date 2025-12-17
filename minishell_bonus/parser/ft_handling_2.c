/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-15 17:46:32 by sternero          #+#    #+#             */
/*   Updated: 2024-10-15 17:46:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipes_nbr(char **str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (strcmp(str[i], "|") == 0)
			res++;
		i++;
	}
	return (res);
}

/*	ft_pipes_nbr function is used to count the number of pipes in the string. */

void	ft_handles_in_redir(char **split, int *i, t_cmd *cmd, int *cont)
{
	cmd->incmd[(*cont)++] = strdup(split[*i]);
	(*i)++;
	if (split[*i])
		cmd->incmd[(*cont)++] = strdup(split[(*i)++]);
}

/*	ft_handles_in_redir() function is used to handle a part of consecutive "<" 
	characters. It recieves the split and the position of the character to 
	start reading, and returns a substring with the consecutive "<" characters.
	*/

void	ft_handles_out_redir(char **split, int *i, t_cmd *cmd, int *cont)
{
	cmd->outcmd[(*cont)++] = strdup(split[*i]);
	(*i)++;
	if (split[*i])
		cmd->outcmd[(*cont)++] = strdup(split[(*i)++]);
}

/*	ft_handles_out_redir() function is used to handle a part of consecutive ">" 
	characters. It recieves the split and the position of the character to 
	start reading, and returns a substring with the consecutive ">" characters.
	*/
