/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-18 12:28:31 by sternero          #+#    #+#             */
/*   Updated: 2024-09-18 12:28:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>						// Include the write function
#include <stdarg.h>						// Include the variable arguments list

void    ft_putstr(char *str, int *len)
{
        if (!str)
                str = "(null)";
        while (*str)
                *len += write(1, str++, 1);
}
void    ft_putnum(long long int nbr, int base, int *len)
{
        char    *hex;
        hex = "0123456789abcdef";
        if (nbr < 0)
        {
                nbr *= -1;
                *len += write(1, "-", 1);
        }
        if (nbr >= base)
                ft_putnum((nbr / base), base, len);
        *len += write(1, &hex[nbr % base], 1);
}
int     ft_printf(const char *format, ...)
{
        int     len;
        va_list ptr;
        len = 0;
        va_start(ptr, format);
        while (*format)
        {
                if ((*format == '%') && *(format + 1))
                {
                        format++;
                        if (*format == 's')
                                ft_putstr(va_arg(ptr, char *), &len);
                        else if (*format == 'd' || *format == 'i')
                                ft_putnum((long long int)va_arg(ptr, int), 10, &len);
                        else if (*format == 'x')
                                ft_putnum((long long int)va_arg(ptr, unsigned int), 16, &len);
                }
                else
                        len += write(1, format, 1);
                format++;
        }
        return (va_end(ptr), len);
}

// ------------------------------- TEST FUNCTION --------------------------------

#include <stdio.h>

int     main(void)
{
        ft_printf("Whit the ft_printf of this code: \n");
        ft_printf("Hello, %s! %d %x\n", "world", 42, 42);
        ft_printf("1971 in hexadecimal is: %x\n", 1971);
        ft_printf("\n");

        printf("Whit the printf of the library: \n");
        printf("Hello, %s! %d %x\n", "world", 42, 42);
        printf("1971 in hexadecimal is: %x\n", 1971);
        printf("\n");

        return (0);
}

// The main function is used to test the ft_printf function.
// Only used for testing purposes. NOT NECESSARY FOR THE PROJECT.

// To compile the program, run the following command:
// gcc -Wall -Wextra -Werror ft_printf.c -o ft_printf
// To run the program, run the following command:
// ./ft_printf

/* -------------------------- DESCRIPTION OF THE CODE ---------------------------

Este código es un ejemplo de cómo se podría implementar la función ft_printf en C.
La función ft_printf es una versión simplificada de la función printf que se utiliza
para imprimir cadenas de texto y números en la consola. La función toma una cadena de
formato y una lista de argumentos variables y muestra la cadena de formato con los
argumentos reemplazados en la consola.

La función ft_printf toma una cadena de formato y una lista de argumentos variables
como argumentos y muestra la cadena de formato con los argumentos reemplazados en la
consola. La función recorre la cadena de formato carácter por carácter y reemplaza los
marcadores de posición %s, %d y %x con los argumentos correspondientes. La función
utiliza las funciones ft_putstr y ft_putnum para imprimir cadenas de texto y números
respectivamente.

La función putnum convierte un número en una cadena de caracteres y lo imprime en la
consola. Primero verifica si el número es negativo y, en ese caso, imprime el signo
negativo. Luego, divide el número por la base y llama a la función de forma recursiva
para imprimir los dígitos restantes. 

La función putstr recorre la cadena de texto carácter por carácter y la imprime en la
consola. Si la cadena es NULL, imprime "(null)" en su lugar. 

El resultado final de la función ft_printf es el número total de caracteres impresos en
la consola. 

El código también incluye una función main para probar la función ft_printf. La función
main llama a la función ft_printf con diferentes cadenas de formato y argumentos y
muestra los resultados en la consola. Esta función main es solo para pruebas y no es
necesaria para el proyecto.

---------------------------------------------------------------------------------

This code is an example of how the ft_printf function could be implemented in C. The
ft_printf function is a simplified version of the printf function used to print strings
and numbers to the console. The function takes a format string and a list of variable
arguments and displays the format string with the arguments replaced on the console.

The ft_printf function takes a format string and a list of variable arguments as
arguments and displays the format string with the arguments replaced on the console. The
function iterates through the format string character by character and replaces the %s,
%d, and %x placeholders with the corresponding arguments. The function uses the ft_putstr
and ft_putnum functions to print strings and numbers respectively.

The putnum function converts a number to a string of characters and prints it to the
console. It first checks if the number is negative and, in that case, prints the negative
sign. Then, it divides the number by the base and calls the function recursively to print
the remaining digits.

The putstr function iterates through the string character by character and prints it to
the console. If the string is NULL, it prints "(null)" instead.

The final result of the ft_printf function is the total number of characters printed to
the console.

The code also includes a main function to test the ft_printf function. The main function
calls the ft_printf function with different format strings and arguments and displays the
results on the console. This main function is for testing purposes only and is not
necessary for the project.

*/