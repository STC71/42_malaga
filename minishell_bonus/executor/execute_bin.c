/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:10:16 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/24 10:42:40 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Frees a matrix of strings (char **str).
** Used to release memory for arrays created by ft_split or similar.
** Calls free for each string and then for the array itself.
*/
void	ft_str_free(char **str)
{
	int	pos;

	if (!str)
		return ;
	pos = 0;
	while (str[pos])
	{
		free(str[pos]);
		pos++;
	}
	free(str);
}

/*
** Joins a binary path and command name with a '/'.
** Checks if the resulting path exists using access(F_OK).
** Returns the valid path or NULL if not found. Uses malloc, ft_strlcpy, 
	ft_strlcat, access.
*/
char	*join_binpath_andcmd(char *cmd, char *bin_path)
{
	char	*joined_path;

	joined_path = malloc(ft_strlen(bin_path) + ft_strlen(cmd) + 2);
	if (joined_path == NULL)
		return (NULL);
	ft_strlcpy(joined_path, bin_path, ft_strlen(bin_path) + 1);
	ft_strlcat(joined_path, "/", ft_strlen(bin_path) + 2);
	ft_strlcat(joined_path, cmd, ft_strlen(bin_path) + ft_strlen(cmd) + 2);
	if (access(joined_path, F_OK) == 0)
		return (joined_path);
	free(joined_path);
	return (NULL);
}

/*
** Prints an error message for a failed binary execution.
** Handles not found, not executable, is directory, and permission errors.
** Returns the correct exit status for the error. Uses opendir, access, write.
*/
int	write_bin_error(char *path, t_shell *shell)
{
	DIR	*dir;
	int	status;

	status = 0;
	shell->g_status = 1;
	dir = opendir(path);
	write(STDERR_FILENO, path, ft_strlen(path));
	if (ft_strchr(path, '/') == NULL)
		write(STDERR_FILENO, ": command not found", 19);
	else if (access(path, F_OK) == -1)
		write(STDERR_FILENO, ": No such file or directory", 27);
	else if (dir != NULL)
		write(STDERR_FILENO, ": is a directory", 16);
	else if (access(path, X_OK) == -1)
		write(STDERR_FILENO, ": Permission denied", 19);
	if (ft_strchr(path, '/') == NULL || access(path, F_OK) == -1)
		status = 127;
	else
		status = 126;
	if (dir != NULL)
		closedir(dir);
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

/*
** Gets the PATH environment variable and splits it into an array of paths.
** Used to search for binaries in system directories. Returns NULL if PATH 
** is not set.
** Uses ft_split (custom split function).
*/
char	**get_bin_paths(t_shell *shell)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			res = ft_split(shell->env[i] + 5, ':');
			return (res);
		}
		i++;
	}
	return (NULL);
}

/*
** Main entry point for executing a binary (non-builtin) command.
** If the command contains '/', executes directly. Otherwise, searches in PATH.
** Calls exec_bin_cmd, get_bin_paths, search_in_path, write_bin_error.
*/
void	execute_bin_cmd_main(t_cmd **commands, t_shell *shell, int i)
{
	char	**bin_paths;

	if (ft_strchr(commands[i]->cmd, '/') != NULL)
	{
		exec_bin_cmd(commands[i]->cmd, commands, shell, i);
		return ;
	}
	bin_paths = get_bin_paths(shell);
	if (!commands[i]->cmd || !bin_paths)
	{
		if (bin_paths)
			ft_str_free(bin_paths);
		write_bin_error(commands[i]->cmd, shell);
		return ;
	}
	search_in_path(commands, shell, i, bin_paths);
}
