/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_strcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 13:00:08 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 13:00:08 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int    ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;     
    return (s1[i] - s2[i]);
}

#include <stdio.h>

int main (int argc, char *argv[])
{
    if (argc == 3)
        printf("%d", ft_strcmp(argv[1], argv[2]));
    return (0);
}

/*
The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror ft_strcmp.c -o ft_strcmp
*/