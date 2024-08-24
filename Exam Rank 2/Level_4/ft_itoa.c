/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-24 10:26:21 by sternero          #+#    #+#             */
/*   Updated: 2024-08-24 10:26:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>             // for malloc
#include <stdio.h>              // for printf

char    *ft_itoa(int nbr)
{
    if (nbr > 2147483647 || nbr < -2147483647)      // read the note below
        return (NULL);
    int num = nbr;              // len = nbr = 42
    int len = 0;
    if (num <= 0)
        len++;                  // for the '-' sign
    while (num)
    {
        num /= 10;              // 42 / 10 = 4 -> 4 / 10 = 0
        len++;                  // 1 -> 2
    }
    char *res = (char *)malloc(sizeof(char) * (len + 1));
    // the length of a char is 1 byte, so we don't need to multiply by sizeof(char)
    // if len = 2 -> res = malloc(3) -> res = "42\0"
    if (!res)
        return (NULL);
    res[len] = '\0';          // res[0] = '4' -> res[1] = '2' -> res[len] = '\0'
    if (nbr == 0)
    {
        res[0] = '0';
        return (res);
    }
    if (nbr < 0)
    {
        res[0] = '-';
        nbr = -nbr;             // if nbr < 0 -> nbr = -42
    }
    while (nbr)
    {
        res[--len] = nbr % 10 + '0';
        // res[1] = 42 % 10 + '0' = 2 + '0' = '2' -> res[0] = 4 + '0' = '4'
        nbr /= 10;              // 42 % 10 = 2 -> 4 % 10 = 4
    }
    return (res);               // return '42'
}

// The main fuction is used to test the ft_itoa function. 
// Its is not necessary to the exercise.

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        char *str = ft_itoa(atoi(argv[1]));
        if (str)
        {
            printf("%s\n", str);
            free(str);
        }
    }
    return (0);
}

// The ft_itoa function takes an integer as an argument and converts it to a string.
// The function first checks if the integer is within the range of an int.
// If the integer is within the range,  it calculates the length of the string
// representation of the integer by counting the number of digits in the integer.
// It then allocates memory for the string and converts the integer to a string
// by extracting the digits one by one and storing them in the string.
// If the integer is negative, it adds a '-' sign to the string.
// Finally, it returns the string representation of the integer.

// To compile and run the program, you can use the following commands:
// gcc -Wall -Werror -Wextra ft_itoa.c -o ft_itoa; ./ft_itoa 42

// La función ft_itoa toma un número entero como argumento y lo convierte en una cadena.
// La función primero verifica si el entero está dentro del rango de un int.
// Si el entero está dentro del rango, calcula la longitud de la representación de cadena
// del entero contando el número de dígitos en el entero.
// Luego asigna memoria para la cadena y convierte el entero en una cadena
// extrayendo los dígitos uno por uno y almacenándolos en la cadena.
// La asignación de memoria se realiza con malloc, 
// Si el entero es negativo, agrega un signo '-' a la cadena.
// Finalmente, devuelve la representación de cadena del entero.

/*
Para buscar el valor más alto y más bajo que puede almacenar un tipo de dato `int` 
en C usando las páginas de manual (`man`), puedes consultar la página del manual 
correspondiente a los límites de los tipos de datos enteros. 
El comando para hacer esto es:

man limits.h

Esto te llevará a la página del manual de `limits.h`, que es la cabecera en la que 
se definen los límites de los tipos de datos enteros en C. Dentro de esta página, 
encontrarás las macros que definen los valores máximo y mínimo de un `int`.

Valores a buscar:

INT_MAX: Es el valor máximo que puede tener un `int`.
INT_MIN: Es el valor mínimo que puede tener un `int`.

Ejemplo de cómo consultarlo:

1. Abre la terminal y escribe:

   man limits.h

2. Navega en la página usando las flechas del teclado o busca directamente los valores 
    usando la función de búsqueda de `man`. Para buscar dentro del `man`, presiona `/` 
    seguido del término que deseas buscar, como `INT_MAX`.

   /INT_MAX

   Luego presiona `Enter`.

Esto te llevará directamente a la sección donde se define `INT_MAX` y `INT_MIN`, y te 
mostrará los valores límite para un `int` en tu sistema.

Estos valores pueden variar dependiendo del sistema y la implementación del compilador, 
pero generalmente en sistemas de 32 bits:

- `INT_MAX` suele ser `2147483647`.
- `INT_MIN` suele ser `-2147483648`.
*/