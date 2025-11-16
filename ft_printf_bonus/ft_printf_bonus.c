/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static t_format	init_format(void)
{
	t_format	fmt;

	fmt.specifier = 0;
	fmt.left_align = 0;
	fmt.zero_pad = 0;
	fmt.alt_form = 0;
	fmt.force_sign = 0;
	fmt.space_sign = 0;
	fmt.min_width = 0;
	fmt.precision = 0;
	fmt.has_precision = 0;
	return (fmt);
}
/*
** init_format - Initialize format structure with default values
**
** Purpose: Creates a clean t_format struct with all flags set to 0
** Why static: Helper function only used within this file
** How it works:
**   1. Creates a t_format variable
**   2. Sets all fields to 0 (no flags, no width, no precision)
**   3. Returns the initialized structure
** This ensures every format starts with a clean slate
*/

int	ft_parse_format(const char *s, int *pos, t_format *fmt, va_list *ap)
{
	*fmt = init_format();
	(*pos)++;
	parse_flags(s, pos, fmt);
	parse_width_precision(s, pos, fmt, ap);
	fmt->specifier = s[*pos];
	if (fmt->specifier)
		(*pos)++;
	return (1);
}
/*
** ft_parse_format - Parse a format specifier from format string
**
** Purpose: Extracts and processes one complete format specifier (like %-10.5d)
** Why int return: Returns 1 for success (future: could handle errors)
** How it works:
**   1. Initialize format structure to defaults
**   2. Skip the '%' character by incrementing position
**   3. Parse flags (-, 0, #, +, space)
**   4. Parse width and precision (numbers or *)
**   5. Extract conversion specifier (d, s, x, etc.)
**   6. Move position past the specifier
** Example: "%-10.5d" → left_align=1, min_width=10, precision=5, specifier='d'
*/

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			count;
	int			i;
	t_format	fmt;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_parse_format(format, &i, &fmt, &ap);
			count += ft_dispatch(fmt, &ap);
		}
		else
			count += ft_putchar_cnt(format[i++]);
	}
	va_end(ap);
	return (count);
}
/*
** ft_printf - Custom implementation of printf with bonus flags
**
** Purpose: Main function that replicates printf behavior with flag support
** Why variadic (...): Accepts variable number of arguments like real printf
** How it works:
**   1. Check if format string is NULL (safety)
**   2. Initialize va_list to access variable arguments
**   3. Loop through format string character by character:
**      - If '%' found: parse format specifier and print accordingly
**      - Otherwise: print character as-is
**   4. Keep count of all characters printed
**   5. Clean up va_list and return total count
** Return: Number of characters printed (like real printf)
** Example: ft_printf("Number: %d", 42) → prints "Number: 42" and returns 10
*/