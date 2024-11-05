/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/05 17:59:58 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

//helper function to check that there is no illegal char's in map
static int	check_map_line(char *line, t_check *check)
{
	int	i;

	i = 0;
	if ((line[i] != ' ' && line[i] != '1') || line[i] == '\n')
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '2'
			&& line[i] != '0' && line[i] != 2 && line[i] != 'N'
			&& line[i] != 'E' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	set_check(t_check *check, char *line)
{
	char	*temp;

	check->map_lines++;
	if (ft_strlen(line) >= check->longest_line)
	{
		temp = ft_strtrim(line, "\n");
		check->longest_line = ft_strlen(temp);
		free (temp);
	}
}

int	read_next_line(t_data *data, int map_found, char *line, t_check *check)
{
	line = get_next_line_cub(data, data->fd);
	if (!line)
		return (1);
	if (*line == '\n')
	{
		if (map_found == 1)
		{
			free(line);
			return (1);
		}
		check->cur_file_line++;
	}
	else if (check_map_line(line, check) == 0)
	{
		map_found = 1;
		set_check(check, line);
	}
	free(line);
	return (0);
}

//finds out a number of lines and checks the longest line for allocation
void	read_file_for_longest_and_lines(t_data *data, t_check *check)
{
	char	*line;
	int		i;
	int		map_found;

	i = 0;
	map_found = 0;
	line = NULL;
	while (i < check->cur_file_line)
	{
		line = get_next_line_cub(data, data->fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
	while (1)
	{
		if (read_next_line(data, map_found, line, check) == 1)
			break ;
	}
	close(data->fd);
	data->scene.rows = check->map_lines + 10;
	data->scene.cols = check->longest_line + 10;
	if (data->scene.cols > 1000 || data->scene.rows > 1000)
		ft_free_data_and_error(data, "invalid file, map is too big");
}

/* ==============================
 *	after checking and etting texttures and colors in parse_textr_col.c
 * this checks that there is no unallowed charachters after that
 * ==============================
 */
void	check_map_lines(t_data *data, t_check *check)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line_cub(data, data->fd);
		if (!line)
		{
			close(data->fd);
			break ;
		}
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		else if (check_map_line(line, check) != 0)
		{
			close(data->fd);
			ft_free_data_and_error(data,
				"invalid file, map not correct or extra lines before map");
		}
		free(line);
		close(data->fd);
	}
}
