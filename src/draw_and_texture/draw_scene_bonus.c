/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/30 16:28:50 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ==============================
 * Draws one block filled with same color 
 * leaves last pixels empty to make grid
 * ==============================
 */
void	fill_square(t_data *data, int color, int xo, int yo)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = xo * (BLOCK_SIZE / 6) + BLOCK_SIZE / 12
		- (int)data->scene.player.px % BLOCK_SIZE / 6;
	start_y = yo * (BLOCK_SIZE / 6) + BLOCK_SIZE / 12
		- (int)data->scene.player.py % BLOCK_SIZE / 6;
	i = 0;
	while (i < BLOCK_SIZE / 6)
	{
		j = 0;
		while (j < BLOCK_SIZE / 6)
		{
			if (pixel_ok(data, start_x + j, start_y + i))
				mlx_put_pixel(data->image, start_x + j,
					start_y + i, darken_color(color, 0.4));
			j++;
		}
		i++;
	}
}

/* ==============================
 * Draws walls (1) or free space 
 * ==============================
 */
void	draw_tile(t_data *data, t_minimap *mmap, int i, int j)
{
	int	**map_c;
	int	x;
	int	y;

	x = mmap->start_x;
	y = mmap->start_y;
	map_c = data->scene.map;
	if (map_c[y][x] == 1)
	{
		fill_square(data, COL_LINE, i, j);
	}
	else if (map_c[y][x] == 0 || map_c[y][x] == 'N' || map_c[y][x] == 'S' || \
	map_c[y][x] == 'E' || map_c[y][x] == 'W')
	{
		fill_square(data, COL_GREEN, i, j);
	}
	else if (map_c[y][x] == 2 || map_c[y][x] == 3)
		fill_square(data, COL_BLUE, i, j);
	else
		fill_square(data, COL_BRICK_RED, i, j);
}

/* ==============================
 * Draws player "body" as circle
 * 
 * ==============================
 */
void	draw_circle(t_data *data, int radius, int color)
{
	int	y;
	int	x;
	int	cxy[2];
	int	pxy[2];

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
 * Draws player "nose"
 * Calculate the center coordinates for the current length
 * Draw two pixels in line side by side
 * ==============================
 */

void	draw_nose(t_data *data, int length, int color)
{
	double	dir;
	int		c_x;
	int		c_y;
	int		i;

	dir = data->scene.player.dir;
	i = 0;
	while (i < length)
	{
		c_x = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12 + (i * cos(dir));
		c_y = 6 * BLOCK_SIZE / 6 + BLOCK_SIZE / 12 + (i * sin(dir));
		if (pixel_ok(data, c_x + 1 * sin(dir), c_y - 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x + 1 * sin(dir),
				c_y - 1 * cos(dir), color);
		if (pixel_ok(data, c_x - 1 * sin(dir), c_y + 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x - 1 * sin(dir),
				c_y + 1 * cos(dir), color);
		i++;
	}
}

void	draw_player(t_data *data)
{
	draw_circle(data, 4, COL_WHITE);
	draw_nose(data, 8, COL_WHITE);
}

void	draw_minimap_box(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 2 * BLOCK_SIZE)
	{
		x = 0;
		while (x < 2 * BLOCK_SIZE)
		{
			if (x < 38 || y < 38 || x > 2 * BLOCK_SIZE - 38
				|| y > 2 * BLOCK_SIZE - 38)
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
void	set_minimap_bounds(t_data *data, t_minimap *mmap)
{
	mmap->start_y = (int)data->scene.player.py / BLOCK_SIZE - 5;
	mmap->end_x = (int)data->scene.player.px / BLOCK_SIZE + 5;
	mmap->end_y = (int)data->scene.player.py / BLOCK_SIZE + 5;
	if (mmap->start_y < 0)
		mmap->start_y = 0;
	if (mmap->end_x > data->scene.cols)
		mmap->end_x = data->scene.cols;
	if (mmap->end_y > data->scene.rows)
		mmap->end_y = data->scene.rows;
}

void	draw_minimap(t_data *data)
{
	t_minimap	mmap;
	int			i;
	int			j;

	i = 1;
	set_minimap_bounds(data, &mmap);
	while (mmap.start_y < mmap.end_y)
	{
		j = 1;
		mmap.start_x = (int)data->scene.player.px / BLOCK_SIZE - 5;
		if (mmap.start_x < 0)
			mmap.start_x = 0;
		while (mmap.start_x < mmap.end_x)
		{
			draw_tile(data, &mmap, j, i);
			mmap.start_x++;
			j++;
		}
		mmap.start_y++;
		i++;
	}
	draw_minimap_box(data);
	draw_player(data);
}

void	draw_scene(t_data *data)
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
