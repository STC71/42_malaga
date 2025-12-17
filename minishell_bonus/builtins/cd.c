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
#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

/*
** Updates PWD and OLDPWD environment variables after cd command.
*/
void	renew_path(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		write_cd_err(shell);
		return ;
	}
	update_pwd_env(shell, cwd);
	if (shell->g_status == 1)
		return ;
	update_oldpwd_env(shell);
}

/*
** Changes directory to the previous path stored in OLDPWD.
** Gets OLDPWD from environment, uses chdir to change directory.
** If OLDPWD is not set or chdir fails, writes error.
** Uses ft_get_environment (custom env search) and chdir (system call).
*/
void	exec_back_pwd(t_shell *shell)
{
	char	*back_path;

	back_path = ft_get_environment("OLDPWD", shell->env);
	if (back_path == NULL)
	{
		write_oldpwd_error(shell);
		return ;
	}
	if (chdir(back_path) == -1)
		write_backpwd_err(back_path, shell);
	else
		shell->g_status = 0;
	write(shell->fdout, back_path, ft_strlen(back_path));
	write(shell->fdout, "\n", 1);
	free(back_path);
}

/*
** Finds and returns the value of an environment variable.
** Searches env_paths for a variable named str_pwd and returns its value as a 
	new string.
** Used to get HOME, OLDPWD, PWD, etc. Returns NULL if not found or allocation 
	fails.
** Uses ft_strdup (custom string duplicate).
*/

/*
** Changes directory to the user's home folder using the HOME environment 
** variable.
** If HOME is not set or chdir fails, writes error.
** Uses ft_get_environment and chdir.
*/
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

/* handle_cd_path is implemented in cd_utils.c */

/*
** Executes the appropriate cd action based on the command argument.
*/
static void	execute_cd_action(char **full_command, t_shell *shell)
{
	if (full_command[0] == NULL || full_command[0][0] == '~')
		exec_cd_home(shell);
	else if (full_command[0][0] == '-')
		exec_back_pwd(shell);
	else
		handle_cd_path(full_command, shell);
}

/*
** Main function for the cd builtin. Changes the current directory.
** Handles too many arguments, home (~), previous (-), and normal paths.
** Updates oldpwd and PWD environment variables. Uses chdir, ft_get_environment
	, renew_path.
** If chdir fails, sets error status and writes error.
*/
void	ft_cd(char **full_command, t_shell *shell)
{
	if (full_command[1] != NULL)
	{
		write_too_many_args(shell);
		return ;
	}
	shell->oldpwd = ft_get_environment("PWD", shell->env);
	execute_cd_action(full_command, shell);
	if (shell->g_status == 1)
	{
		free(shell->oldpwd);
		shell->oldpwd = NULL;
	}
	else
		renew_path(shell);
}
