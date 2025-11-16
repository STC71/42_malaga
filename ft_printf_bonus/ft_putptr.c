/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_ptr(unsigned long n)
{
	const char	*base;
	int			count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthex_ptr(n / 16);
	count += write(1, &base[n % 16], 1);
	return (count);
}
/*
** ft_puthex_ptr - Print pointer address in hex
**
** Purpose: Convert memory address to hexadecimal
** Why static: Helper for ft_putptr only
** Why unsigned long: Pointer size on this system
** How it works:
**   Recursive hex printing (base 16)
**   Always lowercase for pointers
** Example: 0x7fff → prints "7fff"
*/

int	ft_putptr(void *ptr)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_puthex_ptr((unsigned long)ptr);
	return (count);
}
/*
** ft_putptr - Print pointer address (%p)
**
** Purpose: Handle %p conversion (simple version)
** Why void pointer: Accept any pointer type
** How it works:
**   NULL → print "(nil)"
**   Otherwise → print "0x" prefix
**   Cast to unsigned long and print in hex
** Example: ft_putptr(0x7fff) → prints "0x7fff"
*/
