/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:14:47 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/09 15:19:51 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
Initializes the window to fit the screen if the default size is too big
*/
void	init_window(t_data *data)
{
	int	m_width;//these are the new measurements
	int	m_height;
	
	mlx_get_monitor_size(0, &m_width, &m_height);//Gets the monitor size
	if (m_width != data->s_width || m_height != data->s_height)//if there is a difference
	{
		if (m_width < data->s_width)//if screen is smaller than the original window size
			data->s_width = m_width;
		if (m_height < data->s_height)//if screen is smaller than the original window size
			data->s_height = m_height;
		mlx_terminate(data->m);
		data->m = mlx_init(data->s_width, data->s_height, "Cub3D", false);
		if (!data->m)
			ft_free_data_and_error(data, ERR_MLX);
	}
}

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
	
	data->scene.no = NULL;
	data->scene.so = NULL;
	data->scene.ea = NULL;
	data->scene.we = NULL;
	data->scene.cols = 0;
	data->scene.rows = 0;
	data->scene.ceiling = COL_BLUE;
	data->scene.floor = COL_GREEN;
	data->scene.ceiling_rgb[0] = -1;
	data->scene.ceiling_rgb[1] = -1;
	data->scene.ceiling_rgb[2] = -1;
	data->scene.floor_rgb[0] = -1;
	data->scene.floor_rgb[1] = -1;
	data->scene.floor_rgb[2] = -1;
	data->scene.minimap_status = 1;
	/*	data->scene.map = malloc(data->scene.rows * sizeof(int*));
	if (!data->scene.map)
	{
		ft_free_data_and_exit(data);
	}
	row = 0;
	while (row < 8)
	{
		data->scene.map[row] = malloc(data->scene.cols * sizeof(int));
		if (!data->scene.map[row])
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
			data->scene.map[i][j] = temp_map[i][j];
			j++;
		}
		i++;
	}*/


	
}

void	init_check(t_check *check)
{	
	check->player_count = 0;
	check->longest_line = 0;
	check->cur_file_line = 0;
	check->map_lines = 0;
}

void	init_data(t_data *data, char **argv)
{
	data->file = argv[1];
	data->s_height = 1080;
	data->s_width = 1920;
	init_scene(data);
	init_player(&data->scene.player);
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
