/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_putunbr_rec(unsigned long long n, char *base, int base_len)
{
	if (n >= (unsigned long long)base_len)
		ft_putunbr_rec(n / base_len, base, base_len);
	ft_putchar_cnt(base[n % base_len]);
}
/*
** ft_putunbr_rec - Print number in any base recursively
**
** Purpose: Convert and output number digit by digit
** Why static: Helper only for this file
** Why recursive: Print digits in correct order (left to right)
** How it works:
**   If number >= base, recurse with n/base first
**   Then print current digit using n%base as index
** Example: 123 in base 10 → prints "1", "2", "3"
*/

static int	get_num_len(long long n, t_format fmt, int base_len)
{
	int	len;
	int	num_digits;

	if (fmt.has_precision && fmt.precision == 0 && n == 0)
		return (0);
	if (n < 0)
		n = -n;
	num_digits = ft_numlen_base(n, base_len);
	if (fmt.has_precision && fmt.precision > num_digits)
		len = fmt.precision;
	else
		len = num_digits;
	return (len);
}
/*
** get_num_len - Calculate total length of number output
**
** Purpose: Determine space needed for precision padding
** Why static: Internal helper for width calculations
** How it works:
**   Special case: %.0d with zero prints nothing
**   Count natural digits in the number
**   Use precision if larger than natural digit count
** Example: 42 with %.5d → returns 5 (will print 00042)
*/

static int	print_sign_prefix(long long n, t_format fmt)
{
	int	count;

	count = 0;
	if (n < 0)
		count += ft_putchar_cnt('-');
	else if (fmt.force_sign)
		count += ft_putchar_cnt('+');
	else if (fmt.space_sign)
		count += ft_putchar_cnt(' ');
	return (count);
}
/*
** print_sign_prefix - Output sign character if needed
**
** Purpose: Handle +, -, and space flags for numbers
** Why static: Helper for ft_putnbr_base only
** How it works:
**   Negative → always print '-'
**   Positive with + flag → print '+'
**   Positive with space flag → print ' '
** Example: 42 with %+d → prints '+', returns 1
*/

static int	print_number_body(long long n, char *base,
								t_format fmt, int base_len)
{
	int					count;
	int					num_digits;
	unsigned long long	un;

	count = 0;
	if (n < 0)
		un = (unsigned long long)(-n);
	else
		un = (unsigned long long)n;
	num_digits = ft_unumlen_base(un, base_len);
	if (fmt.has_precision && fmt.precision == 0 && n == 0)
		return (0);
	if (fmt.has_precision && fmt.precision > num_digits)
	{
		ft_putpad('0', fmt.precision - num_digits);
		count += fmt.precision - num_digits;
	}
	ft_putunbr_rec(un, base, base_len);
	count += num_digits;
	return (count);
}
/*
** print_number_body - Output number with precision zeros
**
** Purpose: Print the actual digits with leading zeros
** Why static: Helper for main printing function
** How it works:
**   Convert to unsigned (handles negative separately)
**   If %.0d and zero, print nothing
**   Add precision zeros if needed
**   Print actual number recursively
** Example: 42 with %.5d → prints "00042"
*/

int	ft_putnbr_base(long long n, char *base, t_format fmt)
{
	int	count;
	int	base_len;
	int	total_len;
	int	pad;

	count = 0;
	base_len = (int)ft_strlen(base);
	total_len = get_num_len(n, fmt, base_len);
	if (n < 0 || fmt.force_sign || fmt.space_sign)
		total_len++;
	pad = fmt.min_width - total_len;
	if (pad < 0)
		pad = 0;
	if (!fmt.left_align && (!fmt.zero_pad || fmt.has_precision) && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	count += print_sign_prefix(n, fmt);
	if (!fmt.left_align && fmt.zero_pad && !fmt.has_precision && pad > 0)
		count += (ft_putpad('0', pad), pad);
	count += print_number_body(n, base, fmt, base_len);
	if (fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	return (count);
}
/*
** ft_putnbr_base - Print signed number with all formatting
**
** Purpose: Complete number output with flags, width, precision
** Why any base: Handles both decimal (d,i) conversions
** How it works:
**   1. Calculate total length including sign
**   2. If right-align, print space padding first
**   3. Print sign (-, +, or space)
**   4. If zero-pad and no precision, add zeros
**   5. Print number body with precision
**   6. If left-align, add spaces at end
** Example: %-+10.5d with 42 → "+00042    " (sign+zeros+spaces)
*/
