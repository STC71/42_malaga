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

char	**ft_status_map(t_init *game)
{
	t_map	*tmp;
	char	**status;
	int		i;

	i = 0;
	tmp = game->map;
	status = malloc(sizeof(char *) * (game->size.y + 1));
	if (!status)
		return (NULL);
	while (game->map)
	{
		status[i] = ft_strdup(game->map->map);
		if (!status[i])
		{
			ft_free_status(status, i);
			return (NULL);
		}
		i++;
		game->map = game->map->next;
	}
	game->map = tmp;
	status[i] = NULL;
	return (status);
}

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
	tmp->size.x = ft_map_x(tmp->map); 	
	tmp->size.y = ft_map_y(tmp->map);
	tmp->status_a = make_status(tmp);
	if (!tmp->status_a)
	{
		ft_free_all(tmp, 2);
		return (FAILURE);
	}
	tmp->status_b = make_status(tmp);
	if (!tmp->status_b)
	{
		ft_free_all(tmp, 1);
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