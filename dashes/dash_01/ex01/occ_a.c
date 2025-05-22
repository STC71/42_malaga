/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occ_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 09:50:56 by sternero          #+#    #+#             */
/*   Updated: 2025-03-28 09:50:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int occ_a(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;

	while (str[i])
	{
		if (str[i] == 'A')
			count++;
		i++;
	}
	return (count);
}

// #include <stdio.h>
// int main(){
// 	char *str = "ZzAaa";
// 	printf("%d\n", occ_a(str));
// 	return 0;
// }