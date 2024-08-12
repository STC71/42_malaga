/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-04 07:55:38 by sternero          #+#    #+#             */
/*   Updated: 2024-08-04 07:55:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc

int     *ft_range(int start, int end)
{
    int i = 0;  // Counter
    int len = abs((end - start) + 1);   // Length of the array
                                        // +1 is to include the last element
    int *res = (int *)malloc(sizeof(int) * len);
                // It uses malloc to allocate memory for the array of integers.
                // res is a pointer to the first element of the array
                // containing the range of integers, for example, if start is 1
                // and end is 3, the array will contain 1, 2, 3.

    if (res == NULL) // If malloc fails, it returns NULL
        return (NULL);
    while (i < len) // While the counter is less than the length of the array
    {
        if (start < end)
        {
            res[i] = start;
            start++;
            i++;
        }
        else    // If start is greater or equal to end
        {
            res[i] = start;
            start--;
            i++;
        }
    }
    return (res); // It returns the pointer to the first element of the array.
}

/*
The function ft_range receives two integers, start and end.
It calculates the length of the array of integers, len, by taking the absolute
value of the difference between end and start and adding 1.
It uses malloc to allocate memory for the array of integers.
The function doesn't make free because the function that calls it is responsible
for freeing the memory (see the main function).
It initializes a counter, i, to 0. to keep track of the position in the array.
It uses a while loop to fill the array with the range of integers.
If start is less than end, it fills the array with the range of integers from
start to end.
If start is greater or equal to end, it fills the array with the range of
integers from start to end.
It returns the pointer to the first element of the array.

To compile the program:
    gcc -Wall -Wextra -Werror ft_range.c -o ft_range

La función ft_range recibe dos enteros, start y end.
Calcula la longitud del array de enteros, len, tomando el valor absoluto de la
diferencia entre end y start y sumando 1.
Utiliza malloc para asignar memoria para el array de enteros.
La función no hace free porque la función que la llama es responsable de liberar
la memoria (ver la función main).
Inicializa un contador, i, a 0, para llevar la cuenta de la posición en el array.
Utiliza un bucle while para llenar el array con el rango de enteros.
Si start es menor que end, llena el array con el rango de enteros de start a end.
Si start es mayor o igual a end, llena el array con el rango de enteros de start
La función devuelve el puntero al primer elemento del array.

Para compilar el programa:
    gcc -Wall -Wextra -Werror ft_range.c -o ft_range

*/

/*
The main function is only for testing the ft_range function. It isn't part of
the function itself, and it's not necessary to the exercise.
*/

#include <stdio.h>      // to printf
#include <stdlib.h>     // to atoi

int main (int argc, char *argv[])
{
    int *res;
    int *original_res;
    int start;
    int end;

    if (argc == 3)
    {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        res = ft_range(start, end);
        original_res = res; 
        // Save the pointer to the first element of the array
        if (start <= end)
        {
            while (start <= end)
            {
                printf("%d\n", *res);
                res++;
                start++;
            }
        }
        else
        {
            while (start >= end)
            {
                printf("%d\n", *res);
                res++;
                start--;
            }
        }
        free(original_res);
        // Free the memory allocated by malloc in the ft_range function
    }
    return (0);
}

/*
if argv elements are 1 and 3, the output will be:
1
2
3
if argv elements are -1 and 2, the output will be:
-1
0
1
2
if argv elements are 0 and 0, the output will be:
0
if argv elements are 0 and -3, the output will be:
0
-1
-2
-3
*/
