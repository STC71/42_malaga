/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-01 08:04:45 by sternero          #+#    #+#             */
/*   Updated: 2024-06-01 08:04:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen (char *str)
{
    int i;

    i=0;
    while (str[i])
        i++;
    return (i);
}

/*This function returns the length of a string. It is used in the main 
function to determine the length of the string passed as an argument. 
The length is then used to determine the position of the newline character 
in the write function.*/

int main (int argc, char **argv)
{
    if (argc == 2)
        write(1, argv[1], ft_strlen(argv[1]));
}

/*The main function takes two arguments, the first being the number of 
arguments passed to the program and the second being the string to be
printed. If the number of arguments is equal to 2, the write function is
called with the string and the length of the string as arguments. The
length of the string is used to determine the position of the newline
character in the string. The write function then prints the string to
standard output. If the number of arguments is not equal to 2, the program
does nothing. The program is compiled with the following command:
gcc -Wall -Wextra -Werror ft_strlen.c -o ft_strlen*/

// To compile and run:
// gcc -Wall -Wextra -Werror ft_strlen.c -o ft_strlen; ./ft_strlen "Hello, World!"