/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 14:17:10 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 14:17:10 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *s)
{
	int res;

	res = 0;
	while (*s)
		res = (res * 10) + (*s++ - '0'); 
	return (res);	
}

/*
Si se llama a la función con la cadena "123", el ciclo while se ejecutará 
tres veces:
	res = (0 * 10) + ('1' - '0') = 0 + 1 = 1
	res = (1 * 10) + ('2' - '0') = 10 + 2 = 12
	res = (12 * 10) + ('3' - '0') = 120 + 3 = 123
La función devuelve 123, que es el entero correspondiente a la cadena "123".
*/

int	is_prime(int n) //n = 25
{
	int i;

	i = 2;
	if (n <= 1)
		return (0);
	while (i * i <= n) // 2 * 2 = 4 <= 25; i = 2
	{
		if (n % i == 0) // i = 2; n % i = 25 % 2 = 1
						// i = 3; n % i = 25 % 3 = 1
						// i = 4; n % i = 25 % 4 = 1
						// i = 5; n % i = 25 % 5 = 0
			return (0);
		i++;
	}
	return (1);
}

/*
Si se llama a la función con el valor 25, el ciclo while se ejecutará hasta 
que i sea 5. En ese momento, se verifica que 25 % 5 == 0, lo que devuelve 0, 
ya que 25 es divisible por 5. La función devuelve 0, lo que significa que 25
no es un número primo.
*/

void	put_nbr(int n) // n = 123
{
	char c;

	if (n >= 10)
		put_nbr(n / 10); 	// n = 12 n = 1; n = 0
	c = n % 10 + '0'; 		// n % 10 = 3 + '0' = 51 (ASCII) = '3'; c = '3'
							// n % 10 = 2 + '0' = 50 (ASCII) = '2'; c = '2'
							// n % 10 = 1 + '0' = 49 (ASCII) = '1'; c = '1'
	write(1, &c, 1);		// write(1, "3", 1)
							// write(1, "2", 1)
							// write(1, "1", 1)
}

int main (int argc, char *argv[]) // ./a.out 123
{
	if (argc == 2)
	{
		int n;
		int sum;

		n = ft_atoi(argv[1]); 	// n = 123
		sum = 0;
		while (n > 0)
		{
			if (is_prime(n))
				sum += n;
			n--;
		}
		put_nbr(sum);
	}
	if (argc != 2)
		put_nbr(0);
	write(1, "\n", 1);
	return (0);
}

/*
The program takes an integer as an argument and displays the sum of all prime 
numbers up to and including the integer. If the number of arguments is not 1, 
the program displays 0 followed by a newline. The program displays the result 
followed by a newline.

The program compiled with the following flags:
gcc -Wall -Wextra -Werror add_prime_sum.c -o add_prime_sum

El programa toma un número entero como argumento y muestra la suma de todos los
números primos hasta e incluyendo el número entero. Si el número de argumentos
no es 1, el programa muestra 0 seguido de un salto de línea. El programa muestra
el resultado seguido de un salto de línea.

Descripción General:
1. La función main recibe un número entero como argumento y lo convierte a un
   entero con la función ft_atoi.
2. La función ft_atoi convierte la cadena de caracteres a un entero.
3. La función is_prime verifica si un número es primo.
4. La función put_nbr imprime un número entero.
5. Si el número de argumentos es 2, el programa calcula la suma de los números
   primos hasta el número entero.
6. Si el número de argumentos no es 2, el programa imprime 0.
7. El programa imprime un salto de línea al final.
*/