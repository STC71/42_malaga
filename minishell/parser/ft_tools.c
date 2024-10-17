/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 11:29:28 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 11:29:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_vector_len(char **vector)
{
    int i;

    i = 0;
    while (vector[i])
        i++;
    return (i);
}

char    **ft_copy_mtx(char **mtx)
{
    int     i;
    char    **out;

    i = 0;
    if (!mtx)
        return (NULL);
    while (mtx[i])
        i++;
    out = ft_calloc(sizeof(char *), i + 1);
    if (!out)
        return (NULL);
    i = 0;
    while (mtx[i])
    {
        out[i] = ft_strdup(mtx[i]);
        if (!out[i])
        {
            ft_remove_matrix(out);
            return (NULL);
        }
        i++;
    }
    out[i] = NULL;
    return (out);
}

char    **ft_shell_split(char *vector)
{
    int     i;
    char    **out;
    char    *tmp;

    i = 0;
    out = NULL;
    while (vector[i])
    {
        while (vector[i] == ' ')
            i++;
        if (!vector[i])
            break ;
        tmp = process_token(vector, &i);   // pendiente de implementar
        if (!out)
            out = ft_add_env(tmp);
        else
            out = ft_str_add(out, tmp);
        free(tmp);
    }
    return (out);
}

/* The ft_vector_len() function takes one argument: an array of strings. 
    It returns the number of strings in the array. */

/* The ft_copy_mtx() function takes one argument: an array of strings. It
    returns a copy of the array. */

/* The ft_shell_split() function splits a string into an array of strings.
    It takes one argument: a string. It returns an array of strings. */