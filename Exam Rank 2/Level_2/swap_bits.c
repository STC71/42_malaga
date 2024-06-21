/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 11:47:05 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 11:47:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned char	swap_bits(unsigned char octet)
{
    return ((octet >> 4) | (octet << 4));
}

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <byte>\n", argv[0]);
        return 1;
    }

    unsigned char octet = (unsigned char)atoi(argv[1]);
    unsigned char swapped = swap_bits(octet);

    printf("Original: %u (binario: ", octet);
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (octet >> i) & 1);
    }
    printf(")\n");

    printf("Swapped: %u (binario: ", swapped);
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (swapped >> i) & 1);
    }
    printf(")\n");

    return 0;
}

/*
The function swap_bits takes an unsigned char as a parameter
and swaps the 4 most significant bits with the 4 least significant bits.

The main function takes a byte as a command-line argument,
converts it to an unsigned char, and calls swap_bits.

The program compiled with the following command:
gcc -Wall -Wextra -Werror swap_bits.c -o swap_bits
*/