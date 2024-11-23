/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:35:03 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:46:08 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_delete_env_unset(char **name_var, t_shell *shell)
{
	int	x;
	int	i;
	int	j;

	x = -1;
	while (name_var[++x] != NULL)
	{
		i = -1;
		while (shell->env[++i] != NULL)
		{
			if (!ft_strncmp(shell->env[i], name_var[x], ft_strlen(name_var[x]))
				&& shell->env[i][ft_strlen(name_var[x])] == '=')
			{
				free(shell->env[i]);
				j = i;
				while (shell->env[j] != NULL)
				{
					shell->env[j] = shell->env[j + 1];
					j++;
				}
				shell->env[j] = NULL;
				i--;
			}
		}
	}
}

/*	ft_delete_env_unset function is used to delete one or more environment 
	variables from the shell environment. It takes the name of the variable 
	to delete and the shell environment as arguments. It then searches for 
	the variable in the environment and deletes it.
	Use a matrix of strings to store the names of the variables to delete. 
	Then, iterate over the environment and compare each variable with the
	names in the matrix. If a match is found, free the variable and shift
	the rest of the environment to the left.*/