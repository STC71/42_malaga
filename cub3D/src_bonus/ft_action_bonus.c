/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:09:44 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:09:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_callback(void *value)
{
	t_data		*info;

	info = value;
	if (info->player.ray[0].delta_dist_y)
	{
		mlx_delete_image(info->mlx, info->walls);
		mlx_delete_image(info->mlx, info->bonus);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	ft_movements(info);
	ft_handle_rot(info);
	ft_init_walls(info, &info->walls);
	ft_init_walls(info, &info->bonus);
	ft_shoot_ray(info, &info->player);
	ft_minimap(info);
	ft_loop_anim(info);
}

/*	The ft_callback function is divided into 3 parts:
	1. delta_dist_y is checked to delete the walls image, because it is 
		initialized in the first loop.
	2. if the ESC key is pressed, the window is closed.
	3. The player movement and rotation are handled to move the player and 
		rotate the player when the keys are pressed.
	4. The walls image is initialized with the ft_init_walls function.
	5. The rays are printed with the ft_shoot_ray function, it is necessary 
		to print the rays in every loop. The rays are important to print the
		walls and the sprites because the rays are the lines that are drawn
		from the player to the walls and the sprites.	*/

void	ft_play_game(t_data *info)
{
	info->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx_set_cursor_mode(info->mlx, MLX_MOUSE_DISABLED);
	if (!info->mlx)
	{
		printf(RED"Error initializing mlx.\n"RESET);
		exit(FAILURE);
	}
	ft_init_walls(info, &info->background);
	ft_init_walls(info, &info->walls);
	ft_init_walls(info, &info->bonus);
	info->move = 4;
	ft_check_pos_player(info, info->map.map);
	info->prev_map_x = 0;
	info->prev_map_y = 0;
	ft_paint(info);
}

/*	This function initializes the game environment, setting up the window, the
	cursor, the images, and the initial position of the player. First, the 
	window and the graphic context are initialized with the mlx_init function.
	If the function fails, that is, if the window cannot be initialized, an
	error message is printed and the program exits. Then, the images of the
	background, the walls, and the minimap are initialized. With info->move, the
	player's movement speed is initialized. Next, the player's initial position
	on the map is verified. Then, the variables prev_map_x and prev_map_y are
	initialized to 0. Finally, the background is painted, and the function that
	paints the walls is called.	*/

void	ft_start(t_data *info)
{
	ft_play_game(info);
	ft_charge_anim(info);
	info->animation_loop = 0;
	mlx_loop_hook(info->mlx, ft_callback, info);
	mlx_cursor_hook(info->mlx, &ft_mouse_move, info);
	mlx_key_hook(info->mlx, ft_key, info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
}

/*	The ft_play_game function is to initialize the game and the images.
	The ft_loop_hook function is to handle the player movement and rotation. 
		Inside this, ft_callback function is called to print the rays.
	The mlx_loop function is to start the game.
	The mox_terminate function is to close the game.	*/

int	main(int argc, char **argv)
{
	t_data	info;

	if (argc != 2)
	{
		printf(RED"Bad number of arguments\n");
		printf(BLUE"Usage: ./cub3d map.cub\n"RESET);
		return (1);
	}
	ft_var_setup(&info);
	if (ft_parse(argv[1], &info))
	{
		if (info.map.map)
			ft_split_free(info.map.map);
		ft_free_imgs(&info);
		return (FAILURE);
	}
	ft_load_imgs(&info);
	ft_start(&info);
	ft_split_free(info.map.map);
	ft_free_imgs(&info);
	ft_del_imgs(&info);
	return (SUCCESS);
}

/* 	The main function is divided into 3 parts:
	1. The first part is the initialization of the variables and the parsing of 
		the map.
	2. The second part is the loading of the textures and the initialization of 
		the game.
	3. The third part is the start of the game.
	After the game is started, the game loop is called and the game starts.
	When the game is closed, the memory is freed and the images are deleted. */