/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:27:10 by sternero          #+#    #+#             */
/*   Updated: 2025/11/29 12:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*get_next_word(const char **s, char c)
{
	const char	*start;
	const char	*end;

	start = *s;
	while (*start && *start == c)
		start++;
	end = start;
	while (*end && *end != c)
		end++;
	if (start == end)
		return (NULL);
	*s = end;
	return (ft_strndup(start, end - start));
}

void	free_res_on_fail(char **res, int i)
{
	while (i > 0)
	{
		free(res[i - 1]);
		i--;
	}
	free(res);
}

void	debug_alloc_array(char **res, int word_num)
{
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[alloc] ft_split: array=%p words=%d\n",
			(void *)res, word_num);
}

void	debug_alloc_item(char **res, int i)
{
	if (getenv("DEBUG_ALLOCS"))
		fprintf(stderr, "[alloc] ft_split: array[%d]=%p str=%s\n",
			i, (void *)res[i], res[i]);
}

int	fill_split_array(char **res, const char *s, char c)
{
	int		i;
	char	*item;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			item = get_next_word(&s, c);
			if (!item)
			{
				free_res_on_fail(res, i);
				return (-1);
			}
			res[i] = item;
			debug_alloc_item(res, i);
			i++;
		}
		else
			s++;
	}
	return (i);
}
