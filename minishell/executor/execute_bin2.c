/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:56:11 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 14:09:50 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* función que ejecuta el comando en el proceso hijo. Comprueba que  los fdin,
out hayan sido configurados y los establece como la salida y entrada estándar, 
luego los cierra. Luego comprueba que la ruta contenga un "/" y lo ejecuta y
sale del proceso hijo con EXIT */
void    execute_child_proces(char *path, char **exc, t_minishell *shell)
{
    if (shell->fdin > 2)
    {
        dup2(shell->fdin, STDIN_FILENO);
        close(shell->fdin);
    }
    if (shell->fdout > 2)
    {
        dup2(shell->fdout, STDOUT_FILENO);
        close(shell->fdout);
    }
    if (ft_strchr(path, '/') != NULL)
        execve(path, exc, shell->env);
    shell->g_status = write_bin_error(path, shell);
    exit(shell->g_status);
}

/* Función que devuelve una matriz que contiene el comando y sus argumentos 
para poderla usar en un proceso hijo */
char **create_matrix_cmd_and_args(t_cmd **commands, int i)
{
    char **matrix;
    int j;

    j = 0;
    while (commands[i]->args[j] != NULL && commands[i]->args != NULL)
        j++;
    matrix = calloc(j + 1, sizeof(char *));
    j = 0;
    matrix[j] = ft_strdup(commands[i]->cmd);
    j++;
    if (commands[i]->args != NULL)
    {
        while (commands[i]->args[j - 1] != NULL && commands[i]->args != NULL)
        {
            matrix[j] = ft_strdup(commands[i]->args[j - 1]);
            j++;
        }
    }
    matrix[j] = NULL;
    return (matrix);
}

/* Función que ejecuta el comando bin con la ruta completa o con el comando
solamente si la ruta no existe. Lo realiza en un proceso hijo. Luego comprueba
si los fdin y out son > 2 (los 0, 1, 2 corresponden a stdin, stdout y stderror),
es decir, si han sido configurados manualmente. Si es así, los cierra.
 */
void    execute_bin_cmd(char *cmd_path, char **commands, t_minishell *shell, int i)
{
    pid_t   child_id;
    int     status_of_process;
    char    **command_args;

    command_args = create_matrix_cmd_and_args(commands, i);
    child_id = fork();
    if (child_id == 0)
        execute_child_procedd(cmd_path, command_args, shell);
    waitpid(child_id, &status_of_process, 0);
    shell->g_status = status_of_process;
    if (shell->fdin > 2)
        close(shell->fdin);
    if (shell->fdout > 2)
        close(shell->fdout);
    if (shell->g_status == 32512 || shell->g_status == 32256)
        shell->g_status /= 256;
    ft_strd_free(command_args);
}