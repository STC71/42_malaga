/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-02 09:04:06 by sternero          #+#    #+#             */
/*   Updated: 2024-08-02 09:04:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main    (int argc, char *argv[])
{
    char    *str;
    int     first;

    str = argv[1];
    first = 1;      // 1 = true / 0 = false
    if (argc == 2)
    {
        while (*str == 32 || *str == 9)
            str++;
        while (*str)
        { 
            if (!first && (*str != ' ' && *str != '\t')) // if first = 0
                write(1, " ", 1);
            while (*str && *str != ' ' && *str != '\t')
            {
                write(1, str, 1);
                str++;
            }
            while (*str == ' ' || *str == '\t')
                str++;
            first = 0;
        }
    }
    write(1, "\n", 1);
    return (0);
}

/*
The program receives a string as an argument and removes unnecessary 
spaces and tabulations. If the program is called with the string 
    "   hi        how r you?   ",
the program will print "hi how r you?".

The program compiled with the following command:
    gcc -Wall -Wextra -Werror epur_str.c -o epur_str

El programa recibe una cadena como argumento y elimina los espacios y 
tabulaciones innecesarios. Si se llama al programa con la cadena 
    "   hola        que tal?   ", 
el programa imprimirá "hola que tal?".

Descripción General:
1. La función main recibe una cadena como argumento.
2. La variable first se inicializa en 1.
3. Si el número de argumentos es 2, se eliminan los espacios y tabulaciones
   innecesarios.
4. Se imprime la cadena resultante.
*/
