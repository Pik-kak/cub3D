/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/02 16:56:55 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void move_right_wall(t_player *player)
{
	if (player->direction < PI) // LOOK SOUTH
	{ 
		if (player->direction > PI / 2) // LOOK SOUTHWEST
			player->py += PLAYER_SPEED / 2;
		else if (player->direction < PI / 2) // LOOK SOUTHEAST
			player->px += PLAYER_SPEED / 2;
	} 
	else // LOOK NORTH
	{ 
		if (player->direction > PI * 3 / 2) // LOOK NORTHEAST
			player->py -= PLAYER_SPEED / 2;
		else if (player->direction < PI * 3 / 2) // LOOK NORTHWEST
			player->px -= PLAYER_SPEED / 2;
	}
}

void move_left_wall(t_player *player)
{
	if (player->direction < PI) // LOOK SOUTH
	{ 
		if (player->direction > PI / 2) // LOOK SOUTHWEST
			player->px -= PLAYER_SPEED / 2;
		else if (player->direction < PI / 2) // LOOK SOUTHEAST
			player->py += PLAYER_SPEED / 2;
	}
	else // LOOK NORTH
	{ 
		if (player->direction > PI * 3 / 2) // LOOK NORTHEAST
			player->px += PLAYER_SPEED / 2;
		else if (player->direction < PI * 3 / 2) // LOOK NORTHWEST
			player->py -= PLAYER_SPEED / 2;
	}
}

/* ==============================
 * moves player forward or backward using dopx/y 
 * ==============================
 */

void move_player_forward(t_player *player)
{
	if (!player->col_front)
	{
		player->px += player->dposx * PLAYER_SPEED;
		player->py += player->dposy * PLAYER_SPEED;
	}
	else			// MOVES BESIDE WALL
	{
		if (player->col_right && !player->col_left)
			move_right_wall(player);
		else if (player->col_left && !player->col_right)
			move_left_wall(player);
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

/* ==============================
 * counts delta_x and y which is side from player and moves player there
 * ==============================
 */

void move_player_left(t_player *player)
{
	if (!player->col_left)
	{
		double delta_x;
		double delta_y;
		
		delta_x = cos(player->direction - PI / 2) * PLAYER_SPEED * 3;
		delta_y = sin(player->direction - PI / 2) * PLAYER_SPEED * 3;
		player->px += delta_x;
		player->py += delta_y;
	}
	//TODO Handle collision movement
}

void move_player_right(t_player *player)
{
	if (!player->col_right)
	{
		double delta_x;
		double delta_y;
		
		delta_x = cos(player->direction + PI / 2) * PLAYER_SPEED * 3;
		delta_y = sin(player->direction + PI / 2) * PLAYER_SPEED * 3;
		player->px += delta_x;
		player->py += delta_y;
	}
}

/* ==============================
 * Turnsplayer by changing it's direction
 * full round is 2 * PI 
 * sets dposx and dpos y to be next step for player
 * ==============================
 */

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
	if (mlx_is_key_down(data->m, MLX_KEY_ESCAPE))
		ft_free_data_and_exit(data);
	draw_scene(data);
}
