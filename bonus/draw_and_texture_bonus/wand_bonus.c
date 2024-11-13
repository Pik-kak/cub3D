/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:47:48 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/13 14:46:19 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	update_wand(t_data *data)
{
	mlx_delete_image(data->m, data->wand);
	if (data->scene.wand_pos == 1)
		data->wand = mlx_texture_to_image(data->m, data->txtrs->wand_basic);
	else if (data->scene.wand_pos == 2)
		data->wand = mlx_texture_to_image(data->m, data->txtrs->wand_spell1);
	else if (data->scene.wand_pos == 3)
		data->wand = mlx_texture_to_image(data->m, data->txtrs->wand_spell2);
	mlx_image_to_window(data->m, data->wand, WIDTH / 2 - 200, HEIGHT - 800);
	mlx_set_instance_depth(&data->wand->instances[0], 4);
}
