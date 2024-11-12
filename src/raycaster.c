/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:20:00 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/12 14:22:18 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*========================================
 * casts One ray to given angle
 * first it casts ray to find wall in horizontal block sides,
 * then vertical and 
 * draws ray to which ray is shorter and nearer player.
 * =======================================
 */
double	count_texture_x(t_ray *ray, int x)
{
	double	ret;

	ret = fmod(x, BLOCK_SIZE) * ((double)ray->wall->width / (double)BLOCK_SIZE);
	return (ret);
}

void	set_wall(t_data *data, t_ray *ray, int hor_or_ver, bool hor_door)
{
	if (hor_or_ver == 1)
	{
		ray->dist = ray->dist_h;
		if (ray->angle > PI)
			ray->wall = data->walls->no;
		else
			ray->wall = data->walls->so;
		if (hor_door)
		{
			ray->wall = data->walls->door;
			ray->is_door = true;
		}	
		ray->tex_x = count_texture_x(ray, ray->hor_x);
	}
	else
	{
		ray->dist = ray->dist_v;
		if (ray->angle > 0.5 * PI && ray->angle <= PI * 1.5)
			ray->wall = data->walls->we;
		else
			ray->wall = data->walls->ea;
		if (ray->is_door)
			ray->wall = data->walls->door;
		ray->tex_x = count_texture_x(ray, ray->rxry[1]);
	}
}

void	cast_one_ray(t_data *data, t_ray *ray)
{
	bool	hor_door;

	horizontal_cast(ray);
	ray->hor_x = ray->rxry[0];
	hor_door = ray->is_door;
	ray->is_door = false;
	vertical_cast(ray);
	if (ray->dist_h > 0 && (ray->dist_v == 0 || ray->dist_h < ray->dist_v))
	{
		set_wall(data, ray, 1, hor_door);
		data->scene.last_ray_dir = 0;
	}
	else if (ray->dist_v > 0 && (ray->dist_h == 0 || ray->dist_h > ray->dist_v))
	{
		set_wall(data, ray, 0, ray->is_door);
		data->scene.last_ray_dir = 1;
	}
	else
	{
		if (data->scene.last_ray_dir == 0)
			set_wall(data, ray, 1, hor_door);
		else
			set_wall(data, ray, 0, ray->is_door);
	}
}

int	cast_collission_ray(t_data *data, double ray_angle, double x, double y)
{
	t_ray	ray;
	int		ret_dist;

	init_ray(data, &ray, ray_angle);
	horizontal_cast(&ray);
	vertical_cast(&ray);
	if (ray.dist_h > 0 && (ray.dist_v == 0 || ray.dist_h <= ray.dist_v))
	{
		ret_dist = ray.dist_h;
	}
	else if (ray.dist_v > 0 && (ray.dist_h == 0 || ray.dist_v < ray.dist_h))
	{
		ret_dist = ray.dist_v;
	}
	return (ret_dist);
}

