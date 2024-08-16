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

t_cell	ft_count_obj(t_map *map)
{
	t_cell	obj;
	int		i;

	initialize_obj(&obj); // ***** VOY POR AQUÍ *****
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









// void   ft_call_floor(t_vars *vars)
// {
//     vars->floor.img = mlx_xpm_file_to_image(vars->mlx, "img/floor.xpm", \
//         &vars->floor.width, &vars->floor.height);
// 	vars->wall.img = mlx_xpm_file_to_image(vars->mlx, "img/wall.xpm", \
// 		&vars->wall.width, &vars->wall.height);    
// 	vars->start.img = mlx_xpm_file_to_image(vars->mlx, "img/start.xpm", \
// 		&vars->start.width, &vars->start.height);
//     vars->ship.img = mlx_xpm_file_to_image(vars->mlx, "img/ship.xpm", \
// 		&vars->ship.width, &vars->ship.height);
// 	vars->collect.img = mlx_xpm_file_to_image(vars->mlx, "img/collect_3.xpm", \
// 		&vars->collect.width, &vars->collect.height);
// 	vars->exit.img = mlx_xpm_file_to_image(vars->mlx, "img/exit.xpm", \
// 		&vars->exit.width, &vars->exit.height);	  
//     vars->you_win.img = mlx_xpm_file_to_image(vars->mlx, "img/you_win.xpm", \
// 		&vars->you_win.width, &vars->you_win.height);
// }

// void	ft_call_assets(t_vars *vars)
// {
// 	vars->nbrs = malloc(10 * sizeof(t_asset));
// 	vars->nbrs[0].img = mlx_xpm_file_to_image(vars->mlx, "img/0.xpm", \
// 		&vars->nbrs[0].width, &vars->nbrs[0].height);
// 	vars->nbrs[1].img = mlx_xpm_file_to_image(vars->mlx, "img/1.xpm", \
// 		&vars->nbrs[1].width, &vars->nbrs[1].height);
// 	vars->nbrs[2].img = mlx_xpm_file_to_image(vars->mlx, "img/2.xpm", \
// 		&vars->nbrs[2].width, &vars->nbrs[2].height);
// 	vars->nbrs[3].img = mlx_xpm_file_to_image(vars->mlx, "img/3.xpm", \
// 		&vars->nbrs[3].width, &vars->nbrs[3].height);
// 	vars->nbrs[4].img = mlx_xpm_file_to_image(vars->mlx, "img/4.xpm", \
// 		&vars->nbrs[4].width, &vars->nbrs[4].height);
// 	vars->nbrs[5].img = mlx_xpm_file_to_image(vars->mlx, "img/5.xpm", \
// 		&vars->nbrs[5].width, &vars->nbrs[5].height);
// 	vars->nbrs[6].img = mlx_xpm_file_to_image(vars->mlx, "img/6.xpm", \
// 		&vars->nbrs[6].width, &vars->nbrs[6].height);
// 	vars->nbrs[7].img = mlx_xpm_file_to_image(vars->mlx, "img/7.xpm", \
// 		&vars->nbrs[7].width, &vars->nbrs[7].height);
// 	vars->nbrs[8].img = mlx_xpm_file_to_image(vars->mlx, "img/8.xpm", \
// 		&vars->nbrs[8].width, &vars->nbrs[8].height);
// 	vars->nbrs[9].img = mlx_xpm_file_to_image(vars->mlx, "img/9.xpm", \
// 		&vars->nbrs[9].width, &vars->nbrs[9].height);
// }

// void	ft_call_materials(t_vars *vars)
// {
// 	ft_call_floor(vars);
// 	ft_call_assets(vars);
// }

