/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_conversion(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 1));
	else if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}
/*
** ft_handle_conversion - Route conversion specifier to handler
**
** Purpose: Simple dispatcher without flags or modifiers
** Why static: Helper only for mandatory ft_printf
** How it works:
**   Check specifier character
**   Extract argument with va_arg
**   Call appropriate print function
**   Return character count from handler
** This is the simplified version without bonus features
*/

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_handle_conversion(format[i + 1], args);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
** ft_printf - Basic printf implementation (mandatory part)
**
** Purpose: Simplified printf without flags or width
** Why variadic: Accept variable number of arguments like printf
** How it works:
**   Validate format string
**   Initialize argument list with va_start
**   Loop through format string:
**     If '%' → process next char as specifier
**     Otherwise → print character as-is
**   Clean up with va_end
**   Return total character count
** Example: ft_printf("Hello %s", "World") → prints "Hello World"
*/
