/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 09:34:29 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 09:34:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
    t_game	game;

    if (argc = 2)
    {
        if (chek_ber(argv[1]) == ERR_FILE)
            ft_error(ERR_FILE, &game);
        map_draw(argv[1], &game);
        map_init(&game);
        map_check(&game);
        init_gamer(&game);
        init_terminal(&game);
        imgs_init(&game);
        make_game(game);        
        imgs_loop(game);
        imgs_del(game);
        free(game.mlx);
        if (game.map.map)
            free(game.map.map);
    }
    return (0);
}

/*
The main function is the entry point of the program. 
It checks if the number of arguments is equal to 2.
If the number of arguments is not equal to 2, the program exits.
If the number of arguments is equal to 2, the program checks if the file is 
a valid .ber file. If the file is not a valid .ber file, the program exits.
If the file is a valid .ber file, the program draws the map, initializes the
map, checks the map, initializes the player, initializes the terminal,
initializes the images, makes the game, loops the images, deletes the images,
frees the mlx, and frees the map.
The program then returns 0.
*/