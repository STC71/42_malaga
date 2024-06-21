/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 12:03:48 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 12:03:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc > 1)
    {
        while (argv[1][i] != '0')
        {
            if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
                argv[1][i] -= 32;
            else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
                argv[1][i] += 32;
            write (1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
}

/*
This program takes a string as an argument and converts all lowercase letters to
uppercase and all uppercase letters to lowercase. The program then prints the
modified string.

The program is compiled with the following command:
gcc -Wall -Wextra -Werror ulstr.c -o ulstr
*/