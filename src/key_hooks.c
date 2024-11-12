/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/12 13:55:44 by tsaari           ###   ########.fr       */
=======
/*   Updated: 2024/11/12 13:49:34 by kkauhane         ###   ########.fr       */
>>>>>>> ddf1494f545b646607c599a15622581716b8841e
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
