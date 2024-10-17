/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:48:31 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/17 23:22:12 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	get_images(t_data *data)
{
	data->walls = ft_calloc(1, sizeof(t_walls));
	data->walls->no = mlx_texture_to_image(data->m, data->txtrs->no);
	data->walls->so = mlx_texture_to_image(data->m, data->txtrs->so);
	data->walls->ea = mlx_texture_to_image(data->m, data->txtrs->ea);
	data->walls->we = mlx_texture_to_image(data->m, data->txtrs->we);
	mlx_delete_texture(data->txtrs->no);
	mlx_delete_texture(data->txtrs->so);
	mlx_delete_texture(data->txtrs->ea);
	mlx_delete_texture(data->txtrs->we);
}

void	get_textures(t_data *data)
{
	data->txtrs = ft_calloc(1, sizeof(struct s_textures));
	data->txtrs->no = mlx_load_png("textures/wall.png");//data->scene.no);
	data->txtrs->so = mlx_load_png("textures/wall.png");//data->scene.so);
	data->txtrs->ea = mlx_load_png("textures/wall.png");//data->scene.ea);
	data->txtrs->we = mlx_load_png("textures/wall.png");//data->scene.we);
	get_images(data);
}

