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

#include "../includes/philo.h"

void	ft_delay(uint64_t pause)
{
	uint64_t	ini;

	ini = ft_my_watch();
	while ((ft_my_watch() - ini) < pause)
		usleep(500);
}

/*	The function ft_delay() delays the program for the time specified. 
	It receives a time as an argument. It gets the current time, and while the 
	difference between the current time and the initial time is less than the 
	time specified, it sleeps for 500 ms. */

uint64_t	ft_my_watch(void)
{
	struct timeval	ms;

	if (gettimeofday(&ms, NULL))
		return (SUCCESS);
	return ((ms.tv_sec * (uint64_t)1000) + (ms.tv_usec / 1000));
}

/*	The function ft_my_watch() gets the current time. It creates a timeval 
	structure. The gettimeofday() function is the time of day. It gets the
	time of day and returns the current time. tv_sec is the number of seconds
	since the Epoch (00:00:00 UTC, January 1, 1970). tv_usec is the number of
	microseconds. */

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == '\r' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

/*	The function ft_atoi() converts a string to an integer. It receives a string
	as an argument. It initializes the index, the result, and the sign. It skips 
	whitespace characters. If the character is a minus sign, it assigns the sign 
	to -1 and increments the index. If the character is a plus sign, 
	it increments the index. If the character is not a digit, it returns 0. 
	While the character is a digit, it multiplies the result by 10 and adds the 
	character minus '0'. Finally, it returns the result multiplied by the sign. 
*/
