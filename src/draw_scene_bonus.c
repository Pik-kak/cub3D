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

void fill_square(t_data *data, mlx_image_t *img, int x, int y, int color)
{
	int start_x = x * (BLOCK_SIZE / 6);
	int start_y = y * (BLOCK_SIZE / 6);
	int i = 0;
	int j;

	while (i < BLOCK_SIZE / 6)
	{
		j = 0;
		while (j < BLOCK_SIZE / 6)
		{
			if (pixel_ok(data, start_x + j, start_y + i))
				mlx_put_pixel(img, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

/* ==============================
 * Draws walls (1) or free space 
 * ==============================
 */

void draw_tile(t_data *data, t_scene *scene, mlx_image_t *img, int x, int y)
{
	if (scene->map[y][x] == 1)
	{
		fill_square(data, img, x, y, COL_LINE);
	} //get_colour(scene->ceiling_rgb)
	else
	{
		int grey = get_rgba(128, 128, 128, 255);  // Start with a fully opaque grey
        int semi_transparent_grey = adjust_opacity(grey, 0.8);  // Adjust opacity to 50%
		fill_square(data, img, x, y, semi_transparent_grey);
	}
}


/* ==============================
 * Draws map tile by tile
 * ==============================
 */

void draw_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->scene.rows)
	{
		x = 0;
		while (x < data->scene.cols)
		{
			draw_tile(data, &data->scene, data->mimimap_image, x, y);
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

	cx = data->scene.player.px * (BLOCK_SIZE / 6) / BLOCK_SIZE;
	cy = data->scene.player.py * (BLOCK_SIZE / 6) / BLOCK_SIZE;
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
				if (pixel_ok(data, px, py))
					mlx_put_pixel(data->mimimap_image, px, py, color);
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
		c_x = (data->scene.player.px * (BLOCK_SIZE / 6) / BLOCK_SIZE) + (i * cos(dir));
		c_y = (data->scene.player.py * (BLOCK_SIZE / 6) / BLOCK_SIZE)+ (i * sin(dir));
		if (pixel_ok(data, c_x + 1 * sin(dir), c_y - 1 * cos(dir)))
			mlx_put_pixel(data->mimimap_image, c_x + 1 * sin(dir), c_y - 1 * cos(dir), color);
		if (pixel_ok(data, c_x - 1 * sin(dir), c_y + 1 * cos(dir)))
			mlx_put_pixel(data->mimimap_image, c_x - 1 * sin(dir), c_y + 1 * cos(dir), color);
		i++;
	}
}

void draw_player(t_data *data)
{
	draw_circle(data, 4, COL_WHITE);
	draw_nose(data, 8, COL_WHITE);
}

//if we scale the window we need to be able to scale all images. PROBLEM!

//this makes now different image for minimap , works with TAB


static void	draw_background(mlx_image_t *image, int32_t col)
{
	int	x;
	int	y;

	x = 0;
	while (x < (int)image->width)
	{
		y = -1;
		while (++y < HEIGHT)
			mlx_put_pixel(image, x, y, col);
		x++;
	}
}


void draw_scene(t_data *data) 
{
	
	mlx_image_t *bg;
	//mlx_delete_image(data->m, data->mimimap_image);
	mlx_delete_image(data->m, data->image);

	data->image = mlx_new_image(data->m, data->s_width, data->s_height);
	bg = mlx_new_image(data->m, data->s_width, data->s_height);
	
	if (!data->image)
		ft_free_data_and_error(data, "MLX error");


	/*data->mimimap_image = mlx_new_image(data->m, data->s_width, data->s_height);
	if (!data->mimimap_image)
		ft_free_data_and_error(data, "MLX error");*/
	collisions(data);
	cast_rays(data, data->image);
	//draw_flaslight(data);
	//draw_minimap(data);
	//draw_player(data);
	if (mlx_image_to_window(data->m, bg, 0, 0) == -1)
	{
		mlx_delete_image(data->m, bg);
		ft_free_data_and_error(data, "MLX error");
	}
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1)
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, "MLX error");
	}
	/*	if (mlx_image_to_window(data->m, data->mimimap_image, 0, 0) == -1)
	{
		mlx_delete_image(data->m, data->image);
		mlx_delete_image(data->m, data->mimimap_image);
		ft_free_data_and_error(data, "MLX error");
	}
	mlx_set_instance_depth(&data->mimimap_image->instances[0], data->scene.minimap_status);*/
	mlx_set_instance_depth(&bg->instances[0], 1);
	mlx_set_instance_depth(&data->image->instances[0], 2);
	mlx_delete_image(data->m, bg);
}



