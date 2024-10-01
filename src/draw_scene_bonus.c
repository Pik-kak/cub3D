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

int	pixel_ok(int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        return (1);
    return (0);
}


void fill_square(mlx_image_t *img, int x, int y, int color)
{
    int start_x = x * (IMG_SIZE);
    int start_y = y * (IMG_SIZE);
    int i = 0;
    int j;

    while (i < IMG_SIZE - 1)
    {
        j = 0;
        while (j < IMG_SIZE -1)
        {
            if (pixel_ok(start_x + j, start_y + i))
                mlx_put_pixel(img, start_x + j, start_y + i, color);
            j++;
        }
        i++;
    }
}


void draw_tile(t_scene *scene, mlx_image_t *img, int x, int y)
{
	if (scene->map[y][x] == 1)
		fill_square(img, x, y, COL_FLAMINGO);
	else
		fill_square(img, x, y, COL_BLUE);
}


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

/*mlx_texture_t* load_player_sprites(int degree)
{
	
	if (degree > 0 && degree < PI / 4)
		return (mlx_load_png("./sprites/minimap/playerNE.png"));
	else if (degree >= PI / 4 && degree < PI / 2)
		return (mlx_load_png("./sprites/minimap/playerE.png"));
	else if (degree >= PI / 2 && degree < PI - (PI / 4))
		return (mlx_load_png("./sprites/minimap/playerSE.png"));
	else if (degree >= PI - (PI / 4) && degree < PI)
		return (mlx_load_png("./sprites/minimap/playerS.png"));
	else if (degree >= PI && degree < PI + (PI / 4))
		return (mlx_load_png("./sprites/minimap/playerSW.png"));
	else if (degree >= PI + (PI / 4) && degree < PI + (PI / 2))
		return (mlx_load_png("./sprites/minimap/playerW.png"));
	else if (degree >= PI + (PI / 2) && degree < PI  * 2 - (PI / 4))
		return (mlx_load_png("./sprites/minimap/playerNW.png"));
	else
		return (mlx_load_png("./sprites/minimap/playerN.png"));
}*/

void draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	int y;
	
	y = -radius;
	while (y <= radius)
	{
		int x = -radius;
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

void draw_nose(t_data *data, t_player *player, int length, int width, int color)
{
	double dir = player->direction;
	int half_width = width / 2;
	int i = 0;

	while (i < length)
	{
		int center_x = player->px + i * cos(dir);
		int center_y = player->py + i * sin(dir);

		int w = -half_width;
		while (w <= half_width)
		{
			int offset_x = w * cos(dir + PI / 2);
			int offset_y = w * sin(dir + PI / 2);
			int xn = (int)round(center_x + offset_x);
			int yn = (int)round(center_y + offset_y);

			if (pixel_ok(xn, yn))
				mlx_put_pixel(data->image, xn, yn, color);
			w++;
		}
		i++;
	}
}


  

void draw_player(t_data *data)
{
	t_player *player;

	player = &data->scene.player;
	draw_circle(data, player->px, player->py, 5, COL_LINE);
	draw_nose(data, player, 16, 4, COL_LINE);
}
/*void draw_player_icon(t_data *data, mlx_image_t *image)
{
	mlx_texture_t *pl_text;
	
	int plx = data->scene.player.px;

	int ply = data->scene.player.py;

	pl_text = load_player_sprites(data->scene.player.direction);
	if (!pl_text)
	{
		ft_free_data_and_error(data, "Error loading sprite texture.");
		return;
	}
	data->scene.player.player_icon = mlx_texture_to_image(data->m, pl_text);

	if (!data->scene.player.player_icon)
		ft_free_data_and_error(data, "Error creating player icon from texture.");
	mlx_delete_texture(pl_text);
	if (mlx_image_to_window(data->m, data->scene.player.player_icon, plx, ply) == -1) 
		ft_free_data_and_error(data, ERR_MLX);
	mlx_set_instance_depth(&data->scene.player.player_icon->instances[0], 3);
}*/



void draw_scene(t_data *data) 
{
	mlx_delete_image(data->m, data->image);
	data->image = NULL;
	data->image = mlx_new_image(data->m, WIDTH, HEIGHT);
	if (!data->image)
		ft_free_data_and_error(data, ERR_MLX);
	draw_map(data, data->image);
	//draw_one_ray(data, data->scene.player.direction, data->scene.player.px, data->scene.player.py);
	draw_player(data);
	collisions(data);

	//draw_player_icon(data, data->image);
	
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1) 
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, ERR_MLX);
	}
	mlx_set_instance_depth(&data->image->instances[0], 2);
}


