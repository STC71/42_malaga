/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 10:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 10:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Counts how many files in a directory match the given pattern.
** Skips hidden files (starting with .).
** Returns the count of matches.
*/
int	ft_count_matches(char *pattern, DIR *dir)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	return (count);
}

/*
** Fills the result array with filenames that match the pattern.
** Skips hidden files (starting with .).
** Result array must be pre-allocated by caller.
*/
void	ft_fill_matches(char **result, char *pattern, DIR *dir)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
		{
			result[i] = ft_strdup(entry->d_name);
			i++;
		}
		entry = readdir(dir);
	}
	result[i] = NULL;
}

/*
** Processes each argument, expanding wildcards or copying as-is.
** Increments j for each argument added to new_args.
** Helper function for ft_expand_wildcards_in_args.
*/
static void	ft_process_args(char **new_args, char **args, int *j)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_has_wildcard(args[i]))
			ft_copy_expanded(&new_args, args, j, i);
		else
			new_args[(*j)++] = ft_strdup(args[i]);
		i++;
	}
}

/*
** Expands all wildcards in command arguments.
** Replaces cmd->args with a new array containing expanded filenames.
** Frees the old args array after expansion.
*/
void	ft_expand_wildcards_in_args(t_cmd *cmd)
{
	char	**new_args;
	int		j;
	int		total;

	if (!cmd || !cmd->args)
		return ;
	total = ft_count_expanded_args(cmd->args);
	new_args = malloc(sizeof(char *) * (total + 1));
	if (!new_args)
		return ;
	j = 0;
	ft_process_args(new_args, cmd->args, &j);
	new_args[j] = NULL;
	ft_free_array(cmd->args);
	cmd->args = new_args;
}
