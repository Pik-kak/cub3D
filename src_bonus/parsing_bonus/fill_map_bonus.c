/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:40:10 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 14:40:14 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

//raeds line and fills every row
static void	fill_row(t_data *data, char *line, int row)
{
	int	i;
	int	cols;

	i = 0;
	cols = -1;
	if (line[i] == '\n' || ft_strlen(line) < 2)
		ft_free_data_and_error(data, "invalid file");
	while (cols++ < SPACE_AROUND_MAP)
		data->scene.map[row][cols] = ' ';
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == ' ')
			data->scene.map[row][cols] = 32;
		else if (line[i] == '1')
			data->scene.map[row][cols] = 1;
		else if (line[i] == '0')
			data->scene.map[row][cols] = 0;
		else if (line[i] == '2')
			data->scene.map[row][cols] = 2;
		else
			data->scene.map[row][cols] = line[i];
		i++;
		cols++;
	}
	while (cols < data->scene.cols)
	{
		data->scene.map[row][cols] = ' ';
		cols++;
	}
}

//extra rows added with ' ' 
static void	fill_extra_row(t_data *data, int row)
{
	int	i;

	i = 0;
	while (i < data->scene.cols)
	{
		data->scene.map[row][i] = ' ';
		i++;
	}
}

/* ==============================
 *	after checks this fills 2D arrow with map content and adds
 * ' ' around everything
 * ==============================
 */
void	fill_map(t_data *data, t_check *check)
{
	char	*line;
	int		lines;
	int		row;

	row = 0;
	lines = 1;
	line = NULL;
	while (row < SPACE_AROUND_MAP)
	{
		fill_extra_row(data, row);
		row++;
	}
	while (lines <= check->cur_file_line)
	{
		line = get_next_line_cub(data, data->fd);
		free(line);
		lines++;
	}
	while (lines <= check->cur_file_line + check->map_lines)
	{
		line = get_next_line_cub(data, data->fd);
		if (!line)
			break ;
		fill_row(data, line, row);
		free(line);
		lines++;
		row++;
	}
	while (row < check->map_lines + 2 * SPACE_AROUND_MAP)
	{
		fill_extra_row(data, row);
		row++;
	}
}

void	flood_fill(t_data *data, t_point size, t_point cur, int to_fill)
{
	int	**matrix;

	matrix = data->scene.map;
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
		return ;
	if (matrix[cur.y][cur.x] != 1 && matrix[cur.y][cur.x] != 32
		&& matrix[cur.y][cur.x] != -1)
	{
		ft_free_data_and_error(data, "invalid file");
		return ;
	}
	if (matrix[cur.y][cur.x] == 1 || matrix[cur.y][cur.x] == -1)
		return ;
	matrix[cur.y][cur.x] = -1;
	flood_fill(data, size, (t_point){cur.x - 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x + 1, cur.y}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y - 1}, to_fill);
	flood_fill(data, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	fill_maze_if_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->scene.rows)
	{
		j = 0;
		while (j < data->scene.cols)
		{
			if (data->scene.map[i][j] == 32)
				data->scene.map[i][j] = 1;
			j++;
		}
		i++;
	}
}
