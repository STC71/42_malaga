/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-31 11:56:36 by sternero          #+#    #+#             */
/*   Updated: 2024-05-31 11:56:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char **argv)
{
    int i;

    i = 0;
    if (argc == 2)
    {
        while ((argv[1][i] == 9) || (argv[1][i] == 32))
            i++;
        while ((argv[1][i] != 9) && (argv[1][i] != 32) && (argv[1][i]))
        {
            write (1, &argv[1][i], 1);
            i++;
        }
    }
    write (1, "\n", 1);
    return (0);
}