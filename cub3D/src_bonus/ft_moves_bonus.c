/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:14:52 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:14:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	ft_mouse_move(double x, double y, void *param)
{
	t_data	*info;
	double	diff;

	info = (t_data *)param;
	(void)y;
	if (info->prev_mouse_x == -1)
		info->prev_mouse_x = x;
	diff = info->prev_mouse_x - x;
	info->prev_mouse_x = x;
	if (diff < 0)
	{
		info->player.angle = info->player.angle + 0.3;
		if (info->player.angle > 359)
			info->player.angle = 0;
	}
	else if (diff > 0)
	{
		info->player.angle = info->player.angle - 0.3;
		if (info->player.angle < 0)
			info->player.angle = 359;
	}
}

/*	This function is to handle the player rotation with the mouse. The function
	receives the x and y coordinates of the mouse and the param parameter that
	contains the info structure. The function calculates the difference between
	the previous x coordinate of the mouse and the current x coordinate of the
	mouse. The player angle is updated according to the difference. If the
	difference is positive, the player rotates to the left. If the difference is
	negative, the player rotates to the right.
	If it is the first time the mouse is moved, the current position is saved in
	prev_mouse_x. Then, the difference between the current position and the
	previous position of the mouse is calculated. If the difference is positive,
	the player rotates to the left. If the difference is negative, the player
	rotates to the right.
	The calculation of the difference in the x position of the mouse is
	calculated as the difference between the previous position and the current
	position of the mouse. After this, the current position is updated.
	For the adjustment of the player's angle, if the difference is negative (the
	mouse has moved to the left), 0.3 is subtracted from the player's angle. If
	the player's angle is less than 0, it is adjusted to 359. If the difference
	is positive (the mouse has moved to the right), 0.3 is added to the player's
	angle. If the player's angle is greater than 359, it is adjusted to 0.
	The value 0.3 is the value of the mouse sensitivity. It provides an
	appropriate sensitivity for mouse movement. If it were too low, the player
	would have to move the mouse a lot to rotate to make a change of direction.
	If it were too high, the player would rotate too fast and would not be able
	to control the player's direction. In short, the value 0.3 provides an
	appropriate sensitivity for mouse movement, with a smooth and controllable
	gaming experience.	*/
