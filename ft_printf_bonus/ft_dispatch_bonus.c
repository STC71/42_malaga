/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/12 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	handle_char(t_format fmt, va_list *ap)
{
	char	c;
	int		count;
	int		pad;

	c = (char)va_arg(*ap, int);
	count = 0;
	pad = fmt.min_width - 1;
	if (pad < 0)
		pad = 0;
	if (!fmt.left_align && pad > 0)
	{
		ft_putpad(' ', pad);
		count += pad;
	}
	count += ft_putchar_cnt(c);
	if (fmt.left_align && pad > 0)
	{
		ft_putpad(' ', pad);
		count += pad;
	}
	return (count);
}
/*
** handle_char - Print character with width formatting
**
** Purpose: Handle %c conversion with width flags
** Why static: Helper function only used in this file
** How it works:
**   1. Extract char from arguments (promoted to int)
**   2. Calculate padding needed (width - 1 for the char)
**   3. If right-aligned: print spaces first, then char
**   4. If left-aligned: print char first, then spaces
** Example: "%-5c" with 'A' → "A    " (char + 4 spaces)
**          "%5c" with 'A' → "    A" (4 spaces + char)
*/

static int	apply_string_padding(int pad, int is_left)
{
	int	count;

	count = 0;
	if (pad > 0)
	{
		if (is_left)
			ft_putpad(' ', pad);
		else
			ft_putpad(' ', pad);
		count = pad;
	}
	return (count);
}
/*
** apply_string_padding - Helper to add padding spaces for strings
**
** Purpose: Add required spacing for string width formatting
** Why separate function: Keeps handle_string cleaner (norminette)
** How it works: Simply prints 'pad' number of spaces
** Note: is_left parameter exists for potential future use
*/

static int	handle_string(t_format fmt, va_list *ap)
{
	char	*str;
	int		count;
	int		len;
	int		pad;

	str = va_arg(*ap, char *);
	if (!str)
		str = "(null)";
	len = (int)ft_strlen(str);
	if (fmt.has_precision && fmt.precision < len)
		len = fmt.precision;
	pad = fmt.min_width - len;
	if (pad < 0)
		pad = 0;
	count = 0;
	if (!fmt.left_align)
		count += apply_string_padding(pad, 0);
	count += ft_putstr_cnt(str, len);
	if (fmt.left_align)
		count += apply_string_padding(pad, 1);
	return (count);
}
/*
** handle_string - Print string with width and precision
**
** Purpose: Handle %s conversion with flags
** Why static: Helper function only used in this file
** How it works:
**   1. Get string from arguments (handle NULL → "(null)")
**   2. Calculate effective length:
**      - Use full length if no precision
**      - Use min(strlen, precision) if precision specified
**   3. Calculate padding needed
**   4. If right-aligned: padding, then string
**   5. If left-aligned: string, then padding
** Example: "%-10.3s" with "Hello" → "Hel       " (3 chars + 7 spaces)
**          "%10s" with "Hi" → "        Hi" (8 spaces + 2 chars)
*/

static int	dispatch_numbers(t_format fmt, va_list *ap)
{
	if (fmt.specifier == 'd' || fmt.specifier == 'i')
		return (ft_putnbr_base(va_arg(*ap, int), "0123456789", fmt));
	if (fmt.specifier == 'u')
		return (ft_putunsigned(va_arg(*ap, unsigned int), "0123456789", fmt));
	if (fmt.specifier == 'x')
		return (ft_putunsigned(va_arg(*ap, unsigned int),
				"0123456789abcdef", fmt));
	if (fmt.specifier == 'X')
		return (ft_putunsigned(va_arg(*ap, unsigned int),
				"0123456789ABCDEF", fmt));
	return (0);
}
/*
** dispatch_numbers - Route numeric conversions to appropriate handlers
**
** Purpose: Delegate numeric types to specialized functions
** Why static: Helper function only used in this file
** How it works:
**   Check specifier and call corresponding function:
**   - 'd' or 'i' → signed decimal (ft_putnbr_base)
**   - 'u' → unsigned decimal
**   - 'x' → lowercase hexadecimal
**   - 'X' → uppercase hexadecimal
**   Each passes base string and format for flag handling
*/

int	ft_dispatch(t_format fmt, va_list *ap)
{
	if (fmt.specifier == 'c')
		return (handle_char(fmt, ap));
	if (fmt.specifier == 's')
		return (handle_string(fmt, ap));
	if (fmt.specifier == 'p')
		return (ft_putptr(va_arg(*ap, void *), fmt));
	if (fmt.specifier == '%')
		return (ft_putchar_cnt('%'));
	return (dispatch_numbers(fmt, ap));
}
/*
** ft_dispatch - Main dispatcher for all conversion types
**
** Purpose: Route each conversion specifier to its handler
** Why separate function: Clean separation of parsing and printing
** How it works:
**   Check specifier character and route to appropriate function:
**   - 'c' → handle_char (character)
**   - 's' → handle_string (string)
**   - 'p' → ft_putptr (pointer address)
**   - '%' → print literal '%'
**   - others → dispatch_numbers (d, i, u, x, X)
** This is the bridge between parsing and actual output
*/
