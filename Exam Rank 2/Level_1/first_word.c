/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-31 11:56:36 by sternero          #+#    #+#             */
/*   Updated: 2024-05-31 11:56:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char **argv)
{
    int i;

    i = 0;
    if (argc == 2)
    {
        while ((argv[1][i] == 9) || (argv[1][i] == 32))
            i++;
        while ((argv[1][i] != 9) && (argv[1][i] != 32) && (argv[1][i]))
        {
            write (1, &argv[1][i], 1);
            i++;
        }
    }
    write (1, "\n", 1);
    return (0);
}

/*
This program takes a string as an argument and prints the first word of that string.
The program first checks if there is exactly one argument passed to it. If there is,
it then iterates over the characters of the string until it encounters a tab (ASCII 9)
or a space (ASCII 32). This loop is used to skip any leading whitespace characters.
Once it reaches the first non-whitespace character, it prints characters until it
encounters another tab, space, or the end of the string. This prints the first word
of the input string. Finally, the program prints a newline character to end the output. 

To compile and run the program, you can use the following commands:
gcc -Wall -Werror -Wextra first_word.c -o first_word; ./first_word "Hello, World!"

Este programa toma una cadena como argumento e imprime la primera palabra de esa cadena.
El programa primero verifica si se pasa exactamente un argumento. Si es así,
itera sobre los caracteres de la cadena hasta que encuentra un tabulador (ASCII 9)
o un espacio (ASCII 32). Este bucle se utiliza para omitir cualquier carácter de espacio 
en blanco inicial. Una vez que llega al primer carácter que no es un espacio en blanco,
imprime caracteres hasta que encuentre otro tabulador, espacio o el final de la cadena.
Esto imprime la primera palabra de la cadena de entrada. Finalmente, el programa imprime
un carácter de nueva línea para finalizar la salida.
*/