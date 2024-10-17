/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-15 17:46:32 by sternero          #+#    #+#             */
/*   Updated: 2024-10-15 17:46:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_mem_alloc(t_cmd **cmds, char **split_cmd)
{
    int     i;
    int     n_cmd;

    i = 0;
    n_cmd = 0;
    n_cmd = ft_num_pipes(split_cmd);
    while (i < n_cmd)
    {
        cmds[i] = ft_calloc(1, sizeof(t_cmd));
        cmds[i]->cmd = NULL;
        ft_mem_args(cmds[i], split_cmd);
        ft_mem_in(cmds[i], split_cmd);      
        ft_mem_out(cmds[i], split_cmd);
        i++;
    }
}

/* Esta función asigna memoria para los comandos. Toma dos argumentos: un array
    de estructuras t_cmd y un array de strings. Los usa para asignar memoria a
    los comandos, los argumentos, las redirecciones de entrada y las redirecciones
    de salida. */

void    ft_mem_args(t_cmd *cmd, char **split_cmd)
{
    int     i;
    int     n_args;

    i = 0;
    n_args = 0;
    while (split_cmd[i] && strcmp(split_cmd[i], "|") != 0)
    {
        if (i > 0)
        {
            if (strcmp(split_cmd[i], ">" == 0) || strcmp(split_cmd[i], ">>") 
                == 0 || strcmp(split_cmd[i], "<") == 0)
                i+=2;
            else
            {
                i++;
                n_args++;
            }  
        }

    }
}

/* Esta función asigna memoria para los argumentos del comando. Toma dos argumentos:
    un puntero a una estructura t_cmd y un array de strings. Los usa para asignar
    memoria a los argumentos del comando. */

void    ft_mem_out(t_cmd *cmd, char **split_cmd)
{
    int     i;
    int     n_out;

    i = 0;
    n_out = 0;
    while (split_cmd[i] && strcmp(split_cmd[i], "|") != 0)
    {
        if (strcmp(split_cmd[i], ">") == 0 || strcmp(split_cmd[i], ">>") == 0)
        {
            i++;
            n_out++;
            if (split_cmd[i])
            {
                i++;
                n_out++;
            }
        }
        else
            i++;
    }
}

/* Esta función asigna memoria para el comando de redirección de salida. Toma dos
    argumentos: un puntero a una estructura t_cmd y un array de strings. Los usa
    para asignar memoria al comando de redirección de salida. */

void    ft_mem_in(t_cmd *cmd, char **split_cmd)
{
    int     i;
    int     n_in;

    i = 0;
    n_in = 0;
    while (split_cmd[i] && strcmp(split_cmd[i], "|") != 0)
    {
        if (strcmp(split_cmd[i], "<") == 0)
        {
            i++;
            n_in++;
            if (split_cmd[i])
            {
                i++;
                n_in++;
            }
        }
        else
            i++;
    }
}

/* Esta función asigna memoria para el comando de redirección de entrada. Toma dos
    argumentos: un puntero a una estructura t_cmd y un array de strings. Los usa
    para asignar memoria al comando de redirección de entrada. */

/* ft_mem_alloc function allocates memory for the commands. It takes two
    arguments: an array of t_cmd structures and an array of strings. It is used
    to allocate memory for the commands, the arguments, the input redirection
    command, and the output redirection command. */

/* ft_mem_args function allocates memory for the arguments of the command. It
    takes two arguments: a pointer to a t_cmd structure and an array of strings.
    It is used to allocate memory for the arguments of the command. */

/* ft_mem_out function allocates memory for the output redirection command. It
    takes two arguments: a pointer to a t_cmd structure and an array of strings.
    It is used to allocate memory for the output redirection command. */

/* ft_mem_in function allocates memory for the input redirection command. It
    takes two arguments: a pointer to a t_cmd structure and an array of strings.
    It is used to allocate memory for the input redirection command. */