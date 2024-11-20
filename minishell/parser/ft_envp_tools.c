/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 17:51:45 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 17:51:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_value_envp(t_var **list_var, char *key)
{
	int	i;

	i = 0;
	while (list_var[i])
	{
		if (ft_strcmp(list_var[i]->key, key) == 0)
			return (ft_strdup(list_var[i]->value));
		i++;
	}
	return (ft_strdup(""));
}

/*	ft_get_value_envp() function is used to find a key in the list of 
	environment	variables and return its value. If it does not find it, 
	it returns an empty string. */

char	*ft_find_envp(char *str, int pos)
{
	char	*key;
	int		i;

	i = pos;
	while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
		pos++;
	key = ft_strndup(str + i, pos - i);
	return (key);
}

/*	ft_find_envp() function is used to find an environment variable within a 
	string starting from a determined position. */

void	ft_add_dollar(char **dollar)
{
	int	i;
	int	j;

	i = 0;
	while (dollar[i])
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

/*	ft_add_dollar() function is used to replace the character 1 with the 
	dollar sign in the command. If the command is parsed, it is stored in 
	the cmd_struct. */

void	ft_expand_envp(t_shell *shell, char **envp)
{
	int		i;
	t_var	**list;
	char	*status;

	i = 0;
	list = ft_action_envp(envp);
	status = ft_itoa(shell->g_status);
	while (shell->full_cmd[i])
	{
		if (shell->full_cmd[i][0] != '\'')
			ft_replace_status(&shell->full_cmd[i], list, status);
		i++;
	}
	ft_add_dollar(shell->full_cmd);
	free(status);
	i = 0;
	while (shell->full_cmd[i] != NULL)
	{
		ft_del_quotes(shell->full_cmd[i]);
		i++;
	}
	ft_free_env_vars(list);
}

/*	ft_expand_envp() function is used to expand the environment variables in 
	the prompt. It replaces the status variable with the value of the status 
	and deletes the quotes. */
