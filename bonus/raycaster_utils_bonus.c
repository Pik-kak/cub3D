/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:29 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/13 12:16:38 by tsaari           ###   ########.fr       */
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

void	spell_door(t_data *data)
{
	if (data->scene.door_timer > 0)
	{
		if (data->scene.door_timer < 25 && data->scene.door_timer % 3 == 0 \
		&& data->scene.door_timer > 0)
		{
			set_door_open(data, data->scene.door_x, data->scene.door_y);
		}
		if (data->scene.door_timer % 3 == 0)
		{
			data->scene.wand_pos = 2;
		}
		else
		{
			data->scene.wand_pos = 3;
		}
		data->scene.door_timer--;
		if (data->scene.door_timer == 0)
		{
			data->scene.wand_pos = 1;
			set_door_open(data, data->scene.door_x, data->scene.door_y);
		}
	}
}
