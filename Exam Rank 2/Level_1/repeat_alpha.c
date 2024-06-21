/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 08:45:19 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 08:45:19 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c, int n)
{
    while (n > 0)
    {
        write(1, &c, 1);
        n--;
    }
}

void repeat_alpha(char *str)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
            ft_putchar(*str, *str - 'a' + 1);
        else if (*str >= 'A' && *str <= 'Z')
            ft_putchar(*str, *str - 'A' + 1);
        else
            write(1, str, 1);
        str++;
    }
}

// Do not include the main function when submitting to examshell.

int main(int argc, char **argv)
{
    if (argc == 2)
        repeat_alpha(argv[1]);
    write(1, "\n", 1);
    return (0);
}

/*
The main function takes two arguments, the first being the number of
arguments passed to the program and the second being the string to be
printed. If the number of arguments is equal to 2, the repeat_alpha
function is called with the string as an argument. 
The repeat_alpha function prints the string with each letter repeated
a number of times equal to its position in the alphabet. 

If the number of arguments is not equal to 2, the program does nothing. 

The program is compiled with the following command:
gcc -Wall -Wextra -Werror repeat_alpha.c -o repeat_alpha
*/