/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 09:35:56 by sternero          #+#    #+#             */
/*   Updated: 2024-07-14 09:35:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H   // If the header file has not been included.
# define SO_LONG_H  // Define the header file.

# include <stdio.h>         // Standard input/output definitions.
# include <fcntl.h>         // File control options. Used for open().
# include <unistd.h>        // Used for read() and close().
# include <stdlib.h>        // General utilities.
# include <X11/X.h>         // Used to get the keycodes.
# include <X11/keysym.h>    // Used to convert keycodes to keysyms.
# include <sys/types.h>     // Used to define data types.
# include <sys/stat.h>      // Used to get file information.

# include "../ft_printf/ft_printf.h"    // Custom printf function.
# include "../libft/libft.h"            // Custom library functions.
# include "../mlx_linux/mlx.h"          // MiniLibX for linux.

#ifndef DIR     
# define DIR 00200000       // define DIR as 00200000 for linux.

# endif

# define NAME "so_long"     // Name of the executable.
# define TITRE "So Long"    // Title of the window.

# define TILE_SIZE 32       // Size of the tiles in pixels.
# define IMG_SIZE 48        // Size of the images in pixels.

// *** Colors for the terminal. ***

# define WHITE "\033[1;37m"     // White color for the terminal.
# define RED "\033[1;31m"       // Red color for the terminal.
# define GREEN "\033[1;32m"     // Green color for the terminal.
# define YELLOW "\033[1;33m"    // Yellow color for the terminal.
# define BLUE "\033[1;34m"      // Blue color for the terminal.
# define MAGENTA "\033[1;35m"   // Magenta color for the terminal.
# define PEACH "\033[1;91m"     // Peach color for the terminal.
# define CYAN "\033[1;36m"      // Cyan color for the terminal.
# define PINK "\033[1;95m"      // Pink color for the terminal.
# define RESET "\033[0m"        // Reset color for the terminal.

// *** Error messages. ***

# define ERR_FILE "The argument is not a valid file (.ber).\n"
# define ERR_CHAR "The map contains invalid characters.\n"
# define ERR_INIT "One of the required elements in the map is missing.\n"
# define ERR_PLAYER "The map must contain only one player.\n"
# define ERR_BPLAYER "Only one player is allowed on each side.\n"
# define ERR_FORMAT "The map is not rectangular.\n"
# define ERR_BORDER "The map must be surrounded by walls.\n"

// *** Return values. ***

# define ERROR -1       // Error return value. Used for error handling.
# define FAILURE 1      // Failure return value. Used for error handling.
# define SUCCESS 0      // Success... 0 is the default return value.

// *** Keycodes for the game. ***

# define A 97              // ASCII value for the 'a' key.
# define D 100             // ASCII value for the 'd' key.
# define S 115             // ASCII value for the 's' key.
# define W 119             // ASCII value for the 'w' key.

# define Z 122             // ASCII value for the 'z' key.
# define Q 113             // ASCII value for the 'q' key.
# define S 115             // ASCII value for the 's' key.
# define D 100             // ASCII value for the 'd' key.

# define GO_LEFT 65361     // ASCII value for the left arrow key.
# define GO_RIGHT 65363    // ASCII value for the right arrow key.
# define GO_DOWN 65364     // ASCII value for the down arrow key.
# define GO_UP 65362       // ASCII value for the up arrow key.

// *** Paths to graphic materials. ***

# define BEGIN "materials/begin.xpm"       //Image of the beginning.
# define PLAYER "materials/player.xpm"     //Image of the player.
# define ENEMY "materials/enemy.xpm"       //Image of the enemy.
# define WALL "materials/wall.xpm"         //Image of the wall.
# define FLOOR "materials/floor.xpm"       //Image of the floor.
# define COLLECT "materials/collect.xpm"   //Image of the collectible.
# define EXIT "materials/exit.xpm"         //Image of the exit.

# define ESC 65307  // ASCII value for the 'esc' key.

# define FOE ""

typedef struct s_game   // Structure to hold the game data.
{
    void    *mlx;
    void    *win;
    int     i;
    int     j;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;
    t_img img;
    t_img map;
}   t_game;

typedef struct s_form   // Structure to hold the form data.
{
    int     color;  
    int     x;
    int     y;
    int     width;
    int     height;
}   t_form;

typedef struct s_img    // Structure to hold the image data.
{
    void    *img_mlx;
    char    *addr;
    char    *map;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_map    // Structure to hold the map data.
{
    size_t  len_line;
    char    **map;
    int     fd;
    int     count_len; 
    int     width;
    int     height;
}   t_map;


#endif