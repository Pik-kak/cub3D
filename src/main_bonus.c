/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 10:05:19 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_map(t_data *data)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < data->scene.rows)
	{
		cols = 0;
		while (cols < data->scene.cols)
		{
			data->scene.map[rows][cols] = -1;
			cols++;
		}
		rows++;
	}
}

static void	set_map(t_data *data, t_check *check)
{
	t_point	start;
	t_point	end;

	start.x = 0;
	start.y = 0;
	end.x = data->scene.cols;
	end.y = data->scene.rows;
	allocate_map(data);
	init_map(data);
	close(data->fd);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_free_data_and_error(data, "File cannot be opened");
	fill_map(data, check);
	flood_fill(data, end, start, -1);
	fill_maze_if_spaces(data);
	close(data->fd);
	check_player(data);
}

static void	parse(t_data *data)
{
	t_check	*check;

	check = (t_check *)malloc(sizeof (t_check));
	init_check(check);
	if (check_filetype(data->file, ".cub") != 0)
	{
		free(check);
		ft_error(data, ERR_INFILE);
	}
	check_and_set_texttr_and_col_lines(data, check);
	check_map_lines(data, check);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
	{
		free_elements(data);
		free(check);
		ft_error(data, ERR_INFILE);
	}
	read_file_for_longest_and_lines(data, check);
	set_map(data, check);
	free(check);
}
#include <time.h>

static void	render_loop(void *param)
{
	t_data	*data;
	time_t start, end;
	double cpu_time;

	start = clock();

	data = param;
	if (data->scene.wand_visible)
		update_wand(data);
	draw_scene(data);
	if (data->scene.door_timer > 0)
		spell_door(data);
	end = clock();
	cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken
    //printf("Render time: %d seconds\n", (int)round(1 / cpu_time));
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		write(2, ERR_ARG, 27);
		return (0);
	}
	data = (t_data *)ft_calloc(sizeof(t_data), sizeof(t_data));
	if (!data)
		ft_error(data, ERR_MALLOC);
	else
	{
		init_data(data, argv);
		parse(data);
		data->m = mlx_init(data->s_width, data->s_height, "Cub3D", false);
		if (!data->m)
			ft_free_data_and_error(data, ERR_MLX);
		get_textures(data);
		mlx_set_mouse_pos(data->m, WIDTH / 2, HEIGHT / 2);
		mlx_loop_hook(data->m, render_loop, data);
		mlx_loop_hook(data->m, my_keyhook, data);
		mlx_key_hook(data->m, &my_keyhook2, data);
		mlx_loop(data->m);
	}
	ft_free_data_and_exit(data);
}
