/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-06 10:02:40 by sternero          #+#    #+#             */
/*   Updated: 2024-05-06 10:02:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <string.h>

// We use unistd.h to have access to open, read() and write() functions.
// We use stdlib.h to have access to malloc() and free() functions.
// We use stddef.h to have access to size_t, sizeof, NULL...
// We use fcntl.h to have access to open() and close() functions. O_RDONLY.
// We use stdio.h to have access to printf() function and BUFFER_SIZE.
// We use sys/types.h to have access to ssize_t.
// We use string.h to have access to strdup() function.

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

/* BUFFER_SIZE is the maximum number of bytes to read from the file descriptor.
    If BUFFER_SIZE is not defined, we define it as 4096.*/

//The ft_strlen.c function returns the length of a string.
size_t	ft_len(char *str);

/*The *ft_strchr.c function returns a pointer to the first occurrence of 
the character c in the string str.*/
char	*ft_strchr(char *str, int c);

/*The *ft_strjoin.c function concatenates two strings.*/
char	*ft_strjoin(char *s1, char *s2);

//The *ft_nline.c function returns a new string containing the line of text.
char	*ft_alloc(int fd, char *str);

//the *ft_nline.c function returns a new string containing the line of text.
char	*ft_nline(char *str);

//The *ft_rline.c function returns the rest of the string.
char	*ft_rline(char *line);

/*The get_next_line.c function reads a line from a file descriptor.
	Returns a line read from a file descriptor, without the newline character.
	Returns NULL when the reading fails.
	Returns NULL when the reading is finished.*/

char	*get_next_line(int fd);

#endif
