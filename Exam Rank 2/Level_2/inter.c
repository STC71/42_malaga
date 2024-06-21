/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-03 13:47:09 by sternero          #+#    #+#             */
/*   Updated: 2024-06-03 13:47:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int has_char(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return 1;
        str++;
    }
    return 0;
}

void inter(char *str1, char *str2)
{
    char printed[128] = {0};
    int i = 0;

    while (*str1)
    {
        if (has_char(str2, *str1) && !has_char(printed, *str1))
        {
            write(1, str1, 1);
            printed[i] = *str1;
            i++;
        }
        str1++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
        inter(argv[1], argv[2]);
    write(1, "\n", 1);
}
/*
The program takes two strings as command-line arguments and prints the
characters that appear in both strings in the order they appear in the
first string.

The program first checks if the number of arguments is correct.
If not, the program prints a newline and returns 1.

The program then calls the inter function with the two strings as arguments.
The inter function iterates over the first string, checking if each character
is present in the second string and has not been printed yet.

The program compiled with the following command:
gcc -Wall -Wextra -Werror inter.c -o inter
*/
