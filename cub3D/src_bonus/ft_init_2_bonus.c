/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:14:10 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:14:10 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_init_img(t_data *info, mlx_image_t **img)
{
	*img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!*img)
	{
		printf(RED"Error: "RESET"creating floor or/and ceiling.\n");
		exit(FAILURE);
	}
	if (mlx_image_to_window(info->mlx, *img, 0, 0) == -1)
	{
		printf(RED"Error: "RESET"in mlx_image_to_window for \
			floor or/and ceiling.\n");
		exit(FAILURE);
	}
}

/*	This function creates a new image using the MLX42 library, and places it
	in a window. First, a new image is created with the mlx_new_image function,
	and it is saved in the memory address of the image that is received as an
	argument. If the image is not created, an error message is printed and the
	program exits. Then, the image is placed in the window with the
	mlx_image_to_window function. If the function fails, an error message is
	printed and the program exits.	*/

void	ft_key(struct mlx_key_data key_info, void *data)
{
	t_data	*info;

	info = (t_data *)data;
	if (key_info.key == MLX_KEY_F && key_info.action == MLX_PRESS)
		ft_door(info);
}

/*	This function is a callback function that is called when a key is pressed.
	It receives a structure with the key information and a void pointer to the
	data structure. The function checks if the key pressed is the F key and if
	the action is a press. If so, the function ft_door_ident is called with the
	data structure as an argument.	*/

void	ft_hook(void *data)
{
	t_data		*info;

	info = data;
	if (info->player.ray[0].delta_dist_y)
	{
		mlx_delete_image(info->mlx, info->walls);
		mlx_delete_image(info->mlx, info->bonus);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	ft_movements(info);
	ft_handle_rot(info);
	ft_init_img(info, &info->walls);
	ft_init_img(info, &info->bonus);
	ft_shoot_ray(info, &info->player);
	ft_minimap(info);
	ft_loop_anim(info);
}

/*	This function handles the events and updates of the game in each iteration
	of the main loop. First, the images are deleted if necessary, specifically,
	if the delta_dist_y of the first player's ray is different from 0. Then, it
	is checked if the escape key is pressed, and if so, the window is closed.
	Next, the player is moved and/or rotated if necessary. Then, the images of
	the walls and the minimap are initialized. After that, the player's ray is
	shooted and the function that draws the minimap is called. Finally, the
	function that updates the animation is called.	*/
