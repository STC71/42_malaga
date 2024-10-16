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

/* The ft_vector_len() function takes one argument: an array of strings. 
    It returns the number of strings in the array. */