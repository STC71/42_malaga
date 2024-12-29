/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-12 12:49:04 by sternero          #+#    #+#             */
/*   Updated: 2024-12-12 12:49:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ----- Libraries ---------------------------------------------------------- //

# include "../libft/libft.h"				// to use our libft functions
# include "../MLX42/include/MLX42/MLX42.h"	// to use MLX42 functions

# include <errno.h>		// to use errno, perror, and more
# include <fcntl.h>		// to open, close, and more
# include <math.h>		// to use math functions
# include <stdio.h>		// to printf, perror, and more
# include <stdlib.h>	// to malloc, free, and more
# include <string.h>	// to strdup, strlen, and more
# include <unistd.h>	// to write, read, and more

// ----- Colors ------------------------------------------------------------- //

# define BOLD		"\033[1m"			
# define BLUE		"\x1b[34m"
# define CLEAR		"\033[2J"			// clear the screen
# define CYAN		"\x1b[36m"
# define GREEN		"\x1b[32m"
# define GREYM		"\x1B[38;5;245m"	// grey medium
# define GREYM2		"\x1B[38;5;250m"	// more white than GREYM
# define MAGENTA	"\x1b[35m"
# define RED		"\x1b[31m"
# define RESET		"\x1b[0m"			// reset the color to default
# define WHITE		"\033[37m"
# define YELLOW		"\x1b[33m"

// ----- Defines ------------------------------------------------------------ //

# define FAILURE	1	// define FAILURE as 1
# define SUCCESS	0	// define SUCCESS as 0

# define WIDTH 1920		// define the widht of the window as 1920
# define HEIGHT 1280	// define the height of the window as 1280
# define WALL_SIZE 640	// define the size of the wall as 640
# define FOV 60			// define the field of view as 60

// ----- Structures --------------------------------------------------------- //

typedef struct s_texture
{
	char			*no_path;		// the path of the north texture
	char			*so_path;		// the path of the south texture
	char			*we_path;		// the path of the west texture
	char			*ea_path;		// the path of the east texture
	int				no_flag;		// the flag of the north texture
	int				so_flag;		// the flag of the south texture
	int				we_flag;		// the flag of the west texture
	int				ea_flag;		// the flag of the east texture
	int				c_flag;			// the flag of the ceiling color
	int				f_flag;			// the flag of the floor color
	unsigned int	c_color;		// the color of the ceiling
	unsigned int	f_color;		// the color of the floor
	mlx_texture_t	*no_texture;	// the north texture
	mlx_texture_t	*so_texture;	// the south texture
	mlx_texture_t	*we_texture;	// the west texture
	mlx_texture_t	*ea_texture;	// the east texture
}	t_texture;

typedef struct s_point
{
	int	x;							//the x coordinate of the point to draw
	int	y;							//the y coordinate of the point to draw
}	t_point;

typedef struct s_line
{
	int	x;				// the x coordinate of line relative to screen
	int	y;				// the current pixel index of the line (along y axis)
	int	y0;				// y start index of drawing texture
	int	y1;				// y end index of drawing texture
	int	tex_x;			// x coordinate of texture to draw
	int	tex_y;			// y coordinate of texture to draw
}	t_line;

typedef struct s_ray
{
	int			flag;				// the flag of the ray, if it hits a wall
	int			map_x;				// the x coordinate of the map
	int			map_y;				// the y coordinate of the map
	double		angle;				// the angle of the ray in radians
	double		angle_ret;			// the angle of the ray in radians 
	double		pos_x;				// the x coordinate of the player
	double		pos_y;				// the y coordinate of the player
	double		ray_dir_x;			// the x coordinate of the ray direction
	double		ray_dir_y;			// the y coordinate of the ray direction
	double		delta_dist_x;		// distance of the ray to the next x side
	double		delta_dist_y;		// distance of the ray to the next y side
	double		side_dist_x;		// distance of the ray to the next x side
	double		side_dist_y;		// distance of the ray to the next y side
	double		perp_wall_dist;		// the distance of the ray to the wall
	double		pixel_width_impact;	// the width of the pixel to draw
	double		hit;				// the hit point of the ray in the map
	double		hyp_distance;		// the hypotenuse distance of the ray
	double		ver_distance;		// the vertical distance of the ray
	double		step_x;				// the step of the ray in x direction
	double		step_y;				// the step of the ray in y direction
}	t_ray;

typedef struct s_player
{
	double	angle;					// the angle of the player in radians
	double	pos_x;					// the x coordinate of the player
	double	pos_y;					// the y coordinate of the player
	int		map_x;					// the x coordinate of the map
	int		map_y;					// the y coordinate of the map
	t_ray	ray[WIDTH];				// the array of rays of the player
}	t_player;

typedef struct s_map
{
	char	**map;					// the map of the game
	int		map_size_x;				// the size of the map in x
	int		map_size_y;				// the size of the map in y
	int		map_line;				// the line of the map
}	t_map;

typedef struct s_data
{
	int				ray_number;		// the number of rays used to draw the walls
	int				move;			// the flag to move the player
	char			*file;			// the file to read the map
	t_map			map;			// the map of the game
	t_player		player;			// the player of the game
	t_texture		textures;		// the textures of the game
	mlx_t			*mlx;			// the mlx instance used to create windows
	mlx_image_t		*background;	// the background image used to draw the map
	mlx_image_t		*walls;			// the walls image used to draw the walls
}	t_data;

// ----- Functions ---------------------------------------------------------- //

// ----- ft_action.c

void	ft_callback(void *value);
void	ft_play_game(t_data *info);
void	ft_start(t_data *info);

// ----- ft_calculations.c

void	ft_hipo_cal(t_ray *ray);
void	ft_get_player_to_wall(t_data *info, t_ray *ray);
void	ft_vert_cal(t_data *info, t_ray *ray);
void	ft_get_ang(t_data *info, char dir);
void	ft_get_size_map(t_map *map);

// ----- ft_check_1.c

int		ft_check_map(t_data *data);
void	ft_check_angles(double *ang, double i);
bool	ft_check_valid_mov(t_data *info, double mov_x, double mov_y);
bool	ft_check_next_move(t_data *info, double mov_x, double mov_y);
int		ft_check_file(char *file, char *img, int i);

// ----- ft_check_2.c

int		ft_check_imgs(char **c, int i);
int		ft_check_cardinal(char **c, int line);
int		ft_check_path(char **c, int i);
int		ft_check_bad_argument(char **c, int i);
int		ft_check_map_closed(t_data *info);

// ----- ft_check_3.c

void	ft_check_pos_player(t_data *info, char **map);
int		ft_check_end_file(char **map, int end);
int		ft_check_spaces(char **map);
int		ft_check_spaces_map_2(char **map, int i, int j, int res);
int		ft_check_spaces_map(char **map, int i, int j, int res);

// ----- ft_check_4.c

int		ft_check_sides(char **map);
int		ft_check_left_file(char *c);
int		ft_check_right_file(char *c);
int		ft_check_start_file(char **map);
int		ft_check_text(t_data *info, char **c, int *i, int line);

// ----- ft_check_5.c

int		ft_check_cub_ext(char *file, int *i);
int		ft_check_first_last(t_data *info, char **map);
int		ft_check_wrongs(char c);
int		ft_check_inside(char **map);
int		ft_check_extra(char *map);

// ----- ft_colors_1.c

int		ft_check_colors(char **c, int i);
void	ft_error_color(char **path, int r, int g, int b);
int		ft_check_colors_num(char **c, int line);

// ----- ft_colors_2.c

// ----- ft_errors.c

void	ft_bad_letter(char **map, int line, int i);
void	ft_error_border(int line, int flag);
void	ft_error_bad_spc(int line, int i);
void	ft_error_rgb_num(char **rgb, int i, int j, int line);

// ----- ft_impact_ray.c

void	ft_init_ray(t_data *info);
void	ft_impact_ver(t_ray *ray);
void	ft_impact_hor(t_ray *ray);

// ----- ft_init.c

void	ft_init_imgs_values(t_data *info);
void	ft_init_player(t_data *info);
void	ft_init_imgs(t_data *info);
int		ft_var_setup(t_data *info);
void	ft_init_walls(t_data *info, mlx_image_t **img);

// ----- ft_moves.c

void	ft_movements(t_data *info);
void	ft_move_player(t_data *info, double ang);
void	ft_handle_rot(t_data *info);

// ----- ft_paint.c

void	ft_paint_column(t_data *info, t_ray *ray, int x);
int		ft_paint(t_data *info);
void	ft_add_text_path_2(t_data *info, char **c);
void	ft_add_text_path(t_data *info, char **c);

// ----- ft_parse_1.c

int		ft_map_closed(t_data *info);
int		ft_parse(char *cub, t_data *info);
int		ft_check_comma(char **c);
void	ft_missing_id(t_data *info, int *fd, int i);
int		ft_missing_num(t_data *info);

// ----- ft_parse_2.c

int		ft_get_map(t_data *info, int fd);
char	*ft_new_str(char *c, int fd);
int		ft_players_count(char **map);
int		ft_players_num(char **map);

// ----- ft_ray.c

void	ft_init_values_ray(t_data *info, t_ray *ray);
void	ft_shoot_ray(t_data *info, t_player *player);
void	ft_get_impact_ray(t_data *info, t_ray *ray);
void	ft_search_wall(t_data *info, t_ray *ray);

// ----- ft_remove.c

char	*ft_del_nl(char *str);
void	ft_del_imgs(t_data *data);
void	ft_free_imgs(t_data *data);

// ----- ft_tools.c

int		ft_split_map(t_data *info, char *map);
int		ft_split_line(char ***c, int fd);
char	*ft_trim_str(char *s1, char *set);
void	ft_new_fd(t_data *info, int i, int *fd);

// ----- ft_walls.c

int		ft_get_imgs_info(t_data *info, int *res, int *fd);
int		ft_get_walls(t_data *info, int *fd, int *res);
double	ft_size_wall(t_ray *ray);
void	ft_load_imgs(t_data *info);

// ----- other.c

unsigned int	ft_rgb_get(char **c);
unsigned int	ft_rgb_to_hex_split(char **c);
unsigned int	ft_rgb_to_hex(char **c);

uint32_t		ft_get_color(double x, double size, mlx_texture_t *txt);
uint32_t		ft_color_wall(t_data *info, t_ray *ray, double size);
uint32_t		ft_rgba(uint8_t pixels[4]);

#endif