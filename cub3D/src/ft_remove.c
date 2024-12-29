/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*   By: druiz-ca <druiz-ca@student.42malaga.com> +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 10:08:33 by sternero          #+#    #+#             */
/*   Updated: 2024-12-29 10:08:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ft_del_imgs(t_data *data)
{
	mlx_delete_texture(data->textures.no_texture);
	mlx_delete_texture(data->textures.so_texture);
	mlx_delete_texture(data->textures.we_texture);
	mlx_delete_texture(data->textures.ea_texture);
}

/*	This function frees the memory allocated for the texture paths and deletes
	the textures. It takes a pointer to a t_data structure as an argument. It
	initializes a t_texture structure t and stores the texture paths in t. It
	checks if the texture paths are valid and frees the memory allocated for the
	paths. It then deletes the textures. This helps to free the memory allocated
	for the texture paths and delete the textures correctly.	*/

void	ft_free_imgs(t_data *data)
{
	t_texture	t;

	t = data->textures;
	if (t.no_flag)
		free(t.no_path);
	if (t.so_flag)
		free(t.so_path);
	if (t.we_flag)
		free(t.we_path);
	if (t.ea_flag)
		free(t.ea_path);
}

/*	This function frees the memory allocated for the texture paths. It takes a
	pointer to a t_data structure as an argument. It initializes a t_texture
	structure t and stores the texture paths in t. It checks if the texture
	paths are valid and frees the memory allocated for the paths. This helps to
	free the memory allocated for the texture paths correctly.	*/
