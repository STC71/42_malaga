/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 12:51:59 by sternero          #+#    #+#             */
/*   Updated: 2024-09-17 12:51:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd) 			// Function to read a line from a file
{
	int 	i = 0;						// Counter
	int		byte;						// Number of bytes read
	char	*str_buf;					// Buffer to store the line read
	char	c;							// Character read

	if (fd < 0 || BUFFER_SIZE < 1) 		// Check if the file descriptor is valid 
										// and the buffer size is greater than 0
		return (NULL);

	str_buf = (char*)malloc(42000000);	// Allocate memory for the buffer
	if (!str_buf)						// Check if the memory allocation was 
										// successful, if not, return NULL
		return (NULL);
	byte = read(fd, &c, 1);				// Read the first byte from the file

	while (byte > 0)					// Loop to read the file byte by byte
										// until the end of file or a new line
	{
		str_buf[i] = c;					// Store the character in the buffer
		i++;							// Increment the counter
		if (c == EOF || c == '\n')		// Check if the character is the end of 
										// file or a new line
			break ;
		byte = read(fd, &c, 1);			// Read the next byte from the file
	}

	if (i == 0 || byte < 0)				// Check if the buffer is empty or 
										// an error occurred while reading the file
	{
		free(str_buf);					// Free the memory allocated for the buffer
		return (NULL);					// Return NULL
	}
	str_buf[i] = '\0';					// Add a null terminator at the end of the 
										// buffer to mark the end of the string
	return (str_buf);					// Return the pointer to the first character 
										// of the buffer
}

// ------------------------------- TEST FUNCTION --------------------------------

// The main function is used to test the get_next_line function. 
// Only used for testing purposes. NOT NECESSARY FOR THE PROJECT.

// To compile the program, run the following command:
// gcc -Wall -Wextra -Werror get_next_line.c -o gnl
// To run the program, run the following command:
// ./gnl <file.txt>

int		main(int ac, char **av)
{
	int	fd;
	char	*line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (1);
		line = get_next_line(fd);
		while (line)
		{
			printf("%s\n", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (0);
}

/* -------------------------- DESCRIPTION OF THE CODE ---------------------------

Este código es un ejemplo de cómo se podría implementar la función get_next_line 
en C. La función get_next_line se utiliza para leer una línea de un archivo y
almacenarla en un buffer. La función toma un descriptor de archivo como argumento
y devuelve un puntero a la línea leída. 
Un descriptor de archivo es un número entero que se utiliza para identificar un
archivo abierto en un programa. En este código, el descriptor de archivo se pasa
como argumento a la función get_next_line para leer el archivo. 
La función lee el archivo byte por byte hasta encontrar un carácter de nueva 
línea o el final del archivo. Luego almacena los caracteres leídos en un buffer 
y devuelve un puntero al buffer. 
Si no se puede leer ninguna línea o se produce un error, la función devuelve NULL. 
El código también incluye una función main para probar la función get_next_line. 
La función main toma un nombre de archivo como argumento de línea de comandos, 
abre el archivo y llama a get_next_line para leer y mostrar cada línea del archivo. 
Este código es solo un ejemplo y no es necesario para el proyecto. 
Se puede compilar y ejecutar el código para probar la función get_next_line con 
un archivo de texto.

---------------------------------------------------------------------------------

This code is an example of how the get_next_line function could be implemented 
in C. The get_next_line function is used to read a line from a file and store it
in a buffer. The function takes a file descriptor as an argument and returns a
pointer to the line read.
A file descriptor is an integer number used to identify an open file in a program.
In this code, the file descriptor is passed as an argument to the get_next_line
function to read the file.
The function reads the file byte by byte until it finds a newline character or
the end of the file. It then stores the read characters in a buffer and returns
a pointer to the buffer.
If no line can be read or an error occurs, the function returns NULL.
The code also includes a main function to test the get_next_line function.
The main function takes a file name as a command-line argument, opens the file,
and calls get_next_line to read and display each line of the file.
This code is just an example and is not necessary for the project.
It can be compiled and run to test the get_next_line function with a text file.
*/