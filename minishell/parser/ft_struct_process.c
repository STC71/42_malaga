/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 13:00:51 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 13:00:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_process_double(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_double(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != '"')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

char    *ft_process_singel(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_singel(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != '\'')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

char    *ft_process_pipe(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_pipe(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != '|')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

char    *ft_redirection_1(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_redirection_1(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != '>')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

char    *ft_redirection_2(char *str, int *i)
{
    char    *word;
    int     len;
    int     j;

    len = ft_len_redirection_2(str, *i);
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    j = 0;
    while (str[*i] && str[*i] != '<')
    {
        word[j] = str[*i];
        j++;
        *i++;
    }
    word[j] = '\0';
    return (word);
}

/* The ft_process_double() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. The " character is used to extract the word.
*/

/* The ft_process_singel() function extracts a word from a string. It takes 
    two arguments: a string and a pointer to an index. It returns a pointer to 
    the word extracted from the string. The ' character is used to extract the
    word. */ 

/* The ft_process_pipe() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. The | character is used to extract the word.
*/

/* The ft_redirection_1() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. The > character is used to extract the word.
*/

/* The ft_redirection_2() function extracts a word from a string. It takes two
    arguments: a string and a pointer to an index. It returns a pointer to the
    word extracted from the string. The < character is used to extract the word.
*/