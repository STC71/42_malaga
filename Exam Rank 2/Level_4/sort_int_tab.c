/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-26 15:34:08 by sternero          #+#    #+#             */
/*   Updated: 2024-08-26 15:34:08 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>                      // for printf
#include <stdlib.h>                     // for atoi

// The includes are only necessary for the main function to test the function.
// They are not necessary for the exercise.

void	sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i = 0;
    int tmp;

    while (i < (size - 1))              // to 5 3 1 4 2 => size = 5
    {                       
        if (tab[i] > tab[i + 1])
        {
            tmp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = tmp;
            i = 0;                      // start again from the beginning
        }
        else
            i++;
    }
}

// The main function is used to test the sort_int_tab function.
// It is not necessary for the exercise.

int main (int argc, char *argv[])
{
    int tab[argc - 1];
    int i = 0;

    if (argc == 1)
        return 0;
    while (++i < argc)
        tab[i - 1] = atoi(argv[i]);
    sort_int_tab(tab, argc - 1);
    i = -1;
    while (++i < argc - 1)
        printf("%d\n", tab[i]);
    return 0;
}

// To compile and run the program, you can use the following commands:
// gcc -Wall -Werror -Wextra sort_int_tab.c -o sort_int_tab; ./sort_int_tab 5 3 1 4 2

/*
The sort_int_tab function sorts an array of integers in ascending order.
The function takes two arguments: a pointer to the first element of the array
(tab) and an unsigned integer representing the size of the array (size).

The function iterates through the array comparing each element with the next
element. If the current element is greater than the next element, the two
elements are swapped. The function continues to iterate through the array
until no more swaps are needed.

Example:
./sort_int_tab 5 3 1 4 2
first swap: 5 3 => 3 5 1 4 2
second swap: 5 1 => 3 1 5 4 2
third swap: 3 1 => 1 3 5 4 2
fourth swap: 5 4 => 1 3 4 5 2
fifth swap: 5 2 => 1 3 4 2 5
sixth swap: 4 2 => 1 3 2 4 5
seventh swap: 3 2 => 1 2 3 4 5
*/

/*
La función sort_int_tab ordena un array de enteros en orden ascendente.
La función toma dos argumentos: un puntero al primer elemento del array (tab)
y un entero sin signo que representa el tamaño del array (size).

La función itera a través del array comparando cada elemento con el siguiente
elemento. Si el elemento actual es mayor que el siguiente elemento, los dos
elementos se intercambian. La función continúa iterando a través del array
hasta que no se necesiten más intercambios.

Ejemplo:
./sort_int_tab 5 3 1 4 2
primer intercambio: 5 3 => 3 5 1 4 2
segundo intercambio: 5 1 => 3 1 5 4 2
tercer intercambio: 3 1 => 1 3 5 4 2
cuarto intercambio: 5 4 => 1 3 4 5 2
quinto intercambio: 5 2 => 1 3 4 2 5
sexto intercambio: 4 2 => 1 3 2 4 5
séptimo intercambio: 3 2 => 1 2 3 4 5
*/