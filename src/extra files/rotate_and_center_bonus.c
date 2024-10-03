/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_and_center_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:18:15 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/26 15:16:36 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
/*
t_point	correct_point_offset(t_point *point, t_data *map)
{
	point->x = point->x + map->offset_x;
	point->y = point->y + map->offset_y;
	return (*point);
}

t_point	rotate_x(t_point point, double angle)
{
	double	y;
	double	z;

	y = point.y;
	z = point.z;
	point.y = y * cos(angle) - z * sin(angle);
	point.z = y * sin(angle) + z * (cos(angle));
	return (point);
}

t_point	rotate_y(t_point point, double angle)
{
	double	x;
	double	z;

	x = point.x;
	z = point.z;
	point.x = x * cos(angle) + z * sin(angle);
	point.z = x * -sin(angle) + (z * (cos(angle)));
	return (point);
}

t_point	rotate_z(t_point point, double angle)
{
	double	x;
	double	y;

	x = point.x;
	y = point.y;
	point.x = x * cos(angle) - y * sin(angle);
	point.y = x * sin(angle) + y * (cos(angle));
	return (point);
}

t_point	rotate(t_point point, t_data *map)
{
	point.z *= map->z_factor;
	point = rotate_x(point, map->projection.alpha);
	point = rotate_y(point, map->projection.beta);
	point = rotate_z(point, map->projection.gamma);
	return (point);
}



t_pixel	correct_pixel_offset(t_pixel *point, t_data *map)
{
	point->x = point->x + map->offset_x;
	point->y = point->y + map->offset_y;
	return (*point);
}
t_pixel	rotate_x_pix(t_pixel point, double angle)
{
	double	y;
	double	z;

	y = point.y;
	z = point.z;
	point.y = y * cos(angle) - z * sin(angle);
	point.z = y * sin(angle) + z * (cos(angle));
	return (point);
}

t_pixel	rotate_y_pix(t_pixel point, double angle)
{
	double	x;
	double	z;

	x = point.x;
	z = point.z;
	point.x = x * cos(angle) + z * sin(angle);
	point.z = x * -sin(angle) + (z * (cos(angle)));
	return (point);
}


t_pixel	rotate_z_pix(t_pixel point, double angle)
{
	double	x;
	double	y;

	x = point.x;
	y = point.y;
	point.x = x * cos(angle) - y * sin(angle);
	point.y = x * sin(angle) + y * (cos(angle));
	return (point);
}

t_pixel	rotate_pix(t_pixel point, t_data *map)
{
	//point.z *= map->z_factor;
	//point = rotate_x_pix(point, map->projection.alpha);
	//point = rotate_y_pix(point, map->projection.beta);
	point = rotate_z_pix(point, map->projection.gamma);
	return (point);
}*/