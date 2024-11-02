/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:48:07 by pikkak            #+#    #+#             */
/*   Updated: 2024/11/02 17:45:45 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
}*/

/* ==============================
 * Draws map tile by tile
 * ==============================
 */
/*void	set_minimap_bounds(t_data *data, t_minimap *mmap)
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
}*/
