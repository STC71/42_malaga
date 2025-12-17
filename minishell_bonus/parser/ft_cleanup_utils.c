/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:00:00 by assistant          #+#    #+#            */
/*   Updated: 2025/11/27 10:00:00 by assistant         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structures.h"
#include "../includes/functions.h"
#include <stdlib.h>
#ifdef USE_READLINE
# include <readline/history.h>
#endif

/* Per-shell orphan registry stored inside `t_shell->orphan_allocs`. */

void	register_orphan_alloc(t_shell *shell, char **ptr)
{
	int	i;

	if (!shell || !ptr)
		return ;
	if (!shell->orphan_allocs)
	{
		shell->orphan_allocs = malloc(sizeof(char **) * 2);
		if (!shell->orphan_allocs)
			return ;
		shell->orphan_allocs[0] = ptr;
		shell->orphan_allocs[1] = NULL;
		return ;
	}
	i = 0;
	while (shell->orphan_allocs[i])
		i++;
	shell->orphan_allocs = realloc(shell->orphan_allocs,
			sizeof(char **) * (i + 2));
	if (!shell->orphan_allocs)
		return ;
	shell->orphan_allocs[i] = ptr;
	shell->orphan_allocs[i + 1] = NULL;
}

void	unregister_orphan_alloc(t_shell *shell, char **ptr)
{
	int	i;
	int	j;

	if (!shell || !shell->orphan_allocs || !ptr)
		return ;
	i = 0;
	while (shell->orphan_allocs[i])
	{
		if (shell->orphan_allocs[i] == ptr)
		{
			j = i;
			while (shell->orphan_allocs[j])
			{
				shell->orphan_allocs[j] = shell->orphan_allocs[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	cleanup_registry_for_shell(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->orphan_allocs)
	{
		i = 0;
		while (shell->orphan_allocs[i])
		{
			ft_str_free(shell->orphan_allocs[i]);
			i++;
		}
		free(shell->orphan_allocs);
		shell->orphan_allocs = NULL;
	}
}
