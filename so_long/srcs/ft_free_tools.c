/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-14 09:56:18 by sternero          #+#    #+#             */
/*   Updated: 2024-08-14 09:56:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_all(t_init *game, int error)
{
	if (error == 2)
	{
		ft_free_stack(&game->map);
		free(game);
	}
    if (error == 1)
	{
		game->status_a = free_status_a(game->status_a, game->size.y);
		ft_free_stack(&game->map);
		free(game);
	}
	if (error == 0)
	{
		game->status_a = free_status_a(game->status_a, game->size.y);
		ft_free_stack(&game->map);
		ft_free_txt(&game);
		ft_free_img(&game);
		mlx_terminate(game->mlx);
		free(game);
	}
}

void	ft_free_stack(t_map **stack)
{
	t_map	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free((*stack)->map);
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

void	ft_free_txt(t_init **game)
{
	mlx_delete_texture((*game)->textures.ocean);
	(*game)->textures.ocean = NULL;
	mlx_delete_texture((*game)->textures.wall);
	(*game)->textures.wall = NULL;    
 	mlx_delete_texture((*game)->textures.collec);
	(*game)->textures.collec = NULL;
	mlx_delete_texture((*game)->textures.exit_c);
    (*game)->textures.exit_c = NULL;
    mlx_delete_texture((*game)->textures.exit_o);
	(*game)->textures.exit_o = NULL;    
    mlx_delete_texture((*game)->textures.ship);
	(*game)->textures.ship = NULL;
	mlx_delete_texture((*game)->textures.ship_u);
	(*game)->textures.ship_u = NULL;
	mlx_delete_texture((*game)->textures.ship_d);
	(*game)->textures.ship_d = NULL;
	mlx_delete_texture((*game)->textures.ship_l);
	(*game)->textures.ship_l = NULL;
	mlx_delete_texture((*game)->textures.ship_r);
	(*game)->textures.ship_r = NULL;
	mlx_delete_texture((*game)->textures.shark);
	(*game)->textures.shark = NULL;
}

void	ft_free_img(t_init **game)
{
	mlx_delete_image((*game)->mlx, (*game)->imgs.ocean);
	(*game)->imgs.ocean = NULL;	
	mlx_delete_image((*game)->mlx, (*game)->imgs.wall);
	(*game)->imgs.wall = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.collec);
	(*game)->imgs.collec = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.exit_c);
	(*game)->imgs.exit_c = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.exit_o);
	(*game)->imgs.exit_o = NULL;
    mlx_delete_image((*game)->mlx, (*game)->imgs.ship);
	(*game)->imgs.ship = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.ship_u);
	(*game)->imgs.ship_u = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.ship_d);
	(*game)->imgs.ship_d = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.ship_l);
	(*game)->imgs.ship_l = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.ship_r);
	(*game)->imgs.ship_r = NULL;
	mlx_delete_image((*game)->mlx, (*game)->imgs.shark);
	(*game)->imgs.shark = NULL;
}

char	**ft_free_status(char **status, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		free(status[i]);
		status[i] = NULL;
		i++;
	}
	return (status);
}

// char	**free_matrix(char **matrix, int cont)
// {
// 	int	i;

// 	i = 0;
// 	while (i < cont)
// 	{
// 		free(matrix[i]);
// 		matrix[i] = NULL;
// 		i++;
// 	}
// 	free(matrix);
// 	matrix = NULL;
// 	return (matrix);
// }