/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-28 11:50:44 by sternero          #+#    #+#             */
/*   Updated: 2024-10-28 11:50:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_str_add(char **out, char *token)
{
	int len = 0;
    char **new_out;

    while (out && out[len])
        len++;
    new_out = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_out)
        return NULL;
    for (int i = 0; i < len; i++)
        new_out[i] = out[i];
    new_out[len] = strdup(token);
    new_out[len + 1] = NULL;
    free(out);
    return (new_out);
}

/* The ft_str_add() function adds a string to an array of strings. It takes two
	arguments: an array of strings and a string. It returns an array of strings. 
	*/

char	*ft_process_token(char *vector, int *i)
{
	char	*tmp;

	while (vector[*i] == ' ')
		(*i)++;
	if (!vector[*i])
		return (NULL);
	tmp = ft_extract_token(vector, *i, ft_strlen(vector + *i));
	*i += ft_strlen(tmp);
	return (tmp);
}

/* The ft_process_token() function extracts a word from a string. It takes two
	arguments: a string and a pointer to an index. It returns a pointer to the 
	word extracted from the string. */

void	ft_do_command(char **str, t_var **list_var, char *status)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			tmp = ft_find_var(*str, i);
			tmp2 = ft_get_var(list_var, tmp);
			free(tmp);
			*str = ft_replace_str(*str, tmp2, i);
			free(tmp2);
		}
		i++;
	}
}

/* The ft_do_command() function processes the command. It takes three arguments:
	a pointer to a char array, a pointer to a t_var structure, and a pointer to a
	char array. It processes the command by replacing the environment variables
	with their values. */

t_var	**ft_init_env(char **env)
{
	t_var	**list_var;
	int		i;
	char	*name;
	char	*value;

	i = 0;
	list_var = NULL;
	while (env[i])
	{
		name = ft_get_name(env[i]);
		value = ft_get_value(env[i]);
		ft_add_var(&list_var, name, value);
		free(name);
		free(value);
		i++;
	}
	return (list_var);
}

/* The ft_init_env() function initializes the environment variables. It takes an
	array of strings as an argument. It returns a pointer to a t_var structure. 
	*/