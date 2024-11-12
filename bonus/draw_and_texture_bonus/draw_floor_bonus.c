/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:23:50 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/05 17:16:21 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*void	draw_floor_texture(t_data *data, t_ray *ray, t_texture *txtr, int start)
{
	int			i;
	double		floor_dist;
	double		floor_x;
	double		floor_y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	i = start;
	while (i < data->s_height)
	{
		floor_dist = (data->s_height / (2.0 * i - data->s_height)) / cos(ray->angle - data->scene.player.dir);// Calculate distance to the floor at this row using perspective
		floor_x = data->scene.player.px + floor_dist * cos(ray->angle);// Calculate the world floor position based on ray direction and distance
		floor_y = data->scene.player.py + floor_dist * sin(ray->angle);
		tex_x = (int)(floor_x * ray->floor->width) % ray->floor->width;// Map the world position to texture coordinates
		tex_y = (int)(floor_y * ray->floor->height) % ray->floor->height;
		color = get_image_color(data, ray->floor, tex_x, tex_y);
		if (pixel_ok(data, txtr->raycount, i))
			mlx_put_pixel(data->image, txtr->raycount, i, color);
		i++;
	}
}*/
