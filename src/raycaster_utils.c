/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:29 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 16:18:42 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ray_len(t_ray *ray)
{
	double	hyp;

	hyp = hypot(ray->rxry[0] - ray->pxpy[0], ray->rxry[1] - ray->pxpy[1]);
	return ((int)round(hyp));
}

void	set_door_open(t_data *data, int x, int y)
{
	if (data->scene.map[y][x] == 2)
		data->scene.map[y][x] = 3;
	else if (data->scene.map[y][x] == 3)
		data->scene.map[y][x] = 2;
}

void	cast_door_spell(t_data *data, int x, int y)
{
	data->scene.door_x = x;
	data->scene.door_y = y;
	data->scene.wand_pos = 2;
	data->scene.door_timer = 31;
}
