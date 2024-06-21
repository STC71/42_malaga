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

	while (*s)
	{
		res = res * 10 + *s - '0'; 
		s++;
	}
	return (res);	
}
int main (int argc, char *argv[])
{
	int i;
	int j;
	int sum;
	int prime;

	if (argc == 2)
	{
		i = 2;
		sum = 0;
		while (i <= ft_atoi(argv[1]))
		{
			j = 2;
			prime = 1;
			while (j <= i / 2)
			{
				if (i % j == 0)
				{
					prime = 0;
					break;
				}
				j++;
			}
			if (prime == 1)
				sum += i;
			i++;
		}
		write(1, "sum: ", 5);
		
	}
	else
		write(1, "0\n", 2);
	return (0);
}

/*
The program takes an integer as an argument and displays the sum of all prime 
numbers up to and including the integer. If the number of arguments is not 1, 
the program displays 0 followed by a newline. The program displays the result 
followed by a newline.

The program compiled with the following flags:
gcc -Wall -Wextra -Werror add_prime_sum.c -o add_prime_sum
*/