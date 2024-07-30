/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_hxl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:56:20 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:56:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_hxl(unsigned int n)
{
	int		num;
	char	*hex;

	num = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		num += ft_write_hxl(n / 16);
	write(1, &hex[n % 16], 1);
	num++;
	return (num);
}

/*
int	main(void)
{
	ft_write_hxl(42);
	return (0);
}
*/
//must print: 2a
//must return: 2
/*the ft_write_hxl function uses recursion to convert the unsigned integer to 
a hexadecimal string. If the number is greater than or equal to 16, 
the function calls itself recursively to write the more significant 
hexadecimal digits.
After writing the more significant digits, the function writes the least 
significant digit using the hex string. The hex string contains the charac-
ters "0123456789abcdef", which represent the digits 0-15 in hexadecimal format.
Finally, the function increments the count variable and returns it. 
The num variable represents the number of characters written to the console.*/
