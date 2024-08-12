/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-04 09:47:45 by sternero          #+#    #+#             */
/*   Updated: 2024-08-04 09:47:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

int     main (int agrc, char *argv[])
{
    int i = 0;  // Counter to keep track of the position in the string 1
    int j = 0;  // Counter to keep track of the position in the string 2

    if (agrc == 3)  // If the number of arguments is 3
    {
        while (argv[2][j] && argv[1][i]) 
        // While the string 2 and the string 1 are not '\0'
        {
            if (argv[2][j] == argv[1][i])  
            // If the characters are the same in both strings
                i++;    // It increments the counter of the string 1
            j++;        // Else it increments the counter of the string 2
        }
        if (!argv[1][i])        // If the string 2 is '\0'
            write(1, "1", 1);   // because all the characters of the string 1 
                                // are in the string 2
        else
            write(1, "0", 1);    
            // Otherwise, it writes '0' to the standard output.
    }
    write(1, "\n", 1);  // It writes a newline to the standard output.
    return (0); // It returns 0 to the operating system.
}

/*
The program hidenp receives two strings as arguments. S1 and S2.
It uses two counters, i and j, to keep track of the position in the strings.
It uses a while loop to compare the characters of the strings.
If the characters are the same in both strings, it increments the counter of S1,
and so it follows comparing the next characters. Else it increments the counter 
of S2 to compare the same character of S1 with the next character of S2.
If the string 1 is '\0', it means that all the characters of S1 are in S2.
It writes '1' to the standard output.
Otherwise, it writes '0' to the standard output, because not all the characters
of S1 are in S2.
It writes a newline to the standard output, and it returns 0.

To compile the program:
    gcc -Wall -Wextra -Werror hidenp.c -o hidenp

El programa hidenp recibe dos cadenas como argumentos. S1 y S2.
Utiliza dos contadores, i y j, para llevar la cuenta de la posición en las 
cadenas. 
Utiliza un bucle while para comparar los caracteres de las cadenas.
Si los caracteres son iguales en ambas cadenas, incrementa el contador de S1,
y así sigue comparando los siguientes caracteres. De lo contrario, incrementa el
contador de S2 para comparar el mismo carácter de S1 con el siguiente carácter de
S2.
Si la cadena 1 es '\0', significa que todos los caracteres de S1 están en S2.
Escribe '1' en la salida estándar.
De lo contrario, escribe '0' en la salida estándar, porque no todos los caracteres
de S1 están en S2.
Escribe una nueva línea en la salida estándar, y devuelve 0.
*/