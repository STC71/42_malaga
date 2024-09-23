/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-13 14:06:30 by sternero          #+#    #+#             */
/*   Updated: 2024-04-13 14:06:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h> 	// for ssize_t, size_t, NULL, write, read, etc.
# include <stdlib.h> 	// for malloc, free, exit, NULL, size_t, ssize_t, etc.
# include <stddef.h> 	// for NULL, size_t, etc.
# include <fcntl.h>  	// for open, close, etc.
# include <stdio.h>  	// for printf, BUFER_SIZE, etc
# include <string.h>	// for strdup, strlen, etc.
# include <sys/types.h> // for ssize_t, size_t, etc.

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list // The structure 's_list' is defined as a structure.
{
	void			*content;
	/* The next element of the list. NULL if it is the last element.*/
	struct s_list	*next;
	/* The previous element of the list. NULL if it is the first element.*/
}	t_list; // The variable type 't_list' is defined as a structure.

/*The isalpha() function tests for any character for which isupper(3) or
	islower(3) is true.  The value of the argument must be representable as
	an unsigned char or the value of EOF.*/
int		ft_isalpha(int c);

/*The isdigit() function tests for a decimal digit character.  Regardless
	of locale, from '0' to '9'*/
int		ft_isdigit(int c);

/*The isalnum() function tests for any character for which isalpha(3) or
	isdigit(3) is true.  The value of the argument must be representable as
	an unsigned char or the value of EOF.*/
int		ft_isalnum(int c);

/*The isascii() function tests for an ASCII character, which is any charac-
	ter between 0 and octal 0177 inclusive.*/
int		ft_isascii(int c);

/*The isprint() function tests for any printing character, including space.
	The value of the argument must be representable as an unsigned char or 
	the value of EOF.*/
int		ft_isprint(int c);

/*The strlen() function computes the length of the string s.*/
size_t	ft_strlen(const char *str);

/*The strchr() function locates the first occurrence of c (converted to a
	char) in the string pointed to by s.*/
char	*ft_strchr(const char *str, int c);

/*The tolower() function converts an upper-case letter to the corresponding
	lower-case letter.  The argument must be representable as an unsigned
	char.*/
int		ft_tolower(int c);

/*The toupper() function converts a lower-case letter to the corresponding
	upper-case letter.  The argument must be representable as an unsigned
	char.*/
int		ft_toupper(int c);

/*The strchr() function locates the first occurrence of c (converted to a
	char) in the string pointed to by s. The strrchr() function is 
	identical to strchr(), except it locates the last occurrence of c.*/
char	*ft_strrchr(const char *str, int c);

/*The strcmp() and strncmp() functions lexicographically compare the 
	null-terminated strings s1 and s2.*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*The memchr() function locates the first occurrence of c (converted 
	to an unsigned char) in string s.*/
void	*ft_memchr(const void *s, int c, size_t n);

/*The memcmp() function compares byte string s1 against byte string s2.  
	Both strings are assumed to be n bytes long.*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*The strnstr() function locates the first occurrence of the null-termi-
	nated string needle in the string haystack, where not more than len char-
	acters are searched.  Characters that appear after a `\0' character are
	not searched.*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*The atoi() function converts the initial portion of the string pointed to
	by str to int representation.*/
int		ft_atoi(const char *str);

/*The memset() function writes len bytes of value c (converted to an unsigned
	char) to the string b. The memset() function returns its first argument*/
void	*ft_memset(void *dest, int c, size_t len);

/*The bzero() function writes n zeroed bytes to the string s.  If n is
	zero, bzero() does nothing.*/
void	ft_bzero(void *s, size_t n);

/*strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
	NUL-terminating the result if dstsize is not 0.*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*strlcat() appends string src to the end of dst.  It will append at most 
    dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, 
    unless dstsize is 0 or the original dst string was longer than dstsize
    (in practice this should not happen as it means that either dstsize 
    is incorrect or that dst is not a*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/*The memcpy() function copies n bytes from memory area src to memory area dst.
    If dst and src overlap, behavior is undefined.  Applications in which dst
    and src might overlap should use memmove(3) instead.*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*The memmove() function copies len bytes from string src to string dst.  
    The two strings may overlap; the copy is always done in a non-destructive
    manner. The memmove() function returns the original value of dst.*/
void	*ft_memmove(void *dst, const void *src, size_t len);

/*The calloc() function contiguously allocates enough space for count objects 
 	that are size bytes of memory each and returns a pointer to the allocated
	memory.  The allocated memory is filled with bytes of value zero. This 
	function return a pointer to allocated memory.*/
void	*ft_calloc(size_t count, size_t size);

/*The strdup() function allocates sufficient memory for a copy of the string
	s1, does the copy, and returns a pointer to it.*/
char	*ft_strdup(const char *s1);

/*Reserve (with malloc(3)) and return a substring of the string 's'.
	The substring starts from the index 'start' and has a maximum length 
	'len'.*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*Reserve (with malloc(3)) and return a new string, formed by the 
	concatenation of 's1' and 's2'. 
	's1': the first string.
	's2': the string to add to 's1'.
	Return: the new string 'res' or 'NULL' if memory reservation fails.*/
char	*ft_strjoin(char const *s1, char const *s2);

/*Remove all characters from the string 'set' from the beginning and from 
	the end of 's1', until find a character not belonging to 'set'. The
	resulting string is returned with a reservation of malloc, or 'NULL'.*/
char	*ft_strtrim(char const *s1, char const *set);

/*Reserve (using malloc(3)) an array of strings resulting from separating 
	the string 's' into substrings using the character 'c' as a delimiter. 
	the array must be terminated with a NULL pointer.*/
char	**ft_split(char const *s, char c);

/*Using malloc(3), generate a string that represent the integer value 
	received as an argument. Negative numbers have to be managed. 
	n: the integer to convert. Return value: the string representing the 
	number or NULL if the memory reservation fails.*/
char	*ft_itoa(int n);

/*To each character of the string 's', apply the function 'f' giving as 
	parameters the index of each character inside 's' and the character
	itself. Generate a new string with the result of successive use
	of 'f'. Parameters -> s: The string to iterate, f: The function to 
	apply on each character. Return value: the string created after the
	correct use of 'f' over each character or NULL if memory reservation
	fails.*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*Applies the function f to each character of the string passed as argument, 
    and passing its index as first argument. Each character is passed by 
    address to f to be modified if necessary.*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*Outputs the character c to the given file descriptor.*/
void	ft_putchar_fd(char c, int fd);

/*Outputs the string s to the given file descriptor.*/
void	ft_putstr_fd(char *s, int fd);

/*Send the string 's' to the given file descriptor, followed by a line break.*/
void	ft_putendl_fd(char *s, int fd);

/*Outputs the integer 'n' to the given file descriptor.*/
void	ft_putnbr_fd(int n, int fd);

/*Create a new node using malloc(3). The member variable 'content' is 
	initialized with the content of the 'content' parameter. The variable
	'next', with NULL. Content parameter: the content with which to create 
	the node. Return value: the new node*/
t_list	*ft_lstnew(void *content);

/*Add the 'new' node to the beginning of the 'lst' list.
	lst: the address of a pointer to the first node a list. 
	new: a pointer to the node to add to the beginning of the list.*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/*Counts the number of nodes in a list. 
	lst parameters: the beginning of the list. 
	Return value: The length of the list.*/
int		ft_lstsize(t_list *lst);

/*Returns the last node in the list.
	lst parameters: the beginning of the list.
	Return value: Last node in the list.*/
t_list	*ft_lstlast(t_list *lst);

/*Add the 'new' node to the end of the 'lst' list.
	lst: The pointer to the first node in a list.
	new: The pointer to a node to add to the list.
	Return value Nothing*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/*Takes an 'lst' node as a parameter and releases the memory of the content 
	using the 'del' function given as a parameter, in addition to releasing 
	the node. The 'next' memory should not be freed. Parameters lst: the 
	node to release. del: a pointer to the function used to release the 
	content of the node.*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/*Delete and free the given 'lst' node and all consecutive of that node, using
	the function 'del' and free(3). In the end, the pointer to the list must 
	be NULL. Parameters lst: The address of a pointer to a node. del: a 
	function pointer used to delete the content of a node.*/
void	ft_lstclear(t_list **lst, void (*del)(void*));

/*Iterates the list 'lst' and applies the function 'f' to the content of each
	node. Parameters lst: the address of a pointer to a node. f: the address 
	of the function to apply to each node's content.*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*Iterates the list 'lst' and applies the function 'f' to it content of each 
    node. Create a resulting list of the correct and successive application of 
    the function 'f' over each node. The 'del' function is used to delete the 
    contents of a node, if you do lack. Parameters lst: a pointer to a node.
    f: the address of a pointer to a function used in the iteration of each 
    list element. del: a function pointer used to delete the contents of a 
    node, if necessary.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*The get_next_line.c function reads a line from a file descriptor.
	Returns a line read from a file descriptor, without the newline character.
	Returns NULL when the reading fails.
	Returns NULL when the reading is finished.*/

/*The ft_len function returns the length of the string.*/
size_t	ft_len(char *str);

/*The *ft_gnlstrchr function returns a pointer to the first occurrence of 
the character c in the string str.*/
char	*ft_gnlstrchr(char *str, int c);

/*The *ft_gnlstrjoin function concatenates two strings.*/
char	*ft_gnlstrjoin(char *s1, char *s2);

//The *ft_alloc.c function allocates memory for the string.
char	*ft_alloc(int fd, char *str);

//the *ft_nline.c function returns a new string containing the line of text.
char	*ft_nline(char *str);

//The *ft_rline.c function returns the rest of the string.
char	*ft_rline(char *line);

/*The get_next_line.c function reads a line from a file descriptor.*/
char	*get_next_line(int fd);

#endif