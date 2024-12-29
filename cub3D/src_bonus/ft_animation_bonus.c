/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:10:11 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:10:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_init_animation(t_data *info)
{
	info->animation.flag = 0;
	info->animation.scale_x = 0;
	info->animation.scale_y = 0;
	info->animation.target_x = 0;
	info->animation.target_y = 0;
	info->animation.animation_1 = NULL;
	info->animation.animation_2 = NULL;
	info->animation.animation_3 = NULL;
	info->animation.animation_4 = NULL;
	info->animation.animation_5 = NULL;
}

/*	The ft_init_animation function is used to initialize the animation structure
	of the game. It takes a t_data structure as a parameter and initializes the
	animation flag to 0, the scale factors (x and y) to 0, the target coordinate
	(x and y) to 0, and the pointers to the animation textures to NULL. */

uint32_t	ft_get_sprite(double x, double y, mlx_texture_t *text)
{
	unsigned int	i;
	uint32_t		index;
	uint8_t			rgba[4];

	i = 0;
	if (!text || !text->pixels || x >= text->width || y >= text->height)
		return (0);
	index = ((uint32_t)y * text->width + (uint32_t)x) * text->bytes_per_pixel;
	while (i < 4)
	{
		rgba[i] = text->pixels[index + i];
		i++;
	}
	return (ft_rgba(rgba));
}

/*	The ft_get_sprite function is used to get the color of a pixel from a 
	sprite. It takes the x and y coordinates of the pixel and the mlx_texture_t
	structure of the sprite as parameters. It returns the color of the pixel in
	the sprite.
	To get the color of a pixel from a sprite in a textre, in a specified
	position, is a common operation in video games. For example: to draw a sprite
	on the screen, we need to get the color of each pixel of the sprite and draw
	it on the screen; it can also be used to detect collisions between objects
	in the game; or to perform animations, since these involve changing the
	sprites in different positions, so getting the color of a sprite at a
	specific position allows us to update the screen with the new colors of the
	pixels.
	Practical example: developing a game in which a character moves around the
	screen, every time the character moves, we need to draw its sprite in the new
	position. To do this, we need to get the color of each pixel of the sprite
	and draw it in the new position.   */

void	ft_draw_anim(t_data *info, mlx_texture_t *text)
{
	int			i;
	int			j;
	uint32_t	c;

	i = 0;
	info->animation.scale_x = (double)text->width / (SPRITE_WIDTH);
	info->animation.scale_y = (double)text->height / (SPRITE_HEIGHT);
	info->animation.target_x = (WIDTH - SPRITE_WIDTH - 100);
	info->animation.target_y = HEIGHT - SPRITE_HEIGHT + 15;
	while (i < SPRITE_WIDTH)
	{
		j = 0;
		while (j < SPRITE_HEIGHT)
		{
			c = ft_get_sprite(i * info->animation.scale_x, \
				j * info->animation.scale_y, text);
			if (c != 0)
				mlx_put_pixel(info->walls, info->animation.target_x + i, \
					info->animation.target_y + j, c);
			j++;
		}
		i++;
	}
}

/*	This function is util to render animations scaled and positioned correctly
	on the screen. Suppose we have a texture of 100x100 pixels and we want to
	draw it as a sprite of 50x50 pixels on the screen. This function will
	calculate the scale factors (x and y), set the destination coordinates (x
	and y) and draw each pixel of the sprite. The casting to double is done to
	ensure that the division when calculating the scale factors of scale_x and
	scale_y is done with floating point precision. This avoids rounding errors
	and ensures an accurate scaling of the texture to the size of the sprite,
	improving the visual quality and the accuracy of the sprite drawing on the
	screen. */

void	ft_charge_anim(t_data *info)
{
	info->animation.flag = 1;
	info->animation.animation_1 = mlx_load_png("./imgs/tile000.png");
	info->animation.animation_2 = mlx_load_png("./imgs/tile001.png");
	info->animation.animation_3 = mlx_load_png("./imgs/tile002.png");
	info->animation.animation_4 = mlx_load_png("./imgs/tile003.png");
	info->animation.animation_5 = mlx_load_png("./imgs/tile004.png");
	if (!info->animation.animation_1 || !info->animation.animation_2
		|| !info->animation.animation_3 || !info->animation.animation_4
		|| !info->animation.animation_5)
	{
		printf(RED"Failed to open animation images.\n"RESET);
		info->animation.flag = -1;
	}
}

/*	This function is used to load a series of PNG images that will be used to
	represent an animation on the screen and set a flag. The idea is to load a
	series of images for an animation, so the following will be done: set the
	animation flag to 1 to indicate the animation is ready, load the images; if
	all the images are loaded correctly, the animation will be ready to be
	played, if any of the images are not loaded correctly, set the animation
	flag to -1 to indicate that the animation is not ready. */

void	ft_loop_anim(t_data *info)
{
	if (info->animation.flag == -1)
		return ;
	if (mlx_is_key_down(info->mlx, MLX_KEY_SPACE)
		|| mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (info->animation_loop == 0)
			ft_draw_anim(info, info->animation.animation_1);
		if (info->animation_loop == 1)
			ft_draw_anim(info, info->animation.animation_2);
		if (info->animation_loop == 2)
			ft_draw_anim(info, info->animation.animation_3);
		if (info->animation_loop == 3)
			ft_draw_anim(info, info->animation.animation_4);
		if (info->animation_loop == 4)
			ft_draw_anim(info, info->animation.animation_5);
		info->animation_loop++;
		if (info->animation_loop == 6)
			info->animation_loop = 0;
	}
	else
		info->animation_loop = 0;
	if (info->animation_loop == 0)
		ft_draw_anim(info, info->animation.animation_1);
}

/*	This function handles the animation loop, drawing different animation frames
	in response to user input (keyboard or mouse). If the animation flag is -1,
	the function returns immediately, indicating that there was an error loading
	the animation images; it checks if the space key or the left mouse button are
	pressed, if so, it draws a frame of the animation on the screen; depending on
	the value of info->animation_loop, the corresponding frame of the animation
	will be drawn, and the value of info->animation_loop will be incremented to
	move to the next frame; if the value of info->animation_loop is 6, it is
	reset to 0, to repeat the animation.
	The animation initialization when the player presses the space key or the
	left mouse button.	*/
