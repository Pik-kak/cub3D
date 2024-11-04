/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:23:50 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/04 17:28:41 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
void	draw_floor_texture(t_data *data, t_ray *ray, t_texture *txtr, int i)
{
	double		row_distance;
	double		floor_x;
	double		floor_y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	
	row_distance = (data->s_height / 2.0) / (i - (data->s_height / 2.0));
	//this is the distance of the row of blocks we're drawing
	floor_x = data->scene.player.px + row_distance * ray->rxry[0];
	floor_y = data->scene.player.py + row_distance * ray->rxry[1];

	tex_x = (int)(floor_x * ray->floor->width) % ray->floor->width;// Calculate texture coordinates
	tex_y = (int)(floor_y * ray->floor->height) % ray->floor->height;

	color = get_image_color(data, ray->floor, tex_x, tex_y);
	if (pixel_ok(data, txtr->raycount, i))
		mlx_put_pixel(data->image, txtr->raycount, i, color);
}*/