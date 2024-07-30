/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 07:43:12 by sternero          #+#    #+#             */
/*   Updated: 2024/04/18 19:43:17 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_length(int n);
static void	fill_string(char *str, int n, int len);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_number_length(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_string(str, n, len);
	return (str);
}

static int	get_number_length(int n)
{
	int	len;

	len = (0);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	fill_string(char *str, int n, int len)
{
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[--len] = '0';
	while (n != 0)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
}
/*Using malloc(3), generate a string that
	represent the integer value received as an argument.
	Negative numbers have to be managed. n: the integer to convert.
	Return value: the string representing the number 
	or NULL if the memory reservation fails.*/
