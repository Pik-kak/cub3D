/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:41:21 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/13 14:24:35 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/* ==============================
 * moves player forward or backward using dopx/y 
 * ==============================
 */
void	move_player_forward(t_player *player)
{
	if (!player->col_front)
	{
		player->px += player->dposx * PLAYER_SPEED;
		player->py += player->dposy * PLAYER_SPEED;
	}
	else
	{
		if (player->col_right && !player->col_left)
			move_right_wall(player);
		else if (player->col_left && !player->col_right)
			move_left_wall(player);
	}
}

void	move_player_backward(t_player *player)
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

void	move_player_left(t_player *player)
{
	double	delta_x;
	double	delta_y;

	if (!player->col_left)
	{
		delta_x = cos(player->dir - PI / 2) * PLAYER_SPEED * 2;
		delta_y = sin(player->dir - PI / 2) * PLAYER_SPEED * 2;
		player->px += delta_x;
		player->py += delta_y;
	}
}

void	move_player_right(t_player *player)
{
	double	delta_x;
	double	delta_y;

	if (!player->col_right)
	{
		delta_x = cos(player->dir + PI / 2) * PLAYER_SPEED * 2;
		delta_y = sin(player->dir + PI / 2) * PLAYER_SPEED * 2;
		player->px += delta_x;
		player->py += delta_y;
	}
}

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
