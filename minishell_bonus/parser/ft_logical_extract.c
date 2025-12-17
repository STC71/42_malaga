/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_extract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 12:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-24 12:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_copy_trimmed(char *left, char *prompt, int op_pos, int *j)
{
	int	i;

	i = 0;
	while (i < op_pos)
	{
		if (prompt[i] != ' ' && prompt[i] != '\t')
			left[(*j)++] = prompt[i];
		else if (*j > 0 && left[*j - 1] != ' ')
			left[(*j)++] = ' ';
		i++;
	}
	while (*j > 0 && (left[*j - 1] == ' ' || left[*j - 1] == '\t'))
		(*j)--;
}

char	*ft_extract_left_cmd(char *prompt, int op_pos)
{
	char	*left;
	int		j;

	left = malloc(sizeof(char) * (op_pos + 1));
	if (!left)
		return (NULL);
	j = 0;
	ft_copy_trimmed(left, prompt, op_pos, &j);
	left[j] = '\0';
	return (left);
}

char	*ft_extract_right_cmd(char *prompt, int op_pos)
{
	char	*right;
	int		start;
	int		len;

	if (prompt[op_pos] == ';')
		start = op_pos + 1;
	else
		start = op_pos + 2;
	while (prompt[start] && (prompt[start] == ' ' || prompt[start] == '\t'))
		start++;
	len = ft_strlen(prompt + start);
	right = malloc(sizeof(char) * (len + 1));
	if (!right)
		return (NULL);
	ft_strlcpy(right, prompt + start, len + 1);
	return (right);
}
