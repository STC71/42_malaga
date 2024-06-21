/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 08:32:27 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 08:32:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char **argv)
{
    int i;

    i = 0;
    if (argc > 1)
    {
        while (argv[1][i])
        {
            if (argv[1][i] >= 97 && argv[1][i] <= 122)
                argv[1][i] =  122 - argv[1][i] + 97;
            else if (argv[1][i] >= 65 && argv[1][i] <= 90)
                argv[1][i] = 90 - argv[1][i] + 65;
            write (1, &argv[1][i], 1);
            i++;
        }
    }
    write (1, "\n", 1);
    return (0);
}

/*
The funtion compiles with the following flags:
gcc -Wall -Wextra -Werror alpha_mirror.c -o alpha_mirror
*/