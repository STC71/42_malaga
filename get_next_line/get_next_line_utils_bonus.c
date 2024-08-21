/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-06 10:04:01 by sternero          #+#    #+#             */
/*   Updated: 2024-05-06 10:04:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *str1, char *str2)
{
	size_t		i;
	size_t		j;
	char		*out;

	if (!str1)
	{
		str1 = (char *)malloc(sizeof(char) * 1);
		str1[0] = '\0';
	}
	if (!str2)
		return (NULL);
	out = (char *)malloc(sizeof(char) * (ft_len(str1) + ft_len(str2) + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		out[j++] = str1[i++];
	i = 0;
	while (str2[i])
		out[j++] = str2[i++];
	out[j] = '\0';
	free(str1);
	return (out);
}

char	*ft_alloc(int fd, char *str)
{
	char	*buff;
	ssize_t	dim;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	dim = 1;
	while (!(ft_strchr(str, '\n')) && dim > 0)
	{
		dim = read(fd, buff, BUFFER_SIZE);
		if (dim == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[dim] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_nline(char *str)
{
	char	*new;
	ssize_t	i;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_rline(char *line)
{
	char	*str;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_len(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

/*The function ft_strjoin concatenates two strings str1 and str2. 
	It allocates memory for the resulting string (out) based on the lengths 
	of str1 and str2, plus one additional byte for the null-terminator. 
	If str1 is NULL, it allocates memory for an empty string. 
	If str2 is NULL, it returns NULL. Then, it copies the characters of 
	str1 and str2 into out sequentially. Finally, it terminates out with 
	a null character, frees the memory allocated for str1, and returns out.*/

/*The function ft_alloc reads from the file descriptor fd and stores the
	read data in the buffer buff. It allocates memory for buff based on 
	BUFFER_SIZE. If the allocation fails, it returns NULL. It reads from 
	fd into buff until either a newline character is found in str or the 
	read data is empty. It concatenates the read data into str using 
	ft_strjoin. If the read fails, it frees buff and returns NULL. 
	Finally, it frees buff and returns str.*/

/*The function ft_nline returns a new string containing the line of text
	from str. It allocates memory for new based on the length of the line 
	of text in str plus two bytes (one for the newline character and one 
	for the null-terminator). If the allocation fails, it returns NULL. 
	It copies the characters from str into new until a newline character 
	is encountered. If a newline character is found, it copies it into 
	new and increments the index. Finally, it terminates new with a 
	null character and returns it.*/

/*The function ft_rline returns the rest of the string after the newline
	character in line. It allocates memory for str based on the length of 
	the rest of the string in line plus one byte for the null-terminator. 
	If the allocation fails, it returns NULL. It finds the index of the 
	newline character in line. If no newline character is found, it frees 
	line and returns NULL. It copies the characters after the newline 
	character into str. Finally, it terminates str with a null character, 
	frees line, and returns str.*/