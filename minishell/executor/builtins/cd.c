/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:19:32 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:45:50 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// pwd = printf working directory

void	renew_path(t_minishell *shell)
{
	char cwd[PATH_MAX];
	int i;

	i = 0;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (write_cd_err(shell));
	while (shell->env[i] != NULL)
	{
		if (strncmp(shell->env[i], "PWD", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", cwd);
			if (shell->env[i] == NULL)
			{
				shell->g_status = 1;
				return ;
			}
			return ;
		}
		i++;
	}
}

void	back_pwd(t_minishell *shell)
{
	char *back_path;

	back_path = ft_get_env("OLDPWD", shell->env);
	if (back_path == NULL)
		return (write_oldpwd_error(shell));
	if (chdir(back_path) == -1)
		write_backpwd_err(back_path, shell);
	write(shell->fdout, back_path, ft_strlen(back_path));
	write(shell->fdout, "\n", 2);
	free(back_path);	
}

void	exec_cd_home(t_minishell *shell)
{
	char *home_path;

	home_path = ft_get_environment("HOME", shell->env);
	if (home_path == NULL)
		return ;
	if(chdir(home_path) == -1)
		write_cdhome_error(home_path, shell);
	free(home_path);
}

char	*ft_get_environment(char *str_pwd, char **env_paths)
{
	int i;
	char *full_path;
	
	i = 0;
	while (env_paths[i] != NULL)
	{
		if (ft_strncmp(env_paths[i], str_pwd, 3) == 0)
		{
			full_path = ft_strdup(env_paths[i] + 4);
			if (full_path == NULL)
				return (NULL);
			return (full_path);
		}
		i++;
	}
	return (NULL);
}

void	ft_cd(char **full_command, t_minishell *shell)
{
	if (full_command[1] != NULL)
		return(write_too_many_args(shell));
	shell->oldpwd = ft_get_environment("PWD", shell->env);
	if (full_command[0][0] == NULL)
		exec_cd_home(shell);
	else if (full_command[0][0] == '~')
		exec_cd_home(shell);
	else if (full_command[0][0] == '-')
		exec_backpwd(shell);
	else if (chdir(full_command[0]) == -1)
	{
		write(STDERR_FILENO, "cd: no such file or directory: ", 31);
		write(STDERR_FILENO, full_command[0], ft_strlen(full_command[0]));
		write(STDERR_FILENO, "\n", 2);
		shell->g_status = 1;
	}
	if (shell->g_status == 1)
	{
		free(shell->oldpwd);
		shell->oldpwd = NULL;
	}
	else
		renew_path(shell);
}