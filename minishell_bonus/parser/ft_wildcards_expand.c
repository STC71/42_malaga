/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Counts how many files match a single wildcard argument.
** Expands the wildcard and counts the results.
** Frees the expanded array after counting.
*/
static int	ft_count_wildcard_matches(char *arg)
{
	char	**expanded;
	int		count;

	expanded = ft_expand_wildcard(arg);
	if (!expanded)
		return (0);
	count = 0;
	while (expanded[count])
		count++;
	ft_free_array(expanded);
	return (count);
}

/*
** Counts total arguments after wildcard expansion.
** Each wildcard may expand to multiple files.
** Returns the total count needed for the new array.
*/
int	ft_count_expanded_args(char **args)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (ft_has_wildcard(args[i]))
			count += ft_count_wildcard_matches(args[i]);
		else
			count++;
		i++;
	}
	return (count);
}

/*
** Copies expanded wildcard matches into the new arguments array.
** Expands the wildcard at index i and copies all matches.
** Increments j for each match added.
*/
void	ft_copy_expanded(char ***new_args, char **args, int *j, int i)
{
	char	**expanded;
	int		k;

	expanded = ft_expand_wildcard(args[i]);
	if (expanded)
	{
		k = 0;
		while (expanded[k])
		{
			(*new_args)[*j] = ft_strdup(expanded[k]);
			(*j)++;
			k++;
		}
		ft_free_array(expanded);
	}
}

/*
** Expands wildcards in all commands in the shell.
** Iterates through all commands and calls ft_expand_wildcards_in_args.
** This is the main entry point for wildcard expansion.
*/
void	ft_expand_wildcards_all(t_shell *shell)
{
	int	i;

	if (!shell || !shell->cmds)
		return ;
	i = 0;
	while (shell->cmds[i])
	{
		ft_expand_wildcards_in_args(shell->cmds[i]);
		i++;
	}
}
