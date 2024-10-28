/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:04:54 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:47:17 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* Función que controla el tipo de error y lo imprime */
void ft_print_env_err(t_minishell *shell, int env_err, char *command)
{
    int i;

    i = 0;
    shell->g_status = 1;
    if (env_err == 0)
        env_err0(command, i);
    else if (env_err == -3)
    {
        if (command[1] != '\0')
            env_err = -2;
        else
            env_err3(command);
    }
    else if (env_err == -1)
        env_err1(command, i);
    else if (env_err == -2)
        env_err2(command, i);
}

/* Función que comprueba los comandos */
int check_env(char *env)
{
    int i;

    i = 0;
    if (ft_isdigit(env[i]))
        return (0);
    if (env[i] == '=')
        return (-3);
    while (env[i] != NULL)
    {
        if (env[i + 1] == '=' && env[i + 2] != '\0')
            return (-2);
        i++;
    }
    i = 0;
    while (env[i] != NULL && env[i] != '=')
    {
        if (!ft_isalnum(env[i]) && env[i] != '_')
            return (-1);
        i++;
    }
    return (1);
}

/* Imprime todas las env */
void ft_print_env(t_minishell *shell)
{
    int i;

    i = 0;
    while (shell->env[i])
    {
        write(shell->fdout, "declare -x ", 11);
        write(shell->fdout, shell->env[i], ft_strlen(shell->env[i]));
        write(shell->fdout, "\n", 1);
        i++;
    }
}

/* Función para actualizar las env */
void ft_update_env_export(t_minishell *shell, char **commands)
{
    int i;
    
    if (commands[0] == 0)
        ft_print_env(shell);
    else
    {
        i = 0;
        while (commands[i] != NULL)
        {
            if (check_env(commands[i]) > 0)
                ft_update(commands[i], shell);
            else
                ft_print_env_err(shell, check_env(commands[i]), commands[i]);
            i++;
        }
    }
}