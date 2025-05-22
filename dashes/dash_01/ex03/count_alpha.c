/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 10:08:01 by sternero          #+#    #+#             */
/*   Updated: 2025-03-28 10:08:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);
    char c = (n % 10) + '0';
    write(1, &c, 1);
}

void	count_occurrences_and_seen(char *str, int *count, int *seen)
{
    int	i = 0;

    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            count[(int)str[i]]++;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            count[(int)(str[i] + 32)]++;
        else
        {
            seen[(int)str[i]] = 1; // Marcar caracteres no alfabéticos como vistos
        }
        i++;
    }
}

void	print_results(char *str, int *count, int *seen)
{
    int	i = 0;
    int	first = 1;

    while (str[i])
    {
        char c;
        if (str[i] >= 'a' && str[i] <= 'z')
            c = str[i];
        else if (str[i] >= 'A' && str[i] <= 'Z')
            c = str[i] + 32;
        else
        {
            i++;
            continue;
        }

        if (!seen[(int)c])
        {
            seen[(int)c] = 1;
            if (!first)
                write(1, ", ", 2);
            first = 0;
            ft_putnbr(count[(int)c]);
            write(1, &c, 1);
        }
        i++;
    }
}

void	count_alpha(char *str)
{
    int	count[256] = {0};
    int	seen[256] = {0};

    count_occurrences_and_seen(str, count, seen);
    print_results(str, count, seen);
}

int	main(int argc, char *argv[])
{
    if (argc == 2)
        count_alpha(argv[1]);
	write (1, "\n", 1);
    return (0);
}


// #include <unistd.h>

// void	ft_putnbr(int n)
// {
//     if (n > 9)
//         ft_putnbr(n / 10);
//     char c = (n % 10) + '0';
//     write(1, &c, 1);
// }

// void count_alpha(char *str)
// {
//     int	count[256] = {0};
//     int	seen[256] = {0};
//     int	i;
//     int	first = 1;

//     i = 0;

//     while (str[i])
//     {
//         if (str[i] >= 'a' && str[i] <= 'z')
//             count[(int)str[i]]++;
//         else if (str[i] >= 'A' && str[i] <= 'Z')
//             count[(int)(str[i] + 32)]++;
//         i++;
//     }

//     i = 0;
//     while (str[i])
//     {
//         char c;
//         if (str[i] >= 'a' && str[i] <= 'z')
//             c = str[i];
//         else if (str[i] >= 'A' && str[i] <= 'Z')
//             c = str[i] + 32;
//         else
//         {
//             i++;
//             continue;
//         }

//         if (!seen[(int)c])
//         {
//             seen[(int)c] = 1;
//             if (!first)
//                 write(1, ", ", 2);
//             first = 0;
//             ft_putnbr(count[(int)c]);
//             write(1, &c, 1);
//         }
//         i++;
//     }
//     if (!first)
//         write(1, "\n", 1);
// }

// int	main(int argc, char *argv[])
// {
//     if (argc == 2)
//         count_alpha(argv[1]);
//     return (0);
// }

