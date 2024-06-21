/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 09:24:46 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 09:24:46 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char    *ft_strrev(char *str)
{
    char tmp;
    int len;
    int i;

    len = 0;
    i = 0;
    while (str[len])
        len++;
    while (i < (len / 2))
    {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
        i++;
    }
    return (str);
}

#include <stdio.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
        fprintf (stderr, "Uso: %s <cadena para invertir>\n", argv[0]);
    else
    {
        printf ("La cadena original es: %s\n", argv[1]);
        printf ("La cadena invertida es: %s\n", ft_strrev(argv[1]));
    }
    return (0);
}