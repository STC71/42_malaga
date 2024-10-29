/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_tools_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 12:26:17 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 12:26:17 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/* La función ft_get_name extrae el nombre de una variable de entorno. Toma un
   argumento: una cadena. Devuelve un puntero a la cadena. */

/* The function ft_get_name extracts the name of an environment variable. It takes
   one argument: a string. It returns a pointer to the string. */

char	*ft_get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	value = (char *)malloc(sizeof(char) * (ft_strlen(str) -i + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

/* La función ft_get_value extrae el valor de una variable de entorno. Toma un
   argumento: una cadena. Devuelve un puntero a la cadena. La diferencia entre
   esta función y ft_get_name es que esta función devuelve el valor de la 
   variable de entorno, mientras que ft_get_name devuelve el nombre de la
   variable de entorno. */

/* The function ft_get_value extracts the value of an environment variable. 
   It takes one argument: a string. It returns a pointer to the string. The
   difference between this function and ft_get_name is that this function
   returns the value of the environment variable, while ft_get_name returns
   the name of the environment variable. */

void	ft_add_var(t_var ***list_var, char *str, char *value)
{
	int		i;
	t_var	**new_list_var;

	i = 0;
	while ((*list_var)[i])
		i++;
	new_list_var = (t_var **)malloc(sizeof(t_var *) * (i + 2));
	if (!new_list_var)
		return ;
	i = 0;
	while ((*list_var)[i])
	{
		new_list_var[i] = (*list_var)[i];
		i++;
	}
	new_list_var[i] = (t_var *)malloc(sizeof(t_var));
	if (!new_list_var[i])
		return ;
	new_list_var[i]->name = strdup(str);
	new_list_var[i]->value = strdup(value);
	new_list_var[i + 1] = NULL;
	free(*list_var);
	*list_var = new_list_var;
}

/* La función ft_add_var añade una nueva variable de entorno a la lista de
   variables de entorno. Toma tres argumentos: un puntero a un puntero a una
   lista de variables de entorno, una cadena y un valor. */

/* The ft_add_var() function adds a new environment variable to the list of
   environment variables. It takes three arguments: a pointer to a pointer to
   a list of environment variables, a string, and a value. */