/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-15 10:55:21 by sternero          #+#    #+#             */
/*   Updated: 2024-08-15 10:55:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_obj(t_cell checked, t_cell objects)
{
	if (checked.ship != objects.ship)
		return (FAILURE);
    if (checked.collec != objects.collec)
		return (FAILURE);
	if (checked.exit != objects.exit)
		return (FAILURE);

	return (SUCCESS);
}

int	ft_check_obj_nbr(t_cell objects)
{
	if (objects.ship != 1)
		return (FAILURE);
	if (objects.collec < 1)
		return (FAILURE);	
    if (objects.exit != 1)
		return (FAILURE);

	return (SUCCESS);
}

int	ft_check_form(t_init *game)
{
	int	i;
	int	j;
	int	l_size;

	j = 0;
	l_size = 0;
	while (game->status_a[j][l_size] != '\n')
		l_size++;
	while (j < game->size.y)
	{
		i = 0;
		while (game->status_a[j][i] != '\n' && game->status_a[j][i] != '\0')
		{
			if (game->status_a[j][i] != '0' && game->status_a[j][i] != WALL
				&& game->status_a[j][i] != 'P' && game->status_a[j][i] != 'C'
				&& game->status_a[j][i] != EXIT)
				return (1);
			i++;
		}
		if (l_size != i)
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	ft_check_borders(t_init *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->size.y)
	{
		i = 0;
		while (game->status_a[j][i] != '\n' && game->status_a[j][i] != '\0')
		{
			if (j == 0 && game->status_a[j][i] != WALL)
				return (FAILURE);
			if (j == game->size.y - 1 && game->status_a[j][i] != WALL)
				return (FAILURE);
			if (j != 0 && (i == 0 || i == game->size.x - 1)
				&& game->status_a[j][i] != WALL)
				return (FAILURE);
			if (j != game->size.y - 1 && (i == 0 || i == game->size.x - 1)
				&& game->status_a[j][i] != WALL)
				return (FAILURE);
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

