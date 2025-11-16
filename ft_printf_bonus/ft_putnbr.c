/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_rec(long n)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_rec(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}
/*
** ft_putnbr_rec - Print signed integer recursively
**
** Purpose: Output decimal number with sign handling
** Why static: Helper for ft_putnbr only
** Why long: Handle INT_MIN safely
** How it works:
**   If negative, print '-' and make positive
**   If >= 10, recurse with n/10 first
**   Print current digit (n%10)
** Example: -123 → prints "-123"
*/

int	ft_putnbr(int n)
{
	return (ft_putnbr_rec((long)n));
}
/*
** ft_putnbr - Print signed integer (%d, %i)
**
** Purpose: Handle %d and %i conversions
** Why cast to long: Prevent overflow with INT_MIN
** How it works:
**   Cast to long for safe negation
**   Delegate to recursive helper
** Example: ft_putnbr(-2147483648) → prints INT_MIN
*/

int	ft_putnbr_unsigned(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}
/*
** ft_putnbr_unsigned - Print unsigned integer (%u)
**
** Purpose: Handle %u conversion (no sign)
** Why recursive: Print digits left to right
** How it works:
**   If >= 10, recurse with n/10 first
**   Print current digit (n%10)
**   No sign handling needed
** Example: 4294967295 → prints max unsigned int
*/

static int	ft_puthex_rec(unsigned long n, const char *base)
{
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_puthex_rec(n / 16, base);
	count += write(1, &base[n % 16], 1);
	return (count);
}
/*
** ft_puthex_rec - Print hexadecimal recursively
**
** Purpose: Output number in base 16
** Why static: Helper for ft_putnbr_hex only
** Why unsigned long: Handle large hex values
** How it works:
**   If >= 16, recurse with n/16
**   Print hex digit using base string
** Example: 255 → "ff" or "FF" depending on base
*/

int	ft_putnbr_hex(unsigned int n, int uppercase)
{
	if (uppercase)
		return (ft_puthex_rec(n, "0123456789ABCDEF"));
	else
		return (ft_puthex_rec(n, "0123456789abcdef"));
}
/*
** ft_putnbr_hex - Print hexadecimal (%x, %X)
**
** Purpose: Handle %x (lowercase) and %X (uppercase)
** Why two bases: Different case for same value
** How it works:
**   Choose base string based on uppercase flag
**   Delegate to recursive hex printer
** Example: ft_putnbr_hex(255, 0) → "ff"
** Example: ft_putnbr_hex(255, 1) → "FF"
*/
