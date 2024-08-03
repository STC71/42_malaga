/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-03 09:34:43 by sternero          #+#    #+#             */
/*   Updated: 2024-08-03 09:34:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	// If c = 'A'; c + 32 = 'A' + 32 = 'a'
	return (c);
}

int	get_digit(char c, int str_base)
{
	int	max;

	if (str_base <= 10)
		max = str_base - 1 + '0';
		// If str_base = 10; max = 10 - 1 + '0' = 9 + '0' = '9'
		// convert int to char in base 10	
	else
		max = str_base - 10 -1 + 'a';
		// If str_base = 16; max = 16 - 10 - 1 + 'a' = 5 + 'a' = 'f'
		// convert int to char in base 16
	if (c >= '0' && c <= '9' && c <= max)
		return (c - '0');
		// If c = '9'; c - '0' = '9' - '0' = 9
		// convert char to int in base 10
	else if (c >= '0' && c <= '9' && c <= max)
		return (10 + c - 'a');
		// If c = '9' and max = '9'; 
		// 10 + c - 'a' = 10 + '9' - 'a' = 10 + 9 - 10 = 9
	else
		return (-1);
		// If c = 'A'; return -1
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;
	int	digit;

	res = 0;
	sign = 1;
	if (str == NULL || str_base < 2 || str_base > 16)
	// str is a pointer to the first character of the string.
	// don't use * because here we are checking the address 
	// of the first character. For example, if str = "123",
	// str = 0x7ffeefbff6c0 (address of the first character).
	// str will be NULL if the string is empty.
		return (0);
	if (*str == '-')
	// *str is a pointer to the first character of the string.
	// we using * to get the value of the first character.
	// if *str = '-123', *str = '-'
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		digit = get_digit(to_lower(*str), str_base);
		// to_lower(*str) = to_lower('A') = 'a'
		// get_digit('a', 16) = 10
		if (digit == -1)
			return (0);
		res = (res * str_base) + digit;
		str++;
	}
	return (res * sign);
	// if str = "123", res = 123
	// if str = "-123", res = -123
}

// The subjet doesn't want a program. So I will create a main function to test
// the ft_atoi_base function only, and with the put_nbr function to print
// the result. But REMENBER: from here the code are not part of the subject.

void put_nbr(int n) // n = 123
{
	char c;

	if (n >= 10)
		put_nbr(n / 10);
		// if n = 123; put_nbr(123 / 10) = put_nbr(12)
	c = n % 10 + '0';
	// if n = 123; n % 10 = 3 + '0' = 51 (ASCII) = '3'; c = '3'
	write(1, &c, 1);
}

int	main(int argc, char *argv[])
{
	int	nbr;
	int	base;

	if (argc == 3)
	{
		nbr = ft_atoi_base(argv[1], 10);
		base = ft_atoi_base(argv[2], 10);
		if (nbr != 0 && base != 0)
		{
			write(1, "nbr: ", 5);
			put_nbr(nbr);
			// If argv = "-123" and base = 10, put_nbr(nbr) = -123
			write(1, "\n", 1);
			write(1, "base: ", 6);
			put_nbr(base);
			// If argv = "-123" and base = 16, put_nbr(base) = 16
			write(1, "\n", 1);
			write(1, "result: ", 8);
			put_nbr(ft_atoi_base(argv[1], ft_atoi_base(argv[2], 10)));
			// If argv = "-123" and base = 16, 
			// put_nbr(ft_atoi_base(argv[1], ft_atoi_base(argv[2], 10)))
			// = -291
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}

/*
char to lower funtion is used to convert uppercase letters to lowercase letters.
int get_digit function is used to convert a character to an integer. The function
	receives a character and a base. The function returns the integer value of 
	the character in the base. If the character is not a digit in the base, the 
	function returns -1.
int ft_atoi_base function is used to convert a string to an integer. The function
	receives a string and a base. The function returns the integer value of the 
	string in the base. If the string is NULL, the base is less than 2, or the base
	is greater than 16, the function returns 0. If the string starts with a minus
	sign, the function multiplies the result by -1. The function then converts each
	character of the string to an integer using the get_digit function. The function
	multiplies the result by the base and adds the integer value of the character.
	The function returns the result multiplied by the sign.

The program receives two arguments: a number and a base. It  converts the number 
to an integer and the base to an integer. The program then converts the number to 
the base and prints the result. If the number of arguments is not 2, the program 
prints a newline.

For example, if the program is called with the arguments "-123" and "16", the
program will print:
	nbr: -123
	base: 16
	result: -291

But if the program is called with the arguments "-123" and "10", the program
It will print:
	nbr: -123
	base: 10
	result: -123

The program compiles with the following command:
	gcc -Wall -Wextra -Werror ft_atoi_base.c -o ft_atoi_base

char to_lower se utiliza para convertir letras mayúsculas en letras minúsculas.

int get_digit se utiliza para convertir un carácter en un entero. La función 
	recibe un carácter y una base. La función devuelve el valor entero del
	carácter en la base. Si el carácter no es un dígito en la base, la función
	devuelve -1.

int ft_atoi_base se utiliza para convertir una cadena en un entero. La función
	recibe una cadena y una base. La función devuelve el valor entero de la
	cadena en la base. Si la cadena es NULL, la base es menor que 2 o la base
	es mayor que 16, la función devuelve 0. Si la cadena comienza con un signo
	menos, la función multiplica el resultado por -1. Luego, la función convierte
	cada carácter de la cadena en un entero utilizando la función get_digit. La
	función multiplica el resultado por la base y agrega el valor entero del
	carácter. La función devuelve el resultado multiplicado por el signo. 

El programa recibe dos argumentos: un número y una base. El programa convierte
el número a un entero y la base a un entero. Luego, el programa convierte el
número a la base e imprime el resultado. Si el número de argumentos no es 2,
el programa imprime un salto de línea.
Por ejemplo, si se llama al programa con los argumentos "-123" y "16", el
programa imprimirá:
	nbr: -123
	base: 16
	result: -291
Pero si se llama al programa con los argumentos "-123" y "10", el programa
imprimirá:
	nbr: -123
	base: 10
	result: -123

El programa se compila con el siguiente comando:
	gcc -Wall -Wextra -Werror ft_atoi_base.c -o ft_atoi_base
*/