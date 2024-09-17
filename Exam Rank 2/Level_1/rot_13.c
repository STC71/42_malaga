/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 09:57:02 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 09:57:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char **argv)
{
    int i;

    i = 0;
    if (argc > 1)
    {
        while (argv[1][i])
        {
            if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
                argv[1][i] = (argv[1][i] - 'a' + 13) % 26 + 'a';
                // if argv[1][i] = 'a', then argv[1][i] - 'a' = 0
                // (0 + 13) % 26 + 'a' 
                // = 13 % 26 = 13 + 'a' = 'n'
                // if argv[1][i] = 'z', then argv[1][i] - 'a' = 25
                // (25 + 13) = 38 % 26 = 12 + 'a' = 'm'
            else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
                argv[1][i] = (argv[1][i] - 'A' + 13) % 26 + 'A';
            write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}

// The program compiled and run with:
// gcc -Wall -Wextra -Werror rot_13.c -o rot_13; ./rot_13 "Hello, World!"

/*
The main function takes two arguments, the first being the number of
arguments passed to the program and the second being the string to be
printed. If the number of arguments is greater than 1, the program
enters a while loop that iterates through the string. If the character
is a lowercase letter, it is shifted 13 positions in the alphabet. If
the character is an uppercase letter, it is also shifted 13 positions
in the alphabet. The character is then printed to standard output. If
the number of arguments is not greater than 1, the program does nothing.

El programa toma dos argumentos, el primero es el número de argumentos
pasados al programa y el segundo es la cadena a imprimir. Si el número
de argumentos es mayor que 1, el programa entra en un bucle while que
itera a través de la cadena. Si el carácter es una letra minúscula, se
desplaza 13 posiciones en el alfabeto. Si el carácter es una letra
mayúscula, también se desplaza 13 posiciones en el alfabeto. El carácter
se imprime en la salida estándar. Si el número de argumentos no es mayor
que 1, el programa no hace nada.
*/