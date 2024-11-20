/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-14 12:09:15 by sternero          #+#    #+#             */
/*   Updated: 2024-11-14 12:09:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_std(t_shell *shell)
{
	dup2(shell->infile, STDIN_FILENO);
	dup2(shell->outfile, STDOUT_FILENO);
}

/*	reset_std() functios is used to reset the standard input and output to the 
	original values. For example, if the standard input was changed to a file,
	this function will reset it to the original value. */

void	close_fds(t_shell *shell)
{
	if (shell->fdin > 0)
		close(shell->fdin);
	if (shell->fdout > 0)
		close(shell->fdout);
}

/*	close_fds() function is used to close the file descriptors that are open. 
	It is necessary to close the file descriptors to avoid memory leaks. */

void	reset_fds(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
	shell->pid = -1;
	shell->fdnextin = -1;
}

/*	reset_fds() function is used to reset the file descriptors to the original 
	values. For example, if the file descriptor was changed to a file, this
	function will reset it to the original value. It is necessary to reset the
	file descriptors to avoid memory leaks. */

void	ft_close_resets(t_shell *shell)
{
	reset_std(shell);
	close_fds(shell);
	reset_fds(shell);
}

/*	ft_close_resets() function is used to close the file descriptors and reset 
	them to the original values. It is necessary to close the file descriptors 
	to avoid memory leaks. */
