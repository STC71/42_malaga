/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 18:28:16 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 18:28:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		max(int* tab, unsigned int len)
{
    int result;
	unsigned int i = 0;
	
	if (len == 0)
		return (0);
	result = tab[i];
	while(i < len)
	{
		if (result <  tab[i])
			result = tab[i];
		i++;
	}
	return result;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *arr;
    int len;
    int i;

    // Verificar que se haya proporcionado un argumento
    if (argc < 2) 
    {
        printf("Uso: %s <numero1> <numero2>...\n", argv[0]);
        return 1;
    }

    // Convertir los argumentos a enteros y almacenarlos en un arreglo
    len = argc - 1;
    arr = (int *)malloc(len * sizeof(int));
    for (i = 0; i < len; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Encontrar el máximo valor en el arreglo
    int max_val = max(arr, len);

    // Imprimir el resultado
    printf("El máximo valor es: %d\n", max_val);

    free(arr);
    return 0;
}

/*
The function max takes an array of integers and its length as parameters
and returns the maximum value in the array.

The main function takes a list of integers as command-line arguments,
converts them to an array of integers, and calls max to find the maximum value.

The program compiled with the following command:
gcc -Wall -Wextra -Werror max.c -o max
*/
