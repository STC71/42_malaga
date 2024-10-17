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

void    ft_breaking_lines(t_minishell *minishell)
{
    int     n_pipe;
    int     i;
    int     index;
    t_cmd   *cmds;

    index = 0;
    i = 0;
    n_pipe = ft_num_pipes(minishell->split_cmd);
    cmds = ft_calloc(n_pipe + 1, sizeof(t_cmd *));
    ft_mem_alloc(cmds, minishell->split_cmd);
    while (minishell->split_cmd[i])
    {
        ft_parse_command(minishell->split_cmd, &i, cmds[index]);
        if (minishell->split_cmd[i] 
            && strcmp(minishell->split_cmd[i], "|") == 0)
            i++;
        index++;
    }
    i = 0;
    if (minishell->cmds)
    {
        while (minishell->cmds[i])
            ft_free_cmd(minishell->cmds[i++]);
        free(minishell->cmds);
    }
}

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

char    **ft_add_str(char **vector, char *str)
{
    int     i;
    char    **out;

    i = 0;
    while (vector[i])
        i++;
    out = ft_calloc(sizeof(char *), i + 2);
    if (!out)
        return (NULL);
    i = 0;
    while (vector[i])
        out[i] = vector[i++];
    out[i] = ft_strdup(str);
    if (!out[i])
    {
        free(out);
        return (NULL);
    }
    out[i + 1] = NULL;
    free(vector);
    return (out);
}

/* The ft_breaking_lines() function breaks the command into lines. It takes a
    pointer to a t_minishell structure as an argument. It allocates memory for
    the commands and calls the ft_parse_command() function to parse the command.
     */

/* The ft_find_var() function finds the variable in the command. It takes two
    arguments: a string and an index. It returns a pointer to the variable. */

/* The ft_get_var() function gets the value of the variable. It takes two
    arguments: a pointer to a t_var structure and a pointer to a string. It
    returns a pointer to the value of the variable. */

/* The ft_insert_str() function inserts a string into another string. It takes
    three arguments: two strings and a position. It returns a pointer to the new
    string. */

/* The ft_add_str() function adds a new string to an array of strings. It takes
    two arguments: an array of strings and a string. It returns a pointer to the
    new array of strings. */
