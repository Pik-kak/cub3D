/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/26 13:37:59 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"


int adjust_opacity(int color, float opacity)
{
	if (opacity > 1.0)
		opacity = 1.0;
	else if (opacity < 0.0)
		opacity = 0.0;
	int red = (color >> 24) & 0xFF;
	int green = (color >> 16) & 0xFF;
	int blue = (color >> 8) & 0xFF;
	int alpha = (int)((color & 0xFF) * opacity);
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_colour(int rgb[3])
{
	uint32_t	colour;
	uint32_t	a;

	a = 255;
	colour = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | a);
	return (colour);
}


/* ==============================
 * If pixel is out of screen does not draw it 
 * prevents segfault
 * ==============================
 */

int	pixel_ok(t_data *data, int x, int y)
{
	if (x >= 0 && x < data->s_width && y >= 0 && y < data->s_height)
		return (1);
	return (0);
}

/* ==============================
 * Draws one block filled with same color 
 * leaves last pixels empty to make grid
 * ==============================
 */


void fill_square(t_data *data, mlx_image_t *img, int x, int y, int color, int xo, int yo)
{
	int start_x; 
	int start_y;
	int i;
	int j;

	start_x = xo * (BLOCK_SIZE / 6) + BLOCK_SIZE / 12 - (int)data->scene.player.px % BLOCK_SIZE / 6;
	start_y = yo * (BLOCK_SIZE / 6) + BLOCK_SIZE / 12 - (int)data->scene.player.py % BLOCK_SIZE / 6;
	i = 0;
	while (i < BLOCK_SIZE / 6)
	{
		j = 0;
		while (j < BLOCK_SIZE / 6)
		{
			if (pixel_ok(data, start_x + j, start_y + i))
				mlx_put_pixel(img, start_x + j, start_y + i, darken_color(color, 0.4));
			j++;
		}
		i++;
	}
}


/* ==============================
 * Draws walls (1) or free space 
 * ==============================
 */

void draw_tile(t_data *data, t_scene *scene, mlx_image_t *img, int x, int y, int i, int j)
{
	if (scene->map[y][x] == 1)
	{
		fill_square(data, img, x, y, COL_LINE, i, j);
	} 
	else if(scene->map[y][x] == 0 || scene->map[y][x] == 'N' || scene->map[y][x] == 'S' || \
	scene->map[y][x] == 'E' || scene->map[y][x] == 'W')
	{
		fill_square(data, img, x, y, COL_GREEN, i, j);
	}
	else
		fill_square(data, img, x, y, COL_BRICK_RED, i, j);
}

/* ==============================
 * Draws player "body" as circlew
 * 
 * ==============================
 */
void draw_circle(t_data *data, int radius, int color)
{
	int y;
	int x;
	int cxy[2];
	int pxy[2];
	

	cxy[0] = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12;
	cxy[1] = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				pxy[0] = cxy[0] + x;
				pxy[1] = cxy[1] + y;
				if (pixel_ok(data, pxy[0], pxy[1]))
					mlx_put_pixel(data->image, pxy[0], pxy[1], color);
			}
			x++;
		}
		y++;
	}
}

/* ==============================
 * Draws player "nOSE" as circle
 * Calculate the center coordinates for the current length
 * Draw two pixels side by side
 * ==============================
 */

void draw_nose(t_data *data, int length, int color)
{
	double dir; 
	int c_x;
	int c_y;
	int i;

	dir = data->scene.player.direction;
	i = 0;

	while (i < length)
	{
		c_x = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12 + (i * cos(dir));
		c_y = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12 + (i * sin(dir));
		if (pixel_ok(data, c_x + 1 * sin(dir), c_y - 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x + 1 * sin(dir), c_y - 1 * cos(dir), color);
		if (pixel_ok(data, c_x - 1 * sin(dir), c_y + 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x - 1 * sin(dir), c_y + 1 * cos(dir), color);
		i++;
	}
}


void draw_player(t_data *data)
{
	draw_circle(data, 4, COL_WHITE);
	draw_nose(data, 8, COL_WHITE);
}


void draw_minimap_box(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < 2 * BLOCK_SIZE)
	{
		x = 0;
		while (x < 2 * BLOCK_SIZE)
		{
			if (x < 40 || y < 40 || x > 2 * BLOCK_SIZE - 40 || y > 2 * BLOCK_SIZE - 40)
			{
				if (pixel_ok(data, x, y))
					mlx_put_pixel(data->image, x, y, data->scene.col_ceiling);
			}
			x++;
		}
		y++;
	}
}

/* ==============================
 * Draws map tile by tile
 * ==============================
 */


void draw_minimap(t_data *data)
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int i;
	int j;
	
	start_y = (int)data->scene.player.py / BLOCK_SIZE - 5;
	end_x = (int)data->scene.player.px / BLOCK_SIZE + 5;
	end_y = (int)data->scene.player.py / BLOCK_SIZE + 5;
	if (start_y < 0)
		start_y = 0;
	if (end_x > data->scene.cols)
		end_x = data->scene.cols;
	if (end_y > data->scene.rows)
		end_y = data->scene.rows;
	i = 1;
	while (start_y < end_y)
	{
		j = 1;
		start_x = (int)data->scene.player.px / BLOCK_SIZE - 5;
		if (start_x < 0)
			start_x = 0;
		while (start_x < end_x)
		{
			draw_tile(data, &data->scene, data->image, start_x, start_y, j, i);
			start_x++;
			j++;
		}
		start_y++;
		i++;
	}
	draw_minimap_box(data);
	draw_player(data);
}


void draw_scene(t_data *data) 
{
	mlx_delete_image(data->m, data->image);
	data->image = mlx_new_image(data->m, data->s_width, data->s_height);
	if (!data->image)
		ft_free_data_and_error(data, "MLX error");
	collisions(data);
	cast_rays(data);
	if (data->scene.minimap_status == 3)
		draw_minimap(data);
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1)
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, "MLX error");
	}
	mlx_set_instance_depth(&data->image->instances[0], 2);
}


/*void draw_scene(t_data *data) 
{	
	data->m = mlx_init(data->s_width, data->s_height, "Cub3D", false);
	if (!data->m)
		ft_free_data_and_error(data, "MLX error");
	init_window(data);
	data->image = mlx_new_image(data->m, data->s_width, data->s_height);
	if (!data->image)
		ft_free_data_and_error(data, "MLX error");
	else if (data->scene.minimap_status == 1 && data->mimimap_image)
	{
		mlx_delete_image(data->m, data->mimimap_image);
		data->mimimap_image = NULL;
	}
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1)
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, "MLX error");
	}
	//mlx_set_instance_depth(&data->image->instances[0], 2);
}
*/
