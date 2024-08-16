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

#ifndef SO_LONG_H           // If the header file has not been included.
# define SO_LONG_H          // Define the header file.

# include <stdio.h>         // Standard input/output definitions.
# include <fcntl.h>         // File control options. Used for open().
# include <unistd.h>        // Used for read() and close().
# include <stdlib.h>        // General utilities.
# include <stdarg.h>        // VA. To use va_list, va_start, va_arg, va_end.


# include "../ft_printf/ft_printf.h"        // Custom printf function.
# include "../libft/libft.h"                // Custom library functions.
# include "../MLX42/include/MLX42/MLX42.h"  // MLX42 library.
# include "./MLX42/MLX42.h"                 // MLX42 library.

// *** Name of the game. ***

# define NAME "so_long"     // Name of the executable.
# define TITRE "So Long"    // Title of the window.

# define TILE_SIZE 32       // Size of the tiles in pixels.
# define IMG_SIZE 48        // Size of the images in pixels.

// *** Window size. ***

# define WIDTH 1920         // Width of the window.
# define HEIGHT 1080        // Height of the window.

# define TRUE 1             // Boolean true. 
# define FALSE 0            // Boolean false.
# define BOOL short int     // Boolean type. Value can be TRUE or FALSE.

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
# define SLOW_BLINK "\033[5m"   // Slow blink for the terminal.

// *** Map elements. ***

# define PLAYER 'P'     // Player character.
# define ENEMY 'E'      // Enemy character.
# define WALL '1'       // Wall character.
# define FLOOR '0'      // Floor character.
# define COLLECT 'C'    // Collectible character.
# define EXIT 'E'       // Exit character.

// *** Error messages. ***

# define ERR_FILE "Invalid name of the map, must be a *.ber fil\n"
# define ERR_CHAR "The map contains invalid characters.\n"
# define ERR_MLX "Failed MLX initiation.\n"
# define ERR_MAP "The map was not found or cannot be opened.\n"
# define ERR_INIT "Usage: ./so_long [map.ber].\n"
# define ERR_PLAYER "The map must contain only one player.\n"
# define ERR_BPLAYER "Only one player is allowed on each side.\n"
# define ERR_FORMAT "The map is not rectangular.\n"
# define ERR_BORDER "The map must be surrounded by walls.\n"
# define ERR_LINE "Empty line has been detected in the file.\n"
# define ERR_GENERAL "Map or objects failed.\n"
// *** Return values. ***

# define ERROR -1       // Error return value. Used for error handling.
# define FAILURE 1      // Failure return value. Used for error handling.
# define SUCCESS 0      // Success... 0 is the default return value.

// *** Keycodes for the game. ***

# define LEFT 65361        // ASCII value for the left arrow key.
# define RIGHT 65363       // ASCII value for the right arrow key.
# define DOWN 65364        // ASCII value for the down arrow key.
# define UP 65362          // ASCII value for the up arrow key.

# define ESC 65307         // ASCII value for the 'esc' key.

// *** Paths to graphic imgs. ***

// # define IBEGIN "imgs/begin.xpm"       //Image of the beginning.
// # define IPLAYER "imgs/player.xpm"     //Image of the player.
// # define IENEMY "imgs/enemy.xpm"       //Image of the enemy.
// # define IWALL "imgs/wall.xpm"         //Image of the wall.
// # define IFLOOR "imgs/floor.xpm"       //Image of the floor.
// # define ICOLLECT "imgs/collect.xpm"   //Image of the collectible.
// # define IEXIT "imgs/exit.xpm"         //Image of the exit.

// *** Structure for the textures. ***

typedef struct s_txts
{
	mlx_texture_t   *ocean;
	mlx_texture_t   *wall;
	mlx_texture_t   *collec;
	mlx_texture_t   *exit_c;
	mlx_texture_t   *exit_o;
	mlx_texture_t   *ship;
	mlx_texture_t   *ship_u;
	mlx_texture_t   *ship_d;
	mlx_texture_t   *ship_l;
	mlx_texture_t   *ship_r;
	mlx_texture_t   *shark;
	//mlx_texture_t   *shark_u;
	//mlx_texture_t   *shark_d;
	// mlx_texture_t   *shark_l;
	// mlx_texture_t   *shark_r;
} t_txts;

//The textures are created to store the texture of the game. The textures 
//are used to give the visual aspect of the objects in the game.

// *** Structure for the images. ***

typedef struct s_images
{
	mlx_image_t		*ocean;
	mlx_image_t		*wall;
	mlx_image_t		*collec;
	mlx_image_t		*exit_c;
	mlx_image_t		*exit_o;
	mlx_image_t		*ship;
	mlx_image_t		*ship_u;
	mlx_image_t		*ship_d;
	mlx_image_t		*ship_l;
	mlx_image_t		*ship_r;
	mlx_image_t		*shark;
	// mlx_image_t		*shark_u;
	// mlx_image_t		*shark_d;
	// mlx_image_t		*shark_l;
	// mlx_image_t		*shark_r;
} t_images;

//The images are created to store the images of the game. The images are
//the visual objetcs that are displayed in the game.

// *** Structure for the map. ***

typedef struct s_map
{
	char			*map;
	struct s_map	*next;
}	t_map;

//The map is used to store the map of the game. *map store the information
//of the map. *next is used to store the next map. For example, if the player
//goes to the next level. It is not used in this game.

// *** Structure for the cells. ***

typedef struct s_cell
{
	int	ship;
	int shark;
	int ocean;
	int	wall;
	int	collec;
	int	exit;
}	t_cell;

//The cells are used to store the information of the cells of the game. 
//For example, if the cell contains a ship, a wall...
//The values are set to 0 or 1 to indicate if the cell contains the object.

// *** Structure for the key codes. ***

typedef struct s_key_press
{
	int	key;
}	t_key_press;

//The key press is used to store the key pressed by the player.

// *** Structure for the position. ***

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

//The coord structure is used to store the position of the objects in the game.

// *** Structure for the game. ***

typedef struct s_init				// Structure for the game.
{
	mlx_t			*mlx;			// Connection to the graphic display.
	t_txts			txts;			// Textures of the game.
	t_images		imgs;			// Images of the game.
	t_cell			cell;			// Object of the game.
	t_map			*map;			// Map of the game.
	t_coord			ship;			// Position of the player.
	t_coord			shark;			// Position of the enemy.
	t_coord			size;			// Size in pixels of the window.
	char			**status_a;		// Matrix of the map.
	char			**status_b;		// Matrix of the map.
	char			*path;			// Path to the map.
	int				moves;			// Number of moves.
	int				counter;		// Number of collectibles.
	int				collec;			// Number of collectibles.
	int				c;				// Collectibles collected.	
	int				flag; 			// 0 = game, 1 = win, 2 = lose
	char			course;			// Direction of the player.
	bool			walking;		// Walking or not.
}	t_init;

//The game structure is used to store the information of the game.
//	*mlx is used to store the connection to the display.
//	textures is used to store the textures of the game.
//	images is used to store the images of the game.
//	cell is used to store the information of the cells of the game.
//	*map is used to store the map of the game.
//	ship is used to store the position of the ship, the player.
//	path is used to store the path of the map.
//	moves is used to store the number of moves of the player.
//	counter is used to store the number of collectibles.
//	collec is used to store the number of collectibles.
//	flag is used to store the flag of the game. 0 = game, 1 = win, 2 = lose.
//	course is used to store the direction of the player.
//	walking is used to store if the player is walking or not.


// *** Function prototypes. ***

// *** ft_cells.c ***

t_init		**ft_fill(char **stat, t_coord size, t_coord now, t_init **game);
t_init		*ft_flood(t_init *game);

// *** ft_check_game.c ***

int			ft_check_obj(t_cell checked, t_cell objects);
int			ft_check_obj_nbr(t_cell objects);
int			ft_check_form(t_init *game);
int			ft_check_borders(t_init *game);

// *** ft_check_tools.c ***

int 		ft_check_failed(t_init *game, t_cell objects);
int			ft_check_ber(char *file);
void		ft_check_empty_line(t_init game, char *line);
t_init		**ft_check_cell(t_init	**game, char check);
int			ft_key_check(t_init *game);

// *** ft_drawing_moves.c ***

void		ft_ship_go_up(t_init *game, t_coord p, int step);
void		ft_ship_go_down(t_init *game, t_coord p, int step);
void		ft_ship_go_right(t_init *game, t_coord p, int step);
void		ft_ship_go_left(t_init *game, t_coord p, int step);

// *** ft_drawing_tools.c ***

t_map		*ft_add_line(char *line);
void		ft_last_line(t_init *game, t_map *new);
void		ft_drawing_map(t_init *game);
void		ft_drawing_imgs(t_init *game, char img, t_coord p);
void		ft_drawing_ship(t_init *game, t_coord p);

// *** ft_free_tools.c ***

void		ft_free_all(t_init *game, int error);
void		ft_free_stack(t_map **stack);
void		ft_free_txt(t_init **game);
void		ft_free_img(t_init **game);
char		**free_status_a(char **status_a, int size);

// *** ft_initialize.c ***

t_init		*ft_initialize_game(t_init *init);
int			ft_start_map(char *path);
t_map		*ft_map_init(t_init *game);
void		ft_init_txts(t_init *game);
void		ft_init_imgs(t_init *game);

// *** ft_materials.c ***

t_init		*ft_find_ship(t_init *ship);
void		ft_objs_init(t_cell *obj);
t_cell		ft_count_obj(t_map *map);

// *** ft_mlx_init.c ***

void		ft_mlx_init(t_init *gm);

// *** ft_moves.c ***

void		ft_move_ship_right(t_init *game, int y, int x);
void		ft_move_ship_left(t_init *game, int y, int x);
void		ft_move_ship_up(t_init *game, int y, int x);
void		ft_move_ship_down(t_init *game, int y, int x);

// *** ft_tools.c ***

void		ft_map_error(char *str);
int			ft_map_x(t_map *width);
int			ft_map_y(t_map *height);
void		ft_game_over_(void);

// *** so_long.c ***

char		**ft_status_map(t_init *game);
void		ft_key_press(struct mlx_key_data key_data, void *date);
int			ft_map(t_init **game);
//int			main(int argc, char **argv);

#endif;