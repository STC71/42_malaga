/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/13 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
** Why size_t: Standard type for sizes
** How it works:
**   Loop until null character found
**   Return count (excludes null)
** Example: "Hello" → 5
*/

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
/*
** ft_putchar - Print single character
**
** Purpose: Output one character to stdout
** Why int return: Return character count for printf
** How it works:
**   Write 1 byte directly with write()
**   Return 1 (bytes written)
** Example: ft_putchar('A') → prints "A", returns 1
*/

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}
/*
** ft_putstr - Print entire string
**
** Purpose: Output string to stdout with null handling
** Why int return: Return character count
** How it works:
**   NULL pointer → print "(null)"
**   Otherwise → write all characters at once
**   Return number of characters written
** Example: ft_putstr("Hello") → prints "Hello", returns 5
*/
