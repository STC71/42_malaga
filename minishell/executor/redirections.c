/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:21:49 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 09:42:53 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Vuelve las redirecciones a su estado original */
void	reset_redirections(t_shell *shell)
{
	dup2(shell->infile, STDIN_FILENO);
	dup2(shell->outfile, STDOUT_FILENO);
	close(shell->infile);
	close(shell->outfile);
}

/*  reset_redirections() function is used to reset the standard input and output
	to the original values. For example, if the standard input was changed to a 
	file, this function will reset it to the original value. */

void	redir_infile(char **cmd, t_shell *shell, int i)
{
	if (shell->fdin > 2)
		close(shell->fdin);
	if (ft_strcmp(cmd[i], "<<") == 0)
		apply_heredoc(cmd[i + 1], shell);
	else
		shell->fdin = open(cmd[i + 1], O_RDONLY);
	if (shell->fdin == -1)
	{
		write(STDERR_FILENO, cmd[i + 1], ft_strlen(cmd[i + 1]));
		write(STDERR_FILENO, ": no such file or directory\n", 29);
		shell->exec_signal = 1;
		shell->g_status = 1;
	}
}

/*  redir_infile() function is used to manage input redirections (< or <<). 
	If the redirection is <<, it will call the apply_heredoc() function, 
	otherwise it will open the file and save the file descriptor in the 
	structure. */

void	redir_outfile(char **cmd, t_shell *shell, int i)
{
	if (shell->fdout > 2)
		close(shell->fdout);
	if (ft_strcmp(cmd[i], ">>") == 0)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	else
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (shell->fdout == -1)
	{
		write(STDERR_FILENO, cmd[i + 1], ft_strlen(cmd[i + 1]));
		write(STDERR_FILENO, ": no such file or directory\n", 29);
		shell->exec_signal = 1;
		shell->g_status = 1;
	}
}

/*  redir_outfile() function is used to manage output redirections (> or >>). 
	If the redirection is >>, it will open the file in append mode, otherwise 
	it will open the file in write mode. */

void	save_fds(t_shell *shell)
{
	shell->exec_signal = 0;
	shell->infile = dup(STDIN_FILENO);
	shell->outfile = dup(STDOUT_FILENO);
}

/*  save_fds() function is used to save the current file descriptors of the 
	standard input and output. It is necessary to save the file descriptors 
	to reset them to the original values. */

/* Ejemplo de lo que debe contener cmd:
char *redirrections[] = {"<", "entrada.txt", ">", "salida.txt", NULL};*/
void	choose_redirections(char **cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL && cmd != NULL)
	{
		if (ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], ">>") == 0)
			redir_outfile(cmd, shell, i);
		else if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], "<<") == 0)
			redir_infile(cmd, shell, i);
		i++;
	}
}

/*  choose_redirections() function is used to manage the redirections of the 
	command. It will call the redir_outfile() function if the redirection is 
	> or >>, otherwise it will call the redir_infile() function if the 
	redirection is < or <<.
	Example of cmd must contain: char *redirrections[] = {"<", "input.txt",
	">", "output.txt", NULL};
	Whith this example, the function will redirect the input to input.txt and
	the output to output.txt. */
