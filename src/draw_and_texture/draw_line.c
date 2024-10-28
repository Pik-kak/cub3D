/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:18:59 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/28 20:54:54 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_line(t_data *data, t_ray *ray, int vert_or_hor, double angle)
{
	int	i;
	int	length;
	int	xn;
	int	yn;

	if (vert_or_hor == 1)
		length = ray->dist_v;
	else
		length = ray->dist_h;
	i = 0;
	while (i < length)
	{
		xn = ray->pxpy[0] + i * cos(angle);
		yn = ray->pxpy[1] + i * sin(angle);
		if (pixel_ok(data, xn, yn) == 1)
		{
			mlx_put_pixel(data->image, xn, yn, COL_WHITE);
		}
		i++;
	}
}
