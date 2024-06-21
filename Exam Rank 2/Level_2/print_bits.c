/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 18:47:44 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 18:47:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void print_bits(unsigned char octet) 
{
    unsigned char mask = 0x80; // 10000000 in binary

    while (mask > 0) 
    {
        if (octet & mask) 
            printf("1");
        else
            printf("0");
        mask >>= 1; // shift right by 1 bit
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <byte>\n", argv[0]);
        return 1;
    }

    unsigned char octet = (unsigned char)atoi(argv[1]);
    print_bits(octet);

    return 0;
}

/*
The function print_bits takes an unsigned char as a parameter 
and prints its binary representation.

The main function takes a byte as a command-line argument,
converts it to an unsigned char, and calls print_bits.

The program compiled with the following command:
gcc -Wall -Wextra -Werror print_bits.c -o print_bits
*/

/*
La función print_bits toma un parámetro llamado octet, que es un byte 
(un conjunto de 8 bits). El objetivo de la función es imprimir el valor 
de ese byte en binario, es decir, en una secuencia de 0s y 1s.

Vamos a utilizar un ejemplo para ilustrar cómo funciona la función. 
Supongamos que llamamos a la función con el valor 2 como parámetro, 
es decir, print_bits(2).

Paso 1: Inicialización de la variable mask

La función comienza inicializando una variable llamada mask con el valor 0x80. 
¿Qué significa esto? En informática, los números pueden representarse de 
diferentes maneras. En este caso, 0x80 es una representación hexadecimal del número. 
En binario, 0x80 se escribe como 10000000. 
Es importante destacar que esta variable mask se utilizará para "extraer" los bits 
del byte octet.

Paso 2: Bucle while

La función entra en un bucle while que se repetirá mientras la variable mask sea 
mayor que 0. En otras palabras, el bucle se repetirá 8 veces, una vez por cada bit 
del byte octet.

Paso 3: Primera iteración del bucle

En la primera iteración del bucle, la variable mask tiene el valor 10000000. 
La función utiliza el operador & (AND lógico) para comparar el byte octet con la 
variable mask. En nuestro ejemplo, octet es 2, que en binario se escribe como 00000010.

La operación octet & mask se realiza de la siguiente manera:

  00000010 (octet)
& 10000000 (mask)
  ----
  00000000

Como el resultado es 0, la función imprime un 0 en la consola.

Paso 4: Desplazamiento de la variable mask

Después de imprimir el resultado, la función desplaza la variable mask una posición a la 
derecha utilizando el operador >>=. Esto significa que la variable mask se divide entre 2. 
En binario, 10000000 se convierte en 01000000.

Paso 5: Segunda iteración del bucle

En la segunda iteración del bucle, la variable mask tiene el valor 01000000. La función 
vuelve a utilizar el operador & para comparar el byte octet con la variable mask.

La operación octet & mask se realiza de la siguiente manera:

  00000010 (octet)
& 01000000 (mask)
  ----
  00000000

Como el resultado es 0, la función imprime un 0 en la consola.

Paso 6: Continuación del bucle

La función continúa iterando 6 veces más, desplazando la variable mask una posición a 
la derecha en cada iteración y comparando el byte octet con la variable mask. En cada 
iteración, imprime un 0 o un 1 en la consola dependiendo del resultado de la comparación.

Paso 7: Fin del bucle

Después de 8 iteraciones, la variable mask se vuelve 0 y el bucle termina. 
La función ha impreso la secuencia de bits del byte octet en la consola.

En nuestro ejemplo, la función habría impreso la secuencia 00000010, que es el valor 
binario del byte 2.

En resumen, la función print_bits utiliza una variable mask para "extraer" los bits del 
byte octet y imprimirlos en la consola en forma de secuencia de 0s y 1s.
*/