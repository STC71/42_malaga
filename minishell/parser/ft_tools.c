/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 11:29:28 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 11:29:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_delete_str(char *old, size_t start, size_t finish)
{
	size_t	old_pos;
	size_t	new_pos;
	size_t	len;
	size_t	new_len;
	char	*new;

	old_pos = 0;
	new_pos = 0;
	len = ft_strlen(old);
	new_len = len - (finish - start + 1);
	new = ft_calloc(sizeof(char), new_len + 1);
	if (!new)
		return (NULL);
	while (old_pos < start)
		new[new_pos++] = old[old_pos++];
	old_pos = finish + 1;
	while (old_pos < len)
		new[new_pos++] = old[old_pos++];
	new[new_pos] = '\0';
	return (new);
} // elimina una parte de la cadena old desde start hasta finish.

char	*ft_insert_str(char *old, char *part, size_t pos)
{
	size_t	new_pos;
	size_t	part_pos;
	char	*new;

	new_pos = 0;
	part_pos = 0;
	new = ft_calloc(sizeof(char), ft_strlen(old) + ft_strlen(part) + 1);
	while (new_pos < pos)
	{
		new[new_pos] = old[new_pos];
		new_pos++;
	}
	while (part[part_pos])
	{
		new[new_pos] = part[part_pos];
		new_pos++;
		part_pos++;
	}
	while (old[pos])
	{
		new[new_pos] = old[pos];
		new_pos++;
		pos++;
	}
	return (new[new_pos] = '\0', new);
} // inserta la cadena part en la cadena old en la posición pos.

void	ft_replace_envp(char **cmd, int *j, char *status, t_var **list)
{
	char	*key;
	char	*tmp;
	char	*var;

	if ((*cmd)[*j + 1] == '?')
	{
		tmp = *cmd;
		*cmd = ft_delete_str(tmp, *j, *j + 1);
		free(tmp);
		tmp = *cmd;
		*cmd = ft_insert_str(tmp, status, *j);
		free(tmp);
		(*j)++;
	}
	else
	{
		key = ft_find_envp(*cmd, *j + 1);
		*cmd = ft_delete_str(*cmd, *j, *j + ft_strlen(key));
		var = ft_get_value_envp(list, key);
		tmp = *cmd;
		*cmd = ft_insert_str(tmp, var, *j);
		free(key);
		free(tmp);
		free(var);
	}
} // reemplaza las variables de entorno en el comando por su valor.

void	ft_replace_status(char **cmd, t_var **list, char *status)
{
	int	i;
	int	alpha;
	int	dollar;
	int	question;
	int	u_score;

	i = 0;
	while ((*cmd)[i])
	{
		alpha = ft_isalpha((*cmd)[i + 1]);
		dollar = (*cmd)[i] == '$';
		question = (*cmd)[i + 1] == '?';
		u_score = (*cmd)[i + 1] == '_';
		if (dollar && (alpha || question || u_score))
			ft_replace_envp(cmd, &i, status, list);
		i++;
	}
} // reemplaza las variables de entorno en un comando y actualiza el status.
