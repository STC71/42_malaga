/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/12 00:00:00 by sternero         ###   ########.fr       */
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
** ft_putunbr_rec - Print unsigned number recursively
**
** Purpose: Output number in specified base
** Why static: Helper only for this file
** Why recursive: Print digits left to right
** How it works:
**   Same as signed version but no negatives
** Example: 255 in hex → prints "ff" or "FF"
*/

static int	print_prefix(char *base, t_format fmt, unsigned long long n)
{
	int	count;

	count = 0;
	if (fmt.alt_form && n != 0 && ft_strlen(base) == 16)
	{
		count += ft_putchar_cnt('0');
		if (base[10] == 'a')
			count += ft_putchar_cnt('x');
		else
			count += ft_putchar_cnt('X');
	}
	return (count);
}
/*
** print_prefix - Output # flag prefix for hex
**
** Purpose: Add "0x" or "0X" for hex when # flag used
** Why static: Helper for unsigned formatting
** How it works:
**   Check if # flag set and number not zero
**   If base 16, print "0x" (lowercase) or "0X" (uppercase)
**   Check base[10] to determine case ('a' vs 'A')
** Example: %#x with 255 → prints "0x", returns 2
*/

static int	get_total_len(unsigned long long n, t_format fmt, int base_len)
{
	int	num_digits;
	int	precision_len;
	int	prefix_len;

	num_digits = ft_unumlen_base(n, base_len);
	precision_len = num_digits;
	if (fmt.has_precision && fmt.precision > num_digits)
		precision_len = fmt.precision;
	prefix_len = 0;
	if (base_len == 16 && fmt.alt_form && n != 0)
		prefix_len = 2;
	return (precision_len + prefix_len);
}
/*
** get_total_len - Calculate total output length for unsigned
**
** Purpose: Determine space needed for width calculations
** Why static: Internal helper for padding
** How it works:
**   Count natural digits
**   Use precision if larger
**   Add 2 if # flag with hex (for "0x")
** Example: 255 with %#10.5x → 7 (2 for "0x" + 5 for precision)
*/

static int	apply_precision_padding(t_format fmt, int num_digits)
{
	int	count;

	count = 0;
	if (fmt.has_precision && fmt.precision > num_digits)
	{
		ft_putpad('0', fmt.precision - num_digits);
		count = fmt.precision - num_digits;
	}
	return (count);
}
/*
** apply_precision_padding - Add leading zeros for precision
**
** Purpose: Implement %.5u style formatting
** Why static: Helper for main function
** How it works:
**   If precision larger than digit count
**   Print zeros to reach precision
** Example: 42 with %.5u → adds 3 zeros before "42"
*/

int	ft_putunsigned(unsigned long long n, char *base, t_format fmt)
{
	int	count;
	int	base_len;
	int	total_len;
	int	pad;
	int	num_digits;

	count = 0;
	base_len = (int)ft_strlen(base);
	total_len = get_total_len(n, fmt, base_len);
	pad = fmt.min_width - total_len;
	if (pad < 0)
		pad = 0;
	num_digits = ft_unumlen_base(n, base_len);
	if (!fmt.left_align && !fmt.zero_pad && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	count += print_prefix(base, fmt, n);
	if (!fmt.left_align && fmt.zero_pad && pad > 0 && !fmt.has_precision)
		count += (ft_putpad('0', pad), pad);
	count += apply_precision_padding(fmt, num_digits);
	ft_putunbr_rec(n, base, base_len);
	count += num_digits;
	if (fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	return (count);
}
/*
** ft_putunsigned - Print unsigned number with formatting
**
** Purpose: Handle %u, %x, %X with all flags and modifiers
** Why separate from signed: No sign, has # flag for hex
** How it works:
**   1. Calculate total length including prefix
**   2. Right-align: print spaces first
**   3. Print prefix ("0x" if # flag with hex)
**   4. Zero-pad if flag set (without precision)
**   5. Apply precision zeros
**   6. Print number
**   7. Left-align: spaces at end
** Example: %#-10.5x with 255 → "0x000ff   " (prefix+zeros+spaces)
*/
