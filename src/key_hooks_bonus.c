/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/01 10:08:51 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void move_player_left(t_player *player)
{
	if (!player->col_left)
	{
		double delta_x = cos(player->direction - PI / 2) * PLAYER_SPEED * 2;
		double delta_y = sin(player->direction - PI / 2) * PLAYER_SPEED * 2;
		player->px += delta_x;
		player->py += delta_y;
	}
	//TODO Handle collision movement
}

void move_player_right(t_player *player)
{
	if (!player->col_right)
	{
	double delta_x = cos(player->direction + PI / 2) * PLAYER_SPEED * 2;
	double delta_y = sin(player->direction + PI / 2) * PLAYER_SPEED * 2;
	player->px += delta_x;
	player->py += delta_y;
	}
}

void move_player_forward(t_player *player)
{
	if (!player->col_front)
	{
    player->px += player->dposx * PLAYER_SPEED;
    player->py += player->dposy * PLAYER_SPEED;
	}
}

void move_player_backward(t_player *player)
{
	if (!player->col_back)
	{
    player->px -= player->dposx * PLAYER_SPEED;
    player->py -= player->dposy * PLAYER_SPEED;
	}
}
void turn_player(t_player *player, double angle)
{
	player->direction += angle;
	if (player->direction < 0)
		player->direction += 2 * PI;
	else if (player->direction > 2 * PI)
		player->direction -= 2 * PI;
	player->dposx = cos(player->direction) * 5; 
	player->dposy = sin(player->direction) * 5;
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
		turn_player(&data->scene.player, -0.1);
	if (mlx_is_key_down(data->m, MLX_KEY_RIGHT))
		turn_player(&data->scene.player, 0.1);

	draw_scene(data);
}
