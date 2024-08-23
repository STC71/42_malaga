/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-22 11:36:25 by sternero          #+#    #+#             */
/*   Updated: 2024-08-22 11:36:25 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

void    str_capitalizer(char *str)
{
    int i = 0;

    if (str[i] >= 'a' && str[i] <= 'z')
        str[i] -= 32;
    write (1, &str[i], 1);
    while (str[++i]) 
    {  
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if ((str[i] >= 'a' && str[i] <= 'z') && (str[i - 1] == ' ' 
            || str[i - 1] == '\t'))
            str[i] -= 32;
        write(1, &str[i], 1);
    }
}

int     main(int argc, char *argv[])
{
    int i = 1;

    if (argc < 2)
        write(1, "\n", 1);
    else
    {
        while (i < argc)
        {
            str_capitalizer(argv[i]);
            write(1, "\n", 1);
            i++;
        }
    }
    return (0);
}

/*
The program compiled with the following command:
    gcc -Wall -Wextra -Werror str_capitalizer.c -o str_capitalizer

The str_capitalizer function capitalizes the first letter of each word, if it is
lowercase.

The main function calls the str_capitalizer function for each argument passed to
the program.
*/