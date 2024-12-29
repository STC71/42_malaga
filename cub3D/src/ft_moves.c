/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:06:58 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:06:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_movements(t_data *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		ft_move_player(info, info->player.angle);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		ft_move_player(info, info->player.angle + 180);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		ft_move_player(info, info->player.angle - 90);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		ft_move_player(info, info->player.angle + 90);
	if (mlx_is_key_down(info->mlx, MLX_KEY_E))
		info->move = 12;
	if (!mlx_is_key_down(info->mlx, MLX_KEY_E))
		info->move = 4;
}

/*	This function is to handle the player movements. The function receives the
	info structure that contains all the game information. The function checks
	if the player is pressing the W, S, A, D, or E keys. If the player is
	pressing the W key, the player moves forward in the direction it is facing.
	If the player is pressing the S key, the player moves backward in the
	direction it is facing. If the player is pressing the A key, the player 
	moves to the left of the direction it is facing. If the player is pressing 
	the D key, the player moves to the right of the direction it is facing. 
	If the player is pressing the E key, the player moves faster. If the player 
	is not pressing the E key, the player moves at the normal speed.	*/

void	ft_move_player(t_data *info, double ang)
{
	double			mov_x;
	double			mov_y;

	mov_x = (cos(ang * M_PI / 180) * info->move);
	mov_y = (sin(ang * M_PI / 180) * info->move);
	if (ft_check_next_move(info, 0, mov_y))
	{
		info->player.pos_y += mov_y / 64;
	}
	if (ft_check_next_move(info, mov_x, 0))
	{
		info->player.pos_x += mov_x / 64;
	}
}
/*	This function moves the player in a specific direction depending on the 
	angle the player is facing. The function receives the info structure that
	contains all the game information and the angle the player is facing. The
	function calculates the mov_x and mov_y components of the movement in the x
	and y axes respectively. The movement is calculated with trigonometric
	functions, where the cosine and sine of the angle are multiplied by the
	magnitude of the movement. The movement is divided by 64 to convert the
	movement units to map units. The ft_check_next_move function is used to
	check if the player can move to the next position. If the player can move,
	the player position is updated.	*/

void	ft_handle_rot(t_data *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		ft_check_angles(&info->player.angle, -3);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		ft_check_angles(&info->player.angle, 3);
}

/*	This function is to handle the player rotation. The function receives the
	info structure that contains all the game information. The function checks
	if the player is pressing the left or right arrow keys. If the player is
	pressing the left arrow key, the player rotates to the left. If the player
	is pressing the right arrow key, the player rotates to the right.	*/