/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 15:21:10 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"


//helper function to check that there is no illegal char's in map
static int	check_map_line(char *line)
{
	int	i;

	i = 0;
	if ((line[i] != ' ' && line[i] != '1') || line[i] == '\n')
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '2'
			&& line[i] != '0' && line[i] != 'N'
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

int	read_next_line(t_data *data, int map_found, t_check *check)
{
	char *line;
	
	line = NULL;
	line = get_next_line_cub(data, data->fd);
	if (!line)
		return (1);
	if (*line == '\n')
	{
		if (*map_found == 1)
		{
			free(line);
			return (1);
		}
		check->cur_file_line++;
	}
	else if (check_map_line(line) == 0)
	{
		*map_found = 1;
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
		free(line);
		i++;
	}
	while (1)
	{
		if (read_next_line(data, map_found, check) == 1)
			break ;
	}
	close(data->fd);
	free(data->buffer);
	if (check->map_lines > 1000 || check->longest_line > 1000)
		ft_free_data_and_error(data, "invalid file, map is too big");
	data->scene.rows = check->map_lines + 10;
	data->scene.cols = check->longest_line + 10;
}

static char	*skip_empty_lines_at_beginning(t_data *data, t_check *check)
{
	char	*line;

	line = get_next_line_cub(data, data->fd);
	if (!line)
	{
		close(data->fd);
		ft_free_data_and_error(data, "invalid file, no map");
	}
	while (*line == '\n')
	{
		line = get_next_line_cub(data, data->fd);
		if (!line)
		{
			close(data->fd);
			ft_free_data_and_error(data, "invalid file, no map");
		}
	}
	return (line);
}

/* ==============================
 *	after checking and getting textures and colors in parse_textr_col.c
 * this checks that there is no unallowed characters after that
 * ==============================
 */
void	check_map_lines(t_data *data, t_check *check)
{
	char	*line;

	line = skip_empty_lines_at_beginning(data, check);
	while (1)
	{
		if (check_map_line(line, check) != 0)
		{
			free(data->buffer);
			close(data->fd);
			free(line);
			ft_free_data_and_error(data,
				"invalid file, map not correct or extra lines before map");
		}
		free(line);
		line = get_next_line_cub(data, data->fd);
		if (!line)
		{
			close(data->fd);
			break ;
		}
	}
}
