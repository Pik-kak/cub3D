/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:18:59 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/29 14:34:08 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void draw_line(t_data *data, int px, int py, double theta, int length)
{
	int i;
	
	i = 0;
	printf("%d\n", length);
	while (i < length)
	{
		int xn = px + i * cos(theta);
		int yn = py + i * sin(theta);
		if (pixel_ok(xn, yn) == 1)
		{
			mlx_put_pixel(data->image, xn, yn, COL_LINE);
		}
		i++;
	}
}
