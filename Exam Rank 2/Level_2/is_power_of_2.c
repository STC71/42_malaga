/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 15:42:29 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 15:42:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_power_of_2(unsigned int n)
{
    if (n == 0)
        return 0;
    return (n & (n - 1)) == 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int n;

    // Verificar que se haya proporcionado un argumento
    if (argc!= 2) 
    {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }

    // Convertir el argumento a entero
    n = strtoul(argv[1], NULL, 10);

    // Verificar si es una potencia de 2
    if (is_power_of_2(n)) {
        printf("%u es una potencia de 2.\n", n);
    } else {
        printf("%u no es una potencia de 2.\n", n);
    }

    return 0;
}