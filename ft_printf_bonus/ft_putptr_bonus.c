/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
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
** ft_putunbr_rec - Print number recursively for pointer
**
** Purpose: Output hex digits of memory address
** Why static: Helper only for pointer printing
** How it works:
**   Same recursive algorithm as other numeric conversions
** Example: 0x7fff → prints "7fff"
*/

static int	print_nil_ptr(t_format fmt)
{
	int	count;
	int	len;
	int	pad;

	count = 0;
	len = 5;
	pad = fmt.min_width - len;
	if (pad < 0)
		pad = 0;
	if (!fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	count += ft_putstr_cnt("(nil)", 5);
	if (fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	return (count);
}
/*
** print_nil_ptr - Handle NULL pointer special case
**
** Purpose: Print "(nil)" for null pointers
** Why static: Helper for ft_putptr only
** How it works:
**   Calculate padding for width (5 chars for "(nil)")
**   Right-align: spaces first
**   Print "(nil)"
**   Left-align: spaces after
** Example: %15p with NULL → "          (nil)"
*/

int	ft_putptr(void *ptr, t_format fmt)
{
	unsigned long long	addr;
	int					count;
	int					len;
	int					pad;

	if (!ptr)
		return (print_nil_ptr(fmt));
	count = 0;
	addr = (unsigned long long)ptr;
	len = ft_unumlen_base(addr, 16) + 2;
	pad = fmt.min_width - len;
	if (pad < 0)
		pad = 0;
	if (!fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	count += ft_putchar_cnt('0');
	count += ft_putchar_cnt('x');
	ft_putunbr_rec(addr, "0123456789abcdef", 16);
	count += ft_unumlen_base(addr, 16);
	if (fmt.left_align && pad > 0)
		count += (ft_putpad(' ', pad), pad);
	return (count);
}
/*
** ft_putptr - Print memory address with formatting
**
** Purpose: Handle %p conversion for pointers
** Why void pointer: Accept any pointer type
** How it works:
**   NULL → delegate to print_nil_ptr
**   Cast pointer to unsigned long long
**   Calculate length (hex digits + "0x")
**   Right-align: spaces first
**   Always print "0x" prefix
**   Print address in lowercase hex
**   Left-align: spaces after
** Example: %20p with 0x7fff → "            0x7fff"
*/
