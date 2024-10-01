/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:14:47 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/01 16:43:32 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void init_player(t_player *player)
{
	player->direction = 0.0f;
	player->px = 100.0;
	player->py = 100.0;
	player->dposx = cos(player->px) * 5;
	player->dposy = sin(player->py) * 5;
	player->col_front = false;
	player->col_back = false;
	player->col_right = false;
	player->col_left = false;
}

void init_scene(t_data *data)
{
	int row;
	
	data->scene.cols = 0;
	data->scene.rows = 0;
	t_scene *scene;
	scene = &data->scene;
	
	init_player(&scene->player);
	scene->cols = 8;
	scene->rows = 8;
	scene->map = malloc(scene->rows * sizeof(int*));
	if (!scene->map)
	{
		ft_free_data_and_exit(data);
	}
	row = 0;
	while (row < 8)
	{
		scene->map[row] = malloc(scene->cols * sizeof(int));
		if (!scene->map[row])
		{
			ft_free_data_and_exit(data);
		}
		row++;
	}
	int temp_map[8][8] = 
	{
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,1,1,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,1,1,0,0,0,1},
		{1,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	int i = 0;
	while (i < 8)
	{
		int j = 0;
		while (j < 8)
		{
			scene->map[i][j] = temp_map[i][j];
			j++;
		}
		i++;
	}
}



void	init_data(int fd, t_data *data, char **argv)
{
	init_scene(data);
}

void	init_ray(t_data *data, t_ray *ray, double ray_angle)
{
	ray->map = data->scene.map;
	ray->pxpy[0] = data->scene.player.px;
	ray->pxpy[1] = data->scene.player.py;
	ray->rxry[0] = ray->pxpy[0];
	ray->rxry[1] = ray->pxpy[1];
	ray->xoyo[0] = 0;
	ray->xoyo[1] = 0;
	ray->dist_h = 0;
	ray->dist_v = 0;
	ray->cols = data->scene.cols;
	ray->rows = data->scene.rows;
}
