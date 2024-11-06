/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 15:38:11 by tsaari           ###   ########.fr       */
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
	free(data->buffer);
	data->buffer = NULL;
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
	{
		ft_free_data_and_error(data, "File cannot be opened");
	}
	fill_map(data, check, 0, 1);
	flood_fill(data, end, start, -1);
	fill_maze_if_spaces(data);
	close(data->fd);
	free(data->buffer);
	data->buffer = NULL;
	check_player(data);
}
void print_map(t_data *data)
{
	for (int i = 0; i < data->scene.rows; i++) {
        for (int j = 0; j < data->scene.cols; j++) {
            printf("%d ", data->scene.map[i][j]);
        }
		printf("\n");
    }
}

static void	parse(t_data *data)
{
	t_check	check;

	init_check(&check);
	if (check_filetype(data->file, ".cub") != 0)
	{
		ft_error(data, ERR_INFILE);
	}
	check_and_set_texttr_and_col_lines(data, &check);
	check_map_lines(data, &check);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
	{
		free_elements(data);
		ft_error(data, ERR_INFILE);
	}
	read_file_for_longest_and_lines(data, &check);
	set_map(data, &check);
	print_map(data);
}

static void	render_loop(void *param)
{
	t_data	*data;

	data = param;
	if (data->scene.wand_visible)
		update_wand(data);
	draw_scene(data);
	if (data->scene.door_timer > 0)
		spell_door(data);
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
