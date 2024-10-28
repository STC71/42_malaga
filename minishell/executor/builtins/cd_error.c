/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:45:15 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_err(t_minishell *shell)
{
    
	write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

void	write_backpwd_err(char *back_path, t_minishell *shell)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 31);
	write(STDERR_FILENO, back_path, ft_strlen(back_path));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

void 	write_cdhome_error(char *home_path, t_minishell *shell)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 29);
	write(STDERR_FILENO, home_path, ft_strlen(home_path));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

void write_too_many_args(t_minishell *shell)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 23);
	shell->g_status = 1;
}

void write_oldpwd_error(t_minishell *shell)
{
	write(STDERR_FILENO, "cd: OLDPWD not set\n", 20);
	shell->g_status = 1;
}