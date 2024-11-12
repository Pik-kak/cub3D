/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:52:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/03 16:22:40 by kkauhane         ###   ########.fr       */
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
 *	calculates negative tangent of an angle because the y increases
 *  when moving down
 *  checks if palyer direction is to west or east  or directly up or down
 *  if looking up or down just sets ray x to player x etc
 * if looking east or west calculates rxry to next
 * ==============================
 */
void	check_direction_vertical(t_ray *ray, double ray_angle)
{
	double	n_tan;
	double	floored;

	floored = floor(ray->pxpy[0] / BLOCK_SIZE) * BLOCK_SIZE;
	n_tan = -tan(ray_angle);
	if (fabs(ray_angle - 0.5 * PI) < 0.0001 || \
	fabs(ray_angle - 1.5 * PI) < 0.0001)
	{
		ray->rxry[0] = ray->pxpy[0];
		ray->rxry[1] = ray->pxpy[1];
	}
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
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
		ray->xoyo[1] = -ray->xoyo[0] * n_tan;
	}
}

bool	check_if_wall_found(t_ray *ray, int grid_y, int grid_x, int hor_or_ver)
{
	if (ray->map[grid_y][grid_x] == 1 || ray->map[grid_y][grid_x] == 2)
	{
		if (ray->map[grid_y][grid_x] == 2)
			ray->is_door = true;
		if (hor_or_ver == 1)
			ray->dist_h = ray_len(ray);
		else
			ray->dist_v = ray_len(ray);
		return (true);
	}
	else if (ray->map[grid_y][grid_x] == 3 && ray->open_door)
	{
		ray->is_door = true;
		if (hor_or_ver == 1)
			ray->dist_h = ray_len(ray);
		else
			ray->dist_v = ray_len(ray);
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
	calls check_dir function and then divides found block side and 
	checks if next block is wall
	by calling check_if_wall_found function, which sets total 
	length of ray to struct 
 */
void	horizontal_cast(t_ray *ray)
{
	int	size;
	int	grid_x;
	int	grid_y;

	size = ray->cols + ray->rows;
	check_direction_horizontal(ray, ray->angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / BLOCK_SIZE);
		grid_y = (int)(ray->rxry[1] / BLOCK_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && \
		grid_y >= 0 && grid_y < ray->rows)
		{
			if (check_if_wall_found(ray, grid_y, grid_x, 1))
				break ;
		}
		else
			break ;
		size--;
	}
}

/* 
	calls check dir function and then divides
	 block side and checks if next block is wall
	by calling check_if_wall_found function, which 
	sets total length of ray to struct 
 */
void	vertical_cast(t_ray *ray)
{
	int	size;
	int	grid_x;
	int	grid_y;

	size = ray->cols + ray->rows;
	check_direction_vertical(ray, ray->angle);
	while (size > 0)
	{
		grid_x = (int)(ray->rxry[0] / BLOCK_SIZE);
		grid_y = (int)(ray->rxry[1] / BLOCK_SIZE);
		if (grid_x >= 0 && grid_x < ray->cols && grid_y >= 0 \
		&& grid_y < ray->rows)
		{
			if (check_if_wall_found(ray, grid_y, grid_x, 0))
				break ;
		}
		else
			break ;
		size--;
	}
}
