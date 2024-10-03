/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:20:00 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/03 11:24:30 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_direction_horizontal(t_ray *ray, double ray_angle)
{
	double	a_tan;

	a_tan = -1 / tan(ray_angle);
	if (ray_angle > PI)
	{
		ray->rxry[1] = floor(ray->pxpy[1] / BLOCK_SIZE) * BLOCK_SIZE - 0.0001;
		ray->rxry[0] = (ray->pxpy[1] - ray->rxry[1]) * a_tan + ray->pxpy[0];
		ray->xoyo[1] = -BLOCK_SIZE;
		ray->xoyo[0] = -(ray->xoyo[1]) * a_tan;
	}
	else if (ray_angle < PI)
	{
		ray->rxry[1] = floor(ray->pxpy[1] / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
		ray->rxry[0] = (ray->pxpy[1] - ray->rxry[1]) * a_tan + ray->pxpy[0];
		ray->xoyo[1] = BLOCK_SIZE;
		ray->xoyo[0] = -(ray->xoyo[1]) * a_tan;
	}
	else
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	}
}

/* ==============================
 *	calculates negative tangent of an angle because the y increases when moving down
 *  checks if palyer direction is to west or east  or directly up or down
 *  if looking up or down just sets ray x to player x etc
 * if looking east or west calculates rxry to next
 * ==============================
 */

void	check_direction_vertical(t_ray *ray, double ray_angle)
{
	double	n_tan;

	n_tan = -tan(ray_angle);
	if (fabs(ray_angle - 0.5 * PI) < 0.001 || fabs(ray_angle - 1.5 * PI) < 0.001) //looking up or down
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	} 
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)  // looking east
	{
		ray->rxry[0] = floor(ray->pxpy[0] / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;  
		ray->rxry[1] = (ray->pxpy[0] - ray->rxry[0]) * n_tan + ray->pxpy[1];
		ray->xoyo[0] = BLOCK_SIZE;
		ray->xoyo[1] = -ray->xoyo[0] * n_tan;
	} 
	else
	{
		ray->rxry[0] = floor(ray->pxpy[0] / BLOCK_SIZE) * BLOCK_SIZE - 0.0001;
		ray->rxry[1] = (ray->pxpy[0] - ray->rxry[0]) * n_tan + ray->pxpy[1];
		ray->xoyo[0] = -BLOCK_SIZE;
		ray->xoyo[1] = -(ray->xoyo[0]) * n_tan;
	}
}

bool check_if_wall_found(t_ray *ray, int grid_y, int grid_x, int hor_or_ver)
{
	if (ray->map[grid_y][grid_x] == 1)
	{
		if (hor_or_ver == 1)
			ray->dist_h = (int)round(hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]));
		else
			ray->dist_v = (int)round(hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]));
		return (true);
	}
	else
	{
		ray->rxry[0] += ray->xoyo[0];
		ray->rxry[1] += ray->xoyo[1];
		return (false);
	}
}

/* 
	calls check_dir function and then divides found block side and checks if next block is wall
	by calling check_if_wall_found function, which sets total length of ray to struct 
 */

void horizontal_cast(t_ray *ray, double ray_angle)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray_angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / BLOCK_SIZE);
		grid_y = (int)(ray->rxry[1] / BLOCK_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (check_if_wall_found(ray, grid_y, grid_x, 1))
				break;
		}
		else
			break;
		size--;
	}
}

/* 
	calls check dir function and then divides found block side and checks if next block is wall
	by calling check_if_wall_found function, which sets total length of ray to struct 
 */

void vertical_cast(t_ray *ray, double ray_angle)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_vertical(ray, ray_angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / BLOCK_SIZE);
		grid_y = (int)(ray->rxry[1] / BLOCK_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (check_if_wall_found(ray, grid_y, grid_x, 0))
				break;
		}
		else
			break;
		size--;
	}
}

/* 

	casts One ray to given angle
		first it casts ray to find wall in horizontal block sides, then vertical and 
		draws ray to which ray is shorter and nearer player.
*/
int	cast_one_ray(t_data *data, double ray_angle, double x, double y, int flag)
{
	t_ray	ray;
	int		ret_dist;

	init_ray(data, &ray, ray_angle);
	horizontal_cast(&ray, ray_angle);
	vertical_cast(&ray, ray_angle);
	if (ray.dist_h > 0 && (ray.dist_v == 0 || ray.dist_h < ray.dist_v))
	{
		ret_dist = ray.dist_h;
		//if (flag)
		//	draw_line(data, &ray, 0, ray_angle);
	}
	else if (ray.dist_v > 0 && (ray.dist_h == 0 || ray.dist_v <= ray.dist_h))
	{
		ret_dist = ray.dist_v;
	//	if (flag)
	//		draw_line(data, &ray, 1, ray_angle);
	}
	return (ret_dist);
}


int	cast_rays(t_data *data)
{
	int		nbr_of_rays;
	double	ray_angle;
	int		ray_length;
	int	i;

	nbr_of_rays = 60;
	i = -nbr_of_rays;
	while(i <= nbr_of_rays) 
	{
		ray_angle = normalize_angle(data->scene.player.direction + (i * DEGREE));
		ray_length = cast_one_ray(data, ray_angle, data->scene.player.px, data->scene.player.py, 1);
		i++;
	}
	return (ray_length);
}


