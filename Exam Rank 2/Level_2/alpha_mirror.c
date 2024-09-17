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

/*
The function changes the case of the letters in the string passed as argument.

For example:

If the string passed as argument is "Hello", the output will be "Svool".

In this case, the function changes the case of the letters as follows:

H -> S - using the formula 90(Z) - 72(H) + 65(A) = 83 = S
e -> v - using the formula 122(z) - 101(e) + 97(a) = 118 = v
l -> o - using the formula 122(z) - 108(l) + 97(a) = 111 = o
...

a -> z - using the formula 122(z) - 97(a) + 97(a) = 122 = z
m -> n - using the formula 122(z) - 109(m) + 97(a) = 110 = n
n -> m - using the formula 122(z) - 110(n) + 97(a) = 109 = m
z -> a - using the formula 122(z) - 122(z) + 97(a) = 97 = a

97 = a; 122 = z; 65 = A; 90 = Z

*/