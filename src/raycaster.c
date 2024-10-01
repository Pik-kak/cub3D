/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:20:00 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/01 12:50:06 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_direction_horizontal(t_ray *ray, double ray_angle)
{
	double	a_tan;

	a_tan = -1 / tan(ray_angle);
	if (ray_angle > PI)
	{
		ray->rxry[1] = floor(ray->pxpy[1] / IMG_SIZE) * IMG_SIZE - 0.0001;
		ray->rxry[0] = (ray->pxpy[1] - ray->rxry[1]) * a_tan + ray->pxpy[0];
		ray->xoyo[1] = -IMG_SIZE;
		ray->xoyo[0] = -(ray->xoyo[1]) * a_tan;
	}
	else if (ray_angle < PI)
	{
		ray->rxry[1] = floor(ray->pxpy[1] / IMG_SIZE) * IMG_SIZE + IMG_SIZE;
		ray->rxry[0] = (ray->pxpy[1] - ray->rxry[1]) * a_tan + ray->pxpy[0];
		ray->xoyo[1] = IMG_SIZE;
		ray->xoyo[0] = -(ray->xoyo[1]) * a_tan;
	}
	else
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	}
}

void	check_direction_vertical(t_ray *ray, double ray_angle)
{
	double	n_tan;

	n_tan = -tan(ray_angle);
	if (fabs(ray_angle - 0.5 * PI) < 0.001 || fabs(ray_angle - 1.5 * PI) < 0.001)
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	} 
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI) {
		ray->rxry[0] = floor(ray->pxpy[0] / IMG_SIZE) * IMG_SIZE + IMG_SIZE;  
		ray->rxry[1] = (ray->pxpy[0] - ray->rxry[0]) * n_tan + ray->pxpy[1];
		ray->xoyo[0] = IMG_SIZE;
		ray->xoyo[1] = -ray->xoyo[0] * n_tan;
	} 
	else
	{
		ray->rxry[0] = floor(ray->pxpy[0] / IMG_SIZE) * IMG_SIZE - 0.0001;
		ray->rxry[1] = (ray->pxpy[0] - ray->rxry[0]) * n_tan + ray->pxpy[1];
		ray->xoyo[0] = -IMG_SIZE;
		ray->xoyo[1] = -(ray->xoyo[0]) * n_tan;
	}
}

/*bool wall_found(t_ray *ray, int grid_y, int grid_x)
{
	if (ray->map[grid_y][grid_x] == 1)
	{
		ray->dist_h = (int)round(hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]));
		return (true);
	}
	else
	{
		ray->rxry[0] += ray->xoyo[0];
		ray->rxry[1] += ray->xoyo[1];
		return (false);
	}
}*/

/*void horizontal_cast(t_ray *ray, double ray_angle)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray_angle);
	while (size > 0)
	{
		int grid_x = (int)(ray->rxry[0] / IMG_SIZE);
		int grid_y = (int)(ray->rxry[1] / IMG_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (wall_found(ray, grid_y, grid_x))
				break;
		}
		else
			break;
		size--;
	}
}*/


void	horizontal_cast(t_ray *ray, double ray_angle)
{
	int	size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray_angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / IMG_SIZE);
		grid_y = (int)(ray->rxry[1] / IMG_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (ray->map[grid_y][grid_x] == 1)
			{
				ray->dist_h = (int)round(hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]));
				break ;
			}
			else
			{
				ray->rxry[0] += ray->xoyo[0];
				ray->rxry[1] += ray->xoyo[1];
			}
		}
		else
			break ;
		size--;
	}
}

/*void vertical_cast(t_ray *ray, double ray_angle)
{
	int size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray_angle);
	while (size > 0)
	{
		int grid_x = (int)(ray->rxry[0] / IMG_SIZE);
		int grid_y = (int)(ray->rxry[1] / IMG_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (wall_found(ray, grid_y, grid_x))
				break;
		}
		else
			break;
		size--;
	}
}*/



void	vertical_cast(t_ray *ray, double ray_angle)
{
	int	size;
	int grid_x;
	int grid_y;

	size = ray->cols + ray->rows;
	check_direction_vertical(ray, ray_angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / IMG_SIZE);
		grid_y = (int)(ray->rxry[1] / IMG_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 && grid_y < ray->rows)
		{
			if (ray->map[grid_y][grid_x] == 1)
			{
				ray->dist_v = (int)round(hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]));
				break ;
			}
			else
			{
				ray->rxry[0] += ray->xoyo[0];
				ray->rxry[1] += ray->xoyo[1];
			}
		}
		else
			break ;
		size--;
	}
}


int	draw_one_ray(t_data *data, double ray_angle, double x, double y)
{
	t_ray	ray;
	int		ret_dist;

	init_ray(data, &ray, ray_angle);
	horizontal_cast(&ray, ray_angle);
	vertical_cast(&ray, ray_angle);
	if (ray.dist_h > 0 && (ray.dist_v == 0 || ray.dist_h < ray.dist_v))
	{
		ret_dist = ray.dist_h;
		draw_line(data, &ray, 0, ray_angle);
	}
	else if (ray.dist_v > 0 && (ray.dist_h == 0 || ray.dist_v <= ray.dist_h))
	{
		ret_dist = ray.dist_v;
		draw_line(data, &ray, 1, ray_angle);
	}
	return (ret_dist);
}
