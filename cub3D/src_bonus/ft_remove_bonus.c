/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:16:31 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:16:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*ft_del_nl(char *str)
{
	char	*new;

	new = ft_realloc(str, ft_strlen(str));
	if (!new)
		return (NULL);
	return (new);
}

/*	This function reallocates the provided string str to remove the newline
	character at the end of the string. It uses ft_realloc to reallocate the
	string with a new size that is one character less than the original size.
	It then returns the new string without the newline character.	*/

void	ft_del_imgs(t_data *info)
{
	if (info->animation.animation_1)
		mlx_delete_texture(info->animation.animation_1);
	if (info->animation.animation_2)
		mlx_delete_texture(info->animation.animation_2);
	if (info->animation.animation_3)
		mlx_delete_texture(info->animation.animation_3);
	if (info->animation.animation_4)
		mlx_delete_texture(info->animation.animation_4);
	if (info->animation.animation_5)
		mlx_delete_texture(info->animation.animation_5);
	mlx_delete_texture(info->textures.no_texture);
	mlx_delete_texture(info->textures.so_texture);
	mlx_delete_texture(info->textures.ea_texture);
	mlx_delete_texture(info->textures.we_texture);
	if (info->textures.do_flag)
		mlx_delete_texture(info->textures.do_texture);
}

/*	This function frees the memory allocated for the texture paths and deletes
	the textures. It takes a pointer to a t_data structure as an argument. It
	initializes a t_texture structure t and stores the texture paths in t. It
	checks if the texture paths are valid and frees the memory allocated for the
	paths. It then deletes the textures. This helps to free the memory allocated
	for the texture paths and delete the textures correctly.	*/

void	ft_free_imgs(t_data *info)
{
	t_texture	txt;

	txt = info->textures;
	if (txt.no_flag)
		free(txt.no_path);
	if (txt.so_flag)
		free(txt.so_path);
	if (txt.we_flag)
		free(txt.we_path);
	if (txt.ea_flag)
		free(txt.ea_path);
	if (txt.do_flag)
		free(txt.do_path);
}

/*	This function frees the memory allocated for the texture paths. It takes a
	pointer to a t_data structure as an argument. It initializes a t_texture
	structure t and stores the texture paths in t. It checks if the texture
	paths are valid and frees the memory allocated for the paths. This helps to
	free the memory allocated for the texture paths correctly.	*/
