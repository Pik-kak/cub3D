/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:39:16 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:39:38 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ================================
 * Draws a slice of the wall
 * Step tells us how much to move along the texture for each pixel we draw.
 * Tex_start initializes the texture position, centering the wall on the screen.
 * ================================
 */
void	draw_texture(t_data *data, t_ray *ray, t_texture *txtr, int i)
{
	double		step;
	double		tex_start;
	double		tex_y;
	uint32_t	color;

	step = 1.0 * ray->wall->height / txtr->wall_height;
	tex_start = (txtr->start - data->s_height / 2 + txtr->wall_height / 2)
		* step;
	while (i <= txtr->end)
	{
		if (tex_start >= ray->wall->height)
			tex_y = (tex_start - ray->wall->height);
		else
			tex_y = tex_start;
		tex_start += step;
		color = get_image_color(data, ray->wall, (int)ray->tex_x, tex_y);
		if (pixel_ok(data, txtr->raycount, i))
			mlx_put_pixel(data->image, txtr->raycount, i, color);
		i++;
	}
}

/* ===================================
 * Draws the ceiling, walls and floor
 * ===================================
 */
void	draw_walls(t_data *data, int ray_count, t_ray *ray, double wall_height)
{
	int			i;
	t_texture	txtr;

	i = 0;
	calculate_msrmnts(data, &txtr, wall_height);
	while (i < data->s_height)
	{
		if (i < txtr.start)
		{
			if (pixel_ok(data, ray_count, i))
				mlx_put_pixel(data->image, ray_count,
					i, data->scene.col_ceiling);
		}
		else if (i >= txtr.start && i < txtr.end)
		{
			txtr.raycount = ray_count;
			txtr.wall_height = wall_height;
			draw_texture(data, ray, &txtr, i);
			i = txtr.end;
		}
		else
			if (pixel_ok(data, ray_count, i))
				mlx_put_pixel(data->image, ray_count, i, data->scene.col_floor);
		i++;
	}
}

/*
	Casts the rays and calls drawing functions
*/
int	cast_rays(t_data *data)
{
	int		nbr_of_rays;
	double	angle_step;
	int		ray_count;
	double	wall_height;
	t_ray	ray;

	nbr_of_rays = data->s_width;
	angle_step = PI / 3 / nbr_of_rays;
	ray_count = 0;
	while (ray_count < data->s_width)
	{
		ray.angle = normalize_angle(data->scene.player.dir
				- (PI / 3 / 2) + (ray_count * angle_step));
		init_ray(data, &ray, ray.angle);
		cast_one_ray(data, &ray);
		ray.angle = normalize_angle((data->scene.player.dir - ray.angle));
		ray.dist = ray.dist * cos(ray.angle);
		wall_height = (BLOCK_SIZE * data->s_height) / ray.dist;
		draw_walls(data, ray_count, &ray, wall_height);
		ray_count++;
	}
	return (SUCCESS);
}
