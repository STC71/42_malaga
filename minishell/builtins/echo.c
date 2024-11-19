/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/09 12:36:23 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Imprime en stdout los argumentos que recibe */

void ft_echo(char **args, t_shell *shell)
{
    int i;
    int j;
    int new_line;

    i = 0;
    j = 1;
    new_line = 1;
    if (!args[i]) // a;ado esto para que si no hay argumentos imprima un salto de linea
    {
        write(shell->fdout, "\n", 1);
        return ;
    }
    if (args[i])
    {    
        if (args[i][0] == '-' && args[i][1] == 'n' && args[i])
        {    
            while (args[i][j] == 'n')
                j++;
            // esta parte del codigo se tiene que hacer en una funcionexterna pq se llama 2 veces 
            if (args[i][j] != '\0') 
            {
                while (args[i])
                {
                    write(shell->fdout, args[i], ft_strlen(args[i]));
                    if (args[i + 1] && args[i][0] != '\0')
                        write(shell->fdout, " ", 1);
                    i++;
                    if (new_line)
                        write(shell->fdout, "\n", 1);
                }
                return ;
            }        
            new_line = 0;
            i++;
        }
    }
    // llamar a la funcion externa q contenga este codigo de abajo
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