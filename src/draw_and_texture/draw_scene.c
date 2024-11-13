/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/13 12:03:48 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_scene(t_data *data)
{
	mlx_delete_image(data->m, data->image);
	data->image = mlx_new_image(data->m, data->s_width, data->s_height);
	if (!data->image)
		ft_free_data_and_error(data, "MLX error", NULL);
	collisions(data);
	cast_rays(data);
	if (mlx_image_to_window(data->m, data->image, 0, 0) == -1)
	{
		mlx_delete_image(data->m, data->image);
		ft_free_data_and_error(data, "MLX error", NULL);
	}
	mlx_set_instance_depth(&data->image->instances[0], 2);
}
