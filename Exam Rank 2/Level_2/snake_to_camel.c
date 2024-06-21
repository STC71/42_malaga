/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_to_camel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-04 11:40:27 by sternero          #+#    #+#             */
/*   Updated: 2024-06-04 11:40:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        write(1, "Usage: ./snake_to_camel <snake_case_string>\n", 43);
        return 1;
    }

    char *str = argv[1];
    int i = 0;

    while (str[i])
    {
        if (str[i] == '_')
        {
            i++;
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] -= 32;
        }
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
    return 0;
}

/*
The program takes a string in snake_case as a command-line argument 
and prints it in CamelCase.

The program first checks if the number of arguments is correct.
If not, it prints a usage message and returns 1.

The program then iterates over the string, checking for underscores.
If an underscore is found, the next character is converted to uppercase.

Finally, the program prints the modified string and returns 0.

The program compiled with the following command:
gcc -Wall -Wextra -Werror snake_to_camel.c -o snake_to_camel
*/