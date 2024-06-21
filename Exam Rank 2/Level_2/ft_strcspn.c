/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 13:29:02 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 13:29:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
    int  i = 0;
    int  j = 0;

    while (s[i] != '\0')
    {
        j = 0;
        while (reject[j] != '\0')
        {
            if (s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}

#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        fprintf(stderr, "Instrucción de uso: %s <cadena> <reject>\n", argv[0]);
        return 1;
    }

    const char *s = argv[1];
    const char *reject = argv[2];

    size_t result = ft_strcspn(s, reject);

    printf("La longitud del segmento inicial de '%s' que no contiene ningún carácter de '%s' es %zu.\n", s, reject, result);

    return 0;
}

/*
The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror ft_strcspn.c -o ft_strcspn
*/