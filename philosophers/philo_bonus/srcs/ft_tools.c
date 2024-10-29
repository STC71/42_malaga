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

int     ft_atoi_pro(char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '\n'
		|| *c == '\v' || *c == '\f' || *c == '\r')
		return (1);
	else
		return (0);
}

int     ft_atoi(const char *str)
{
	int	res;
	int	sig;
	int	sign;
	int	i;

	i = 0;
	sig = 1;
	sign = 0;
	res = 0;
	while (ft_atoi_pro((char *)&str[i]))
		i++;
	if (str[i] == '-')
		sig = -1;
	while (str[i] == '-' || str[i] == '+')
	{
		i++;
		sign++;
	}
	while (str[i] >= 48 && str[i] <= 57 && sign <= 1)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sig);
}