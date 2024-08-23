/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 11:40:04 by sternero          #+#    #+#             */
/*   Updated: 2024-08-21 11:40:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // write

int     ft_atoi(char *str)
{
    int n = 0;      // Variable to store the number

    while (*str)
    {
        n = n * 10;           // It multiplies the number by 10
        n = n + (*str - '0'); // It converts the character to an integer
        str++;  // It increments the pointer to the next character
    }
    return (n); // It returns the number as an integer
}

void    print_hex(int n)
{
    char *hex = "0123456789abcdef"; // String with the hexadecimal characters

    if (n >= 16)                // If n is greater or equal to 16. 42 > 16
        print_hex(n / 16);      // It calls itself with the number divided by 16
    write(1, &hex[n % 16], 1);  // It writes the hexadecimal character to the standard output
}

int     main(int argc, char *argv[])
{
    if (argc == 2)                   // If the number of arguments is 2
        print_hex(ft_atoi(argv[1])); // It prints the hexadecimal representation of the number
    write(1, "\n", 1);               // It writes a newline to the standard output
    return (0);                      // It returns 0 to the operating system
}

/*
The program compiled with the following command:
    gcc -Wall -Wextra -Werror print_hex.c -o print_hex
*/