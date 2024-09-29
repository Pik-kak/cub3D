/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:34 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/29 12:23:20 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void draw_one_ray(t_data *data, float ray_angle, float x, float y)
{
	float rx = x;
	float ry = y;
	float xo = 0;
	float yo = 0;
	float distance_h;
	float distance_v;
	
	// check_horizontal_lines()
	int dof = 0;
	if (ray_angle > PI) 
	{
		float aTan= -1/tan(ray_angle);
		ry = (floor(y / 64) * 64) - 0.0001;
		rx = (y - ry) * aTan + x;
		yo = -64;
		xo = -yo * aTan;
	}
	else if (ray_angle < PI)
	{
		float aTan= -1/tan(ray_angle);
		ry = (floor(y / 64) * 64) + 64;
		rx = (y - ry) * aTan + x;
		yo = 64;
		xo = -yo * aTan;
	}
	else
	{
		rx = x;
		ry = y;
		dof = 8;
	}
	while (dof < 8)
	{
		int gridX = (int)(rx / 64);
		int gridY = (int)(ry / 64);
		if (gridX >= 0 && gridX < data->scene.cols && gridY >= 0 && gridY < data->scene.rows) 
		{
			if (data->scene.map[gridY][gridX] == 1)
			{
				distance_h = sqrt((rx - x) * (rx - x) + (ry - y) * (ry - y));
				draw_line(data, x, y, ray_angle, distance_h);
				break;
			}
			else 
			{
				rx += xo;
				ry += yo;
			}
		} 
		else 
			break;
		dof++;
	}

	 // Vertical Raycasting
	int dof_v = 0;
	rx = x;
	ry = y;

	const double epsilon = 0.0001;

	if (fabs(ray_angle - 0.5 * PI) < epsilon || fabs(ray_angle - 1.5 * PI) < epsilon) {
		rx = x;
		ry = y;
		dof = 8;
	}
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI) // looking right
	{
		rx = (floor(x / 64) * 64) + 64;
		ry = (x - rx) * tan(ray_angle) + y;
		xo = 64;
		yo = -xo * tan(ray_angle);
	}
	else // Looking left
	{
		rx = (floor(x / 64) * 64) - 0.0001;
		ry = (x - rx) * tan(ray_angle) + y;
		xo = -64;
		yo = -xo * tan(ray_angle);
	}

	while (dof_v < 8)
	{
		int gridX = (int)(rx / 64);
		int gridY = (int)(ry / 64);
		if (gridX >= 0 && gridX < data->scene.cols && gridY >= 0 && gridY < data->scene.rows) 
		{
			if (data->scene.map[gridY][gridX] == 1)
			{
				distance_v = sqrt((rx - x) * (rx - x) + (ry - y) * (ry - y));
				break;
			}
			else 
			{
				rx += xo;
				ry += yo;
			}
		} 
		else 
			break;
		dof_v++;
	}
	if (distance_h > 0.0 && (distance_v == 0.0 || distance_h < distance_v))
	{
		draw_line(data, x, y, ray_angle, distance_h);
	}
	else if (distance_v > 0.0 && (distance_h == 0.0 || distance_v < distance_h))
	{
		draw_line(data, x, y, ray_angle, distance_v);
	}

}

