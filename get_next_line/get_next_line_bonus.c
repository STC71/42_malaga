/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-06 10:01:39 by sternero          #+#    #+#             */
/*   Updated: 2024-05-06 10:01:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_len(str)]);
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	*str[4096];

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) == -1)
	{
		free (str[fd]);
		str[fd] = (NULL);
		return (NULL);
	}
	str[fd] = ft_alloc(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	out = ft_nline(str[fd]);
	str[fd] = ft_rline(str[fd]);
	return (out);
}

// int main(int argc, char **argv)
// {
//     int *fds;
//     char **lines;
//     int i;
//     int files_remaining;

//     if (argc < 2)
//     {
//         printf("Usage: %s file1 file2 ...\n", argv[0]);
//         return 1;
//     }

//     fds = malloc((argc - 1) * sizeof(int));
//     lines = malloc((argc - 1) * sizeof(char *));
//     if (!fds || !lines)
//     {
//         perror("malloc");
//         return 1;
//     }
//     i = 0;
//     while (i < argc - 1)
//     {
//         fds[i] = open(argv[i + 1], O_RDONLY);
//         if (fds[i] == -1)
//         {
//             perror("open");
//             return 1;
//         }
//         lines[i] = get_next_line(fds[i]);
//         i++;
//     }
//     files_remaining = argc - 1;
//     while (files_remaining > 0)
//     {
//         files_remaining = 0;
//         i = 0;
//         while (i < argc - 1)
//         {
//             if (lines[i])
//             {
//                 printf("%s\n", lines[i]);
//                 free(lines[i]);
//                 lines[i] = get_next_line(fds[i]);
//                 if (lines[i])
//                 {
//                     files_remaining++;
//                 }
//             }
//             i++;
//         }
//     }
//     i = 0;
//     while (i < argc - 1)
//     {
//         close(fds[i]);
//         i++;
//     }
//     free(fds);
//     free(lines);
//     return 0;
// }

/*
To compile the program, run the following command:
	gcc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
To run the program, run the following command:
	./gnl_bonus file1 file2 ...
	./gnl_bonus txt01.txt txt02.txt txt 03.txt
Replace file1, file2, etc. with the names of the files you want to read.
The program reads lines from the files and prints them to the standard output.
*/
/*The function ft_len calculates the length of a null-terminated 
	string str. It iterates through the characters of str until 
	it encounters the null terminator ('\0'), counting each character 
	encountered. If str is NULL, indicating an empty string, it returns 0. 
	Finally, it returns the total count of characters encountered, 
	excluding the null terminator.*/

/*The function ft_strchr searches for the first occurrence of the
	character c in the null-terminated string str. It iterates through 
	the characters of str until it encounters the null terminator ('\0'). 
	For each character encountered, it compares the character to c. 
	If the character matches c, it returns a pointer to the character 
	in str. If c is the null terminator, it returns a pointer to the 
	null terminator in str. If c is not found in str, it returns NULL.*/

/*The function get_next_line reads a line from the file descriptor fd.
	It checks if BUFFER_SIZE is valid, if fd is valid, and if the read 
	operation fails. It then reads from fd into the static variable str 
	associated with fd. If the read operation fails, it frees the memory 
	allocated for str and returns NULL. It then extracts a line of text 
	from str using ft_nline and updates str with the remaining text 
	using ft_rline. Finally, it returns the line of text read from fd.*/
