/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:13:54 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:13:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_init_imgs_values(t_data *info)
{
	info->open_flag = 0;
	info->textures.c_flag = 0;
	info->textures.f_flag = 0;
	info->textures.no_flag = 0;
	info->textures.so_flag = 0;
	info->textures.ea_flag = 0;
	info->textures.we_flag = 0;
	info->textures.do_flag = 0;
	info->textures.do_error = 0;
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
	info->textures.ea_path = NULL;
	info->textures.we_path = NULL;
	info->textures.do_path = NULL;
	info->textures.no_texture = NULL;
	info->textures.so_texture = NULL;
	info->textures.ea_texture = NULL;
	info->textures.we_texture = NULL;
	info->textures.do_texture = NULL;
}

/*	This function initializes the game images. The function receives the info
	structure that contains all the game information. The function initializes
	the texture flags, the colors, the paths, and the textures.	*/

int	ft_var_setup(t_data *info)
{
	ft_init_animation(info);
	ft_init_imgs(info);
	ft_init_player(info);
	info->animation_loop = 0;
	info->background = NULL;
	info->bonus = NULL;
	info->file = NULL;
	info->move = 0;
	info->mlx = NULL;
	info->prev_map_x = 0;
	info->prev_map_y = 0;
	info->prev_mouse_x = -1;
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
		printf(RED"Error in mlx_image_to_window() "RESET);
		printf("for floor or/and ceiling\n");
		exit(FAILURE);
	}
}

/*	This function initializes the walls image. It takes a pointer to a t_data
	structure and a pointer to a pointer to a mlx_image_t structure as arguments
	It initializes the image with mlx_new_image. If the image is not created, it
	prints an error message and exits with FAILURE. It then displays the image
	with mlx_image_to_window. If the image is not displayed, it prints an error
	message and exits with FAILURE.	*/