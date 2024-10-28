/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:47:05 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:47:31 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* libera las env existentes para sustituirlas */
void    ft_free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        free(env[i]);
    free(env);
}

/* Fusiona el nombre y el valor de la env*/
char *ft_new_env(char *name, char *value)
{
    char *new_env;

    new_env = ft_strjoin(name, "=");
    if (value)
        new_env = ft_strjoin(new_env, value);
    return (new_env);
}

/* Crea una nueva env */
void    ft_create_env(char *name, char *value, t_minishell *shell)
{
    int i;
    char **new_env;

    i = 0;
    while (shell->env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return ;
    i = 0;
    while (shell->env[i])
    {
        new_env[i] = ft_strdup(shell->env[i]);
        i++;
    }
    new_env[i++] = ft_new_env(name, value);
    new_env[i] = NULL;
    ft_free_env(shell->env);
    shell->env = new_env;
    free(new_env);
}

/* Actualiza una env existente */
int ft_check_update_env(char *name, char *value, t_minishell *shell)
{
    int i;

    i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
        {
            free(shell->env[i]);
            shell->env[i] = ft_strjoin(name, "=");
            if (value)
            {
                free(shell->env[i]);
                shell->env[i] = ft_strjoin(shell->env[i], value);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

/* Separa el nombre y el valor del comando e intenta actualizar una env
existente, sino crear una nueva*/
void ft_update_env(char *command, t_minishell *shell)
{
    char *equal;
    char *name;
    char *value;
    

    equal = ft_strchr(command, '=');
    if (equal)
    {
        *equal = '\0';
        name = command;
        value = equal + 1;
        if (!ft_check_update_env(name, value, shell))
            ft_create_env(name, value, shell);
    }
}