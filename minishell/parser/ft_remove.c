/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 18:51:58 by sternero          #+#    #+#             */
/*   Updated: 2024-10-03 18:51:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_spcs(char *str)
{
	int	i;

	if (str == NULL)
		return ;
	i = ft_strlen(str);
	while (i > 0 && str[i - 1] == ' ')
		i--;
	str[i] = '\0';
}
