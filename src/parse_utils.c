/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/11 12:54:58 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
rgb to hexadecimal 
*/

int	check_file_type(t_data *data, t_check *check)
{
	char			*file_name;
	char			*file_type;
	unsigned int	i;

	i = 0;
	file_type = ".cub";
	file_name = ft_strrchr(data->file, '.');
	if (!file_name)
		return (ERROR);
	while (file_name[i] != '\0' && file_type[i] == file_name[i])
		i++;
	return (file_name[i] - file_type[i]);
}

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
		ft_free_data_and_error(data, "malloc error");
	}
	while (row < data->scene.rows)
	{
		data->scene.map[row] = malloc(data->scene.cols * sizeof(int));
		if (!data->scene.map[row])
		{
			ft_free_data_and_error(data, "malloc error");
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
		return;
	}
	if (matrix[cur.y][cur.x] == 1 || matrix[cur.y][cur.x] == -1)
		return;
	matrix[cur.y][cur.x] = -1;
	flood_fill(data, size, (t_point){cur.x - 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x + 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y - 1}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y + 1}, to_fill);
}



/*int	fill(int **matrix, t_point size, t_point cur, int to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x || matrix[cur.y][cur.x] != to_fill)
		return (0);

	matrix[cur.y][cur.x] = 2;
	fill(matrix, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(matrix, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(matrix, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(matrix, size, (t_point){cur.x, cur.y + 1}, to_fill);
	return (0);
}*/

/*int fill(t_data *data, int **matrix, t_fpoint size, t_fpoint cur, int to_fill)
{
	
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x  || matrix[cur.x][cur.y] != 32)
		return (0);
	//if (matrix[cur.y][cur.x] != to_fill && matrix[cur.y][cur.x] != 1)
	//	return (1);
	if (matrix[cur.y][cur.x] == to_fill)
		matrix[cur.y][cur.x] = 2;
	fill(data, matrix, size, (t_fpoint){cur.x - 1, cur.y}, to_fill); // left
	fill(data, matrix, size, (t_fpoint){cur.x + 1, cur.y}, to_fill); // right
	fill(data, matrix, size, (t_fpoint){cur.x, cur.y - 1}, to_fill); // up
	fill(data, matrix, size, (t_fpoint){cur.x, cur.y + 1}, to_fill); // down

	return (0);
}

void flood_fill(t_data *data)
{
	t_fpoint begin;
	t_fpoint last;
	
	last.x = data->scene.cols - 1;
	last.y = data->scene.rows - 1;
	begin.x = 0;
	begin.y = 0;

	if (fill(data, data->scene.map, last, begin, 32) != 0)
		ft_free_data_and_error(data, "invalid map");
}*/

