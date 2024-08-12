/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 09:34:29 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 09:34:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_map(t_init **game)
{
	t_init	*tmp;

	tmp = *game;
	tmp->map = ft_map_init(tmp);
	if (!tmp->map)
	{
		free(tmp);
		return (1);
	}
	tmp->size.x = map_size_x(tmp->map); // ***** VOY POR AQUÍ *****	
	tmp->size.y = map_size_y(tmp->map);
	tmp->status_a = make_matrix(tmp);
	if (!tmp->status_a)
	{
		free_game(tmp, 2);
		return (FAILURE);
	}
	tmp->status_b = make_matrix(tmp);
	if (!tmp->status_b)
	{
		free_game(tmp, 1);
		return (FAILURE);
	}
	*game = tmp;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ft_map_error("Usage: ./so_long [map.ber]");
		return (1);
	}
	if (argc == 2)
	{
		if (ft_check_ber(argv[1]) == FAILURE)
		{
			ft_map_error("Invalid name of the map, must be a *.ber file.");
			return (FAILURE);
		}
		i = ft_start_map(argv[1]); 
		if (i == 1)
			return (1);
	}
	return (0);
}