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

#include "../includes/minishell.h"

void	write_cd_err(t_shell *shell)
{
	
	write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

/*	The write_cd_err() function prints an error message to the standard error 
	output and returns a failure status, which is 1, if an error occurs while 
	retrieving the current directory. It recives a pointer to the shell 
	structure.
	This function provides a clear and informative error message to the user 
	when an	error occurs while retrieving the current directory.
	STDERR_FILENO, "pwd: error retrieving current directory: ", 
		41 -> file descriptor for standard error output.
	STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)) 
		-> prints the error message.
	STDERR_FILENO, "\n", 2 -> prints a new line.
	Status Code: Setting the g_status to 1 is a standard way to indicate 
		an error.
	Return Value: The function returns 1 to signal that an error occurred, 
		which can be used for further error handling or reporting. */

void	write_backpwd_err(char *back_path, t_shell *shell)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 31);
	write(STDERR_FILENO, back_path, ft_strlen(back_path));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

/*	The write_backpwd_err() function prints an error message to the standard 
	error output and returns a failure status, which is 1, if the path does 
	not exist. It recives a pointer to the shell structure and a pointer to 
	the path.
	This function provides a clear and informative error message to the user 
	when the path does not exist.
	STDERR_FILENO, "cd: no such file or directory: ", 31 -> file descriptor 
		for standard error output.
	STDERR_FILENO, back_path, ft_strlen(back_path) -> prints the path.
	STDERR_FILENO, "\n", 2 -> prints a new line.
	Status Code: Setting the g_status to 1 is a standard way to indicate an 
		error.
	Return Value: The function returns 1 to signal that an error occurred, 
		which can be used for further error handling or reporting. */

void 	write_cdhome_error(char *home_path, t_shell *shell)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 29);
	write(STDERR_FILENO, home_path, ft_strlen(home_path));
	write(STDERR_FILENO, "\n", 2);
	shell->g_status = 1;
}

/*	The write_cdhome_error() function prints an error message to the standard 
	error output and returns a failure status, which is 1, if the path does 
	not exist. It recives a pointer to the shell structure and a pointer to 
	the path.
	This function provides a clear and informative error message to the user 
	when the path does not exist.
	STDERR_FILENO, "cd: no such file or directory: ", 29 -> file descriptor 
		for standard error output.
	STDERR_FILENO, home_path, ft_strlen(home_path) -> prints the path.
	STDERR_FILENO, "\n", 2 -> prints a new line.
	Status Code: Setting the g_status to 1 is a standard way to indicate an 
		error.
	Return Value: The function returns 1 to signal that an error occurred, 
		which can be used for further error handling or reporting. */

void write_too_many_args(t_shell *shell)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 23);
	shell->g_status = 1;
}

/*	The write_too_many_args() function prints an error message to the standard 
	error output and returns a failure status, which is 1, if there are too 
	many arguments. It recives a pointer to the shell structure.
	This function provides a clear and informative error message to the user 
	when there are too many arguments.
	STDERR_FILENO, "cd: too many arguments\n", 23 -> file descriptor for 
		standard error output.
	Status Code: Setting the g_status to 1 is a standard way to indicate an 
		error.
	Return Value: The function returns 1 to signal that an error occurred, 
		which can be used for further error handling or reporting. */

void write_oldpwd_error(t_shell *shell)
{
	write(STDERR_FILENO, "cd: OLDPWD not set\n", 20);
	shell->g_status = 1;
}

/*	The write_oldpwd_error() function prints an error message to the standard 
	error output and returns a failure status, which is 1, if the OLDPWD 
	environment variable is not set. It recives a pointer to the shell 
	structure.
	This function provides a clear and informative error message to the user 
	when the OLDPWD environment variable is not set.
	STDERR_FILENO, "cd: OLDPWD not set\n", 20 -> file descriptor for standard 
		error output.
	Status Code: Setting the g_status to 1 is a standard way to indicate an 
		error.
	Return Value: The function returns 1 to signal that an error occurred, 
		which can be used for further error handling or reporting. */
