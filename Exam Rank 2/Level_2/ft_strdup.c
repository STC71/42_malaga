/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 14:38:21 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 14:38:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char    *ft_strdup(char *src)
{
    int i = 0;
    int len = 0;
    char *dst;

    while (src[len])
        len++;
    dst = malloc (sizeof(*dst) * (len + 1));  
    if (dst != NULL)
    {
        while (src[i])
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (dst);
}

#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Uso: %s <cadena>\n", argv[0]);
        return 1;
    }

    char *src = argv[1];
    char *duplicado = ft_strdup(src);

    if (duplicado == NULL) {
        fprintf(stderr, "No se pudo asignar memoria para la cadena duplicada.\n");
        return 1;
    }

    printf("Cadena original: %s\n", src);
    printf("Cadena duplicada: %s\n", duplicado);

    // Liberar la memoria asignada
    free(duplicado);

    return 0;
}

/*
The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror ft_strdup.c -o ft_strdup
*/