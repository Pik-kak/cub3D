/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:47:48 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/05 16:06:07 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	update_wand(t_data *data)
{
	mlx_texture_t	*wand_text;

	mlx_delete_image(data->m, data->wand);
	if (data->scene.wand_pos == 1)
		wand_text = mlx_load_png("./textures/testwand2.png");
	else if (data->scene.wand_pos == 2)
		wand_text = mlx_load_png("./textures/wand_spell1.png");
	else if (data->scene.wand_pos == 3)
		wand_text = mlx_load_png("./textures/wand_spell2.png");
	if (!wand_text)
		ft_free_data_and_error(data, "error loading wand texture");
	data->wand = mlx_texture_to_image(data->m, wand_text);
	mlx_delete_texture(wand_text);
	mlx_image_to_window(data->m, data->wand, WIDTH / 2 - 200, HEIGHT - 800);
	mlx_set_instance_depth(&data->wand->instances[0], 4);
}
