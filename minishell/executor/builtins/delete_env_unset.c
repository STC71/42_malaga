/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:35:03 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:46:08 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Función para eliminar una o varias variable de entorno del entorno de shell */

void ft_delete_env_unset(char **name_var, t_minishell *shell)
{
    int	x;
    int	i;
    int	j;
    int	len;

    x = -1;
    /* usa una matrix xq puede enviarle varias env para eliminar*/
    while (name_var[++x] != NULL)
    {
        i = -1;
        while (shell->env[++i] != NULL)
        {
            if (!ft_strncmp(shell->env[i], name_var[x], ft_strlen(name_var[x])) 
            && shell->env[i][ft_strlen(name_var[x])] == '=')
            {// en name_var[x] está el nombre de la env a borrar (PATH, HOME, etc)
                // como el ft_strlen devuelve el i una pos +, se compara con el =
                free(shell->env[i]);
                j = i;
                while (shell->env[j] != NULL)
                {
                    shell->env[j] = shell->env[j + 1];
                    /* mueve todas las lineas siguientes de la matriz atrás
                    para que sigan estando las lineas juntas una vez borrada
                    la env */
                    j++;
                }
                shell->env[j] = NULL;
                i--; // retrocede para poder volver a controlar env[i] ==NULL y salir
            }
        }
    }
}