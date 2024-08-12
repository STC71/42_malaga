/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-04 11:05:20 by sternero          #+#    #+#             */
/*   Updated: 2024-08-04 11:05:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

void    ft_putnbr(int n)
{
    char nbr;               // Variable to store the digit as a character

    if (n >= 10)
        ft_putnbr(n / 10);  // It calls itself with the number divided by 10
    nbr = n % 10 + '0';     // It calculates the digit and converts it to a char
    write(1, &nbr, 1);      // It writes the digit to the standard output
}

int     main(int argc, char *argv[])
{
    (void)argv;             // To avoid the warning: unused parameter 'argv'

    ft_putnbr(argc - 1);   // It writes the number of arguments
    write(1, "\n", 1);      // It writes a newline to the standard output
    return (0);             // It returns 0 to the operating system
}

/*
The program paramsum receives a list of arguments.
It uses a function ft_putnbr to write the number of arguments to the standard 
output.
If n is greater or equal to 10, it calls itself with the number divided by 10, 
to write the digits in the correct order. For example, if the number of arguments
is 12, it will write '1' and '2'.
The function will finish writing a newline to the standard output, 
and returning 0.

El programa paramsum recibe una lista de argumentos.
Utiliza una función ft_putnbr para escribir el número de argumentos en la salida
estándar.
Si n es mayor o igual a 10, se llama a sí misma con el número dividido por 10,
para escribir los dígitos en el orden correcto. Por ejemplo, si el número de
argumentos es 123 escribirá '1', '2' y '3'.
La función terminará escribiendo un salto de línea en la salida estándar, y
devolviendo 0.
*/

// To compile the program:
//     gcc -Wall -Wextra -Werror paramsum.c -o paramsum
