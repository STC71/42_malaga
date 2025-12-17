/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 13:44:02 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 13:44:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_matrixdup(char **matrix)
{
	char	**new;
	int		i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i])
		i++;
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		if (!new[i])
		{
			ft_matrix_free(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

/*	The ft_matrixdup and ft_matrix_free functions are used to duplicate and 
	free a matrix of strings. The ft_matrixdup function duplicates the matrix
	of strings passed as an argument and returns a pointer to the new matrix.
	The ft_matrix_free function frees the memory of the matrix of strings
	passed as an argument.*/
