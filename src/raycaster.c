/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:20:00 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/24 10:20:54 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_direction_horizontal(t_ray *ray, double ray_angle)
{
	double	a_tan;
	double	floored;

	floored = floor(ray->pxpy[1] / BLOCK_SIZE) * BLOCK_SIZE;
	a_tan = -1 / tan(ray_angle);
	if (ray_angle > PI)
	{
		ray->rxry[1] = floored - 0.0001;
		ray->rxry[0] = (ray->pxpy[1] - ray->rxry[1]) * a_tan + ray->pxpy[0];
		ray->xoyo[1] = -BLOCK_SIZE;
		ray->xoyo[0] = -(ray->xoyo[1]) * a_tan;
	}
	else if (ray_angle < PI)
	{
		ray->rxry[1] = floored + BLOCK_SIZE;
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
	double floored;
	
	floored = floor(ray->pxpy[0] / BLOCK_SIZE) * BLOCK_SIZE;
	n_tan = -tan(ray_angle);
	if (fabs(ray_angle - 0.5 * PI) < 0.0001 || fabs(ray_angle - 1.5 * PI) < 0.0001) //looking up or down
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	} 
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)  // looking east
	{
		ray->rxry[0] = floored + BLOCK_SIZE;  
		ray->rxry[1] = (ray->pxpy[0] - ray->rxry[0]) * n_tan + ray->pxpy[1];
		ray->xoyo[0] = BLOCK_SIZE;
		ray->xoyo[1] = -ray->xoyo[0] * n_tan;
	} 
	else
	{
		ray->rxry[0] = floored - 0.0001;
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

void horizontal_cast(t_ray *ray)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray->angle);
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

void vertical_cast(t_ray *ray)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_vertical(ray, ray->angle);
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


void	cast_one_ray(t_data *data, t_ray *ray)
{
	double hor_x;
	
	horizontal_cast(ray);
	hor_x = ray->rxry[0];
	vertical_cast(ray);
	if (hor_x == ray->rxry[1])
		hor_x -= 0.0001;
	if (ray->dist_h > 0 && (ray->dist_v == 0 || ray->dist_h < ray->dist_v))
	{
		ray->dist = ray->dist_h;
		if (ray->angle > 0 && ray->angle < PI)
		{
			//ray->tex_x = (int)(ray->rxry[0]);
			ray->tex_x = (fmod(hor_x, BLOCK_SIZE)) * ((double)data->walls->so->width / (double)BLOCK_SIZE);
			ray->wall = data->walls->so;
		}
		else
		{
			//ray->tex_x = (int)(ray->rxry[0]);
			ray->tex_x = (fmod(hor_x, BLOCK_SIZE)) * ((double)data->walls->no->width / (double)BLOCK_SIZE);
			ray->wall = data->walls->no;
			printf("ray angle %f\n", ray->angle);
		}
	}
	else if (ray->dist_v > 0 && (ray->dist_h == 0 || ray->dist_v <= ray->dist_h))
	{
		ray->dist = ray->dist_v;
		if (ray->angle > PI * 3 / 2 || ray->angle < PI / 2)
		{
			//ray->tex_x = (int)(ray->rxry[1]);
			ray->tex_x = (fmod(ray->rxry[1], BLOCK_SIZE)) * ((double)data->walls->ea->width / (double)BLOCK_SIZE);
			ray->wall = data->walls->ea;
		}
		else
		{
			//ray->tex_x = (int)(ray->rxry[1]);
			ray->tex_x = (fmod(ray->rxry[1], BLOCK_SIZE)) * ((double)data->walls->we->width / (double)BLOCK_SIZE);
			ray->wall = data->walls->we;
		}
	}
}



int	cast_collission_ray(t_data *data, double ray_angle, double x, double y)
{
	t_ray 	ray;
	int		ret_dist;

	init_ray(data, &ray, ray_angle);
	
	horizontal_cast(&ray);
	vertical_cast(&ray);
	if (ray.dist_h > 0 && (ray.dist_v == 0 || ray.dist_h < ray.dist_v))
	{
		ret_dist = ray.dist_h;
	}
	else if (ray.dist_v > 0 && (ray.dist_h == 0 || ray.dist_v <= ray.dist_h))
	{
		ret_dist = ray.dist_v;
	}
	return (ret_dist);
}
