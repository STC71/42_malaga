/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-22 12:14:50 by sternero          #+#    #+#             */
/*   Updated: 2024-08-22 12:14:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

int     ft_atoi(char *str)
{
    int     res;
    int     sig;

    res = 0;
    sig = 1;
    while (*str == 32 || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '+')
        str++;
    while (*str)
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res * sig);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putnbr(int n)
{
    if (n / 10 > 0)
        ft_putnbr(n / 10);
    ft_putchar(n % 10 + '0');
}

int     main(int argc, char *argv[])
{
    int     i;
    int     n;

    if (argc != 2)
        ft_putchar('\n');
    else
    {
        n = ft_atoi(argv[1]);
        i = 1;
        while (i <= 9)
        {
            ft_putnbr(n);
            write(1, " x ", 3);
            ft_putnbr(i);
            write(1, " = ", 3);
            ft_putnbr(i * n);
            ft_putchar('\n');
            i++;
        }
    }
    return (0);
}

// This program takes a number as argument and displays a multiplication table
// with the number from 1 to 9. The result is displayed in the following format:
// "number x i = result", followed by a newline. If the number of arguments is
// different from 2, the program displays a newline.

// The code is a simple implementation of the atoi function, putchar and putnbr
// functions. The main function checks if the number of arguments is different
// from 2, if so, it displays a newline. Otherwise, it converts the argument to
// an integer and displays the multiplication table. The putnbr function is used
// to display the integer values, while the putchar function is used to display
// characters.

// To compile the program, you can use the following command:
// gcc tab_mult.c -o tab_mult

// To run the program, you can use the following command:
// ./tab_mult 5