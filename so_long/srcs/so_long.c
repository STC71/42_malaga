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

    if (argc != 2)
    {
        ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
        return (1);
    }
    if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
    {
        ft_putstr_fd("Error\nInvalid file extension\n", 2);
        return (1);
    }
    game = init_game();
    if (!game.map)
    {
        ft_putstr_fd("Error\nMap not found\n", 2);
        return (1);
    }
    if (!parse_map(&game, argv[1]))
    {
        ft_putstr_fd("Error\nInvalid map\n", 2);
        return (1);
    }
    mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
    mlx_hook(game.win, 17, 1L << 17, close_game, &game);
    mlx_loop(game.mlx);
    return (0);
}