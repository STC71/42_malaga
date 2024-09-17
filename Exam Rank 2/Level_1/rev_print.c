/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 09:39:44 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 09:39:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void rev_print (char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    i--;
    while (i >= 0)
    {
        write (1, &str[i], 1);
        i--;
    }
}

int main (int argc, char **argv)
{
    if (argc == 2)
        rev_print(argv[1]);
    write(1, "\n", 1);
    return (0);    
}

/*
The main function takes two arguments, the first being the number of
arguments passed to the program and the second being the string to be   
printed. If the number of arguments is equal to 2, the rev_print
function is called with the string as an argument.

The rev_print function prints the string in reverse order.
If the number of arguments is not equal to 2, the program does nothing.

The program is compiled and runed with the following command:
gcc -Wall -Wextra -Werror rev_print.c -o rev_print; ./rev_print "Hello, World!"
*/