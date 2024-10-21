/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 18:51:58 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 18:51:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    ft_remove_last(char **vector)
{
	int     i;
	int     len;
	char    **out;

	i = 0;
	len = ft_vector_len(vector);
	out = ft_calloc(sizeof(char *), len);
	while (i < len - 1)
	{
		out[i] = ft_strdup(vector[i]);
		i++;
	}
	ft_free_vector(vector);
	return (out);
}

void    ft_remove_quotes(char *str)
{
	int     i;
	int     j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				str[j++] = str[i++];
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				str[j++] = str[i++];
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

char    *ft_delete_str(char *str, size_t init, size_t end)
{
	char    *out;
	size_t  len;
	size_t  mpos;
	size_t  npos;
	size_t  nlen;

	len = ft_strlen(str);
	mpos = 0;
	npos = 0;
	nlen = len - (end - init + 1);
	out = (char *)ft_calloc(sizeof(char), nlen + 1);
	while (mpos < init)
		out[npos++] = str[mpos++];
	mpos = end + 1;
	while (mpos < len)
		out[npos++] = str[mpos++];
	out[npos] = '\0';
	return (out);
}

void    ft_remove_matrix(char **matrix)
{
	int     i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
		i++;
	free(matrix);
}

/* The ft_remove_last() function removes the last element from an array of strings.
	It takes one argument: an array of strings. It returns a new array of strings
	with the last element removed. */

/* The ft_remove_qotes() function removes the single and double quotes from a 
	string. It takes one argument: a string and returns void. */

/* The ft_delete_str() function deletes a substring from a string. It takes 
	three arguments: a string, an initial position, and an end position. It
	returns a new string with the substring removed. */

/* The ft_remove_matrix() function frees the memory allocated for a matrix of
	strings. It takes one argument: a matrix of strings. The function frees the
	memory allocated for each string in the matrix and then frees the memory
	allocated for the matrix. */