/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-23 11:39:30 by sternero          #+#    #+#             */
/*   Updated: 2024-08-23 11:39:30 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOOD_FILL
# define FLOOD_FILL

#include <stdlib.h>     // for malloc
#include <stdio.h>      // for printf

typedef struct  s_point
{
    int         x;  // x : width (horizontal) | x-axis (abscissa)
    int         y;  // y : height (vertical) | y-axis (ordinate)
}   t_point;

#endif

// The t_point_flood_fill.h file contains the definition of the t_point structure
// used in the flood_fill function. The t_point structure contains two integer
// fields, x and y, which represent the coordinates of a point in a two-dimensional
// space. The x field represents the horizontal position of the point, while the y
// field represents the vertical position of the point. 