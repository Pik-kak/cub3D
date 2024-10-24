/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:47:29 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/24 14:49:58 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
Calculates the starting and ending points of the wall slice
*/
void calculate_measurements(t_data *data, int wall_height, int *start, int *end)
{
	*start = -(wall_height / 2) + (data->s_height / 2);
	if (*start < 0)
		*start = 0;
	*end = (wall_height / 2) + (data->s_height / 2);
	if (*end >= data->s_height)
		*end = data->s_height - 1;
}

float calculate_opacity(int ray, int nbr_of_rays, int start, int end)
{
	float distance_from_center;
	float opac;

	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = 1 - (distance_from_center / 1000);
	return opac;
}