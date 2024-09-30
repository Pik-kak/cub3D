/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:34 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/29 15:13:03 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void draw_one_ray(t_data *data, double ray_angle, double x, double y)
{
	double rx = x;
	double ry = y;
	double xo = 0;
	double yo = 0;
	int distance_h = 0;
	int distance_v = 0;
	
	// Horizontal Raycasting
	int dof = 0;
	if (ray_angle > PI) 
	{
		double aTan = -1 / tan(ray_angle);
		ry = (floor(y / IMG_SIZE) * IMG_SIZE) - 0.0001;
		rx = (y - ry) * aTan + x;
		yo = -IMG_SIZE;
		xo = -yo * aTan;
	}
	else if (ray_angle < PI)
	{
		double aTan = -1 / tan(ray_angle);
		ry = (floor(y / IMG_SIZE) * IMG_SIZE) + IMG_SIZE;
		rx = (y - ry) * aTan + x;
		yo = IMG_SIZE;
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
		int gridX = (int)(rx / IMG_SIZE);
		int gridY = (int)(ry / IMG_SIZE);
		if (gridX >= 0 && gridX < data->scene.cols && gridY >= 0 && gridY < data->scene.rows) 
		{
			if (data->scene.map[gridY][gridX] == 1)
			{
				printf("horizontal hit to wall %d, %d\n", gridY, gridX);
				distance_h = (int)round(sqrt((rx - x) * (rx - x) + (ry - y) * (ry - y)));
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
	double nTan = -tan(ray_angle);
	
	const double epsilon = 0.0001;

	if (fabs(ray_angle - 0.5 * PI) < epsilon || fabs(ray_angle - 1.5 * PI) < epsilon) 
	{
		rx = x;
		ry = y;
		dof_v = 8;
	}
	else if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
	{
		rx = (floor(x / IMG_SIZE) * IMG_SIZE) + IMG_SIZE;  
		ry = (x - rx) * nTan + y;
		xo = IMG_SIZE;
		yo = -xo * nTan;
	}
	else
	{
		rx = (floor(x / IMG_SIZE) * IMG_SIZE) - 0.0001;
		ry = (x - rx) * nTan + y;
		xo = -IMG_SIZE;
		yo = -xo * nTan;
	}

	while (dof_v < 8)
	{
		int gridX = (int)(rx / IMG_SIZE);
		int gridY = (int)(ry / IMG_SIZE);
		if (gridX >= 0 && gridX < data->scene.cols && gridY >= 0 && gridY < data->scene.rows) 
		{
			if (data->scene.map[gridY][gridX] == 1)
			{
				printf("vertical hit to wall %d, %d\n", gridY, gridX);
				distance_v = (int)round(sqrt((rx - x) * (rx - x) + (ry - y) * (ry - y)));
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
		printf("%f\n", ray_angle);
		draw_line(data, x, y, ray_angle, distance_h);
	}
	else if (distance_v > 0.0 && (distance_h == 0.0 || distance_v <= distance_h))
	{
		printf("%f\n", ray_angle);
		draw_line(data, x, y, ray_angle, distance_v);
	}
}
