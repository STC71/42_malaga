/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/02 19:17:50 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void write_exit_toomany_err(t_minishell *shell)
{
    write(STDERR_FILENO, "exit: too many arguments\n", 26);
    shell->g_status = 1;
}

void    write_numeric_err(t_minishell *shell, char **command)
{
    write(STDERR_FILENO, "exit: ", 6);
    write(STDERR_FILENO, command[0], ft_strlen(command[0]));
    write(STDERR_FILENO, ": numeric argument requiered\n", 30);
    shell->g_status = 1;
}

void write_pwd_err(t_minishell *shell)
{
    write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
    write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
    write(STDERR_FILENO, "\n", 2);
    shell->g_status = 1;
}