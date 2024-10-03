/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/03 11:13:33 by tsaari           ###   ########.fr       */
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

void read_file_for_longest_map_line(t_data *data, t_check *check)
{
	char	*line;
	int		line_count;

	line_count = 0;
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
			line_count++;
			continue ;
		}
		if (check_map_line(line, check) == 0)
		{
			printf("line count %d", line_count);
			check->first_map_line = line_count;
			if (ft_strlen(line) >= check->longest_line)
				check->longest_line = ft_strlen(line);
			free(line);
			continue;
		}
		else
			line_count++;
		free(line);
	}
	free(line);
}
