/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:57:00 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:57:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_uns(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += ft_write_chr('0');
	else
	{
		if (n / 10 != 0)
			ft_write_uns(n / 10);
		ft_write_chr((n % 10) + '0');
		while (n > 0)
		{
			n /= 10;
			size++;
		}
	}
	return (size);
}

int	ft_write_nbr(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += ft_write_chr('0');
	if (n == -2147483648)
	{
		len += ft_write_str("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		len += ft_write_chr('-');
		n = -n;
	}
	if (n > 0)
		len += ft_write_uns((unsigned int)n);
	return (len);
}
/*
int	main(void)
{
	ft_write_nbr(-42);
	return (0);
}
*/
//must print : -42
//must return : 3
/*the ft_write_nbr function first checks if the input integer n is negative. 
If it is, the function writes a minus sign to the output and negates the 
integer. The function then recursively writes the most significant digits 
of the integer by dividing it by 10 and calling ft_write_nbr again. 
The least significant digit is then written using the modulo operator % and 
the character '0'.
The function returns the total number of characters written, which is the sum 
of the number of characters written for the most significant digits and the 
least significant digit.

The difference between %d and %i in C is minimal and only becomes apparent when 
used with scanf(). Both format specifiers are used to print a decimal number 
(base 10) and an integer in base 10. However, when used with scanf(), %i can 
detect the base of the input number (binary, octal, decimal, or hexadecimal), 
while %d always assumes the base to be 10.*/
