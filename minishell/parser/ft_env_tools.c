/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 17:51:45 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 17:51:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_find_var(char *str, int i)
{
    char    *var;
    int     j;

    j = i;
    while (str[i] && ft_isalnum(str[i]))
        i++;
    var = ft_strndup(str + j, i - j);
    return (var);    
}

char    *ft_get_var(t_var **list_var, char *str)
{
    int     i;

    i = 0;
    while (list_var[i])
    {
        if (ft_strcmp(list_var[i]->name, str) == 0)
            return (ft_strdup(list_var[i]->value));
        i++;
    }
    return (ft_strdup(""));
}

char    *ft_insert_str(char *str, char *ins, size_t pos)
{
    char    *out;
    size_t  npos;
    size_t  ppos;

    npos = 0;
    ppos = 0;
    out = ft_calloc(sizeof(char), ft_strlen(str) + ft_strlen(ins) + 1);
    while (npos < pos)
        out[npos] = str[ppos++];
    while (ins[ppos])
        out[npos++] = ins[ppos++];
    while (str[pos])
        out[npos++] = str[pos++];
    return (out[npos] = '\0', out);
}

/* The ft_find_var() function finds the variable in the command. It takes two
    arguments: a string and an index. It returns a pointer to the variable. */

/* The ft_get_var() function gets the value of the variable. It takes two
    arguments: a pointer to a t_var structure and a pointer to a string. It
    returns a pointer to the value of the variable. */

/* The ft_insert_str() function inserts a string into another string. It takes
    three arguments: two strings and a position. It returns a pointer to the new
    string. */
