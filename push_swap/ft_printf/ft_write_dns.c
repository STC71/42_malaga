/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_dns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:56:03 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:56:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_dns(unsigned int n)
{
	int	num;

	num = 0;
	if (n >= 10)
		num += ft_write_dns(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	num++;
	return (num);
}

/*
int main()
{
	ft_write_dns(-01.5);
	return 0;
}
*/
//must print: 1
//must return: 1
/*The ft_write_dns function uses a recursive strategy to convert the unsigned 
integer to a character string. If the number is greater than or equal to 10, 
the function is called recursively to write the most significant digits. 
After writing the most significant digits, the function writes the least 
significant digit using character array notation. Finally, the function 
returns the number of digits written, which is 1 more than the number of 
digits written recursively.*/
