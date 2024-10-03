/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/02 17:01:23 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void print_parsing(t_data *data, t_check *check)
{
	printf("%s\n", data->scene.no);
	printf("%s\n", data->scene.ea);
	printf("%s\n", data->scene.so);
	printf("%s\n", data->scene.we);
	printf("%X\n", data->scene.floor);
	printf("%X\n", data->scene.ceiling);
	printf("%d, %d, %d\n", data->scene.ceiling_rgb[0], data->scene.ceiling_rgb[1], data->scene.ceiling_rgb[2]);
	printf("%d, %d, %d\n", data->scene.floor_rgb[0], data->scene.floor_rgb[1], data->scene.floor_rgb[2]);
	printf("%d\n", data->scene.rows);
	printf("%d\n", data->scene.cols);
	printf("first map line : %d\n", check->first_map_line);
	printf("longest map line : %d\n", check->longest_line);
}

void parse(t_data *data)
{
	t_check check;

	init_check(&check);
	if (check_file_type(data, &check) != 0)
		ft_error(ERR_INFILE);
	check_and_parse_file(data, &check);
	print_parsing(data, &check);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_check	*check;

	if (argc != 2)
		ft_error(ERR_ARG);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error(ERR_MALLOC);
	else
	{
		init_data(data, argv);
		parse(data);
		data->m = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
		if (!data->m)
			ft_free_data_and_error(data, ERR_MLX);
		init_window(data);
		mlx_loop_hook(data->m, my_keyhook, data);
		
		mlx_loop(data->m);
		mlx_terminate(data->m);
	}
	ft_free_data_and_exit(data);
}
