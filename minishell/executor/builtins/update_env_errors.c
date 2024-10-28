/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:18:14 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:47:03 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    env_err0(char *command, int i)
{
        write(STDERR_FILENO, "export: not an identifier: ", 27);
        while (command[i] != NULL && command[i] != '=')
            write(STDERR_FILENO, &command[i++], 1);
        write(STDERR_FILENO, "\n", 1);
}

void    env_err1(char *command, int i)
{
        write(STDERR_FILENO, "export: not valid in this context: ", 36);
        while (command[i] != NULL && command[i] != '=')
            write(STDERR_FILENO, &command[i++], 1);
        write(STDERR_FILENO, "\n", 1);
}

void    env_err2(char *command, int i)
{
        write(STDERR_FILENO, "export: ", 8);
        while (command[i] != NULL && command[i] != '=')
            i++;
        i++;
        write(STDERR_FILENO, &command[i], 1);
        write(STDERR_FILENO, ": not a valid identifier\n", 26);
}

void    env_err3(char *command)
{
        write(STDERR_FILENO, "export: not valid in this context", 33);
        write(STDERR_FILENO, "\n", 2);
}
