/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-24 09:48:29 by sternero          #+#    #+#             */
/*   Updated: 2024-08-24 09:48:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>  // for printf
#include <stdlib.h> // for atoi

int     main(int argc, char **argv)
{
    int     nb;
    int     div;

    if (argc == 2)
    {
        nb = atoi(argv[1]);            // nb = argv[1] = "42" -> nb = 42
        if (nb == 1)
            printf("1");
        else
        {
            div = 2;
            while (nb > 1)
            {
                if (nb % div == 0)
                {
                    printf("%d", div);  // 42 % 2 = 0 -> 21 % 3 = 0 -> 7 % 7 = 0
                    nb /= div;         // 42 / 2 = 21 -> 21 / 3 = 7 -> 7 / 7 = 1
                    if (nb > 1)
                        printf("*");
                }
                else
                    div++;             // 2 -> 3 -> 7
            }
        }
    }
    printf("\n");
    return (0);
}

// The fprime program takes an integer as an argument and prints the prime factors
// of that integer. The program first checks if there is exactly one argument passed
// to it. If there is, it converts the argument to an integer using the atoi function.
// If the integer is 1, it prints "1" as the only prime factor. Otherwise, the program
// initializes a divisor variable to 2 and enters a loop that continues until the 
// integer becomes 1. In each iteration, it checks if the current divisor is a factor
// of the integer. If it is, it prints the divisor, divides the integer by the divisor,
// and continues the loop. If the divisor is not a factor, it increments the divisor
// and continues the loop. This process finds all the prime factors of the integer.
// Finally, the program prints a newline character to end the output.

// To compile and run the program, you can use the following commands:
// gcc -Wall -Werror -Wextra fprime.c -o fprime; ./fprime 42

// El programa fprime toma un número entero como argumento e imprime los factores
// primos de ese número. El programa primero verifica si se pasa exactamente un
// argumento. Si es así, convierte el argumento a un entero usando la función atoi.
// Si el entero es 1, imprime "1" como el único factor primo. De lo contrario, el
// programa inicializa una variable de divisor en 2 y entra en un bucle que continúa
// hasta que el entero se convierte en 1. En cada iteración, verifica si el divisor
// actual es un factor del entero. Si lo es, imprime el divisor, divide el entero por
// el divisor y continúa el bucle. Si el divisor no es un factor, incrementa el divisor
// y continúa el bucle. Este proceso encuentra todos los factores primos del entero.
// Finalmente, el programa imprime un carácter de nueva línea para finalizar la salida.
