/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
** ft_isdigit - Check if character is a digit
**
** Purpose: Simple digit checker (0-9)
** Why int param: Follows standard isdigit convention
** How it works: Returns 1 if c is between '0' and '9', 0 otherwise
*/

int	ft_atoi_skip(const char *s, int *i)
{
	int	val;

	val = 0;
	while (ft_isdigit(s[*i]))
	{
		val = val * 10 + (s[*i] - '0');
		(*i)++;
	}
	return (val);
}
/*
** ft_atoi_skip - Convert string digits to int and advance position
**
** Purpose: Parse number from string while moving index forward
** Why pointer to i: Allows updating position in original string
** How it works:
**   1. Start with value 0
**   2. For each digit: multiply current value by 10 and add new digit
**   3. Advance position in string
**   4. Return final number
** Example: "123abc" at i=0 → returns 123, i becomes 3
*/

void	parse_flags(const char *s, int *i, t_format *fmt)
{
	while (s[*i] == '-' || s[*i] == '0' || s[*i] == '#'
		|| s[*i] == '+' || s[*i] == ' ')
	{
		if (s[*i] == '-')
			fmt->left_align = 1;
		else if (s[*i] == '0')
			fmt->zero_pad = 1;
		else if (s[*i] == '#')
			fmt->alt_form = 1;
		else if (s[*i] == '+')
			fmt->force_sign = 1;
		else if (s[*i] == ' ')
			fmt->space_sign = 1;
		(*i)++;
	}
}
/*
** parse_flags - Extract format flags from format string
**
** Purpose: Identify and set all flags (-, 0, #, +, space)
** Why void: Modifies fmt structure directly (no return needed)
** How it works:
**   Loop while current character is a flag:
**   - '-' → left alignment (add spaces on right)
**   - '0' → zero padding instead of spaces
**   - '#' → alternative form (0x for hex)
**   - '+' → always show sign (+ or -)
**   - ' ' → space before positive numbers
**   Advances position past all flags
** Example: "%-0+" → sets left_align=1, zero_pad=1, force_sign=1
*/

void	parse_width_precision(const char *s, int *i,
								t_format *fmt, va_list *ap)
{
	if (s[*i] == '*')
	{
		fmt->min_width = va_arg(*ap, int);
		if (fmt->min_width < 0)
		{
			fmt->left_align = 1;
			fmt->min_width = -fmt->min_width;
		}
		(*i)++;
	}
	else if (ft_isdigit(s[*i]))
		fmt->min_width = ft_atoi_skip(s, i);
	if (s[*i] == '.')
	{
		fmt->has_precision = 1;
		(*i)++;
		if (s[*i] == '*')
		{
			fmt->precision = va_arg(*ap, int);
			(*i)++;
		}
		else
			fmt->precision = ft_atoi_skip(s, i);
	}
}
/*
** parse_width_precision - Parse width and precision values
**
** Purpose: Extract minimum width and precision from format
** Why va_list: Needed for '*' (dynamic width/precision from arguments)
** How it works:
**   WIDTH:
**   - If '*': get width from next argument (negative → left align)
**   - If digit: parse number directly
**   PRECISION (after '.'):
**   - Mark that precision is specified
**   - If '*': get precision from next argument
**   - If digit: parse number directly
** Example: "%10.5d" → min_width=10, precision=5
** Example: "%*.*d" with args 10,5 → same result but dynamic
*/
