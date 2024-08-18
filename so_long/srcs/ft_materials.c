/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-08 08:17:28 by sternero          #+#    #+#             */
/*   Updated: 2024-08-08 08:17:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_init	*ft_find_ship(t_init *ship)
{
	int		i;
	int		j;

	j = 1;
	ship->ship.x = 0;
	ship->ship.y = 0;
	while (j < ship->size.y)
	{
		i = 1;
		while (ship->status_a[j][i] != '\n')
		{
			if (ship->status_a[j][i] == PLAYER)
			{
				ship->ship.x = i;
				ship->ship.y = j;
				return (ship);
			}
			i++;
		}
		j++;
	}
	return (ship);
}

void	ft_objs_init(t_cell *obj)
{
	obj->ship = 0;
	obj->collec = 0;
	obj->exit = 0;
}

t_cell	ft_count_obj(t_map *map)
{
	t_cell	obj;
	int		i;

	ft_objs_init(&obj);
	while (map)
	{
		i = 0;
		while (map->map[i])
		{
			if (map->map[i] == PLAYER)
				obj.ship++;
			if (map->map[i] == COLLECT)
				obj.collec++;
			if (map->map[i] == EXIT)
				obj.exit++;
			i++;
		}
		map = map->next;
	}
	return (obj);
}
