/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atbash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 10:22:34 by sternero          #+#    #+#             */
/*   Updated: 2025-11-17 10:22:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		str_len(char *str);
void	print_encoded(char *result, int len);
char	*encode(char *text);
void	decode(char *text);
int		validate_input(char *mode, char *text);
int		str_cmp(char *s1, char *s2);

/*
** Main program for Atbash cipher encoding/decoding.
** Usage: ./atbash [encode|decode] [text]
** - Validates arguments (must be exactly 2 parameters)
** - Checks mode and text validity
** - Encodes: transforms text and prints in 5-character groups
** - Decodes: reverses cipher and prints plain text
** Error handling:
** - Wrong number of arguments: prints specific error message
** - Invalid mode or empty text: prints generic "Error"
** Returns: 0 on success, 1 on error
*/

int	main(int argc, char **argv)
{
	char	*result;

	if (argc != 3)
	{
		write(1, "Error: Incorrect number of arguments\n", 38);
		return (1);
	}
	if (!validate_input(argv[1], argv[2]))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (str_cmp(argv[1], "encode") == 0)
	{
		result = encode(argv[2]);
		if (!result)
			return (1);
		print_encoded(result, str_len(result));
		free(result);
	}
	else if (str_cmp(argv[1], "decode") == 0)
		decode(argv[2]);
	return (0);
}
