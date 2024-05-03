/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_hxu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:56:45 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:56:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_hxu(unsigned int n)
{
	int		num;
	char	*hex;

	num = 0;
	hex = "0123456789ABCDEF";
	if (n >= 16)
		num += ft_write_hxu(n / 16);
	write(1, &hex[n % 16], 1);
	num++;
	return (num);
}

/*
int	main(void)
{
	ft_write_hxu(42);
	return (0);
}
*/
// must print: 2A
// must return: 2
/* The ft_write_hxu function uses recursion to convert the unsigned integer to
a hexadecimal string. If the number is greater than or equal to 16,
the function calls itself recursively to write the more significant
hexadecimal digits.
After writing the more significant digits, the function writes the least
significant digit using the hex string. The hex string contains the charac-
ters "0123456789ABCDEF", which represent the digits 0-15 in hexadecimal format.
Finally, the function increments the count variable and returns it.
The num variable represents the number of characters written to the console.*/
