/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-04 10:37:52 by sternero          #+#    #+#             */
/*   Updated: 2024-08-04 10:37:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int    lcm(unsigned int a, unsigned int b)
{
    unsigned int n; // Variable to store the result of the operation

    if (a == 0 || b == 0) // If a or b is 0, the result is 0
        return (0);
    if (a > b)  // If a is greater than b, n is assigned the value of a
        n = a;
    else        // Otherwise, n is assigned the value of b
        n = b;
    while (1)   // Infinite loop
    {
        if (n % a == 0 && n % b == 0)   // If n is divisible by a and b
            return (n);                 // It returns n
        n++;                            // It increments n
    }
}

/*
The function lcm receives two unsigned integers, a and b.
If a or b is 0, the function returns 0.
If a is greater than b, the variable n is assigned the value of a, otherwise, 
n is assigned the value of b. This is because n must be the greater value 
between a and b.
The function uses an infinite loop to find the least common multiple of a and b.
If n is divisible by a and b, it returns n.
Otherwise, it increments n and continues the loop.
The function finishes when it finds the least common multiple of a and b.

La función lcm recibe dos enteros sin signo, a y b.
Si a o b es 0, la función devuelve 0.
Si a es mayor que b, a la variable n se le asigna el valor de a, de lo contrario,
n se le asigna el valor de b. Esto es porque n debe ser el valor mayor de a y b.
La función utiliza un bucle infinito para encontrar el mínimo común múltiplo de 
a y b. Si n es divisible por a y b, devuelve n. De lo contrario, incrementa n y
continúa el bucle. La función termina cuando encuentra el mínimo común múltiplo 
de ambos números.
*/

// The main function is used to test the lcm function. 
// It is not necessary for the evaluation.
// To compile the program:
//     gcc -Wall -Wextra -Werror lcm.c -o lcm

#include <stdio.h> // printf
#include <stdlib.h> // atoi

int main(int argc, char *argv[])
{
    unsigned int a; // First number
    unsigned int b; // Second number
    unsigned int res; // Result of the operation

    if (argc == 3) // If the number of arguments is 3
    {
        a = atoi(argv[1]); // It converts the first argument to an integer
        b = atoi(argv[2]); // It converts the second argument to an integer
        res = lcm(a, b); // It calculates the least common multiple of a and b
        printf("%d\n", res); // It prints the result to the standard output
    }
    return (0); // It returns 0 to the operating system
}