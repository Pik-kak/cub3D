/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:48:31 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/05 14:39:49 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	is_directory(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (1);
	}
	return (0);
}

void	check_texture_file(t_data *data, char *file)
{
	int	fd;

	if (is_directory(file))
		ft_free_data_and_error(data, "Texture file is a directory");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_free_data_and_error(data, "Texture file cannot be opened");
	close(fd);
	if (check_filetype(file, ".png"))
		ft_free_data_and_error(data, "Wrong filetype, give a png -file");
}

void	get_images(t_data *data)
{
	data->walls = ft_calloc(1, sizeof(t_walls));
	data->walls->no = mlx_texture_to_image(data->m, data->txtrs->no);
	data->walls->so = mlx_texture_to_image(data->m, data->txtrs->so);
	data->walls->ea = mlx_texture_to_image(data->m, data->txtrs->ea);
	data->walls->we = mlx_texture_to_image(data->m, data->txtrs->we);
	data->walls->door = mlx_texture_to_image(data->m, data->txtrs->door);
	mlx_delete_texture(data->txtrs->no);
	mlx_delete_texture(data->txtrs->so);
	mlx_delete_texture(data->txtrs->ea);
	mlx_delete_texture(data->txtrs->we);
	mlx_delete_texture(data->txtrs->door);
}

void	get_textures(t_data *data)
{
	data->txtrs = ft_calloc(1, sizeof(struct s_textures));
	check_texture_file(data, data->scene.no);
	check_texture_file(data, data->scene.so);
	check_texture_file(data, data->scene.ea);
	check_texture_file(data, data->scene.we);
	data->txtrs->no = mlx_load_png(data->scene.no);
	data->txtrs->so = mlx_load_png(data->scene.so);
	data->txtrs->ea = mlx_load_png(data->scene.ea);
	data->txtrs->we = mlx_load_png(data->scene.we);
	data->txtrs->door = mlx_load_png("./textures/bookshelf5.png");
	get_images(data);
}
