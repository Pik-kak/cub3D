/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
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

unsigned int rgb_to_hex(int r, int g, int b, int alpha)
{
	return (alpha << 24) | (r << 16) | (g << 8) | b;
}


/*
Skips spaces 
*/


char *skip_spaces(char *line)
{
	int		i;
	char	*pointer;

	i  = 0;
	while (line[i] == ' ')
		i++;
	pointer = &line[i];
	return (pointer);
}

void allocate_map(t_data *data)
{
	int row;

	row = 0;
	data->scene.map = malloc(data->scene.rows * sizeof(int*));
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



void	flood_fill(t_data *data, t_point size, t_point cur, int to_fill)
{
	int **matrix = data->scene.map;

	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
		return;
	if (matrix[cur.y][cur.x] != 1 && matrix[cur.y][cur.x] != 32 && matrix[cur.y][cur.x] != -1)
	{
		ft_free_data_and_error(data, "invalid file");
	}
	if (matrix[cur.y][cur.x] == 1 || matrix[cur.y][cur.x] == -1)
		return;
	matrix[cur.y][cur.x] = -1;
	flood_fill(data, size, (t_point){cur.x - 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x + 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y - 1}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y + 1}, to_fill);
}


