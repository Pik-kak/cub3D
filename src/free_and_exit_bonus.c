/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:27:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/09/26 15:56:28 by tsaari           ###   ########.fr       */
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
	free(data->scene.map);
	free(data);
	data = NULL;
	exit(0);
}