/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 12:25:01 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 12:25:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putstr(char *str)
{
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}

int wdmatch(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 == *s2)
            s1++;
        s2++;
    }
    return (!*s1);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        if (wdmatch(argv[1], argv[2]))
            ft_putstr(argv[1]);
    }
    write(1, "\n", 1);
    return 0;
}

/*
The program takes two strings as command-line arguments and prints the 
first string if all characters in the first string are present in the 
second string in the same order.

If the strings are identical, the program prints the first string.
If the strings are not identical, the program prints a newline.

The program first checks if the number of arguments is correct.
If not, the program prints a newline and returns 1.

The program then calls the wdmatch function with the two strings as 
arguments. The wdmatch function iterates over the strings, comparing 
each character.

If the characters match, the first string is incremented.
If the first string reaches the end, the function returns 1.
If the second string reaches the end, the function returns 0.

If the wdmatch function returns 1, the program prints the first string.
If the wdmatch function returns 0, the program prints a newline.

The program compiled with the following command:
gcc -Wall -Wextra -Werror wdmatch.c -o wdmatch
*/