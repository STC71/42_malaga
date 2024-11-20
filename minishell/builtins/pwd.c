/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/02 19:17:50 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_pwd(t_shell *shell)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (write_pwd_err(shell));
	write(shell->fdout, cwd, ft_strlen(cwd));
	write(shell->fdout, "\n", 2);
}

/*	ft_pwd function is used to print the current working directory to the 
	standard output. It uses getcwd to get the current working directory and 
	then writes it to the standard output. If getcwd fails, it writes an error 
	message to the standard output.*/