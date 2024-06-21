/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 11:10:15 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 11:10:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
    int end;
    int sig;

    end = 0;
    sig = 1;

    while (*str == 32 || (*str >=9 && *str <= 13))
        str++;
    if (*str == '-')
        sig = -1;
    if (*str == '-' || *str == '+')
        str++;
    while (*str >= 48 && *str <= 57)
    {
        end = end * 10 + *str - '0';
        str++;
    }
    return (sig * end); 

}

#include <stdio.h>

int main (int argc, char *argv[])
{
    if (argc == 2)
    {
        printf ("%d", ft_atoi(argv[1]));
    }
    return (0);
}

/*
The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror ft_atoi.c -o ft_atoi
*/