/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 17:18:19 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 17:18:19 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_replace_vars(char **str, int *i, char *status, t_var **list_var)
{
	char	*abc;
	char	*tmp;
	char	*var;

	if ((*str)[*i + 1] == '?')
	{
		tmp = *str;
		*str = ft_delete_str(tmp, *i, *i + 1);
		free(tmp);
		tmp = *str;
		*str = ft_insert_str(tmp, status, *i);
		free(tmp);
		*i++;
	}
	else
	{
		abc = ft_find_var(*str, *i + 1);
		*str = ft_delete_str(*str, *i, *i + ft_strlen(abc));
		var = ft_get_var(list_var, abc);
		tmp = *str;
		*str = ft_insert_str(tmp, var, *i);
		free(tmp);
		free(abc);
		free(var);
	}
}

static void	ft_do_cmd(char **str, t_var **list_var, char *status)
{
	int		i;
	int		is_alpha;
	int		is_dollar;
	int		is_question;
	int		is_underscore;

	i = 0;
	while ((*str)[i])
	{
		is_alpha = ft_isalpha((*str)[i + 1]);
		is_dollar = (*str)[i] == '$';
		is_question = (*str)[i] == '?';
		is_underscore = (*str)[i] == '_';
		if (is_dollar && (is_alpha || is_question || is_underscore))
			ft_replace_vars(str, &i, status, list_var);
		i++;
	}
}

void	ft_restore_dolar(char **dolar)
{
	int		i;
	int		j;

	i = 0;
	while ((*dolar)[i])
	{
		j = 0;
		while ((dolar)[i][j])
		{
			if ((dolar)[i][j] == 1)
				dolar[i][j] = '$';
			j++;
		}	
		i++;
	}

}

/* The ft_env_var() function replaces the environment variables in the command
	with their values. It takes a pointer to a t_minishell structure and a
	pointer to a char array as arguments.*/

/* The ft_do_cmd() function processes the command. It takes three arguments: a
	pointer to a char array, a pointer to a t_var structure, and a pointer to a
	char array. */

/* The ft_restore_dolar() function restores the dollar signs in the command. It
	takes a pointer to a char array as an argument. */

