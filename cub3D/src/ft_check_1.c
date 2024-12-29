/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:03:15 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:03:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_map(t_data *data)
{
	int	flag;

	flag = 0;
	if (!data || !data->map.map)
		return (FAILURE);
	if (ft_check_first_last(data, data->map.map)
		|| ft_check_map_closed(data) || ft_check_inside(data->map.map)
		|| ft_check_spaces(data->map.map) || ft_players_num(data->map.map))
		flag = 1;
	if (flag == 1)
		return (FAILURE);
	return (SUCCESS);
}
/*	The ft_check_map function is divided into 6 parts:
	1. statement checks if the map is NULL.
	2. check of the header and the footer of the map.
	2. check of the map being closed.
	3. check of the middle lines of the map.
	4. check of the spaces in the map.
	5. check of the number of players in the map.
	If any of the checks fail, the function returns FAILURE.
*/

void	ft_check_angles(double *ang, double i)
{
	*ang += i;
	if (*ang > 359)
		*ang = 0;
	if (*ang < 0)
		*ang = 359;
}

/*	This function adjusts an angle by adding a variation and ensures that the
	resulting angle is within the range of 0 to 359. If the resulting angle is
	greater than 359, the angle is adjusted to 0. If the resulting angle is less
	than 0, the angle is adjusted to 359.
	Suppose the current angle is 350 degrees and we want to add 20 degrees. The
	result would be 370 degrees, but since the range is from 0 to 359, the angle
	is adjusted to 0 degrees. If the current angle is 10 degrees and we want to
	subtract 20 degrees, the result would be -10 degrees, but since the range is
	from 0 to 359, the angle is adjusted to 0 degrees again.
	In short, this function ensures that any adjustment to the angle remains
	within the range of 0 to 359, preventing the angle from going out of this
	range and normalizing the angle to be valid within a full circle.	*/

bool	ft_check_valid_mov(t_data *info, double mov_x, double mov_y)
{
	int	check_x;
	int	check_x2;
	int	check_y;
	int	check_y2;

	check_x = (int)floor((info->player.pos_x + 0.25) + (mov_x / 64));
	check_x2 = (int)floor((info->player.pos_x - 0.25) + (mov_x / 64));
	check_y = (int)floor((info->player.pos_y + 0.25) + (mov_y / 64));
	check_y2 = (int)floor((info->player.pos_y - 0.25) + (mov_y / 64));
	if (info->map.map[check_y][check_x] == '1')
		return (0);
	if (info->map.map[check_y2][check_x] == '1')
		return (0);
	if (info->map.map[check_y][check_x2] == '1')
		return (0);
	if (info->map.map[check_y2][check_x2] == '1')
		return (0);
	return (1);
}

/*	The ft_check_valid_mov function is to check if the player can move to the 
	next position. If the player can move, the function returns 1. If not, the 
	function returns 0.	
	The value 0.25 is used to add a small margin around the player position. 
	This margin helps to check if the player is close to a wall, even if it is 
	not exactly in the center of a map cell.
	The value 64 is used to convert the player movement units to the map units.
	This is necessary because the map is divided into 64x64 pixel cells, which
	represents the size of each map cell.
*/

bool	ft_check_next_move(t_data *info, double mov_x, double mov_y)
{
	if (!ft_check_valid_mov(info, mov_x, mov_y))
		return (0);
	info->player.map_x = info->player.pos_x + mov_x / 64;
	info->player.map_y = info->player.pos_y + mov_y / 64;
	return (1);
}

/*	The ft_check_next_move function is to check if the player can move to the 
	next position. If the player can move, the player position is updated. 
	If not, the player position is not updated.	*/

int	ft_check_file(char *file, char *img, int i)
{
	int	fd;

	(void)i;
	if (!ft_strcmp(file, "C") || !ft_strcmp(file, "F"))
		return (SUCCESS);
	fd = open(img, O_RDONLY);
	if (fd < 0)
	{
		printf(RED"Failed to open the texture file\n"RESET);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

/*	This function checks if a file can be opened in read-only mode. First, it
	checks if the texture name is "C" for the ceiling or "F" for the floor. If
	so, the function returns SUCCESS. After this, it tries to open the texture
	file, if it opens correctly it closes and returns SUCCESS. If the file 
	cannot be opened, an error message is printed and FAILURE is returned. This
	ensures that texture files can be opened and read correctly.	*/
