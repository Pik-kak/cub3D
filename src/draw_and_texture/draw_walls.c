/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:45 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/02 13:57:17 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ================================
 * Draws a slice of the wall
 * Step tells us how much to move along the texture for each pixel we draw.
 * Tex_start initializes the texture position, centering the wall on the screen.
 * ================================
 */
void	draw_texture(t_data *data, t_ray *ray, int ray_count, int start, int end, mlx_image_t *image, int i, double wall_height)
{
	double		step;
	double		tex_start;
	double		tex_y;
	uint32_t	color;

	step = 1.0 * image->height / wall_height;
	tex_start = (start - data->s_height / 2 + wall_height / 2) * step;
	while (i <= end)
	{
		if (tex_start >= image->height)
			tex_y = (tex_start - image->height);
		else
			tex_y = tex_start;
		tex_start += step;
		color = get_image_color(image, (int)ray->tex_x, tex_y);
		if (pixel_ok(data, ray_count, i))
			mlx_put_pixel(data->image, ray_count, i, color);
		i++;
	}
	//printf("Tex_x:%f Tex_y:%f\n", ray->tex_x, tex_y);
}

/* ===================================
 * Draws the ceiling, walls and floor
 * ===================================
 */
void	draw_walls(t_data *data, int ray_count, t_ray *ray, double wall_height)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	calculate_msrmnts(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		if (i < start)
		{
			if (pixel_ok(data, ray_count, i))
				mlx_put_pixel(data->image, ray_count,
					i, data->scene.col_ceiling);
		}
		else if (i >= start && i < end)
		{
			draw_texture(data, ray, ray_count, start, end,
				ray->wall, i, wall_height);
			i = end;
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
