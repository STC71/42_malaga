/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec_builtins.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:07:50 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/27 12:02:07 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Función que elige el builtin a ejecutar */
void choose_builtin(t_minishell *shell, t_cmd **commands, int i)
{
    char *builtin;
    //en la mia extaigo el comando de la estructura
    builtin = commands[i]->cmd;
    if (!ft_strcmp(builtin, "echo"))
        ft_echo(commands[i]->args, shell);
    else if (!ft_strcmp(builtin, "cd"))
        ft_cd(commands[i]->args, shell);
    else if (!ft_strcmp(builtin, "env"))
        ft_print_env_env(shell, commands[i]->args);
    else if (!ft_strcmp(builtin, "exit"))
        ft_exit(commands[i]->args, shell);
    else if (!ft_strcmp(builtin, "export"))
        ft_update_env_export(commands[i]->args, shell);
    else if (!ft_strcmp(builtin, "unset"))
        ft_delete_env_unset(commands[i]->args, shell);
    else if (!ft_strcmp(builtin, "pwd"))
        ft_pwd(shell);
}

/* Función que comprueba si es un builtin */
int check_if_is_builtin(char *command)
{
    if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd") || !ft_strcmp(command,
            "env") || !ft_strcmp(command, "exit") || !ft_strcmp(command, "export")
        || !ft_strcmp(command, "unset") || !ft_strcmp(command, "pwd"))
        return (1);
    return (0);
}