/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-04 09:17:05 by sternero          #+#    #+#             */
/*   Updated: 2024-08-04 09:17:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc

int     *ft_rrange(int start, int end)
{
    int *range;     // Pointer to the first element of the array
    int i = 0;      // Counter to keep track of the position in the array
    int step = 1;   // Step to increment or decrement the value of start
    int n = end - start;    // Difference between end and start

    if (n < 0)  // If n is negative, it means that end is less than start
        (n *= -1);  // It makes n positive, to know the length of the array
    n++;            // It adds 1 to include the last element

    range = (int *)malloc(sizeof(int) * n); 
    // It allocates memory for the array
    if (range)      // If malloc is successful
    {
        if (start < end)    // If start is less than end
            step = -1;      // It changes the step to -1
        while (i < n)       // While the counter is less than n
        {
            range[i] = end; 
            // It assigns the value of end to the current position
            end += step;    // It increments or decrements the value of end
            i++;            // It increments the counter
        }
    }
    return (range); // It returns the pointer to the first element of the array
}

/*
The function ft_rrange receives two integers, start and end.
It calculates the difference between end and start and assigns it to n.
If n is negative, it makes it positive.
It adds 1 to n to include the last element.
It uses malloc to allocate memory for the array of integers.
It initializes a counter, i, to 0, to keep track of the position in the array.
It initializes a step to 1, to increment or decrement the value of start.
If start is less than end, it changes the step to -1.
It uses a while loop to fill the array with the range of integers.
It assigns the value of end to the current position in the array.
It increments or decrements the value of end depending on the step.
It increments the counter.
It returns the pointer to the first element of the array.

La función ft_rrange recibe dos enteros, start y end.
Calcula la diferencia entre end y start y la asigna a n.
Si n es negativa, la convierte en positiva.
Añade 1 a n para incluir el último elemento.
Utiliza malloc para asignar memoria para el array de enteros.
Inicializa un contador, i, a 0, para llevar la cuenta de la posición en el array.
Inicializa un paso a 1, para incrementar o decrementar el valor de start.
Si start es menor que end, cambia el paso a -1.
Utiliza un bucle while para llenar el array con el rango de enteros.
Asigna el valor de end a la posición actual en el array.
Incrementa o decrementa el valor de end dependiendo del paso.
Incrementa el contador.
Devuelve el puntero al primer elemento del array.
*/

// The next main function is only for testing the ft_rrange function. It isn't 
// part of the exercise.

#include <stdio.h> // printf

int main (int argc, char *argv[])
{
    int start;  // Start of the range
    int end;    // End of the range
    int *range; // Pointer to the first element of the array
    int i;      // Counter to keep track of the position in the array

    if (argc == 3)  // If the number of arguments is 3
    {
        start = atoi(argv[1]);  // It converts the first argument to an integer
        end = atoi(argv[2]);    // It converts the second argument to an integer
        range = ft_rrange(start, end);  // It calls the function ft_rrange
        if (range)  // If the pointer is not NULL
        {
            i = 0;  // It initializes the counter to 0
            while (i < end - start + 1) // While the counter is less than the length
            {
                printf("%d ", range[i]);    // It prints the current element
                i++;    // It increments the counter
            }
            free(range);    // It frees the memory allocated by malloc
        }
    }
    printf("\n");   // It prints a new line
    return (0);     // It returns 0 to indicate that the program ended successfully
}

// To compile the program:
// gcc -Wall -Wextra -Werror ft_rrange.c -o ft_rrange
