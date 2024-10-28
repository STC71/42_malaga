/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bultins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:05 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 14:17:26 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*actualiza la variable de entorno OLDPWD a la posición anterior */
void    reset_oldpwd(t_minishell *shell, int i)
{
    if (shell->oldpwd != NULL && ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
    {
        free(shell->env[i]);
        shell->env[i] = ft_strjoin("OLDPWD=", shell->oldpwd);
    }
    free(shell->oldpwd);
}

/* resetea las variables de entorno OLDPWD y "_"(último comando
ejecutado), si el último comando ejecutado tenía argumentos, se mostrará
solamente el último argumento (ni el comando ni los arg intermedios), 
y si no tení args, se mostrará el comando solo */
void    reset_oldpwd_and_lastcmd(t_minishell *shell, t_cmd **commands)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (shell->env[i])
    {
        reset_oldpwd(shell, i);
        if(ft_strncmp(shell->env[i], "_=", 2) == 0)
        {
            if (commands[0]->args && commands[0]->args[0] != NULL)
            {
                while (commands[0]->args[j] != NULL)
                    j++;
                free(shell->env[i]);
                shell->env[i] = ft_strjoin("_=", commands[0]->args[j - 1]);
            }
            else if (commands[0]->cmd != NULL)
            {
                free(shell->env[i]);
                shell->env[i] = ft_strjoin("_=", commands[0]->cmd);
            }
        }
        i++;
    }
}

/* Comprueba si el comando es un builtin o un comando del sistema  (bin)*/
void    check_if_bultin(t_cmd **commands, t_minishell *shell, int i)
{
    shell->g_status = 0;
    if (commands[i]->cmd && check_if_is_builtin(commands[i]->cmd) == 1)
        choose_builtin(shell, commands, i);
    else if (commands[i]->cmd)
        execute_bin_cmd(commands[i]->cmd, commands, shell, i);
}

/* Crea la tubería y guarda los fd en la estructura */
void    config_pipe(t_minishell *shell)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        write(STDERR_FILENO, "pipe: error creating pipe\n", 27);
        shell->exec_signal = 1;
        shell->g_status = 1;
    }
    else
    {
        shell->fdnextin = fd[0];
        shell->fdout = fd[1];
    }
}

void    execute(t_cmd **commands, t_minishell *shell)
{
    int i;

    i = 0;
    save_fds(shell);
    while (commands[i] != NULL)
    {
        shell->fdnextin = -1;
        if (commands[i + 1] != NULL)
            config_pipe(shell);
        else
            shell->fdout = STDOUT_FILENO;
        choose_redirections(commands[i]->cmd_in, shell);
        choose_redirections(commands[i]->cmd_out, shell);
        if (commands[i]->cmd != NULL)
            check_if_builtin(commands, shell, i);
        shell->fdin = shell->fdnextin;
        i++;
    }
    reset_old_pwd_and_lastcmd(shell, commands);
    reset_redirections(shell);
}