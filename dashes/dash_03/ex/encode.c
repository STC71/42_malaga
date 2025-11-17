/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 10:23:10 by sternero          #+#    #+#             */
/*   Updated: 2025-11-17 10:23:10 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	transform_char(char c);
int		count_valid_chars(char *str);

/*
** Encodes text using Atbash cipher.
** Process:
** 1. Counts valid characters (letters and digits)
** 2. Allocates memory for the result string
** 3. Iterates through input, transforming only valid characters
** 4. Ignores punctuation and special characters
** Returns: pointer to encoded string, or NULL if malloc fails
** Note: Caller must free the returned string
*/

char	*encode(char *text)
{
	char	*result;
	int		valid_count;
	int		i;
	int		j;

	valid_count = count_valid_chars(text);
	result = malloc(sizeof(char) * (valid_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (text[i])
	{
		if ((text[i] >= 'a' && text[i] <= 'z')
			|| (text[i] >= 'A' && text[i] <= 'Z')
			|| (text[i] >= '0' && text[i] <= '9'))
		{
			result[j] = transform_char(text[i]);
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
