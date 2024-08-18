/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-11 07:57:02 by sternero          #+#    #+#             */
/*   Updated: 2024-08-11 07:57:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_mlx_init(t_init *gm)
{
	gm = ft_find_ship(gm);
	gm->mlx = mlx_init(gm->size.x * 64, gm->size.y * 64, "so_long", true);
	if (!gm || !gm->mlx)
	{
		ft_map_error(ERR_MLX);
		ft_free_all(gm, 1);
		exit(FAILURE);
	}
	ft_init_txts(gm);
	ft_init_imgs(gm);
	ft_drawing_map(gm);
	gm->imgs.ship = NULL;
	mlx_key_hook(gm->mlx, ft_key_press, gm);
	mlx_loop(gm->mlx);
}
