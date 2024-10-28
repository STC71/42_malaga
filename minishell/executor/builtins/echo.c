/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:46:17 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Imprime en stdout los argumentos que recibe */

void echo(char **args, t_minishell *shell)
{
    int i;
    int j;
    int new_line;

    i = 0;
    j = 1;
    new_line = 1;
    while (args[i][0] == '-' && args[i][1] == 'n' && args[i] == '\0')
    {    
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')         
            return ;
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        write(shell->fdout, args[i], ft_strlen(args[i]));
        if (args[i + 1] && args[i][0] != '\0')
            write(shell->fdout, " ", 1);
        i++;
    }
    if (new_line)
        write(shell->fdout, "\n", 1);
}
/* -n se usa en la ft echo para suprimir la nueva línea final que de forma
normal se imprimiría */