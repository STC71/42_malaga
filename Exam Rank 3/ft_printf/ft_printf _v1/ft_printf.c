/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 11:26:40 by sternero          #+#    #+#             */
/*   Updated: 2024-09-17 11:26:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>						// Include the write function
#include <stdarg.h>						// Include the variable arguments list

int putstr(char *str, int i)                    // Function to print a string
{
	if (!str)
		return putstr("(null)", i);		// Print "(null)" if the string is NULL
	if (!str[i])
		return i;						// Return the number of characters printed
	write(1, &str[i], 1);
	return putstr(str, i+1);			// Recursively print the next character
}

int putnum(long num, int base)                  // Function to print a number
{
	char *b = "0123456789abcdef";		// Array of characters for base conversion
	if (num <0 && base == 10)
		return write(1, "-", 1) + putnum(num*-1, base);	// Print the negative sign
	if (num <0 && base == 16)
		return putnum((unsigned int)num, base);	// Print the negative number in hexadecimal
	if (num/base==0)
		return write(1, &b[num%base], 1); 		// Print the last digit of the number
	return putnum(num/base, base) + putnum(num%base, base); 
								// Recursively print the number in the given base
}

int ptf(char *s, va_list args, int i, int n)    // Function to parse the string
{
	if (!s[i])
		return n;						// Return the number of characters printed
	if (s[i] == '%' && s[i + 1] == 's')		// Check for the %s format specifier
		return ptf(s, args, i + 2, n + putstr(va_arg(args, char *), 0));
	if (s[i] == '%' && s[i + 1] == 'd') 	// Check for the %d format specifier
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 10));
	if (s[i] == '%' && s[i + 1] == 'x')		// Check for the %x format specifier
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 16));
	write(1, &s[i], 1);					// Print the character if no format specifier
	return ptf(s, args, i + 1, n + 1);	// Recursively parse the next character
}

int ft_printf(char *s, ...)                     // Function to call the parser
{
	va_list args;								// Variable arguments list
	return va_start(args, s), va_end(args), ptf(s, args, 0, 0);
								// Call the parser with the string and arguments
}

// ------------------------------- TEST FUNCTION --------------------------------

#include <stdio.h>

int 	main (void)
{
	ft_printf("Whit the ft_printf of this code: \n");
	ft_printf("Hello, %s! %d %x\n", "world", 42, 42);
	ft_printf("1971 in hexadecimal is: %x\n", 1971);
	ft_printf("\n");

	printf("Whit the printf of the library: \n");
	printf("Hello, %s! %d %x\n", "world", 42, 42);
	printf("1971 in hexadecimal is: %x\n", 1971);
	printf("\n");

	return 0;
}

// The main function is used to test the ft_printf function.
// Only used for testing purposes. NOT NECESSARY FOR THE PROJECT.

// To compile the program, run the following command:
// gcc -Wall -Wextra -Werror ft_printf.c -o ft_printf
// To run the program, run the following command:
// ./ft_printf
// For example, the output of the program should be:
// Hello, world! 42 2a

/* -------------------------- DESCRIPTION OF THE CODE ---------------------------

Este código es un ejemplo de cómo se podría implementar la función ft_printf en C.
La función ft_printf es una versión simplificada de la función printf que se utiliza
para imprimir cadenas de texto y números en la consola. La función toma una cadena de
formato y una lista de argumentos variables y muestra la cadena de formato con los
argumentos reemplazados en la consola.
La función ft_printf utiliza las funciones putstr y putnum para imprimir cadenas de
texto y números respectivamente. La función putstr recorre la cadena de texto
carácter por carácter y la imprime en la consola. La función putnum convierte un
número en una cadena de caracteres y lo imprime en la consola.
La función ptf se encarga de analizar la cadena de formato y los argumentos
variables y llamar a las funciones putstr y putnum según sea necesario. La función
ptf recorre la cadena de formato carácter por carácter y reemplaza los marcadores
de posición %s, %d y %x con los argumentos correspondientes.
La función ft_printf se encarga de inicializar y finalizar la lista de argumentos
variables y llamar a la función ptf con la cadena de formato y los argumentos
variables. La función ft_printf devuelve el número total de caracteres impresos en
la consola.
El código también incluye una función main para probar la función ft_printf. La
función main llama a la función ft_printf con diferentes cadenas de formato y
argumentos y muestra los resultados en la consola.

---------------------------------------------------------------------------------

This code is an example of how the ft_printf function could be implemented in C.
The ft_printf function is a simplified version of the printf function used to print
strings and numbers to the console. The function takes a format string and a list of
variable arguments and displays the format string with the arguments replaced on the
console.
The ft_printf function uses the putstr and putnum functions to print strings and
numbers respectively. The putstr function iterates through the string character by
character and prints it to the console. The putnum function converts a number to a
string of characters and prints it to the console.
The ptf function is responsible for parsing the format string and variable arguments
and calling the putstr and putnum functions as needed. The ptf function iterates
through the format string character by character and replaces the %s, %d, and %x
placeholders with the corresponding arguments.
The ft_printf function handles initializing and finalizing the variable arguments
list and calling the ptf function with the format string and variable arguments. The
ft_printf function returns the total number of characters printed to the console.
The code also includes a main function to test the ft_printf function. The main
function calls the ft_printf function with different format strings and arguments and
displays the results on the console.
*/