/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024/11/12 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_format
{
	char	specifier;
	int		left_align;
	int		zero_pad;
	int		alt_form;
	int		force_sign;
	int		space_sign;
	int		min_width;
	int		precision;
	int		has_precision;
}	t_format;

int		ft_printf(const char *format, ...);
int		ft_parse_format(const char *s, int *pos, t_format *fmt, va_list *ap);
int		ft_dispatch(t_format fmt, va_list *ap);
int		ft_putchar_cnt(char c);
int		ft_putstr_cnt(char *str, int max_len);
int		ft_putnbr_base(long long n, char *base, t_format fmt);
int		ft_putunsigned(unsigned long long n, char *base, t_format fmt);
int		ft_putptr(void *ptr, t_format fmt);
size_t	ft_strlen(const char *s);
int		ft_numlen_base(long long n, int base);
int		ft_unumlen_base(unsigned long long n, int base);
void	ft_putpad(char c, int count);
int		ft_isdigit(int c);
int		ft_atoi_skip(const char *s, int *i);
void	parse_flags(const char *s, int *i, t_format *fmt);
void	parse_width_precision(const char *s, int *i,
			t_format *fmt, va_list *ap);

#endif
