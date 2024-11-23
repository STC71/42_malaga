/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:18:14 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 10:28:19 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_err0(char *command, int i)
{
	write(STDERR_FILENO, "export: not an identifier: ", 27);
	while (command[i] != '\0' && command[i] != '=')
		write(STDERR_FILENO, &command[i++], 1);
	write(STDERR_FILENO, "\n", 1);
}

/*  env_err0 function is used to write an error message to the standard output 
    when the export command receives an invalid identifier. It takes the command
    and the index of the invalid character as arguments. It then writes the 
    error message to the standard output.*/

void	env_err1(char *command, int i)
{
	write(STDERR_FILENO, "export: not valid in this context: ", 36);
	while (command[i] != '\0' && command[i] != '=')
		write(STDERR_FILENO, &command[i++], 1);
	write(STDERR_FILENO, "\n", 1);
}

/*  env_err1 function is used to write an error message to the standard output 
    when the export command is not valid in the current context. It takes the 
    command and the index of the invalid character as arguments. It then writes 
    the error message to the standard output.*/

void	env_err2(char *command, int i)
{
	write(STDERR_FILENO, "export: ", 8);
	while (command[i] != '\0' && command[i] != '=')
		i++;
	i++;
	write(STDERR_FILENO, &command[i], 1);
	write(STDERR_FILENO, ": not a valid identifier\n", 26);
}

/*  env_err2 function is used to write an error message to the standard output 
    when the export command receives an invalid identifier. It takes the command
    and the index of the invalid character as arguments. It then writes the 
    error message to the standard output.*/

void	env_err3(void)
{
	write(STDERR_FILENO, "export: not valid in this context", 33);
	write(STDERR_FILENO, "\n", 2);
}

/*  env_err3 function is used to write an error message to the standard output 
    when the export command is not valid in the current context. It then writes 
    the error message to the standard output.*/

/*  The differences between the functions are:
    - env_err0 writes "export: not an identifier: ", the characters of the 
	command until the invalid character, "\n" to the standard output.
    - env_err1 writes "export: not valid in this context: ", the characters of 
	the command until the invalid character, "\n" to the standard output.
    - env_err2 writes "export: ", the character after the invalid character, 
	": not a valid identifier\n" to the standard output.
    - env_err3 writes "export: not valid in this context\n" to the standard 
	output.*/
