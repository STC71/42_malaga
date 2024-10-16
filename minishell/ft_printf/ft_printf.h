/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-26 08:27:29 by sternero          #+#    #+#             */
/*   Updated: 2024-04-26 08:27:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*unistd.h - Contains the prototypes of C functions for
input/output operations.*/

/*stdlib.h - Contains the prototypes of C functions for
dynamic memory management, process control, and others.*/

/*stddef.h - is used to define macros like NULL and size_t
NULL: A macro that includes the pointer constant to null.
size_t : Represents the size of objects in memory areas.*/

/*stdarg.h - It allows the definition of functions with a
list of variable arguments, that is, a function where the
number or type of argument they will receive is not known.*/

/*stdint.h - Allow programmers to write more portable code 
by providing a set of typedefs that specify exact-width 
integer types, together with the defined minimum and maximum
allowable values for each type, using macros. (uintptr_t)*/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_flags
{
	int		chr;	//%c - Print one character.
	int		str;	//%s - Print one string.
	int		ptr;	//%p - Print pointer (hexadecimal format)
	int		ndf;	//%d - Print number (decimal format).
	int		nbr;	//%i - Print number (integer).
	int		dns;	//%u - Print number (unsigned decimal).
	int		hxl;	//%x - Print number (hexadecimal format - lowercase).
	int		hxu;	//%X - Print number (hexadecimal format - uppercase).
	int		prs;	//%% - Print percentage sign '%'.
	va_list	args;	//Information about variable arguments.
	/*
	int		wdt;	//wdt - Width.
	int		prc;	//prc - Precision.
	int		zer;	//zer - Zero padding.
	int		len;	//len - Total length.
	int		sig;	//num - pos. or neg.
	int		spc;	//spc - Space ' '
	int		pnt;	//pnt - Point '.'
	int		das;	//das - Dash '-'
	int		per;	//per - Percentage '%'
	int		isz;	//isz - Is number: '0'
	*/
}	t_flags;

/*The ft_printf() function emulates the operation of the
original printf() function.*/
int			ft_printf(char const *str, ...);

/*The ft_strlen() function calculates the length of the
string passed as an argument.*/
size_t		ft_strlen(const char *str);

/* Print one character */
int			ft_write_chr(int chr);

/* Print number (unsigned decimal) */
int			ft_write_dns(unsigned int n);

/* Print number (hexadecimal format - lowercase) */
int			ft_write_hxl(unsigned int n);

/* Print number (hexadecimal format - uppercase)*/
int			ft_write_hxu(unsigned int n);

/* Print number (decimal format - pos. or neg.)  */
int			ft_write_nbr(int n);

/* Print number (decimal format - pos. or neg.)*/
//int			ft_write_ndf(int n);

/* Print pointer (hexadecimal format) */
int			ft_write_ptr(unsigned long long ptr);

/* Print one string */
int			ft_write_str(char *str);

/* Convert the pointer to hexadecimal format */
//static char		*ft_write_ptr_to_hex(unsigned long long ptr);

/* Convert the pointer to string */
//static void	ft_write_ptr_to_str(unsigned long long n, char *str, int bas);

/* Select the flag to be used based on the character passed as an argument */
//void		vs_start(va_list arg, const char *str);

#endif
