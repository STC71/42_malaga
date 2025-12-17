/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:00:00 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/26 10:00:00 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

/*
** Finds and returns the value of an environment variable.
** Searches env_paths for a variable named str_pwd and returns its value as a 
** new string.
** Used to get HOME, OLDPWD, PWD, etc. Returns NULL if not found or allocation 
** fails.
** Uses ft_strdup (custom string duplicate).
*/
char	*ft_get_environment(char *str_pwd, char **env_paths)
{
	int		i;
	int		j;
	char	*full_path;

	i = 0;
	while (env_paths[i] != NULL)
	{
		j = 0;
		while (env_paths[i][j] == str_pwd[j] && str_pwd[j] != '\0')
			j++;
		if (env_paths[i][j] == '=' && str_pwd[j] == '\0')
		{
			j++;
			full_path = ft_strdup(env_paths[i] + j);
			if (full_path == NULL)
				return (NULL);
			return (full_path);
		}
		i++;
	}
	return (NULL);
}

/*
** Handles changing directory to a given path and error reporting.
*/
void	handle_cd_path(char **full_command, t_shell *shell)
{
	if (chdir(full_command[0]) == -1)
	{
		write(STDERR_FILENO, "cd: no such file or directory:", 31);
		write(STDERR_FILENO, full_command[0], ft_strlen(full_command[0]));
		write(STDERR_FILENO, "\n", 2);
		shell->g_status = 1;
	}
}

/*
** Updates PWD in environment with current directory.
*/
void	update_pwd_env(t_shell *shell, char *cwd)
{
	int	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (strncmp(shell->env[i], "PWD", 3) == 0
			&& shell->env[i][3] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", cwd);
			if (shell->env[i] == NULL)
				shell->g_status = 1;
			break ;
		}
		i++;
	}
}

/*
** Updates OLDPWD in environment.
*/
void	update_oldpwd_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] != NULL && shell->oldpwd != NULL)
	{
		if (strncmp(shell->env[i], "OLDPWD", 6) == 0
			&& shell->env[i][6] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", shell->oldpwd);
			if (shell->env[i] == NULL)
				shell->g_status = 1;
			break ;
		}
		i++;
	}
	if (shell->oldpwd)
		free(shell->oldpwd);
	shell->oldpwd = NULL;
}
