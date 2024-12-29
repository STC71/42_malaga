/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:07:48 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:07:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_map_closed(t_data *info)
{
	int	res;

	res = 0;
	if (ft_check_sides(info->map.map))
		res = 1;
	if (res == 1)
		return (FAILURE);
	return (SUCCESS);
}

/*	This function checks if the map is correctly closed on the sides.
	First, it initializes res to 0 and calls the ft_check_sides function to do
	the verification. If the ft_check_sides function returns FAILURE, res is set
	to 1. If res is 1, the function returns FAILURE. If res is 0, the function
	returns SUCCESS.	*/

int	ft_parse(char *cub, t_data *info)
{
	int	fd;
	int	fault_flag;

	fault_flag = 0;
	if (ft_check_cub_ext(cub, &fault_flag))
		return (FAILURE);
	info->file = cub;
	fd = open(cub, O_RDONLY);
	if (fd < 0)
	{
		printf(RED"Opening the map file failed.\n"RESET);
		return (FAILURE);
	}
	if (ft_get_imgs_info(info, &fault_flag, &fd) || ft_get_map(info, fd)
		|| ft_check_map(info))
		fault_flag = 1;
	close(fd);
	ft_get_size_map(&info->map);
	return (fault_flag);
}
/*	The ft_parse function is divided into 3 parts:
	1. The first part is the check of the extension of the file.
	2. The second part is the opening of the file and the parsing of the 
		textures and the map.
	3. The third part is the check of the map.
	After the map is checked, the size of the map is calculated.
*/

int	ft_check_comma(char **c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			if (c[i][j] == ',')
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

/*	This function counts the number of commas in the provided string array c.
	It iterates through the array and counts the number of commas in each string
	adding them up to a total count. It then returns the total number of commas
	found in the array.	It is used to check the format of the color arguments.*/

void	ft_missing_id(t_data *info, int *fd, int i)
{
	ft_new_fd(info, i, fd);
	if (info->textures.c_flag != 1)
		printf(RED"\"C\" identifier is missing\n"RESET);
	if (info->textures.f_flag != 1)
		printf(RED"\"F\" identifier is missing\n"RESET);
	if (info->textures.no_flag != 1)
		printf(RED"\"NO\" identifier is missing\n"RESET);
	if (info->textures.so_flag != 1)
		printf(RED"\"SO\" identifier is missing\n"RESET);
	if (info->textures.we_flag != 1)
		printf(RED"\"WE\" identifier is missing\n"RESET);
	if (info->textures.ea_flag != 1)
		printf(RED"\"EA\" identifier is missing\n"RESET);
}

/*	This function checks for missing identifiers in the map config file. It
	takes a pointer to a t_data structure that contains the game information as
	an argument. The variable i is declared to store the number of missing
	identifiers. If the ceiling color flag is not set, i is incremented. If the
	floor color flag is not set, i is incremented. If the north texture flag is
	not set, i is incremented. If the south texture flag is not set, i is
	incremented. If the west texture flag is not set, i is incremented. If the
	east texture flag is not set, i is incremented. The function returns i which
	is the number of missing identifiers.	*/

int	ft_missing_num(t_data *info)
{
	int	i;

	i = 0;
	if (info->textures.c_flag != 1)
		i++;
	if (info->textures.f_flag != 1)
		i++;
	if (info->textures.no_flag != 1)
		i++;
	if (info->textures.so_flag != 1)
		i++;
	if (info->textures.we_flag != 1)
		i++;
	if (info->textures.ea_flag != 1)
		i++;
	return (i);
}

/*	This function checks for missing identifiers in the map config file. It
	takes a pointer to a t_data structure that contains the game information as
	an argument. The variable i is declared to store the number of missing
	identifiers. If the ceiling color flag is not set, i is incremented. If the
	floor color flag is not set, i is incremented. If the north texture flag is
	not set, i is incremented. If the south texture flag is not set, i is
	incremented. If the west texture flag is not set, i is incremented. If the
	east texture flag is not set, i is incremented. The function returns i which
	is the number of missing identifiers.	*/
