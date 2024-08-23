/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 11:24:01 by sternero          #+#    #+#             */
/*   Updated: 2024-08-21 11:24:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>     // atoi
#include <stdio.h>      // printf

int     pgcd(int a, int b)
{
    int i;          // Counter to iterate from 1 to the smallest number
    int pgcd;       // Variable to store the greatest common divisor

    i = 1;
    pgcd = 1;
    while (i <= a && i <= b)    // While i is less or equal to a and b
    {
        if (a % i == 0 && b % i == 0)   // If i is a divisor of a and b
            pgcd = i;           // It assigns i to pgcd
        i++;                    // It increments i
    }
    return (pgcd);  // It returns the greatest common divisor
}

int     main(int argc, char *argv[])
{
    int a;      // First number
    int b;      // Second number

    if (argc == 3)  // If the number of arguments is 3
    {
        a = atoi(argv[1]);  // It converts the first argument to an integer
        b = atoi(argv[2]);  // It converts the second argument to an integer
        printf("%d\n", pgcd(a, b)); // It prints the greatest common divisor
    }
    return (0); // It returns 0 to the operating system
}

/*
The function pgcd receives two integers, a and b.
It initializes a counter, i, to 1, and a variable, pgcd, to 1.
It uses a while loop to iterate from 1 to the smallest number between a and b.
If i is a divisor of a and b, it assigns i to pgcd.
It increments i.
It returns the greatest common divisor.

The main function receives two arguments.
It converts the arguments to integers.
It prints the greatest common divisor.
It returns 0 to the operating system.

The program compiled with the following command:
    gcc -Wall -Wextra -Werror pgcd.c -o pgcd
*/
// int main(int argc, char const *argv[])
// {
// 	int nbr1;
// 	int nbr2;

// 	if (argc == 3)
// 	{
// 		if ((nbr1 = atoi(argv[1])) > 0 && (nbr2 = atoi(argv[2])) > 0)
// 		{
// 			while (nbr1 != nbr2)
// 			{
// 				if (nbr1 > nbr2)
// 					nbr1 -= nbr2;
// 				else
// 					nbr2 -= nbr1;
// 			}
// 			printf("%d", nbr1);
// 		}
// 	}
// 	printf("\n");
// 	return (0);
// }