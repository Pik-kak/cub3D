/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:21 by pikkak            #+#    #+#             */
/*   Updated: 2024/10/02 19:15:24 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	my_mouse_hook(t_data *data)
{
	int				x;
	int				y;
	static double	last_x;
	double			change_x;

	mlx_get_mouse_pos(data->m, &x, &y);
	change_x = x - last_x;
	last_x = x;
	if (change_x != 0)
		turn_player(&data->scene.player, change_x * 0.005);//sensitivity?
	mlx_set_cursor_mode(data->m, MLX_MOUSE_HIDDEN);
}