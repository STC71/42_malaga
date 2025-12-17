/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-02 12:37:26 by sternero          #+#    #+#             */
/*   Updated: 2025-12-02 12:37:26 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Extracts the directory path from a wildcard pattern.
** For "builtins / *.c", returns "builtins".
** For "*.c", returns "." (current directory).
** Returns a new string that must be freed by caller.
*/
char	*ft_get_dir_from_pattern(char *pattern)
{
	char	*last_slash;
	char	*dir;
	int		len;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup("."));
	len = last_slash - pattern;
	dir = malloc(len + 1);
	if (!dir)
		return (NULL);
	ft_strlcpy(dir, pattern, len + 1);
	return (dir);
}

/*
** Extracts the filename pattern from a full wildcard path.
** For "builtins / *.c", returns "*.c".
** For "*.c", returns "*.c".
** Returns a pointer to the pattern part (no memory allocation).
*/
char	*ft_get_pattern_base(char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (pattern);
	return (last_slash + 1);
}

/*
** Creates a full path by joining directory and filename.
** Adds a "/" separator between them.
** Returns a new string that must be freed by caller.
*/
static char	*ft_create_full_path(char *dir, char *filename)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, filename);
	free(tmp);
	return (full);
}

/*
** Adds directory prefix to all matched filenames in the result array.
** If dir is ".", does nothing (current directory needs no prefix).
** Modifies the result array in place, freeing old strings.
*/
void	ft_add_dir_prefix(char **result, char *dir, int count)
{
	char	*full;
	int		i;

	if (ft_strcmp(dir, ".") == 0)
		return ;
	i = 0;
	while (i < count && result[i])
	{
		full = ft_create_full_path(dir, result[i]);
		if (full)
		{
			free(result[i]);
			result[i] = full;
		}
		i++;
	}
}

/*
** Returns the pattern itself when no files match.
** Creates a result array with just the pattern as a literal string.
** Frees the dir_path before returning.
*/
char	**ft_no_matches(char *pattern, char *dir_path)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (free(dir_path), NULL);
	result[0] = ft_strdup(pattern);
	result[1] = NULL;
	return (free(dir_path), result);
}
