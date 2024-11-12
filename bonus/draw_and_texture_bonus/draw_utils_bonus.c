/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:47:29 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/12 13:52:36 by tsaari           ###   ########.fr       */
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
void	calc_msrmnts(t_data *data, t_texture *tx, double w_hght, int r)
{
	tx->start = -(w_hght / 2) + (data->s_height / 2);
	if (tx->start < 0)
		tx->start = 0;
	tx->end = (w_hght / 2) + (data->s_height / 2);
	if (tx->end >= data->s_height)
		tx->end = data->s_height - 1;
	tx->wall_height = w_hght;
	tx->raycount = r;
}
