/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 09:25:27 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 09:25:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_var   **ft_env(char **env)
{
    int     i;
    int     len;
    t_var   **l_var;
    
    i = 0;
    len = ft_vector_len(env);
    l_var = ft_calloc(sizeof(t_var *), len + 1);
    if (!l_var)
        return (NULL);
    while (i < len)
    {
        l_var[i] = ft_calloc(sizeof(t_var), 1);
        if (!l_var[i])
            return (NULL);
        l_var[i]->name = ft_strdup(env[i]), ft_strchr(env[i], '=') - env[i];
        l_var[i]->value = ft_strdup(ft_strchr(env[i], '=') + 1);
        i++;
    }
    l_var[i] = NULL;
    return (l_var);
}

char    **ft_add_env(char *new)
{
    char   **out;

    out = ft_calloc(sizeof(char *), 2);
    if (!out)
        return (NULL);
    out[0] = ft_strdup(new);
    if (!out[0])
    {
        free(out);
        return (NULL);
    }
    out[1] = NULL;
    return (out);
}

/* The ft_env() function creates a list of environment variables. It takes one
    argument: an array of strings. It returns a pointer to a list of environment
    variables. The function allocates memory for the list of environment 
    variables and copies the environment variables from the array of strings to
    the list of environment variables. */

/* The ft_add_new() function adds a new environment variable to the list of
    environment variables. It takes one argument: a string. It returns a pointer
    to an array of strings. The function allocates memory for the new environment
    variable and copies the string to the new environment variable. */