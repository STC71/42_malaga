/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 10:55:46 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 10:55:46 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	int		i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = (res << 1) | (octet & 1);
        octet >>= 1;
        i--;
	}
	return (res);
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }

    // Convertir el argumento de la línea de comandos a un número
    unsigned char octet = (unsigned char)atoi(argv[1]);

    // Llamar a la función reverse_bits
    unsigned char reversed = reverse_bits(octet);

    // Imprimir el resultado
    printf("Original: %u (binario: ", octet);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (octet >> i) & 1);
    }
    printf(")\n");

    printf("Invertido: %u (binario: ", reversed);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (reversed >> i) & 1);
    }
    printf(")\n");

    return 0;
}

/*
The function reverse_bits takes an unsigned char as a parameter and returns 
the value of that byte with its bits reversed. For example, if the input is 
00000001, the output will be 10000000.

The main function takes a byte as a command-line argument, converts it to an
unsigned char, and calls reverse_bits. The result is then printed to the
standard output.

The program compiled with the following command:
gcc -Wall -Wextra -Werror reverse_bits.c -o reverse_bits
*/