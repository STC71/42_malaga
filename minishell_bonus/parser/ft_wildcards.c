/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 10:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-12-02 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Checks if a string contains a wildcard (*) outside of quotes.
** Returns 1 if wildcard is found, 0 otherwise.
** Quoted wildcards like "*" or '*.c' are ignored.
*/
int	ft_has_wildcard(char *str)
{
	int	i;
	int	in_quotes;

	if (!str)
		return (0);
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quotes = !in_quotes;
		if (str[i] == '*' && !in_quotes)
			return (1);
		i++;
	}
	return (0);
}

/*
** Handles the matching of a star (*) wildcard.
** Tries to match the remaining pattern at every position in the string.
** This is the recursive engine for wildcard expansion.
*/
static int	ft_match_star(char *pattern, char *str)
{
	if (!*pattern)
		return (1);
	while (*str)
	{
		if (ft_match_pattern(pattern, str))
			return (1);
		str++;
	}
	return (ft_match_pattern(pattern, str));
}

/*
** Recursively matches a pattern against a string.
** Handles both literal characters and wildcards (*).
** Returns 1 if pattern matches, 0 otherwise.
*/
int	ft_match_pattern(char *pattern, char *str)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*')
		return (ft_match_star(pattern + 1, str));
	if (*pattern == *str)
		return (ft_match_pattern(pattern + 1, str + 1));
	return (0);
}

/*
** Processes directory matches after counting them.
** Allocates result array, fills it with matching files,
** and adds directory prefix to each match.
*/
static char	**ft_process_matches(char *pattern, char *dir_path, int count)
{
	DIR		*dir;
	char	**result;
	char	*base_pattern;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (free(dir_path), NULL);
	dir = opendir(dir_path);
	base_pattern = ft_get_pattern_base(pattern);
	ft_fill_matches(result, base_pattern, dir);
	closedir(dir);
	ft_add_dir_prefix(result, dir_path, count);
	free(dir_path);
	return (result);
}

/*
** Main wildcard expansion function.
** Takes a pattern like "builtins / *.c" and returns an array of matching files.
** If no matches are found, returns the pattern itself as a literal.
*/
char	**ft_expand_wildcard(char *pattern)
{
	DIR		*dir;
	char	*dir_path;
	char	*base_pattern;
	int		count;

	dir_path = ft_get_dir_from_pattern(pattern);
	base_pattern = ft_get_pattern_base(pattern);
	dir = opendir(dir_path);
	if (!dir)
		return (free(dir_path), NULL);
	count = ft_count_matches(base_pattern, dir);
	closedir(dir);
	if (count == 0)
		return (ft_no_matches(pattern, dir_path));
	return (ft_process_matches(pattern, dir_path, count));
}
