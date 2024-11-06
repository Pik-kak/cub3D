/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:57 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 15:46:38 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	read_next_line(t_data *data, int *map_found, char *line, t_check *check)
{
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
	else if (check_map_line(line, check) == 0)
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
		if (read_next_line(data, &map_found, line, check) == 1)
			break ;
	}
	close(data->fd);
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
		free(line);
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
