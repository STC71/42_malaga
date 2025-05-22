/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_alen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 10:01:22 by sternero          #+#    #+#             */
/*   Updated: 2025-03-28 10:01:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int count_alen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'a')
			return (i);
		i++;
	}
	return (i);
}

// #include <stdio.h>
// int main(){
// 	char *str = "ZzAAAAAaa";
// 	printf("%d\n", count_alen(str));
// 	return 0;
// }