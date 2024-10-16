/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:55:05 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:55:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_sel_flag(va_list *arg, const char let);

int	ft_printf(char const *str, ...)
{
	int			num;
	int			wid;
	va_list		arg;

	num = 0;
	wid = 0;
	va_start(arg, str);
	while (str[num])
	{
		if (str[num] == '%')
		{
			wid += ft_sel_flag(&arg, str[num + 1]);
			num++;
		}
		else
			wid += (int) write(1, &str[num], 1);
		num++;
	}
	va_end(arg);
	return (wid);
}

static int	ft_sel_flag(va_list *arg, const char wrd)
{
	int	wid;

	wid = 0;
	if (wrd == 'c')
		wid += ft_write_chr(va_arg(*arg, int));
	else if (wrd == 's')
		wid += ft_write_str(va_arg(*arg, char *));
	else if (wrd == 'p')
		wid += ft_write_ptr(va_arg(*arg, unsigned long long));
	else if ((wrd == 'd') || (wrd == 'i'))
		wid += ft_write_nbr(va_arg(*arg, int));
	else if (wrd == 'u')
		wid += ft_write_dns(va_arg(*arg, unsigned int));
	else if (wrd == 'x')
		wid += ft_write_hxl(va_arg(*arg, unsigned int));
	else if (wrd == 'X')
		wid += ft_write_hxu(va_arg(*arg, unsigned int));
	else if (wrd == '%')
		wid += ft_write_chr(wrd);
	else
		wid += ft_write_chr(wrd);
	return (wid);
}
/*
int	main(void)
{
	ft_printf("Hello, World %i from 42!");
	return (0);
}
*/
// must print: Hello, World 42 from 42!
// must return: 26
/*The ft_printf function emulates the operation of the original printf 
function. 
The ft_sel_flag function selects the flag to be used based on the 
character passed as an argument.
The function takes a string as an argument and a variable number of
arguments. The function iterates over each character in the string and
checks if the character is a '%' character. ç
If it is, the function calls the ft_sel_flag function to select the flag 
to be used based on the next character in the string. If the character 
is not a '%', the function calls the ft_sel_flag function to select the flag 
to be used based on the current character in the string. 
The function returns the number of characters written to standard output.*/