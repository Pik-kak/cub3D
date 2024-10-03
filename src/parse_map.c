/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/03 15:10:40 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


int check_map_line(char *line, t_check *check)
{
	int i;
	int found_map;

	i = 0;
	found_map = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && line[i] != 'W' && line[i] != '\n')
			return (1);
		else if (line[i] == '1')
			found_map = 1;
		i++;
	}
	if (found_map == 0)
		return (1);
	return (0);
}

void fill_row(t_data *data, char *line, int row)
{
	int i;
	int cols;
	
	i = 0;
	cols = 0;
	data->scene.map[row][cols] = 2;
	cols++;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == ' ')
			data->scene.map[row][cols] = 2;
		else if(line[i] == '1')
			data->scene.map[row][cols] = 1;
		else if (line[i] == '0')
			data->scene.map[row][cols] = 0;
		else if (line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W')
			data->scene.map[row][cols] = 0;
		i++;
		cols++;
	}
	while(cols < data->scene.cols)
	{
		data->scene.map[row][cols] = 2;
		cols++;
	}
}

void fill_extra_row(t_data *data, int row)
{
	int i;
	
	i = 0;
	while (i < data->scene.cols)
	{
		data->scene.map[row][i] = 2;
		i++;
	}
}

void fill_map(t_data *data, t_check *check)
{
	char	*line;
	int		lines;
	int		row;
	
	row = 0;
	lines = 1;
	line = NULL;
	fill_extra_row(data, row);
	row++;
	while(lines < check->first_map_line)
	{
		line = get_next_line(data->fd);
		free(line);
		lines++;
	}
	while (lines <= check->first_map_line + check->map_lines)
	{
		line = get_next_line(data->fd);
		if (!line)
			break;
		fill_row(data, line, row);
		free(line);
		lines++;
		row++;
	}
	fill_extra_row(data, row);
	free(line);
}


void read_file_for_longest_map_line(t_data *data, t_check *check)
{
	char	*line;
	int		line_before;
	
	line_before = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
		{
			break;
		}
		if (*line == '\n')
		{
			free(line);
			line_before++;
			continue ;
		}
		if (check_map_line(line, check) == 0)
		{
			check->map_lines++;	
			check->first_map_line = line_before + 1;
			if (ft_strlen(line) >= check->longest_line)
				check->longest_line = ft_strlen(line) - 1;
			free(line);
			continue;
		}
		else
			line_before++;
		free(line);
	}
	free(line);
}
