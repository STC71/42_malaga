/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:10:16 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 14:41:13 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_str_free(char **str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		free(str[pos]);
		pos++;
	}
	free(str);
}

/*  ft_str_free function is used to free the memory allocated for the string. */

char	*join_binpath_and_cmd(char *cmd, char *bin_path)
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
	else
	{
		free(joined_path);
		return (NULL);
	}
}

/*  join_binpath_and_cmd() function is used to join the path of the bin with the
	name of the command adding "/" in the middle of both. Once joined, it
	verifies if that path exists with ACCESS and the F_OK mode. If it exists,
	it returns the path, otherwise it frees the memory and returns NULL. */

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
	else if (dir == NULL)
	{
		write(STDERR_FILENO, ": is a directory", 16);
		closedir(dir);
	}
	else if (access(path, X_OK) == -1)
		write(STDERR_FILENO, ": Permission denied", 19);
	if (ft_strchr(path, '/') == NULL || (dir == NULL))
		status = 127;
	else
		status = 126;
	if (dir != NULL)
		closedir(dir);
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

/*  write_bin_error() function is used to print an error message according to 
	the type of error that occurs. It can be: for commands not found, files or 
	directories not found, directories and permissions denied and returns a 
	code with the type of error. */

char	**get_bin_paths(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			return (ft_split(shell->env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

/*  get_bin_paths() function is used to get the path of the env and return it 
	in a matrix separated by ":" in each array of the matrix. It is used to
	search for the command in the directories of the PATH, and if it is not
	found, it will return NULL. */

void	execute_bin_cmd_main(t_cmd **commands, t_shell *shell, int i)
{
	char	**bin_paths;
	int		j;

	j = 0;
	bin_paths = get_bin_paths(shell);
	if (!commands[i]->cmd || !bin_paths)
	{
		write_bin_error(commands[i]->cmd, shell);
		return ;
	}
	while (bin_paths[j])
	{
		shell->cmd_path = join_binpath_and_cmd(commands[i]->cmd, bin_paths[j++]);
		if (shell->cmd_path != NULL)
			break ;
	}
	if (shell->cmd_path != NULL)
		execute_bin_cmd(shell->cmd_path, commands, shell, i);
	else
		execute_bin_cmd(commands[i]->cmd, commands, shell, i);
	ft_str_free(bin_paths);
	free(shell->cmd_path);
}

/*  execute_bin_cmd_main() function is the main function that contains the 
	sub-functions for the execution of the system command (bin, not builtin) 
	received by the user. */
