/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 12:51:29 by sternero          #+#    #+#             */
/*   Updated: 2024-09-17 12:51:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H         // If the GET_NEXT_LINE_H is not defined
# define GET_NEXT_LINE_H        // Define the GET_NEXT_LINE_H

# include <unistd.h>            // Include the read function
# include <stdlib.h>	        // Include the malloc and free functions
# include <stdio.h>             // Include the printf function and NULL
# include <fcntl.h>             // Include the open and close functions

# ifndef BUFFER_SIZE            // Define the buffer size if not already defined
#  define BUFFER_SIZE 42        // Set the buffer size to 42 by default
# endif                         // End of the BUFFER_SIZE definition

#endif                          // End of the GET_NEXT_LINE_H definition
