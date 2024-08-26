/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-26 07:58:29 by sternero          #+#    #+#             */
/*   Updated: 2024-08-26 07:58:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>         // for write

int main(int argc, char *argv[])
{
    int i = 0;
    int start_first_word;
    int end_first_word;
    int flag = 0;

    if (argc >= 2)
    {
        while (argv[1][i] == ' ' || argv[1][i] == '\t')
            i++;
        start_first_word = i;
        while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t' && argv[1][i] != '\0')
            i++;
        end_first_word = i - 1;
        if (argv[1][i] != '\0')
            i++;
        while (argv[1][i] != '\0')
        {
            if (argv[1][i] && ((argv[1][i] == ' ' || argv[1][i] == '\t') 
                && (argv[1][i + 1] == ' ' || argv[1][i + 1] == '\t' || !argv[1][i + 1])))
                i++;
            else
            {
                write (1, &argv[1][i], 1);
                i++;
                flag = 1;
            }
        }
        if (flag)
            write (1, " ", 1);
        while (start_first_word <= end_first_word)
        {
            write (1, &argv[1][start_first_word], 1);
            start_first_word++;
        }
    }
    write (1, "\n", 1);
    return (0);  
}

// to compile and run the program:
// gcc -Wall -Wextra -Werror rostring.c -o rostring; ./rostring "Hello world, from 42 Málaga"

