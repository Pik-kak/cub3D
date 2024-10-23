/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:52:25 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/22 12:44:28 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

/* ==============================
 * casts four rays to four directions and if ray is shorter than 15 
 * sets collision true 
 * ==============================
 */

void collisions(t_data *data)
{
	if (cast_collission_ray(data, normalize_angle(data->scene.player.direction), data->scene.player.px, data->scene.player.py) < 50)
		data->scene.player.col_front = true;
	else
		data->scene.player.col_front = false;
		
	if (cast_collission_ray(data, normalize_angle(data->scene.player.direction + PI / 2), data->scene.player.px, data->scene.player.py) < 50)
		data->scene.player.col_right = true;
	else
		data->scene.player.col_right = false;
		
	if (cast_collission_ray(data, normalize_angle(data->scene.player.direction + PI), data->scene.player.px, data->scene.player.py) < 50)
		data->scene.player.col_back = true;
	else
		data->scene.player.col_back = false;
		
	if (cast_collission_ray(data, normalize_angle(data->scene.player.direction + PI * 3 / 2), data->scene.player.px, data->scene.player.py) < 50)
		data->scene.player.col_left = true;
	else
		data->scene.player.col_left = false;
}
