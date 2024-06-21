/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 11:59:01 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 11:59:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void search_and_replace(char *str, char *search, char *replace)
{
    while (*str)
    {
        if (*str == *search)
            ft_putchar(*replace);
        else
            ft_putchar(*str);
        str++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 4)
        search_and_replace(argv[1], argv[2], argv[3]);
    ft_putchar('\n');
    return (0);
}

/*
This program takes a string, a character to search for, and a character to
replace the search character with. The program iterates through the string and
replaces the search character with the replacement character.

The program is compiled with the following command:
gcc -Wall -Wextra -Werror search_and_replace.c -o search_and_replace
*/