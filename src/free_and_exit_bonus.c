/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:27:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/01 16:20:21 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_error(char *error)
{
	perror(error);
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
	perror(error);

	i = 0;
	while (i < 8)
	{
		free(data->scene.map[i]);
		i++;
	}
	free(data->scene.map);
	free(data);
	data = NULL;
	exit(1);
}

void	ft_free_data_and_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(data->scene.map[i]); 
		i++;
	}
	if (data->scene.no != NULL)
		free(data->scene.no);
	if (data->scene.so != NULL)
		free(data->scene.so);
	if (data->scene.ea != NULL)
		free(data->scene.ea);
	if (data->scene.we != NULL)
		free(data->scene.we);
	free(data->scene.map);
	free(data);
	data = NULL;
	exit(0);
}
