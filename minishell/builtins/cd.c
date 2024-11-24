/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:19:32 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/24 10:33:35 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	renew_path(t_shell *shell)
{
	char	cwd[PATH_MAX];
	int		i;

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

/*	renew_path function is used to update the PWD environment variable after 
	a cd command. It uses getcwd to get the current working directory and then 
	searches for the PWD variable in the environment. 
	Once it finds it, it frees the old value and replaces it with the new one.*/

void	exec_back_pwd(t_shell *shell)
{
	char	*back_path;

	back_path = ft_get_environment("OLDPWD", shell->env);
	if (back_path == NULL)
		return (write_oldpwd_error(shell));
	if (chdir(back_path) == -1)
		write_backpwd_err(back_path, shell);
	write(shell->fdout, back_path, ft_strlen(back_path));
	write(shell->fdout, "\n", 2);
	free(back_path);
}

/*	exec_back_pwd function is used to go back to the previous directory. 
	It uses the OLDPWD environment variable to get the previous directory path. 
	Then it changes the current directory to the previous one using chdir. 
	If the chdir fails, it writes an error message to the standard output.*/

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

/*	ft_get_environment function is used to get the value of an environment 
	variable. It takes the name of the variable and the environment as 
	arguments. It then searches for the variable in the environment and 
	returns its value.*/

void	exec_cd_home(t_shell *shell)
{
	char	*home_path;

	home_path = ft_get_environment("HOME", shell->env);
	if (home_path == NULL)
		return ;
	if (chdir(home_path) == -1)
		write_cdhome_error(home_path, shell);
	free(home_path);
}

/*	exec_cd_home function is used to change the current directory to the 
	home directory. It uses the HOME environment variable to get the home 
	directory path. Then it changes the current directory to the home directory 
	using chdir. If the chdir fails, it writes an error message to the standard 
	output.*/

void	ft_cd(char **full_command, t_shell *shell)
{
	if (full_command[1] != NULL)
		return (write_too_many_args(shell));
	shell->oldpwd = ft_get_environment("PWD", shell->env);
	if (full_command[0] == NULL || full_command[0][0] == '~')
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

/*	ft_cd function is used to change the current directory. It takes the 
	command arguments and the shell structure as arguments. It first checks 
	if there are too many arguments. Then it gets the current directory path 
	and saves it in the oldpwd variable. It then checks if the command is 
	empty or starts with a tilde (~) or a dash (-). If it is empty or starts 
	with a tilde, it changes the current directory to the home directory. 
	If it starts with a dash, it goes back to the previous directory. 
	Otherwise, it changes the current directory to the specified directory. 
	If the chdir fails, it writes an error message to the standard output. 
	Finally, it updates the PWD environment variable with the new path.*/