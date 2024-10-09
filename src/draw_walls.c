/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:45 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/07 11:09:34 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	calculate_measurements(t_data *data, int wall_height, int *start, int *end)
{
	*start = -(wall_height / 2) + (data->s_height / 2);// Calculate the starting and ending points of the wall slice
	if (*start < 0)
		*start = 0;
	*end = (wall_height / 2) + (data->s_height/ 2);
	if (*end >= data->s_height)
		*end = data->s_height - 1;
}

void draw_walls(t_data *data, int ray, int wall_height, int dist)
{
	int i;
	int start;
	int end;

	i = 0;
	calculate_measurements(data, wall_height, &start, &end);
	while (i < data->s_height)
	{
		if (i < start)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, COL_BLUE);
		}
		else if (i >= start && i <= end)
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, COL_FLAMINGO);
		}
		else
		{
			if (pixel_ok(data, ray, i))
				mlx_put_pixel(data->image, ray, i, COL_BLUE);
		}
		i++;
	}
}

int	cast_rays(t_data *data, mlx_image_t *image)
{
	int		nbr_of_rays;
	double	ray_angle;
	double	angle_step;
	int		i;
	int		dist;
	int		wall_height;

	nbr_of_rays = data->s_width;//Number of rays corresponds to screen width
	angle_step = PI / 3 / nbr_of_rays;//Divide FOV into equal slices for each ray
	i = 0;
	while(i <= (nbr_of_rays -1)) 
	{
		ray_angle = normalize_angle(data->scene.player.direction - (PI / 3 / 2) + (i * angle_step));//Calculate ray angle starting from the left-most point of the FOV
		dist = cast_one_ray(data, ray_angle, data->scene.player.px, data->scene.player.py, 1);
		wall_height = (64 * data->s_height) / (dist);
		draw_walls(data, i, wall_height, dist);// Draw the wall slice for this ray
		i++;
	}
	return (SUCCESS);
}

