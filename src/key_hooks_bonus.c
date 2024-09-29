/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/29 10:14:27 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void move_player_left(t_player *player)
{
   	double delta_x = cos(player->direction - PI / 2) * PLAYER_SPEED;
	double delta_y = sin(player->direction - PI / 2) * PLAYER_SPEED;
	player->px += delta_x;
	player->py += delta_y;
}

void move_player_right(t_player *player)
{
	double delta_x = cos(player->direction + PI / 2) * PLAYER_SPEED;
	double delta_y = sin(player->direction + PI / 2) * PLAYER_SPEED;
	player->px += delta_x;
	player->py += delta_y;
}

void move_player_forward(t_player *player)
{
    player->px += player->dposx * PLAYER_SPEED; // Move by dposx in the X direction
    player->py += player->dposy * PLAYER_SPEED; // Move by dposy in the Y direction
}

void move_player_backward(t_player *player)
{
    player->px -= player->dposx * PLAYER_SPEED; // Move by dposx in the X direction
    player->py -= player->dposy * PLAYER_SPEED; // Move by dposy in the Y direction
}
void turn_player(t_player *player, double angle)
{
	player->direction += angle;
	printf("%f\n", player->direction);
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
