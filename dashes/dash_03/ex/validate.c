/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 10:23:42 by sternero          #+#    #+#             */
/*   Updated: 2025-11-17 10:23:42 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	str_len(char *str);

/*
** Validates that the mode string matches the target string exactly.
** Used to ensure the user typed "encode" or "decode" completely,
** not just "e" or "d" or any partial/incorrect input.
** Returns: 1 if strings match exactly, 0 otherwise
*/

int	validate_mode(char *mode, char *target)
{
	int	i;
	int	len;

	i = 0;
	len = str_len(target);
	while (mode[i] && target[i])
	{
		if (mode[i] != target[i])
			return (0);
		i++;
	}
	if (i != len || mode[i] != '\0')
		return (0);
	return (1);
}

/*
** Validates command-line arguments before processing.
** Checks:
** 1. Text is not empty (string length > 0)
** 2. Mode starts with 'e' or 'd'
** 3. Mode is exactly "encode" or "decode" (not abbreviated)
** Returns: 1 if input is valid, 0 if any check fails
*/

int	validate_input(char *mode, char *text)
{
	if (str_len(text) == 0)
		return (0);
	if (mode[0] != 'e' && mode[0] != 'd')
		return (0);
	if (mode[0] == 'e' && !validate_mode(mode, "encode"))
		return (0);
	if (mode[0] == 'd' && !validate_mode(mode, "decode"))
		return (0);
	return (1);
}
