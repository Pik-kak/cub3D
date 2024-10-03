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

#include "../includes/cub3d_bonus.h"


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

int	pixel_ok(int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		return (1);
	return (0);
}

/* ==============================
 * Draws one block filled with same color 
 * leaves last pixels empty to make grid
 * ==============================
 */

void fill_square(mlx_image_t *img, int x, int y, int colour)
{
	int start_x = x * (BLOCK_SIZE);
	int start_y = y * (BLOCK_SIZE);
	int i = 0;
	int j;

	while (i < BLOCK_SIZE - 1)
	{
		j = 0;
		while (j < BLOCK_SIZE -1)
		{
			if (pixel_ok(start_x + j, start_y + i))
				mlx_put_pixel(img, start_x + j, start_y + i, colour);
			j++;
		}
		i++;
	}
}

/* ==============================
 * Draws walls (1) or free space 
 * ==============================
 */

void draw_tile(t_scene *scene, mlx_image_t *img, int x, int y)
{
	if (scene->map[y][x] == 1)
	{
		fill_square(img, x, y, COL_BLUE);
	} //get_colour(scene->ceiling_rgb)
	else
	{
		fill_square(img, x, y, get_colour(scene->floor_rgb));
	}
}

/* ==============================
 * Draws map tile by tile
 * ==============================
 */

void draw_map(t_data *data, mlx_image_t *image)
{
	int x;
	int y;

	y = 0;
	while (y < data->scene.rows)
	{
		x = 0;
		while (x < data->scene.cols)
		{
			draw_tile(&data->scene, image, x, y);
			x++;
		}
		y++;
	}
}

/* ==============================
 * Draws player "body" as circle
 * 
 * ==============================
 */
void draw_circle(t_data *data, int radius, int color)
{
	int y;
	int x;
	int cx;
	int cy;

	cx = data->scene.player.px;
	cy = data->scene.player.py;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				int px = cx + x;
				int py = cy + y;
				if (pixel_ok(px, py))
					mlx_put_pixel(data->image, px, py, color);
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
		c_x = data->scene.player.px + i * cos(dir);
		c_y = data->scene.player.py + i * sin(dir);
		if (pixel_ok(c_x + 1 * sin(dir), c_y - 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x + 1 * sin(dir), c_y - 1 * cos(dir), color);
		if (pixel_ok(c_x - 1 * sin(dir), c_y + 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x - 1 * sin(dir), c_y + 1 * cos(dir), color);
		i++;
	}
}

void draw_player(t_data *data)
{
	draw_circle(data, 7, COL_WHITE);
	draw_nose(data, 16, COL_WHITE);
}
//if we scale the window we need to be able to scale all images. PROBLEM!
void draw_scene(t_data *data) 
{
	mlx_delete_image(data->m, data->image);
	data->image = NULL;
	data->image = mlx_new_image(data->m, WIDTH, HEIGHT);
	if (!data->image)
		ft_free_data_and_error(data, ERR_MLX);
	draw_map(data, data->image);
	draw_player(data);
	collisions(data);

	cast_rays(data);

	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1) 
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, ERR_MLX);
	}
	mlx_set_instance_depth(&data->image->instances[0], 2);
}
