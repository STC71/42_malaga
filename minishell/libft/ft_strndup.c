/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:21:41 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/27 14:24:43 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s1, size_t n)
{
    size_t len;
    char *s2;

    len = strnlen(s1, n);

    s2 = (char *)malloc((len + 1) * sizeof(char));
    if (s2 == NULL)
        return NULL;

    strncpy(s2, s1, len);
    s2[len] = '\0';

    return s2;
}