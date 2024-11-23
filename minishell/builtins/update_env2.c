/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:47:05 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:47:31 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/*  ft_free_env function is used to free the memory allocated for the 
	environment variables. It takes the environment as an argument and 
	then iterates over the environment, freeing each variable.*/

char *ft_new_env(char *name, char *value)
{
	char *new_env;

	new_env = ft_strjoin(name, "=");
	if (value)
		new_env = ft_strjoin(new_env, value);
	return (new_env);
}

/*  ft_new_env function is used to merge the name and value of an environment 
	variable. It takes the name and value as arguments and then concatenates 
	them with an equal sign in between. It then returns the new environment 
	variable.*/

void    ft_create_env(char *name, char *value, t_shell *shell)
{
	int i;
	char **new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = ft_strdup(shell->env[i]);
		i++;
	}
	new_env[i++] = ft_new_env(name, value);
	new_env[i] = NULL;
	ft_free_env(shell->env);
	shell->env = new_env;
	//free(new_env);
}

/*  ft_create_env function is used to create a new environment variable. 
	It takes the name, value, and shell as arguments. It then creates a new 
	environment variable by merging the name and value. It then adds the new 
	variable to the environment.*/

int ft_check_update_env(char *name, char *value, t_shell *shell)
{
	int i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(name, "=");
			if (value)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strjoin(shell->env[i], value);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

/*  ft_check_update_env function is used to check if an environment variable 
	already exists. It takes the name, value, and shell as arguments. It then 
	iterates over the environment variables, comparing the name of each variable 
	with the name argument. If a match is found, it updates the value of the 
	variable and returns 1. Otherwise, it returns 0.*/

void ft_update_env(char *command, t_shell *shell)
{
	char *equal;
	char *name;
	char *value;
	

	equal = ft_strchr(command, '=');
	if (equal)
	{
		*equal = '\0';
		name = command;
		value = equal + 1;
		if (!ft_check_update_env(name, value, shell))
			ft_create_env(name, value, shell);
	}
}

/*  ft_update_env function is used to update the environment variables with 
	the export command. It takes the command and the shell as arguments. It 
	then splits the command into the name and value of the environment variable.
	If the variable already exists, it updates the value. Otherwise, it creates 
	a new environment variable.*/
	