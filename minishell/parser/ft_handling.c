/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 11:50:34 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 11:50:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_end_word(char *str, int i)
{
    while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<' 
        && str[i] != '|')
        i++;
    return (i);
}

int     ft_len_word(char *str, int i)
{
    int len;

    len = 0;
    while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<' 
        && str[i] != '|')
    {
        len++;
        i++;
    }
    return (len);
}

char    *ft_process_word(char *str, int *i)
{
    char *word;
    int len;
    int j;

    len = ft_len_word(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != ' ' && str[*i] != '>' && str[*i] != '<')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

void    ft_handling_inside(char **elements, int *i, t_cmd *cmds, int *inside)
{
    cmds->cmd_in[(*inside++)] = ft_strdup(elements[(*i)]);
    (*i)++;
    if (elements[(*i)])
        cmds->cmd_in[(*inside++)] = ft_strdup(elements[(*i)++]);
}

void    ft_handling_outside(char **elements, int *i, t_cmd *cmds, int *outside)
{
    cmds->cmd_out[(*outside++)] = ft_strdup(elements[(*i)]);
    (*i)++;
    if (elements[(*i)])
        cmds->cmd_out[(*outside++)] = ft_strdup(elements[(*i)++]);
}

/* The ft_end_word() function calculates the end of a word in a string. It takes
    two arguments: a string and an index. It returns the index of the next space
    or redirection character in the string. */

/* The ft_len_word() function calculates the length of a word in a string. It
    takes two arguments: a string and an index. It returns the length of the 
    word in the string. */

/* The process_char() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. */

/* The ft_handling_inside() function processes the input redirection command. It
    takes four arguments: an array of elements, a pointer to an index, a pointer
    to a structure of type t_cmd, and a pointer to a variable. */

/* The ft_handling_outside() function processes the output redirection command. 
    It takes four arguments: an array of elements, a pointer to an index, a 
    pointer to a structure of type t_cmd, and a pointer to a variable. */

