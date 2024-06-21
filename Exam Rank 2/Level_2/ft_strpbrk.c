/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 08:18:29 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 08:18:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
    int i;
    int j;

    i = 0;
    while (s1[i] != '\0')
    {
        j = 0;
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j])
                return ((char*) &s1[i]);
            j++;
        }
        i++;   
    }
    return NULL; 
}

#include <stdio.h>

int main (int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf (stderr, "Uso: %s <cadena> <caracteres>\n", argv[0]);
        return 1;
    }
    char *resultado = ft_strpbrk(argv[1], argv[2]);
    if(resultado)
        printf("El primer caracter encontrado es %s en la posición %ld.\n", resultado, resultado - argv[1]);
    else
        printf("Ninguno de los resultados de %s se encontro en %s.\n", argv[1], argv[2]);
    return (0);
}

/*
The strpbrk() function locates the first occurrence in the string s1 
of any of the characters in the string s2.

It returns a pointer to the character in s1 that matches one of the 
characters in s2, or NULL if no such character is found.

The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror ft_strpbrk.c -o ft_strpbrk
*/