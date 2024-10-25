/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/25 20:56:37 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void print_parsing(t_data *data)
{
	/*printf("%s\n", data->scene.no);
	printf("%s\n", data->scene.ea);
	printf("%s\n", data->scene.so);
	printf("%s\n", data->scene.we);
	printf("%X\n", data->scene.floor);
	printf("%X\n", data->scene.ceiling);
	printf("rows %d\n", data->scene.rows);
	printf("cols %d\n", data->scene.cols);
	printf("%d, %d, %d\n", data->scene.ceiling_rgb[0], data->scene.ceiling_rgb[1], data->scene.ceiling_rgb[2]);
	printf("%d, %d, %d\n", data->scene.floor_rgb[0], data->scene.floor_rgb[1], data->scene.floor_rgb[2]);
	printf("%d\n", data->scene.rows);
	printf("%d\n", data->scene.cols);*/

	printf("\n");
	int rows = 0;
	int cols = 0;
	while( rows < data->scene.rows)
	{
		while (cols < data->scene.cols)
		{
			printf("%d", data->scene.map[rows][cols]);
			cols++;
		}
		printf("\n");
		rows++;	
		cols = 0;
	}
}


void init_map(t_data *data)
{
	int rows;
	int cols;

	rows = 0;
	while( rows < data->scene.rows)
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

void free_before_map(t_data *data)
{
	free(data->scene.ea);
	free(data->scene.so);
	free(data->scene.no);
	free(data->scene.we);
	//free(data);
	ft_error(data, "File cannot be opened");
}

void parse(t_data *data)
{
	t_check *check;

	check = (t_check *)malloc(sizeof (t_check));//do we need to allocate this to the heap?
	init_check(check);
	if (check_filetype(data->file, ".cub") != 0)
		ft_error(data, ERR_INFILE);
	check_and_set_texttr_and_col_lines(data, check);
	check_map_lines(data, check);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		free_before_map(data);
	read_file_for_longest_and_lines(data, check);
	data->scene.rows = check->map_lines + 10;
	data->scene.cols = check->longest_line + 10;
	allocate_map(data);
	init_map(data);
	close(data->fd);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_free_data_and_error(data, "File cannot be opened");
	fill_map(data, check);
	flood_fill(data, (t_point){data->scene.cols, data->scene.rows}, (t_point){0,0}, 32);
	fill_maze_if_spaces(data);
	close(data->fd);
	check_player(data);
	print_parsing(data);
	free(check);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		write(2, "Invalid amount of arguments", 27);
		return (0);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error(data, "malloc error");
	else
	{
		init_data(data, argv);
		parse(data);
		data->m = mlx_init(data->s_width, data->s_height, "Cub3D", false);
		if (!data->m)
			ft_free_data_and_error(data, "MLX error");
		get_textures(data);
		mlx_loop_hook(data->m, my_keyhook, data);
		mlx_key_hook(data->m, &my_keyhook2, data);
		mlx_loop(data->m);
	}
	ft_free_data_and_exit(data);
}
