/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:50:52 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/26 13:20:06 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

#define SUCCESS 0
#define ERROR 1

# define WIDTH 1920
# define HEIGHT 1080

# define COL_RED		0xFF0000FF
# define COL_GREEN		0x00FF00FF
# define COL_BLUE		0x0000FFFF
# define COL_WHITE		0xFFFFFFFF
# define COL_BLACK		0x000000FF
# define COL_DISCO		0x9A1F6AFF
# define COL_BRICK_RED	0xC2294EFF
# define COL_FLAMINGO	0xEC4B27FF
# define COL_JAFFA		0xEF8633FF
# define COL_SAFFRON	0xF3AF3DFF
# define COL_BG 		0x050203FF
# define COL_LINE		0xF8F7edFF
# define COL_LINE2		0x8B0000C8
# define COL_PINK		0xFFC0CBFF
# define COL_RAY		0xADD8E6FF
# define COL_GREY		0x40808080


# define ERR_INFILE "Wrong file type"
# define ERR_ARG "Invalid amount of arguments"
# define ERR_OPEN "File cannot be opened"
# define ERR_MALLOC "Malloc error"
# define ERR_MLX "MLX error"

#define FIXED_POINT_SCALE 1000
#define PI 3.14159265
#define DEGREE 0.0174532925 //one degree in radians (1° × π / 180°)
#define PLAYER_SPEED 2
#define SENSITIVITY 0.0008
#define BLOCK_SIZE 128
#define GRID_GAP 1
#define FOV PI / 3;
#define SPACE_AROUND_MAP 5


typedef struct	s_point
{
	int x;
	int y;
} t_point;


typedef struct s_ray
{
	float	angle;
	int		**map;
	double	pxpy[2];
	double	rxry[2];
	double	xoyo[2];
	int		dist_v;
	int		dist_h;
	int		dist;
	int		cols;
	int		rows;
	int		hor_x;
	mlx_image_t		*wall;
	bool	is_door;
	bool	open_door;
	int		dir_hor;
	int		dir_ver;
	double	tex_x;
}	t_ray;
typedef struct s_check
{
	int	player_count;
	int longest_line;
	int	cur_file_line;
	int map_lines;
}				t_check;


typedef struct s_player
{
	double		dir;
	double		px;
	double		py;
	double		dposx;
	double		dposy;
	bool		col_front;
	bool		col_back;
	bool		col_right;
	bool		col_left;
}	t_player;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_texture_t	*door;
}	t_textures;

typedef struct s_walls
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*ea;
	mlx_image_t	*we;
	mlx_image_t *door;
}	t_walls;

typedef struct s_scene
{
	t_player	player;
	int			**map;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			floor;
	int			ceiling;
	int			ceiling_rgb[3];
	int			floor_rgb[3];
	uint32_t	col_floor;
	uint32_t	col_ceiling;
	int			cols;
	int			rows;
	int			minimap_status;
}	t_scene;

typedef struct s_data
{
	mlx_t		*m;
	mlx_image_t	*image;
	mlx_image_t	*txtr;
	t_textures	*txtrs;
	t_walls		*walls;
	int			s_width;
	int			s_height;
	char		*file;
	int			fd;
	t_scene		scene;
}	t_data;


//Map parsing
int		check_filetype(char *filename, char *filetype);
void	check_and_parse_file(t_data *data, t_check *check);
void	parse_file_for_walls_and_colours(t_data *data, t_check *check);
void	fill_map(t_data *data, t_check *check);
void	read_file_for_map(t_data *data, t_check *check);
char	*skip_spaces(char *line);
unsigned int	rgb_to_hex(int r, int g, int b, int alpha);
void	read_file_for_longest_map_line(t_data *data, t_check *check);
void	check_and_set_texttr_and_col_lines(t_data *data, t_check *check);
void	check_map_lines(t_data *data, t_check *check);
void	read_file_for_longest_and_lines(t_data *data, t_check *check);
void	allocate_map(t_data *data);
void	check_player(t_data *data);
void	flood_fill(t_data *data, t_point size, t_point cur, int to_fill);
void 	fill_maze_if_spaces(t_data *data);
char	*copy_str(t_data *data, char *line);

//Map drawing
void	draw_scene(t_data *data);
void	draw_line(t_data *data, t_ray *ray, int vert_or_hor, double angle);

int		pixel_ok(t_data *data, int x, int y);
void	draw_ceiling_and_floor(t_data *data);
int		adjust_opacity(int color, float opacity);
uint32_t	get_colour(int rgb[3]);
void draw_minimap(t_data *data);

//initialize
void	init_data(t_data *data, char **argv);
void	init_z_factor(t_data *data);
void	init_ray(t_data *data, t_ray *ray, double ray_angle);
void	init_check(t_check *check);

//raycasting
double	normalize_angle(double angle);
void	raycaster(t_data *data);
void	cast_one_ray(t_data *data, t_ray *ray);
int		cast_rays(t_data *data);
int	cast_collission_ray(t_data *data, double ray_angle, double x, double y);
void	cast_door_ray(t_data *data, double ray_angle, double x, double y);
void	vertical_cast(t_ray *ray);
void	horizontal_cast(t_ray *ray);

//raycaster utils
int		ray_len(t_ray *ray);
void 	set_door(t_data *data, int x, int y);

//player handling
void	collisions(t_data *data);
void	move_player_forward(t_player *player);
void	move_player_backward(t_player *player);
void	move_player_left(t_player *player);
void	move_player_right(t_player *player);
void	move_right_wall(t_player *player);
void	move_left_wall(t_player *player);

//utils
int		ft_atoi_hex(char *str);


//hooks
void	my_keyhook(void *param);
void	my_keyhook2(mlx_key_data_t keydata, void* param);
void	my_mouse_hook(t_data *data);
void	turn_player(t_player *player, double angle);

//free and error
void	ft_free_data_and_array_error(t_data *data, char **array, char *error);
void	ft_free_data_and_exit(t_data *data);
void	ft_error(t_data *data, char *error);
void	ft_free_data_and_error(t_data *data, char *error);
void	ft_free_double_array(char **array);

//textures
void	get_textures(t_data *data);

//draw_utils
void calculate_measurements(t_data *data, int wall_height, int *start, int *end);
float calculate_opacity(int ray, int nbr_of_rays, int start, int end);
int squared_distance(int x1, int y1, int x2, int y2);
uint32_t darken_color(uint32_t color, double factor);


void print_parsing(t_data *data);

#endif