/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:27:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/29 14:07:40 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_error(t_data *data, char *error)
{
	perror(error);
	if (data)
		free(data);
	exit(1);
}

void	ft_free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_data_and_error(t_data *data, char *error)
{
	int	i;

	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	i = 0;
	/*	while (i < data->scene.rows)
	{
		free(data->scene.map[i]);
		i++;
	}

	free(data->scene.map);
	if (data->scene.no != NULL)
		free(data->scene.no);
	if (data->scene.so != NULL)
		free(data->scene.so);
	if (data->scene.ea != NULL)
		free(data->scene.ea);
	if (data->scene.we != NULL)
		free(data->scene.we);
	if (data->walls)
		free(data->walls);
	if (data->txtrs)
		free(data->txtrs);
	if (data->m)
		mlx_terminate(data->m);
	free(data);*/
	data = NULL;
	exit(1);
}


void	ft_free_data_and_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->scene.rows)
	{
		free(data->scene.map[i]);
		i++;
	}
	free(data->scene.map);
	if (data->scene.no != NULL)
		free(data->scene.no);
	if (data->scene.so != NULL)
		free(data->scene.so);
	if (data->scene.ea != NULL)
		free(data->scene.ea);
	if (data->scene.we != NULL)
		free(data->scene.we);
	if (data->walls)
		free(data->walls);
	if (data->txtrs)
		free(data->txtrs);
	if (data->m)
		mlx_terminate(data->m);
	free(data);
	data = NULL;
	exit(0);
}
