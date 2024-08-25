/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 09:12:09 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 09:12:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char *ft_strncpy(char *s1, char *s2, int n) // copy n characters from s2 to s1
{
    int i = -1;                             // initialize i to -1 to start at 0

    while (++i < n && s2[i])
        s1[i] = s2[i];
    s1[i] = '\0';
    return (s1);                            // return the copied string
}

char	**ft_split(char *str)           // *str = "Hello world, from 42 Málaga"
{
	int i = 0;                              // i to iterate through the string
	int j = 0;                              // j to store the start of a word
	int k = 0;                              // k to store the index of the word
	int wc = 0;                             // wc to store the word count
	
	// With the string "Hello world, from 42 Málaga" we have 5 words.
    // With the next loop we will count the number of words in the string.
    while (str[i])                          // while the string is not over
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;                            
        // if we have space or tab or newline, before the first word, we skip it
        if (str[i])
            wc++;
        // if we find the first word, we increment the word count.
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
            i++;
        // we follow the word until we find a space, tab or newline.
    }
    //Now we know the number of words in the string = wc = 5
	
	char **out = (char **)malloc(sizeof(char *) * (wc + 1));
	// malloc = 5 (words) + 1 (null pointer) = 6 * sizeof(char *) = 6 * 8 = 48 bytes
    // sizeof(char *) = 8 bytes on a 64-bit system
    
    i = 0;                                // reset i to 0
	

    // Now we will split the string into words and store each word in the out array.
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
        // j will store the start of the word. j = 0, 6, 12, 18, 22
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
        // i will store the end of the word. i = 5, 11, 17, 21, 29
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
            // We reserve memory for the word + 1 byte for the null character.
            // sizeof(char) = 1 byte on a 64-bit system 
            // 5 + 1 = 6 bytes, for the first word "Hello"
            // 6 + 1 = 7 bytes, for the second word "world,"
            // 4 + 1 = 5 bytes, for the third word "from"
            // 2 + 1 = 3 bytes, for the fourth word "42"
            // 7 + 1 = 8 bytes, for the fifth word "Málaga"
        	ft_strncpy(out[k++], &str[j], i - j);
            // We copy the word into the out array.
            // out[0] = "Hello"
            // out[1] = "world,"
            // out[2] = "from"
            // out[3] = "42"
            // out[4] = "Málaga"
		}
	}
	out[k] = NULL;
    // We assign a null pointer at the end of the out array.
    // out[5] = NULL
	return (out);
    // We return the out array containing the words from the original string.
    // out = ["Hello", "world,", "from", "42", "Málaga", NULL]
}

// The main fuction is used to test the ft_split function.
// Its is not necessary to the exercise.

int main (int argc, char *argv[])
{
    if (argc == 1)
        return 0;

    char *str = argv[1];
    char **words = ft_split(str);
    int i = -1;

    while (words[++i])
        printf("%s\n", words[i]);
    return 0;
}

// To compile and run the program, you can use the following commands:
// gcc -Wall -Werror -Wextra ft_split.c -o ft_split; ./ft_split "Hello world"


/*
The ft_strncpy function copies n characters from string s2 to string s1.
The function takes three arguments: a pointer to the destination string (s1),
a pointer to the source string (s2), and an integer representing the number
of characters to copy (n).

The ft_split function splits a string into words and stores each word in an
array of strings. It takes a pointer to a string (str) as an argument and
returns a pointer to an array of strings containing the words from the original
string.

Function ft_split:

The function starts with a while loop that iterates through the input string (str).
In each iteration of the loop, spaces, tabs, and newlines are skipped by incrementing
the index i. The number of words in the string is counted by counting the spaces
between the words (wc) and the current word is skipped by incrementing the index i.

Memory is allocated for the output array of strings (out) using malloc. The size of
the array is calculated as the number of words in the string plus one to store a null
pointer at the end of the array.

The index i is reset to 0 and the input string is iterated through again. In each
iteration, spaces, tabs, and newlines are skipped by incrementing the index i. The
start index of the word is stored in j and the current word is skipped by incrementing
the index i. If the length of the word is greater than 0, memory is allocated to store
the word in the output array of strings (out) and the word is copied into the array
using the ft_strncpy function.

At the end of the loop, a null pointer is assigned to the end of the output array of
strings to mark the end of the array.

The function returns the output array of strings (out) containing the words from the
original string.

The difference between the two mallocs is that the first one allocates memory for an
array of pointers to char (char **) and the second one allocates memory for an array
of characters (char *). In the first malloc, memory is allocated to store the pointers
to the word strings, while in the second malloc, memory is allocated to store the words
themselves. The sizes are not proportional, as the size of a pointer to char (char **) is
different from the size of a char. In a 64-bit system, the size of a pointer to char
(char **) is 8 bytes, while the size of a char (char) is 1 byte.

Example Usage:

Suppose we have a string containing: "Hello world, from 42 Málaga".
We can use the ft_split function to split the string into words and store each word
in an array of strings. And the result would be an array of strings containing the 
words from the original string: ["Hello", "world,", "from", "42", "Málaga"]
*/


/*
La función ft_strncpy copia n caracteres de la cadena s2 a la cadena s1.
La función toma tres argumentos: un puntero a la cadena de destino (s1), 
un puntero a la cadena de origen (s2) y un entero que representa el número
de caracteres a copiar (n). 

La función ft_split divide una cadena en palabras y almacena cada palabra
en un array de cadenas. Toma un puntero a una cadena (str) como argumento
y devuelve un puntero a un array de cadenas que contiene las palabras de
la cadena original.

Función ft_split:

La función comienza con un bucle while que recorre la cadena de entrada (str).
En cada iteración del bucle, se saltan los espacios en blanco, tabulaciones y
saltos de línea al incrementar el índice i. Se cuenta el número de palabras en
la cadena contando los espacios entre las palabras (wc) y se salta la palabra
actual al incrementar el índice i.

Se asigna memoria para el array de cadenas de salida (out) utilizando malloc.
El tamaño del array se calcula como el número de palabras en la cadena más uno
para almacenar un puntero nulo al final del array.

Se reinicia el índice i a 0 y se recorre la cadena de entrada nuevamente.
En cada iteración, se saltan los espacios en blanco, tabulaciones y saltos de
línea al incrementar el índice i. Se almacena el índice de inicio de la palabra
en j y se salta la palabra actual al incrementar el índice i. Si la longitud de
la palabra es mayor que 0, se asigna memoria para almacenar la palabra en el
array de cadenas de salida (out) y se copia la palabra en el array utilizando
la función ft_strncpy.

Al final del bucle, se asigna un puntero nulo al final del array de cadenas de
salida para marcar el final del array.

La función devuelve el array de cadenas de salida (out) que contiene las palabras
de la cadena original.

La diferencia entre los dos malloc es que el primero reserva memoria para un array
de punteros a char (char **) y el segundo reserva memoria para un array de caracteres
(char *). En el primer malloc, se reserva memoria para almacenar los punteros a las
cadenas de palabras, mientras que en el segundo malloc, se reserva memoria para
almacenar las palabras en sí. Los tamaños no son proporcionales, ya que el tamaño
de un puntero a char (char *) es diferente al tamaño de un char. En un sistema de
64 bits, el tamaño de un puntero a char (char **) es de 8 bytes, mientras que el
tamaño de un char (char) es de 1 byte.

Ejemplo de uso:

Supongamos que tenemos una cadena que contiene: "Hello world, from 42 Málaga".
Podemos utilizar la función ft_split para dividir la cadena en palabras y almacenar
cada palabra en un array de cadenas.

El resultado sería un array de cadenas que contiene las palabras de la cadena original:
["Hello", "world,", "from", "42", "Málaga"]
*/