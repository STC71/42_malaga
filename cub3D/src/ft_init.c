/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:06:34 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:06:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_imgs_values(t_data *info)
{
	info->textures.c_flag = 0;
	info->textures.f_flag = 0;
	info->textures.no_flag = 0;
	info->textures.so_flag = 0;
	info->textures.we_flag = 0;
	info->textures.ea_flag = 0;
}

/*	This function initializes the texture flags. The function receives the info
	structure that contains all the game information. The function sets the color
	flags to 0, the texture flags to 0, and the paths to NULL.	*/

void	ft_init_player(t_data *info)
{
	info->player.angle = 0;
	info->player.map_x = 0;
	info->player.map_y = 0;
	info->player.pos_x = 0;
	info->player.pos_y = 0;
}

/*	This function initializes the player variables. The function receives the
	info structure that contains all the game information. The function sets the
	player angle to 0, the player map x and y to 0, and the player position x
	and y to 0.	*/

void	ft_init_imgs(t_data *info)
{
	ft_init_imgs_values(info);
	info->textures.c_color = 0;
	info->textures.f_color = 0;
	info->textures.no_path = NULL;
	info->textures.so_path = NULL;
	info->textures.we_path = NULL;
	info->textures.ea_path = NULL;
	info->textures.no_texture = NULL;
	info->textures.so_texture = NULL;
	info->textures.we_texture = NULL;
	info->textures.ea_texture = NULL;
}

/*	This function initializes the game images. The function receives the info
	structure that contains all the game information. The function initializes
	the texture flags, the colors, the paths, and the textures.	*/

int	ft_var_setup(t_data *info)
{
	ft_init_imgs(info);
	ft_init_player(info);
	info->background = NULL;
	info->file = NULL;
	info->move = 0;
	info->mlx = NULL;
	info->ray_number = 0;
	info->walls = NULL;
	info->map.map = NULL;
	info->map.map_line = 0;
	info->map.map_size_x = 0;
	info->map.map_size_y = 0;
	return (SUCCESS);
}

/*	This function initializes the game variables. The function receives the
	info structure that contains all the game information.	*/

void	ft_init_walls(t_data *info, mlx_image_t **img)
{
	*img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!*img)
	{
		printf(RED"Error creating floor-ceiling\n"RESET);
		exit(FAILURE);
	}
	if (mlx_image_to_window(info->mlx, *img, 0, 0) == -1)
	{
		printf(RED"Eror in mlx_image_to_window() for floor-ceiling\n"RESET);
		exit(FAILURE);
	}
}

/*	This function initializes the walls image. It takes a pointer to a t_data
	structure and a pointer to a pointer to a mlx_image_t structure as arguments
	It initializes the image with mlx_new_image. If the image is not created, it
	prints an error message and exits with FAILURE. It then displays the image
	with mlx_image_to_window. If the image is not displayed, it prints an error
	message and exits with FAILURE.	*/