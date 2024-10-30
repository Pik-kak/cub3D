/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/30 12:37:15 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/* ==============================
 * Turnsplayer by changing it's dir
 * full round is 2 * PI 
 * sets dposx and dpos y to be next step for player
 * ==============================
 */
void	turn_player(t_player *player, double angle)
{
	player->dir += angle;
	if (player->dir < 0)
		player->dir += 2 * PI;
	else if (player->dir > 2 * PI)
		player->dir -= 2 * PI;
	player->dposx = cos(player->dir) * 5;
	player->dposy = sin(player->dir) * 5;
}

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
//	my_mouse_hook(data);
	draw_scene(data);
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
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		cast_door_ray(data, normalize_angle(data->scene.player.dir), \
		data->scene.player.px, data->scene.player.py);
	}
}
