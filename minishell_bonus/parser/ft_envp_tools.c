/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 07:48:41 by sternero          #+#    #+#             */
/*   Updated: 2025-11-30 07:48:41 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_value_envp(t_var **list_var, char *key)
{
	int	i;

	i = 0;
	if (!list_var)
		return (ft_strdup(""));
	while (list_var[i])
	{
		if (ft_strcmp(list_var[i]->key, key) == 0)
			return (ft_strdup(list_var[i]->value));
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_find_envp(char *str, int pos)
{
	int	i;

	i = pos;
	while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
		pos++;
	return (ft_strndup(str + i, pos - i));
}

void	ft_add_dollar(char **dollar)
{
	int	i;
	int	j;

	i = 0;
	while (dollar && dollar[i])
	{
		j = 0;
		while (dollar[i][j])
		{
			if (dollar[i][j] == 1)
				dollar[i][j] = '$';
			j++;
		}
		i++;
	}
}

void	ft_expand_envp(t_shell *shell, char **envp)
{
	int		i;
	t_var	**list;
	char	*status ;

	i = 0;
	list = ft_action_envp(envp);
	status = ft_itoa(shell->g_status);
	while (shell->full_cmd && shell->full_cmd[i])
	{
		ft_replace_status_quote_aware(&shell->full_cmd[i], list, status);
		i++;
	}
	ft_add_dollar(shell->full_cmd);
	free(status);
	i = 0;
	while (shell->full_cmd && shell->full_cmd[i])
	{
		ft_del_quotes(shell->full_cmd[i]);
		i++;
	}
	ft_free_env_vars(list);
}
/* Use a quote-aware replacer: expand variables except when inside
   single quotes. The previous implementation skipped the entire
   argument if any single-quote character was present, which caused
   cases like echo "'\$USER'" to not expand $USER even though
   it appears inside double quotes. */
