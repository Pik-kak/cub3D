/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:41:15 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:41:18 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
Checks that the file type ends with .cub
*/
int	check_filetype(char *filename, char *filetype)
{
	char			*file_end;
	unsigned int	i;

	i = 0;
	file_end = ft_strrchr(filename, '.');
	if (!file_end)
		return (ERROR);
	while (file_end[i] != '\0' && filetype[i] == file_end[i])
		i++;
	return (file_end[i] - filetype[i]);
}

/*
rgb to hexadecimal 
*/
unsigned int	rgb_to_hex(int r, int g, int b, int alpha)
{
	return ((alpha << 24) | (r << 16) | (g << 8) | b);
}

/*
Skips spaces 
*/
char	*skip_spaces(char *line)
{
	int		i;
	char	*pointer;

	i = 0;
	while (line[i] == ' ')
		i++;
	pointer = &line[i];
	return (pointer);
}

void	allocate_map(t_data *data)
{
	int	row;

	row = 0;
	data->scene.map = malloc(data->scene.rows * sizeof(int *));
	if (!data->scene.map)
	{
		ft_free_data_and_error(data, ERR_MALLOC);
	}
	while (row < data->scene.rows)
	{
		data->scene.map[row] = malloc(data->scene.cols * sizeof(int));
		if (!data->scene.map[row])
		{
			ft_free_data_and_error(data, ERR_MALLOC);
		}
		row++;
	}
}
