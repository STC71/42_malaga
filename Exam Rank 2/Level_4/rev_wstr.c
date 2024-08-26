/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 11:27:39 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 11:27:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>         // for write

int main(int argc, char *argv[])
{
	int start;              // start of the word
	int end;                // end of the word
	int i = 0;              // index to iterate through the string
		
	if(argc == 2)
	{   
		while(argv[1][i] != '\0')
			i++;
        // For the string "Hello world, from 42 Málaga" i = 29 
		while(i >= 0)
		{
			while( argv[1][i] == '\0' || argv[1][i] == ' ' || argv[1][i] == '\t')
				i--;        // skip spaces, tabs and null characters
			end = i;        // ends at the last character of the word
			while(argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
				i--;
			start = i + 1;	// starts at the first character of the word
			int  flag;		// flag to check if it is the first word
			flag = start;	// flag is the first word
			while(start <= end)
			{
				write (1, &argv[1][start],1);
				start++;		
			}
			if (flag != 0)	// if it is not the first word
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}

// to compile and run the program:
// gcc -Wall -Wextra -Werror rev_wstr.c -o rev_wstr; ./rev_wstr "Hello world, from 42 Málaga"

/*
The program receives a string of characters as an argument and displays each
word of the string in reverse order.
It checks that the number of arguments is equal to 2. If so, it iterates through
the string until the end of the string is found. It iterates through the string
from right to left, skipping spaces, tabs, and null characters. It saves the
position of the end of the word and iterates through the word from left to right
displaying each character. It displays a space if it is not the first word. It
repeats the process until the beginning of the string.

Example:
./rev_wstr "Hello world, from 42 Málaga"
Málaga 42 from world, Hello
*/

/*
El programa recibe una cadena de caracteres como argumento y muestra cada 
palabra de la cadena en orden inverso.
Se comprueba que el número de argumentos sea igual a 2. Si es así, se recorre
la cadena de caracteres hasta encontrar el final de la cadena. Se recorre la
cadena de caracteres de derecha a izquierda, se salta los espacios, tabuladores
y caracteres nulos. Se guarda la posición del final de la palabra y se recorre
la palabra de izquierda a derecha mostrando cada caracter. Se muestra un espacio
si no es la primera palabra. Se repite el proceso hasta llegar al inicio de la
cadena.

Ejemplo:
./rev_wstr "Hello world, from 42 Málaga"
Málaga 42 from world, Hello
*/