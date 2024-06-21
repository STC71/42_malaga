/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 09:23:35 by sternero          #+#    #+#             */
/*   Updated: 2024-06-02 09:23:35 by sternero         ###   ########.fr       */
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
            if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                write (1, "_", 1);
                argv[1][i] += 32;
                write (1, &argv[1][i], 1);
            }
            else 
                write (1, &argv[1][i], 1);
            i++;       
        }
    }
    write (1, "\n", 1);
    return (0);
}