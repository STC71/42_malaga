/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
/*
** ft_strlen - Calculate string length
**
** Purpose: Count characters until null terminator
** Why size_t: Standard type for sizes and counts
** How it works:
**   Start at 0, increment while character exists
**   Return final count (excludes null terminator)
** Example: "Hello" → 5
*/

int	ft_putchar_cnt(char c)
{
	return ((int)write(1, &c, 1));
}
/*
** ft_putchar_cnt - Print single character and count it
**
** Purpose: Output one character and return count for printf
** Why int return: Printf needs total character count
** How it works:
**   Write 1 byte to stdout using write(1, ...)
**   Return 1 (number of characters written)
** Used by all other print functions for counting
*/

int	ft_putstr_cnt(char *str, int max_len)
{
	int	i;

	i = 0;
	while (str[i] && i < max_len)
	{
		ft_putchar_cnt(str[i]);
		i++;
	}
	return (i);
}
/*
** ft_putstr_cnt - Print string up to max length
**
** Purpose: Output string respecting precision limit
** Why max_len parameter: Implements %.5s precision feature
** How it works:
**   Loop through string characters
**   Stop at null terminator OR max_len
**   Return number of characters actually printed
** Example: ("Hello", 3) → prints "Hel", returns 3
*/

void	ft_putpad(char c, int count)
{
	while (count-- > 0)
		ft_putchar_cnt(c);
}
/*
** ft_putpad - Print padding character multiple times
**
** Purpose: Add spaces or zeros for width formatting
** Why void: No need to count, caller already knows
** How it works:
**   Print character 'c' exactly 'count' times
**   Used for width padding with ' ' or '0'
** Example: (' ', 5) → prints "     " (5 spaces)
*/
