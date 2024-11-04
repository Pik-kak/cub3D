/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:47:48 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/04 16:54:35 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	update_wand(t_data *data)
{
	mlx_texture_t	*wand_text;

	mlx_delete_image(data->m, data->wand);
	if (data->scene.wand_pos == 1)
		wand_text = mlx_load_png("./textures/wand_2.png");
	else if (data->scene.wand_pos == 2)
		wand_text = mlx_load_png("./textures/wand_3.png");
	if (!wand_text)
		ft_free_data_and_error(data, "error loading wand texture");
	data->wand = mlx_texture_to_image(data->m, wand_text);
	mlx_delete_texture(wand_text);
	if (data->scene.wand_pos == 1)
		mlx_image_to_window(data->m, data->wand, WIDTH / 2, HEIGHT - 200);
	else if (data->scene.wand_pos == 2)
		mlx_image_to_window(data->m, data->wand, WIDTH / 2, HEIGHT - 200);
	mlx_set_instance_depth(&data->wand->instances[0], 3);
}
