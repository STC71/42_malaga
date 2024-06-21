/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 09:41:48 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 09:41:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op.h"

int main (int argc, char *argv[])
{
    if (argc == 4)
    {
        if (argv[2][0] == '+')
            printf("%d", (atoi(argv[1]) + atoi(argv[3])));
        if (argv[2][0] == '-')
            printf("%d", (atoi(argv[1]) - atoi(argv[3])));
        if (argv[2][0] == '*')
            printf("%d", (atoi(argv[1]) * atoi(argv[3])));
        if (argv[2][0] == '/')
            printf("%d", (atoi(argv[1]) / atoi(argv[3])));
        if (argv[2][0] == '%')
            printf("%d", (atoi(argv[1]) % atoi(argv[3])));
    }
    printf ("\n");
    return (0);
}

/*
The funtion compile with the following flags:
gcc -Wall -Wextra -Werror do_op.c -o do_op
*/