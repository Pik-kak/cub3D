/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 17:19:22 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

	cxy[0] = (6 * BLOCK_SIZE / MINIMAP_DIV / 6 + BLOCK_SIZE / MINIMAP_DIV / 12);
	cxy[1] = (6 * BLOCK_SIZE /MINIMAP_DIV / 6 + BLOCK_SIZE / MINIMAP_DIV / 12);
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
		c_x = (6 * BLOCK_SIZE / MINIMAP_DIV / 6
				+ BLOCK_SIZE / MINIMAP_DIV / 12 + (i * cos(dir)));
		c_y = (6 * BLOCK_SIZE / MINIMAP_DIV / 6
				+ BLOCK_SIZE / MINIMAP_DIV / 12 + (i * sin(dir)));
		if (pixel_ok(data, c_x + 1 * sin(dir), c_y - 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x + 1 * sin(dir),
				c_y - 1 * cos(dir), color);
		if (pixel_ok(data, c_x - 1 * sin(dir), c_y + 1 * cos(dir)))
			mlx_put_pixel(data->image, c_x - 1 * sin(dir),
				c_y + 1 * cos(dir), color);
		i++;
	}
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
