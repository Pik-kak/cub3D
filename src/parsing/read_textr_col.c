/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textr_col.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:30:37 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/08 13:54:37 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	check_valid_line(t_data *data, char *line, t_check *check)
{
	if (check_texture_line(data, line) == 0)
		return (0);
	else if (check_colour_line(data, line) == 0)
		return (0);
	else
	{
		ft_free_data_and_error(data,
			"invalid file, missing or invalid color or texture line", line);
	}
	return (1);
}

/* ==============================
 * Reads the file line by line and calls check line to check
 * that the lines contain the elements needed.
 * Doesn't yet check floor/ceiling or stop at map
 * ==============================
 */
static void	check_file_lines(t_data *data, t_check *check, int lines)
{
	char	*line;

	line = NULL;
	while (lines < 6)
	{
		line = get_next_line_cub(data, data->fd);
		if (!line || *line == '\0')
		{
			free(line);
			free_buffer_close_fd(data);
			ft_error(data, "File has not enough information");
		}
		else if (*line == '\n')
		{
			check->cur_file_line++;
			free(line);
			continue ;
		}
		else if (check_valid_line(data, line, check) == 0)
		{
			check->cur_file_line++;
			lines++;
			free(line);
		}
	}
}

void	check_and_set_texttr_and_col_lines(t_data *data, t_check *check)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(data, ERR_OPEN);
	init_buffer(data);
	check_file_lines(data, check, 0);
	data->scene.col_ceiling = get_colour(data->scene.ceiling_rgb);
	data->scene.col_floor = get_colour(data->scene.floor_rgb);
}
