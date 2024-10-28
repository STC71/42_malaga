/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:21:49 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:48:35 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Vuelve las redirecciones a su estado original */
void    reset_redirections(t_minishell *shell)
{
    dup2(shell->infile, STDIN_FILENO);
    dup2(shell->outfile, STDOUT_FILENO);
    close(shell->infile);
    close(shell->outfile);
}

/* Función que gestiona las redirecciones de entrada (< o <<)*/
void redir_infile(char *cmd, t_minishell *shell, int i)
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

/* Función que gestiona las redirecciones de salida ( >> o > )*/
void    redir_outfile(char *cmd, t_minishell *shell, int i)
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

/* Guarda los descriptores de archivo actuales de entrada y salida estándar */
void    save_fds(t_minishell *shell)
{
    shell->exec_signal = 0;
    shell->infile = dup(STDIN_FILENO);
    shell->outfile = dup(STDOUT_FILENO);
}

/* Ejemplo de lo que debe contener cmd:
char *redirrections[] = {"<", "entrada.txt", ">", "salida.txt", NULL};*/
void    choose_redirections(char **cmd, t_minishell *shell)
{
    int i;

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