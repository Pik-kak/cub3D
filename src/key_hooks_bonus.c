/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/27 14:02:09 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void move_player_forward(t_player *player)
{
   	float delta_x = cos(player->direction - PI / 2) * PLAYER_SPEED;
	float delta_y = sin(player->direction - PI / 2) * PLAYER_SPEED;
	player->px += delta_x / FIXED_POINT_SCALE;
	player->py += delta_y / FIXED_POINT_SCALE;
}

void move_player_backward(t_player *player)
{
	float delta_x = cos(player->direction + PI / 2) * PLAYER_SPEED;
	float delta_y = sin(player->direction + PI / 2) * PLAYER_SPEED;
	player->px += delta_x / FIXED_POINT_SCALE;
	player->py += delta_y / FIXED_POINT_SCALE;
}

void move_player_left(t_player *player)
{
	int delta_x = (int)(cos(player->direction) * PLAYER_SPEED);
	int delta_y = (int)(sin(player->direction) * PLAYER_SPEED);

	player->px -= delta_x / FIXED_POINT_SCALE;
	player->py -= delta_y / FIXED_POINT_SCALE;
	
}

void move_player_right(t_player *player)
{
	int delta_x = (int)(cos(player->direction) * PLAYER_SPEED);
	int delta_y = (int)(sin(player->direction) * PLAYER_SPEED);

	player->px += delta_x / FIXED_POINT_SCALE;
	player->py += delta_y / FIXED_POINT_SCALE;
  
}
void turn_player_left(t_player *player)
{
	player->direction -= 0.1;
	if (player->direction < 0)
		player->direction += 2 * PI; 
	player->dposx = cos(player->px); 
	player->dposy = cos (player->py);

}
void turn_player_right(t_player *player)
{
	player->direction += 0.1;
	if (player->direction > 2 * PI)
		player->direction -= 2 * PI; 
	player->dposx = cos(player->px);
	player->dposy = cos (player->py);
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
		turn_player_left(&data->scene.player);
	if (mlx_is_key_down(data->m, MLX_KEY_RIGHT))
		turn_player_right(&data->scene.player);
	draw_scene(data);
}
