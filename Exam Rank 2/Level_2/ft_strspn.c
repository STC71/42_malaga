/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 11:39:56 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 11:39:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strspn(const char *s, const char *accept)
{
    size_t  i;
    size_t  res;
    int     j;

    i = 0;
    res = 0;
    while (s[i])
    {
        j = 0;
        while (accept[j])
        {
            if (s[i] == accept[j])
            {
                res++;
                break;
            }
            j++;
        }
        if (!accept[j])
            break;
        i++;
    }
    return (res);
}

#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
    if (argc != 3)
        fprintf(stderr, "Uso: %s <cadena 1> <cadena 2>\n", argv[0]);
    else
    {
        printf("El número de caracteres coincidentes es: %zu\n", ft_strspn(argv[1], argv[2]));
        printf("El resultado de la función original es : %zu\n", strspn(argv[1], argv[2]));
    }
    return (0);
}
