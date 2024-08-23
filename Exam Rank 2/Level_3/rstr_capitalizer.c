/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-22 10:43:55 by sternero          #+#    #+#             */
/*   Updated: 2024-08-22 10:43:55 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

void    rstr_capitalizer(char *str)
{
    int i = 0; // Variable to store the index of the string

    while (str[i]) // While the character is not the null character
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if ((str[i] >= 'a' && str[i] <= 'z') && (str[i + 1] == ' ' 
            || str[i + 1] == '\t' || str[i + 1] == '\0'))
            str[i] -= 32;
        write(1, &str[i++], 1);
    }
}

int     main(int argc, char *argv[])
{
    int i;

    if (argc == 1)          // If the number of arguments is 1
        write(1, "\n", 1);  // It writes a newline to the standard output
    else
    {
        i = 1;
        while (i < argc)    // While the index is less than the number of arguments
        {
            rstr_capitalizer(argv[i]); // It capitalizes the string
            write(1, "\n", 1);         // It writes a newline to the standard output
            i++;                       // It increments the index
        }
    }
    return (0);
}

/*
The program compiled with the following command:
    gcc -Wall -Wextra -Werror rstr_capitalizer.c -o rstr_capitalizer

The rstr_capitalizer function capitalizes the last word of a string and the 
first letter of each word, if it is lowercase. 

The main function calls the rstr_capitalizer function for each argument 
passed to the program.
*/