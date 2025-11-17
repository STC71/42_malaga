/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 10:23:01 by sternero          #+#    #+#             */
/*   Updated: 2025-11-17 10:23:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	transform_char(char c);

/*
** Decodes Atbash-encoded text back to plain text.
** Process:
** 1. Iterates through encoded text
** 2. Skips space characters (used for grouping in encoded format)
** 3. Transforms each valid character using Atbash cipher
** 4. Outputs the decoded character directly (no memory allocation needed)
** Note: Atbash is symmetric, so encoding and decoding use same transformation
*/

void	decode(char *text)
{
	int		i;
	char	c;

	i = 0;
	while (text[i])
	{
		if (text[i] != ' ')
		{
			c = transform_char(text[i]);
			if (c != '\0')
				write(1, &c, 1);
		}
		i++;
	}
	write(1, "\n", 1);
}
