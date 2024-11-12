/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/12 13:49:34 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	move_right_wall(t_player *player)
{
	if (player->dir < PI)
	{
		if (player->dir > PI / 2)
			player->py += PLAYER_SPEED / 2;
		else if (player->dir < PI / 2)
			player->px += PLAYER_SPEED / 2;
	}
	else
	{
		if (player->dir > PI * 3 / 2)
			player->py -= PLAYER_SPEED / 2;
		else if (player->dir < PI * 3 / 2)
			player->px -= PLAYER_SPEED / 2;
	}
}

void	move_left_wall(t_player *player)
{
	if (player->dir < PI)
	{
		if (player->dir > PI / 2)
			player->px -= PLAYER_SPEED / 2;
		else if (player->dir < PI / 2)
			player->py += PLAYER_SPEED / 2;
	}
	else
	{
		if (player->dir > PI * 3 / 2)
			player->px += PLAYER_SPEED / 2;
		else if (player->dir < PI * 3 / 2)
			player->py -= PLAYER_SPEED / 2;
	}
}

void	my_keyhook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->m, MLX_KEY_W))
		move_player_forward(&data->scene.player);
	if (mlx_is_key_down(data->m, MLX_KEY_S))
		move_player_backward(&data->scene.player);
	if (mlx_is_key_down(data->m, MLX_KEY_D))
		move_player_right(&data->scene.player);
	if (mlx_is_key_down(data->m, MLX_KEY_A))
		move_player_left(&data->scene.player);
	if (mlx_is_key_down(data->m, MLX_KEY_LEFT))
		turn_player(&data->scene.player, -0.05);
	if (mlx_is_key_down(data->m, MLX_KEY_RIGHT))
		turn_player(&data->scene.player, 0.05);
	if (mlx_is_key_down(data->m, MLX_KEY_ESCAPE))
		ft_free_data_and_exit(data);
}

void	wand_visibility(t_data *data)
{
	if (!data->scene.wand_visible)
		data->scene.wand_visible = true;
	else if (data->scene.wand_visible)
	{
		data->scene.wand_visible = false;
		mlx_delete_image(data->m, data->wand);
	}
}

void	my_keyhook2(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		if (data->scene.minimap_status == 3)
			data->scene.minimap_status = 1;
		else
			data->scene.minimap_status = 3;
	}
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS \
	&& data->scene.wand_visible)
	{
		cast_door_ray(data, normalize_angle(data->scene.player.dir), \
		data->scene.player.px, data->scene.player.py);
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		wand_visibility(data);
	}
}
