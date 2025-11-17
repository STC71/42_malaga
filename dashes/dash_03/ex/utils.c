/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 10:23:29 by sternero          #+#    #+#             */
/*   Updated: 2025-11-17 10:23:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

/*
** Transforms a character using Atbash cipher algorithm.
** Lowercase letters: a->z, b->y, c->x, etc. (reverse alphabet)
** Uppercase letters: converted to lowercase then transformed
** Numbers: kept unchanged
** Other characters: return null character
*/

char	transform_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return ('z' - (c - 'a'));
	if (c >= 'A' && c <= 'Z')
		return ('z' - (c - 'A'));
	if (c >= '0' && c <= '9')
		return (c);
	return ('\0');
}

/*
** Calculates the length of a string.
** Returns: the number of characters before the null terminator
*/

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** Counts valid characters in a string for encoding.
** Valid characters: lowercase letters (a-z), uppercase letters (A-Z),
** and digits (0-9). Punctuation and special characters are excluded.
** Returns: total count of valid characters
*/

int	count_valid_chars(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9'))
			count++;
		i++;
	}
	return (count);
}

/*
** Compares two strings character by character.
** Returns: 0 if strings are equal, otherwise the difference between
** the first non-matching characters
*/

int	str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*
** Prints encoded text in groups of 5 characters separated by spaces.
** Example: "helloworld" prints as "hello world"
** The last group may have fewer than 5 characters.
** Always ends with a newline.
*/

void	print_encoded(char *result, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(1, &result[i], 1);
		if ((i + 1) % 5 == 0 && i + 1 < len)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
