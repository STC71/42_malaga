/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-02 08:57:49 by sternero          #+#    #+#             */
/*   Updated: 2024-05-02 08:57:49 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_str(char *str)
{
	int	num;

	num = 0;
	if (!str)
		str = "(null)";
	while (str[num] != '\0')
	{
		write(1, &str[num], 1);
		num++;
	}
	return (num);
}

/*
int	main(void)
{
	ft_write_str("Hello, World... from 42!");
	return (0);
}
*/
// must print: Hello, World... from 42!
// must return: 26
/*The ft_write_str function first checks if the pointer to the string is null. 
If it is, it assigns the string "(null)" to the pointer and continues. 
The function then iterates over each character in the string and writes each 
character to standard output using the write function. Finally, the function 
returns the number of characters written, which is the length of the string.*/