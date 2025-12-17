/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:00:00 by assistant         #+#    #+#             */
/*   Updated: 2025/11/27 10:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structures.h"
#include <stdlib.h>
#ifdef USE_READLINE
# include <readline/history.h>
#endif

/* Helpers for registry, readline and atexit handling were moved to
** `parser/ft_cleanup_utils.c` to reduce the number of functions in this
** file and keep the cleanup logic compact for style checks.
*/

static void	free_cmds(t_shell *shell);
static void	free_misc_strs(t_shell *shell);
static void	clear_readline_history(void);

void	ft_cleanup_shell(t_shell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->ast)
		ft_free_ast(shell->ast);
	if (shell->env)
	{
		ft_free_array(shell->env);
		shell->env = NULL;
	}
	free_cmds(shell);
	free_misc_strs(shell);
	clear_readline_history();
	cleanup_registry_for_shell(shell);
}

/* ft_register_shell provided in ft_cleanup_utils.c to keep registry state
** internal to that module and avoid exposing globals in headers.
*/

static void	free_cmds(t_shell *shell)
{
	int	i;

	if (shell->cmds == NULL)
		return ;
	i = 0;
	while (shell->cmds[i])
	{
		ft_free_commands(shell->cmds[i]);
		i++;
	}
	free(shell->cmds);
	shell->cmds = NULL;
}

static void	free_misc_strs(t_shell *shell)
{
	if (shell->full_cmd)
		ft_free_array(shell->full_cmd);
	if (shell->split_cmd)
		ft_free_array(shell->split_cmd);
	if (shell->cmd_path)
		free(shell->cmd_path);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->parsed_prompt)
		free(shell->parsed_prompt);
	if (shell->prompt)
		free(shell->prompt);
	shell->full_cmd = NULL;
	shell->split_cmd = NULL;
	shell->cmd_path = NULL;
	shell->oldpwd = NULL;
	shell->parsed_prompt = NULL;
	shell->prompt = NULL;
}

#ifdef USE_READLINE

static void	clear_readline_history(void)
{
	clear_history();
}
#else

static void	clear_readline_history(void)
{
	(void)0;
}
#endif
