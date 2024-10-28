/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:21:11 by sternero          #+#    #+#             */
/*   Updated: 2024/10/27 13:25:26 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -------------------------- Includes system ------------------------------- //

# include <dirent.h>                       // Directory entries
# include <errno.h>                        // Error numbers
# include <fcntl.h>                        // File control options
# include <readline/history.h>             // History for readline
# include <readline/readline.h>            // Readline library
# include <signal.h>                       // Signal handling
# include <stdio.h>                        // Standard input/output 
# include <sys/types.h>                    // System types
# include <sys/wait.h>                     // Wait for process to change state
# include <termios.h>                      // Terminal I/O interface
# include <unistd.h>                       // Symbolic constants and types
# include <stddef.h>                       // Standard definitions

// -------------------------- Includes own ---------------------------------- //

# include "colors.h"                       // Colors for the prompt
# include "define.h"                       // Defines for the project
# include "structures.h"                   // Structures for the project
# include "functions.h"                    // Functions for the project
# include "messages.h"                     // Messages for the project
# include "../libft/libft.h"               // Libft library
# include "../ft_printf/ft_printf.h"       // Ft_printf library

#endif
