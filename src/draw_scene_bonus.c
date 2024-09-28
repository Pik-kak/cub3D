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
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		return (1);
	return (-1);
}


void fill_square(mlx_image_t *img, int x, int y, int color)
{
	
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = x * (IMG_SIZE + 2);
	start_y = y * (IMG_SIZE + 2);
	i = 0;
	while (i < IMG_SIZE)
	{
		j = 0;
		while (j < IMG_SIZE)
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



mlx_texture_t* load_player_sprites(int degree)
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
}

void draw_player_icon(t_data *data, mlx_image_t *image)
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
}


void draw_scene(t_data *data) 
{
	mlx_delete_image(data->m, data->image);
	data->image = NULL;
	data->image = mlx_new_image(data->m, WIDTH, HEIGHT);
	if (!data->image)
		ft_free_data_and_error(data, ERR_MLX);
	draw_map(data, data->image);
	draw_player_icon(data, data->image);
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1) 
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, ERR_MLX);
	}
	mlx_set_instance_depth(&data->image->instances[0], 2);
}


