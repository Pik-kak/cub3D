/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:14:47 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/01 16:19:04 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void init_player(t_player *player)
{
	player->direction = 0.0f;
	player->player_icon = NULL;
	player->px = (double)100.0;
	player->py= (double)100.0f;
	player->dposx = cos(player->px) * 5;
	player->dposy = sin(player->py) * 5;
	
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
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
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

void	init_check(t_data *data)
{
	t_check	check;
	
	check.fd = -1;
	check.player_count = 0;
	if (check_file_type(data, &check) != 0)
		ft_error(ERR_INFILE);
	check_file(data, &check);
}

void	init_data(t_data *data, char **argv)
{
	data->file = argv[1];
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(ERR_OPEN);
	init_scene(data);
	init_check(data);
}