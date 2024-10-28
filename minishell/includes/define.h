/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:49:59 by sternero          #+#    #+#             */
/*   Updated: 2024/10/26 14:05:14 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2
// STDIN_FILENO = Standard Input File Descriptor. 
// Used to read input from the keyboard.
// STDOUT_FILENO = Standard Output File Descriptor.
// Used to write output to the screen.
// STDERR_FILENO = Standard Error File Descriptor.
// Used to write error messages to the screen.

# define _XOPEN_SOURCE \
    700 // Used to define the version of the X/Open Portability Guide.
        // and to enable the use of certain functions.

# define SUCCESS 0
# define FAILURE 1
// Used to gestion errors in the main function.

# define SHELL_NAME "minishell"
# define SHELL_PROMPT "minishell$ "
// SHELL_NAME = Name of the shell. Used to print the name of the program.
// SHELL_PROMPT = Prompt of the shell. Used to print the prompt of the program.
// prompt: command line, command prompt, prompt string...

# define DQ_OPEN 1
# define SQ_OPEN 2
# define NO_QUOTE 0
// DQ_OPEN = Double Quote Open. Used to gestion the double quotes.
// SQ_OPEN = Single Quote Open. Used to gestion the single quotes.
// NO_QUOTE = No Quote. Used to gestion the absence of quotes.
// quotes: cite, call...

# define PATH_MAX 4096

#endif