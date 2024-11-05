/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:48:07 by kkauhane            #+#    #+#             */
/*   Updated: 2024/11/03 17:21:08 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ==============================
 * Draws one block filled with same color 
 * leaves last pixels empty to make grid
 * ==============================
 */

/*void	fill_square(t_data *data, int color, int xo, int yo)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = xo * (BLOCK_SIZE / MINIMAP_DIV / 6) + (BLOCK_SIZE / MINIMAP_DIV / 12)
		- ((int)data->scene.player.px % BLOCK_SIZE / MINIMAP_DIV / 6);
	start_y = yo * (BLOCK_SIZE / MINIMAP_DIV / 6) + (BLOCK_SIZE / MINIMAP_DIV / 12)
		- ((int)data->scene.player.py % BLOCK_SIZE / MINIMAP_DIV / 6);
	i = 0;
	while (i < BLOCK_SIZE / MINIMAP_DIV / 6)
	{
		j = 0;
		while (j < BLOCK_SIZE / MINIMAP_DIV / 6)
		{
			if (pixel_ok(data, start_x + j, start_y + i))
				mlx_put_pixel(data->image, start_x + j,
					start_y + i, darken_color(color, 0.4));
			j++;
		}
		i++;
	}
}*/


void	fill_square(t_data *data, int color, int xo, int yo)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;
	int block_size;

	block_size = BLOCK_SIZE / MINIMAP_DIV;

	start_x = xo * (block_size / 6) + block_size / 12 - (int)data->scene.player.px % BLOCK_SIZE / 6 / MINIMAP_DIV;
	start_y = yo * (block_size / 6) + block_size / 12 - (int)data->scene.player.py % BLOCK_SIZE / 6 / MINIMAP_DIV;
	i = 0;
	while (i < block_size/ 6)
	{
		j = 0;
		while (j < block_size / 6)
		{
			if (pixel_ok(data, start_x + j, start_y + i))
				mlx_put_pixel(data->image, start_x + j, start_y + i, darken_color(color, 0.4));
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


void	draw_minimap_box(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 2 * BLOCK_SIZE / MINIMAP_DIV)
	{
		x = 0;
		while (x < 2 * BLOCK_SIZE / MINIMAP_DIV)
		{
			if (x < 38 || y < 38 || x > 2 * BLOCK_SIZE / MINIMAP_DIV - 38
				|| y > 2 * BLOCK_SIZE / MINIMAP_DIV - 38)
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
	mmap->start_y = (int)data->scene.player.py / BLOCK_SIZE - 5 ;
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
	draw_circle(data, 4, COL_WHITE);
	draw_nose(data, 8, COL_WHITE);
}
/*void	draw_player(t_data *data)
{
	draw_circle(data, 4, COL_WHITE);
	draw_nose(data, 8, COL_WHITE);
}

void	draw_minimap_box(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 2 * BLOCK_SIZE /MINIMAP_DIV)
	{
		x = 0;
		while (x < 2 * BLOCK_SIZE /MINIMAP_DIV)
		{
			if (x < 38 || y < 38 || x > 2 * BLOCK_SIZE /MINIMAP_DIV - 38
				|| y > 2 * BLOCK_SIZE /MINIMAP_DIV - 38)
			{
				if (pixel_ok(data, x, y))
					mlx_put_pixel(data->image, x, y, data->scene.col_ceiling);
			}
			x++;
		}
		y++;
	}
}*/

/* ==============================
 * Draws map tile by tile
 * ==============================
 */
/*void	set_minimap_bounds(t_data *data, t_minimap *mmap)
{
	mmap->start_y = (int)data->scene.player.py / BLOCK_SIZE /MINIMAP_DIV - 5;
	mmap->end_x = (int)data->scene.player.px / BLOCK_SIZE /MINIMAP_DIV + 5;
	mmap->end_y = (int)data->scene.player.py / BLOCK_SIZE /MINIMAP_DIV + 5;
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
		mmap.start_x = (int)data->scene.player.px / BLOCK_SIZE /MINIMAP_DIV - 5;
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
}*/
