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

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*	ft_free_array() function is used to free the memory allocated for the 
	array. */

void	ft_free_commands(t_cmd *commands)
{
	if (!commands)
		return ;
	free(commands->cmd);
	ft_free_array(commands->args);
	ft_free_array(commands->incmd);
	ft_free_array(commands->outcmd);
	free(commands);
}

/*	ft_free_commands() function is used to free the memory allocated for the 
	commands. */

void	ft_free_env_vars(t_var **vars)
{
	int	i;

	if (!vars)
		return ;
	i = 0;
	while (vars[i])
	{
		ft_free_vars(vars[i]);
		i++;
	}
	free(vars);
}

/*	ft_free_env_vars() function is used to free the memory allocated for the 
	environment variables. */

void	ft_free_structures(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->cmds)
	{
		i = 0;
		while (shell->cmds[i])
		{
			ft_free_commands(shell->cmds[i]);
			i++;
		}
		free(shell->cmds);
	}
}

/*	ft_free_structures() function is used to free the memory allocated for the 
	structures. */

void	ft_free_vars(t_var *vars)
{
	if (!vars)
		return ;
	free(vars->key);
	free(vars->value);
	free(vars);
}

/*	ft_free_vars() function is used to free the memory allocated for the 
	environment variables. */
