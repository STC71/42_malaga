/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-26 08:03:04 by sternero          #+#    #+#             */
/*   Updated: 2024-09-26 08:03:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_strlen(char *str)
{
	int		res;

	res = 0;
	while (str[res] != '\0')
		res++;
	return (res);
}

int	ft_num_digits(long n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long	aux;
	int		len;
	char	*res;
	int		sig;

	aux = n;
	sig = 0;
	if (n < 0)
	{
		aux = (long)n * (-1);
		sig = 1;
	}
	len = ft_num_digits(aux) + sig;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (sig == 1)
		res[0] = '-';
	while (sig != len)
	{
		res[len-- - 1] = (aux % 10) + '0';
		aux /= 10;
	}
	return (res);
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sig;

	i = 0;
	res = 0;
	sig = 1;
	while (str[i] == '\r' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sig = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sig);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *) malloc(total * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free(s2);
	return (str);
}
