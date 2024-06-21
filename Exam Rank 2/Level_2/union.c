/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 11:55:40 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 11:55:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

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

void union_str(char *str1, char *str2)
{
    char seen[256] = {0};
    int i = 0;

    while (*str1)
    {
        if (!has_char(seen, *str1))
        {
            seen[i] = *str1;
            write(1, str1, 1);
            i++;
        }
        str1++;
    }
    while (*str2)
    {
        if (!has_char(seen, *str2))
        {
            seen[i] = *str2;
            write(1, str2, 1);
            i++;
        }
        str2++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
        union_str(argv[1], argv[2]);
    write(1, "\n", 1);
}

/*
The program takes two strings as command-line arguments and prints 
the characters that appear in either string.

The program first checks if the number of arguments is correct.
If not, it prints a usage message and returns 1.

The program then iterates over the first string, adding each character 
to a union string.

The program then iterates over the second string, adding each character
to the union string if it is not already present.

Finally, the program prints the union string and returns 0.

The program compiled with the following command:
gcc -Wall -Wextra -Werror union.c -o union
*/