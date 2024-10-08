/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 14:21:11 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 14:21:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -------------------------- Includes own ---------------------------------- //

# include "colors.h"                       // Colors for the prompt
# include "define.h"                       // Defines for the project
# include "functions.h"                    // Functions for the project
# include "messages.h"                     // Messages for the project
# include "structures.h"                   // Structures for the project
# include "../libft/libft.h"               // Libft library

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

#endif
