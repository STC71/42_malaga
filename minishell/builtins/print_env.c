/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:58 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 10:25:57 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_print_env_err(t_shell *shell, char *path)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	shell->g_status = 127;
	return (FAILURE);
}

/*  The ft_print_env_err() function prints an error message to the standard
	error output and returns a failure status, which is 127 (command not found),
	if the path does not exist. It recives a pointer to the shell structure and
	a pointer to the path.
	This function provides a clear and informative error message to the user 
	when a command is not found.
	STDERR_FILENO, "env: ", 5 -> file descriptor for standard error output.
	STDERR_FILENO, path, ft_strlen(path) -> prints the path.
	STDERR_FILENO, ": No such file or directory\n", 29 -> prints the message.
	Status Code: Setting the g_status to 127 is a standard way to indicate a 
	"command not found" error.
	Return Value: The function returns 1 to signal that an error occurred, 
	which can be used for further error handling or reporting. */

int	ft_check_path(t_shell *shell, char **paths)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (paths[i] != NULL)
	{
		j = 0;
		flag = 1;
		while (paths[i][j])
		{
			if (paths[i][j] == '=')
				flag = 0;
			j++;
			if (flag == 1 && paths[i][j] == '\0')
				return (ft_print_env_err(shell, paths[i]));
		}
		i++;
	}
	return (SUCCESS);
}

/*  The ft_check_path() function checks if the path exists. It recives a pointer
	to the shell structure and a pointer to the paths.
	This function is used to check if the path exists before printing the 
	environment variables.
	Return Value: The function returns 0 if the path exists, otherwise it returns
	a failure status using the ft_print_env_err() function. */

void	ft_print_env(t_shell *shell, char **paths)
{
	int	i;

	i = 0;
	if (ft_check_path(shell, paths) == 0)
	{
		while (shell->env[i])
		{
			write(shell->fdout, shell->env[i], ft_strlen(shell->env[i]));
			write(shell->fdout, "\n", 1);
			i++;
		}
		i = 0;
		while (paths[i])
		{
			write(shell->fdout, paths[i], ft_strlen(paths[i]));
			write(shell->fdout, "\n", 1);
			i++;
		}
	}
}

/*	The ft_print_env() function prints the environment variables to the standard
	output. It recives a pointer to the shell structure and a pointer to the 
	paths.
	This function prints the environment variables and the paths to the standard
	output. It uses the ft_check_path() function to check if the path exists 
	before printing the environment variables.
	Return Value: The function does not return a value... is void */