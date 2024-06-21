/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 11:28:37 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 11:28:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void rotone (char *str)
{
    while (*str)
    {
        if ((*str >= 'a' && *str < 'z') || (*str >= 'A' && *str < 'Z'))
            ft_putchar(*str + 1);
        else if (*str == 'z' || *str == 'Z')
            ft_putchar(*str - 25);
        else
            ft_putchar(*str);
        str++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
        rotone(argv[1]);
    ft_putchar('\n');
    return (0);
}

/*
This program takes a string as an argument and replaces each letter with the
next letter in the alphabet. If the letter is 'z' or 'Z', it is replaced with
'a' or 'A'. 

The program is compiled with the following command:
gcc -Wall -Wextra -Werror rotone.c -o rotone
*/