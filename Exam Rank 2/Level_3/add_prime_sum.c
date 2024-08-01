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
		res = res * 10 + *s++ - 48; 
	return (res);	
}

int	is_prime(int n)
{
	int i;

	i = 2;
	if (n <= 1)
		return (0);
	while (i * i <= n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void	put_nbr(int n)
{
	char c;

	if (n >= 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int main (int argc, char *argv[])
{
	if (argc == 2)
	{
		int n;
		int sum;

		n = ft_atoi(argv[1]);
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
*/