/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:57:30 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:57:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len_ptr(unsigned long long ptr);
static void	ft_srh_ptr(unsigned long long ptr);

int	ft_write_ptr(unsigned long long ptr)
{
	int	size;

	size = 0;
	size += ft_write_str("0x");
	if (ptr == 0)
		size += ft_write_chr('0');
	else
	{
		ft_srh_ptr(ptr);
		size += ft_len_ptr(ptr);
	}
	return (size);
}

static int	ft_len_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	while (ptr > 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

static void	ft_srh_ptr(unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_srh_ptr(ptr / 16);
		ft_srh_ptr(ptr % 16);
	}
	else
	{
		if (ptr < 10)
			ft_write_chr(ptr + '0');
		else
			ft_write_chr(ptr - 10 + 'a');
	}
}
/*
int main()
{
	ft_write_ptr((unsigned long long)42);
	return (0);
}
*/
//must print: 0x2a
//must return: 4
/*The ft_write_ptr function writes the pointer address in hexadecimal format
and returns the number of characters written.
The ft_len_ptr function calculates the length of the pointer address.
The ft_srh_ptr function searches for the pointer address in hexadecimal format.*/