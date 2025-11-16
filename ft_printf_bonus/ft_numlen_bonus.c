/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_numlen_base(long long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
/*
** ft_numlen_base - Calculate digit count for signed number
**
** Purpose: Determine how many characters number needs
** Why long long: Handle full range of signed integers
** How it works:
**   Zero always needs 1 digit
**   If negative, add 1 for minus sign
**   Divide by base until zero, count divisions
** Example: -123 in base 10 → 4 (includes minus sign)
** Example: 255 in base 16 → 2 (FF in hex)
*/

int	ft_unumlen_base(unsigned long long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
/*
** ft_unumlen_base - Calculate digit count for unsigned number
**
** Purpose: Determine character count for positive numbers
** Why unsigned long long: Handle %u, %x, %X, pointers
** How it works:
**   Zero always needs 1 digit
**   Divide by base repeatedly, count divisions
**   No sign handling (always positive)
** Example: 255 in base 10 → 3 digits
** Example: 255 in base 16 → 2 digits (FF)
*/
