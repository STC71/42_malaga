/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-02 12:14:38 by sternero          #+#    #+#             */
/*   Updated: 2024-08-02 12:14:38 by sternero         ###   ########.fr       */
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
                write(1, "   ", 3);
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
This program receives a string as an argument and expands the string by
replacing each space by three spaces. If the program is called with the
string "hi how r you?", the program will print "hi   how   r   you?".

The program compiled with the following command:
    gcc -Wall -Wextra -Werror expand_str.c -o expand_str

El programa recibe una cadena como argumento y expande la cadena reemplazando
cada espacio por tres espacios. Si se llama al programa con la cadena
"¿qué tal?", el programa imprimirá "¿qué   tal?".
*/