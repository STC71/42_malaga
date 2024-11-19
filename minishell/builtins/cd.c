/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:19:32 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 14:09:10 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	renew_path(t_shell *shell)
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

void	exec_back_pwd(t_shell *shell)
{
	char *back_path;

	back_path = ft_get_environment("OLDPWD", shell->env);
	if (back_path == NULL)
		return (write_oldpwd_error(shell));
	if (chdir(back_path) == -1)
		write_backpwd_err(back_path, shell);
	write(shell->fdout, back_path, ft_strlen(back_path));
	write(shell->fdout, "\n", 2);
	free(back_path);	
}

char	*ft_get_environment(char *str_pwd, char **env_paths)
{
	int i;
	int j;
	char *full_path;
	
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

void	exec_cd_home(t_shell *shell)
{
	char *home_path;

	home_path = ft_get_environment("HOME", shell->env);
	if (home_path == NULL)
		return ;
	if(chdir(home_path) == -1)
		write_cdhome_error(home_path, shell);
	free(home_path);
}

void	ft_cd(char **full_command, t_shell *shell)
{
	if (full_command[1] != NULL)
		return(write_too_many_args(shell));
	shell->oldpwd = ft_get_environment("PWD", shell->env);
	if (full_command[0] == NULL)
		exec_cd_home(shell);
	else if (full_command[0][0] == '~')
		exec_cd_home(shell);
	else if (full_command[0][0] == '-')
		exec_back_pwd(shell);
	else  
	{
		if (chdir(full_command[0]) == -1)
		{	
			write(STDERR_FILENO, "cd: no such file or directory: ", 31);
			write(STDERR_FILENO, full_command[0], ft_strlen(full_command[0]));
			write(STDERR_FILENO, "\n", 2);
			shell->g_status = 1;
		}
	}
	if (shell->g_status == 1)
	{
		free(shell->oldpwd);
		shell->oldpwd = NULL;
	}
	else
		renew_path(shell);
}