/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-03 17:11:55 by sternero          #+#    #+#             */
/*   Updated: 2024-05-03 17:11:55 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_gnlstrchr(char *str, int c)
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
	static char	*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) == -1)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	str = ft_alloc(fd, str);
	if (!str)
		return (NULL);
	out = ft_nline(str);
	str = ft_rline(str);
	return (out);
}

/*int main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (1);
		line = get_next_line(fd);
		while (line)
		{
			printf("%s\n", line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		close(fd);
	}
	return (0);
}*/

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
