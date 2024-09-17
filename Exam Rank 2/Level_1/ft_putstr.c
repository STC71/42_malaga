/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-31 11:56:07 by sternero          #+#    #+#             */
/*   Updated: 2024-05-31 11:56:07 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putstr(char *str)
{
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}

// Do not include the main function when submitting to examshell.
// It is only included here for testing purposes.

int main(int argc, char **argv)
{
    if (argc == 2)
        ft_putstr(argv[1]);
    write(1, "\n", 1);
    return (0);
}

// Compile and run with the following commands:
// gcc -Wall -Wextra -Werror ft_putstr.c -o ft_putstr; ./ft_putstr "Hello, World!"