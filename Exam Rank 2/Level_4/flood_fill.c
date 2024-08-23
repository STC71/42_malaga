/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-23 11:43:53 by sternero          #+#    #+#             */
/*   Updated: 2024-08-23 11:43:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_flood_fill.h"

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x 
        || tab[cur.y][cur.x] != to_fill)
		return;
	tab[cur.y][cur.x] = 'F';
	fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}

// The fill function is a recursive function that fills the area around 
// a given point with a specific character. The function takes 
// the following parameters:
// - tab: a two-dimensional array of characters representing the area to fill
// - size: a t_point structure representing the size of the area
// - cur: a t_point structure representing the current position
// - to_fill: a character representing the character to fill the area with
// The function recursively fills the area around the current point with
// the character to_fill. It checks if the current position is within the
// bounds of the area and if the character at that position is equal to
// the character to_fill. If so, it fills the current position with the
// character 'F' and recursively calls the fill function on the adjacent
// positions (left, right, up, down).
// The flood_fill function is a wrapper function that calls the fill function
// with the initial position and character to fill. It is used to start the
// flood fill algorithm on the given area.