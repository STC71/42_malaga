/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-25 11:27:39 by sternero          #+#    #+#             */
/*   Updated: 2024-08-25 11:27:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>         // for write

int main(int argc, char *argv[])
{
	int start;              // start of the word
	int end;                // end of the word
	int i = 0;              // index to iterate through the string
		
	if(argc == 2)
	{   
		while(argv[1][i] != '\0')
			i++;
        // For the string "Hello world, from 42 Málaga" i = 29 
		while(i >= 0)
		{
			while( argv[1][i] == '\0' || argv[1][i] == ' ' || argv[1][i] == '\t')
				i--;        // skip spaces, tabs and null characters
			end = i;        // end =
			while(argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
				i--;
			start = i + 1;
			int  flag;
			flag = start;
			while(start <= end)
			{
				write (1, &argv[1][start],1);
				start++;		
			}
			if (flag !=0)
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}