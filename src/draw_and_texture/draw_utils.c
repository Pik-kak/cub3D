/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:47:29 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/03 17:21:36 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* ==============================
 * If pixel is out of screen does not draw it 
 * prevents segfault
 * ==============================
 */
int	pixel_ok(t_data *data, int x, int y)
{
	if (x >= 0 && x < data->s_width && y >= 0 && y < data->s_height)
		return (1);
	return (0);
}

/* ==============================
 * Calculates the starting and ending points of the wall slice
 * ===============================
 */
void	calculate_msrmnts(t_data *data, t_texture *txtr, double wall_height)
{
	txtr->start = -(wall_height / 2) + (data->s_height / 2);
	if (txtr->start < 0)
		txtr->start = 0;
	txtr->end = (wall_height / 2) + (data->s_height / 2);
	if (txtr->end >= data->s_height)
		txtr->end = data->s_height - 1;
}

float	calculate_opacity(int ray, int nbr_of_rays, int start, int end)
{
	float	distance_from_center;
	float	opac;

	distance_from_center = fabs((float)nbr_of_rays / 2 - (float)ray);
	opac = 1 - (distance_from_center / 1000);
	return (opac);
}

int	squared_distance(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return ((dx * dx) + (dy * dy));
}
