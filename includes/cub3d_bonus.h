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


# define ERR_INFILE "Wrong file type"
# define ERR_ARG "Invalid amount of arguments"
# define ERR_OPEN "File caannot be opened"
# define ERR_MALLOC "Malloc error"
# define ERR_MLX "MLX error"

#define FIXED_POINT_SCALE 1000
#define PI 3.14159265
#define DEGREE 0.0174532925 //one degree in radians (1° × π / 180°)
#define PLAYER_SPEED 0.4
#define SENSITIVITY 0.002
#define BLOCK_SIZE 64
#define GRID_GAP 1
#define FOV PI / 3;

typedef struct s_ray
{
	int		**map;
	double	pxpy[2];
	double	rxry[2];
	double	xoyo[2];
	int		dist_v;
	int		dist_h;
	int		cols;
	int		rows;
}	t_ray;

typedef struct s_check
{
	int	fd;
	int	player_count;
	int longest_line;
	int	first_map_line;
	int map_lines;
}				t_check;


typedef struct s_player
{
	double		direction;
	double		px;
	double		py;
	double		dposx;
	double		dposy;
	bool		col_front;
	bool		col_back;
	bool		col_right;
	bool		col_left;
}	t_player;

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
	int			cols;
	int			rows;
}	t_scene;

typedef struct s_data
{
	mlx_t		*m;
	mlx_image_t	*image;
	int			s_width;
	int			s_height;
	char		*file;
	int			fd;
	t_scene		scene;
}	t_data;


//Map parsing
int		check_file_type(t_data *data, t_check *check);
void	check_and_parse_file(t_data *data, t_check *check);
void 	parse_file_for_walls_and_colours(t_data *data, t_check *check);

void	read_file_for_map(t_data *data, t_check *check);
char	*skip_spaces(char *line);
unsigned int	rgb_to_hex(int r, int g, int b, int alpha);
void read_file_for_longest_map_line(t_data *data, t_check *check);

//Map drawing
void	draw_scene(t_data *data);
void	draw_line(t_data *data, t_ray *ray, int vert_or_hor, double angle);
//void	set_offset(t_data *data);
int		pixel_ok(int x, int y);
//int32_t	get_col(t_point *start, t_point *end, t_data *data);
//void	bresenham_line(mlx_image_t *image, t_point s, t_point e, int32_t col);

//initialize
void	init_data(t_data *data, char **argv);
void	init_window(t_data *data);
void	init_z_factor(t_data *data);
void	init_ray(t_data *data, t_ray *ray, double ray_angle);
void	init_check(t_check *check);


//raycasting
double	normalize_angle(double angle);
void	raycaster(t_data *data);
int		cast_one_ray(t_data *data, double ray_angle, double x, double y, int flag);
int		cast_rays(t_data *data);

//player handling
void	collisions(t_data *data);

//rotate and center
//t_point	correct_point_offset(t_point *point, t_data *data);
//t_point	rotate(t_point point, t_data *data);
//t_point	rotate_x(t_point point, double angle);
//t_point	rotate_y(t_point point, double angle);
//t_point	rotate_z(t_point point, double angle);

//t_pixel	rotate_pix(t_pixel point, t_data *data);
//t_point	rotate_x_pix(t_pixel point, double angle);
//t_pixel	rotate_y_pix(t_pixel point, double angle);
//t_pixel	rotate_z_pix(t_pixel point, double angle);

//utils
int		ft_atoi_hex(char *str);
//void	set_colours(t_point *point);

//hooks
void	my_keyhook(void *param);
void	my_mouse_hook(t_data *data);
void	turn_player(t_player *player, double angle);

//free and error
void	ft_free_data_and_array_error(t_data *data, char **array, char *error);
void	ft_free_data_and_exit(t_data *data);
void	ft_error(char *error);
void	ft_free_data_and_error(t_data *data, char *error);
void	ft_free_double_array(char **array);

#endif