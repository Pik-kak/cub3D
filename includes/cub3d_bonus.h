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

# define WIDTH 1920
# define HEIGHT 1080

# define COL_DISCO		0x9A1F6AFF
# define COL_BRICK_RED	0xC2294EFF
# define COL_FLAMINGO	0xEC4B27FF
# define COL_JAFFA		0xEF8633FF
# define COL_SAFFRON	0xF3AF3DFF
# define COL_BG 		0x050203FF
# define COL_LINE		0xF8F7edFF
# define COL_LINE2		0x8B0000C8
# define COL_BLUE		0x1B03A3FF
# define COL_PINK		0xFFC0CBFF


# define ERR_INFILE "Invalid data"
# define ERR_ARG "Invalid amount of arguments"
# define ERR_MALLOC "Malloc error"
# define ERR_MLX "MLX error"

#define FIXED_POINT_SCALE 1000
#define PI 3.14159265
#define PLAYER_SPEED 1.2
#define IMG_SIZE 64
#define GRID_GAP 1



typedef struct s_player
{
	mlx_image_t *player_icon;
	double		direction;
	double		px;
	double		py;
	double		dposx;
	double		dposy;
}	t_player;



typedef struct s_scene
{
	t_player	player;
	int			**map;
	int			cols;
	int			rows;
	
}	t_scene;


typedef struct s_data
{
	mlx_t		*m;
	mlx_image_t	*image;
	t_scene		scene;
}	t_data;




//Map drawing
void	draw_scene(t_data *data);
void	draw_line(t_data *data, int px, int py, double theta, int length);
//void	set_offset(t_data *data);
int		pixel_ok(int x, int y);
//int32_t	get_col(t_point *start, t_point *end, t_data *data);
//void	bresenham_line(mlx_image_t *image, t_point s, t_point e, int32_t col);

//initialize
void	init_data(int fd, t_data *data, char **argv);
void	init_z_factor(t_data *data);

//raycasting
void draw_one_ray(t_data *data, float ray_angle, float x, float y);


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

//free and error
void	ft_free_data_and_array_error(t_data *data, char **array, char *error);
void	ft_free_data_and_exit(t_data *data);
void	ft_error(char *error);
void	ft_free_data_and_error(t_data *data, char *error);
void	ft_free_double_array(char **array);

#endif