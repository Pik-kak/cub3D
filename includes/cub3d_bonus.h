/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:13:30 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/19 11:15:16 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define COL_GREEN		0x00FF00FF
# define COL_BLUE		0x0000FFFF
# define COL_BRICK_RED	0xC2294EFF
# define COL_LINE		0xF8F7edFF
# define COL_WHITE		0xFFFFFFFF
# define PI 3.14159265
# define PLAYER_SPEED 8
# define SENSITIVITY 0.0008
# define BLOCK_SIZE 512
# define MINIMAP_DIV 4
# define SPACE_AROUND_MAP 5
# define BUFFER_SIZE 1024

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_minimap
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_minimap;

typedef struct s_texture
{
	int	start;
	int	end;
	int	raycount;
	int	wall_height;
}		t_texture;

typedef struct s_ray
{
	float		angle;
	int			**map;
	double		pxpy[2];
	double		rxry[2];
	double		xoyo[2];
	int			dist_v;
	int			dist_h;
	int			dist;
	int			cols;
	int			rows;
	int			hor_x;
	mlx_image_t	*wall;
	int			wall_height;
	bool		is_door;
	bool		open_door;
	double		tex_x;
}	t_ray;

typedef struct s_check
{
	int	player_count;
	int	longest_line;
	int	cur_file_line;
	int	map_lines;
	int	current_line;
}	t_check;

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
	mlx_image_t	*door;
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
	int			wand_pos;
	bool		wand_visible;
	int			door_timer;
	int			wand_timer;
	int			door_x;
	int			door_y;
	int			last_ray_dir;
}	t_scene;

typedef struct s_data
{
	mlx_t		*m;
	mlx_image_t	*image;
	mlx_image_t	*wand;
	mlx_image_t	*txtr;
	t_textures	*txtrs;
	t_walls		*walls;
	int			s_width;
	int			s_height;
	char		*file;
	int			fd;
	char		*buffer;
	t_scene		scene;
}	t_data;

//free_and_exit
void		free_elements(t_data *data);
void		ft_error(t_data *data, char *error);
void		ft_free_double_array(char **array);
void		ft_free_data_and_error(t_data *data, char *error, char *str);
void		ft_free_data_and_exit(t_data *data);
void		free_buffer_close_fd(t_data *data);

//init
void		init_data(t_data *data, char **argv);
void		init_check(t_check *check);
void		init_ray(t_data *data, t_ray *ray, double ray_angle);

//init2
void		init_buffer(t_data *data);

//parse_utils
int			check_map_line(char *line);
void		set_check(t_check *check, char *line);
int			check_filetype(char *filename, char *filetype);
char		*skip_spaces(char *line);
void		allocate_map(t_data *data);
//parse_utils2
char		*copy_str(t_data *data, char *pointer, char *line);
void		check_valid_color_value(t_data *data,
				char **spl, char *str, char *line);
void		check_amount_of_commas(t_data *data, char *str, char *line);

//copy_str
char		*copy_str(t_data *data, char *pointer, char *line);

//read_textr_col
void		set_texttr_and_col_lines(t_data *data, t_check *check);

//parse_textr_col
int			check_texture_line(t_data *data, char *line);
void		check_texture_file(t_data *data, char *file);
int			check_colour_line(t_data *data, char *line);

//draw_utils_color
uint32_t	get_img_col(t_data *data, mlx_image_t *image, int tex_x, int tex_y);
uint32_t	get_colour(int rgb[3]);
uint32_t	darken_color(uint32_t color, double factor);

//parse_map
void		check_map_lines(t_data *data, t_check *check);
void		read_file_for_longest_and_lines(t_data *data, t_check *check);
void		check_player(t_data *data);

//fill_map
void		fill_map(t_data *data, t_check *check, int row, int lines);
void		flood_fill(t_data *data, t_point size, t_point cur, int to_fill);
void		fill_maze_if_spaces(t_data *data);

//read_utils
char		*get_next_line_cub(t_data *data, int fd);

//draw_scene
void		draw_tile(t_data *data, t_minimap *mmap, int i, int j);
void		draw_circle(t_data *data, int radius, int color);
void		draw_nose(t_data *data, int length, int color);
void		draw_scene(t_data *data);

//draw_utils
void		calc_msrmnts(t_data *data, t_texture *tx, double w_hght, int r);
int			pixel_ok(t_data *data, int x, int y);

//draw_minimap
void		draw_minimap(t_data *data);

//textures
void		get_textures(t_data *data);

//raycaster_utils
int			ray_len(t_ray *ray);
void		set_door_open(t_data *data, int x, int y);
void		cast_door_spell(t_data *data, int x, int y);
void		spell_door(t_data *data);

//key_hooks
void		my_keyhook(void *param);
void		my_keyhook2(mlx_key_data_t keydata, void *param);
void		my_mouse_hook(t_data *data);
void		turn_player(t_player *player, double angle);
void		move_right_wall(t_player *player);
void		move_left_wall(t_player *player);

//player_movement
void		move_player_forward(t_player *player);
void		move_player_backward(t_player *player);
void		move_player_left(t_player *player);
void		move_player_right(t_player *player);

//wand.c
void		update_wand(t_data *data);

//raycaster
void		cast_door_ray(t_data *data, double ray_angle, double x, double y);
int			cast_collission_ray(t_data *data,
				double ray_angle, double x, double y);

//raycast_math
void		horizontal_cast(t_ray *ray);
void		vertical_cast(t_ray *ray);

//collissions
double		normalize_angle(double angle);
void		collisions(t_data *data);
void		cast_one_ray(t_data *data, t_ray *ray);

//draw_walls
int			cast_rays(t_data *data);

#endif