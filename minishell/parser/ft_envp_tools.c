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

/*dsdf
	Busca en la lista de variables de entorno (list_var) un key (key) y
	devuelve su valor. So no lo encuentra no devuelve nada.
*/
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

/*
	Encuentra una variable de entorno dentro de un string (str) a partir
	de una posicion determinada (pos).
*/
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
} // una vez que se ha parseado el comando, se almacena en la estructura cmd_struct.

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
} // expande las variables de entorno en el prompt.
