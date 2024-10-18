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

int     ft_check_invalid_pipe(char *str)
{
    int     i;

    i = 0;
    if (ft_strlen(str) > 0)
        i = ft_strlen(str) - 1;
    else
        i = 0;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
        i--;
    if (i >= 0 && str[i] == '|' || str[i] == '<' || str[i] == '>')
        return (0);
    return (1);
}

int     ft_vector_len(char **vector)
{
    int i;

    i = 0;
    if (!vector)
        return (0);
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

char    *ft_extract_token(const char *str, unsigned int ini, size_t len)
{
    char    *out;
    size_t  i;

   if (!str)
        return (NULL);
    out = ft_strlen(str);
    if (ini >= out)
        return (NULL);
    if (len > out - ini)
        len = out - ini;
    out = ft_calloc(sizeof(char), len + 1);
    if (!out)
        return (NULL);
    ft_strlcpy(out, str + ini, len + 1);
    return (out);
}

/* The ft_check_invalid_pipe() function checks if a string contains a pipe 
    character at the end. It takes one argument: a string. It returns 1 if the
    string does not contain a pipe character at the end, and 0 if the string
    contains a pipe character at the end. */

/* The ft_vector_len() function takes one argument: an array of strings. 
    It returns the number of strings in the array. */

/* The ft_copy_mtx() function takes one argument: an array of strings. It
    returns a copy of the array. */

/* The ft_shell_split() function splits a string into an array of strings.
    It takes one argument: a string. It returns an array of strings. */

/* The ft_extract_token() function extracts a token from a string. It is
    used to extract the tokens from the string. It does not modify the
    original string, but creates a new string with the extracted token. It
    take three arguments: a string, an index, and a length. It returns a
    pointer to the new string. */