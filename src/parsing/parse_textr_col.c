/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textr_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:27:23 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/04 17:25:39 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	set_colour_line(t_data *data, char *temp, char *pointer, int *rgb)
{
	char	*str;
	char	**splitted;
	int		i;

	str = copy_str(data, pointer);
	check_amount_of_commas(data, str);
	splitted = ft_split (str, ',');
	if (!splitted)
		ft_free_data_and_error(data, "malloc error");
	free(str);
	i = 0;
	while (splitted[i] != 0)
		check_valid_color_value(data, splitted[i++]);
	if (i != 3)
		ft_free_data_and_error(data,
			"invalid file, invalid amount color parameters");
	rgb[0] = ft_atoi(splitted[0]);
	rgb[1] = ft_atoi(splitted[1]);
	rgb[2] = ft_atoi(splitted[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		ft_free_data_and_error(data, "invalid file, colour value out of range");
	ft_free_double_array(splitted);
}

static int	check_colour_line(t_data *data, char *line)
{
	char	*pntr;
	char	*temp;

	pntr = skip_spaces(line);
	if (*pntr == '\n' || *pntr == '\0')
		return (1);
	temp = pntr;
	if (ft_strncmp(pntr, "F", 1) == 0 \
		|| ft_strncmp(pntr, "C", 1) == 0 && pntr[1] == ' ')
		pntr = skip_spaces(pntr + 1);
	if (ft_strncmp(temp, "F", 1) == 0)
	{
		if (data->scene.floor_rgb[0] != -1
			&& data->scene.floor_rgb[1] != -1 && data->scene.floor_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, F-color already set");
		return (set_colour_line(data, temp, pntr, data->scene.floor_rgb), 0);
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		if (data->scene.ceiling_rgb[0] != -1 \
		&& data->scene.ceiling_rgb[1] != -1 && data->scene.ceiling_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, C-color already set");
		return (set_colour_line(data, temp, pntr, data->scene.ceiling_rgb), 0);
	}
	return (1);
}

static int	set_texture_line(t_data *data, char *temp, char *pointer)
{
	if (ft_strncmp(temp, "NO", 2) == 0)
	{
		if (data->scene.no)
			ft_free_data_and_error(data, "invalid file, double NO path");
		return (data->scene.no = copy_str(data, pointer), 0);
	}
	else if (ft_strncmp(temp, "SO", 2) == 0)
	{
		if (data->scene.so)
			ft_free_data_and_error(data, "invalid file, double SO path");
		return (data->scene.so = copy_str(data, pointer), 0);
	}
	else if (ft_strncmp(temp, "EA", 2) == 0)
	{
		if (data->scene.ea)
			ft_free_data_and_error(data, "invalid file, double EA path");
		return (data->scene.ea = copy_str(data, pointer), 0);
	}
	else if (ft_strncmp(temp, "WE", 2) == 0)
	{
		if (data->scene.we)
			ft_free_data_and_error(data, "invalid file, double WE path");
		return (data->scene.we = copy_str(data, pointer), 0);
	}
	return (1);
}

static int	check_texture_line(t_data *data, char *line)
{
	char	*pointer;
	char	*temp;

	pointer = skip_spaces(line);
	if (*pointer == '\n' || *pointer == '\0')
		return (1);
	temp = pointer;
	if ((ft_strncmp(pointer, "NO", 2) == 0 || ft_strncmp(pointer, "SO", 2) == 0
			|| ft_strncmp(pointer, "EA", 2) == 0
			|| ft_strncmp(pointer, "WE", 2) == 0)
		&& pointer[2] == ' ')
	{
		pointer = pointer + 2;
		pointer = skip_spaces(pointer);
	}
	if (set_texture_line(data, temp, pointer) == 0)
		return (0);
	return (1);
}

static int	check_valid_line(t_data *data, char *line)
{
	if (check_texture_line(data, line) == 0)
		return (0);
	else if (check_colour_line(data, line) == 0)
		return (0);
	else
	{
		return (ft_free_data_and_error(data,
				"invalid file, invalid color or texture line"), 1);
	}
	return (1);
}

/* ==============================
 * Reads the file line by line and calls check line to check
 * that the lines contain the elements needed.
 * Doesn't yet check floor/ceiling or stop at map
 * ==============================
 */
static void	check_file_lines(t_data *data, t_check *check)
{
	char	*line;
	int		lines;

	lines = 0;
	line = NULL;
	while (lines < 6)
	{
		line = get_next_line_cub(data, data->fd);
		if (*line == '\n')
		{
			check->cur_file_line++;
			free(line);
			continue ;
		}
		else if (check_valid_line(data, line) == 0)
		{
			check->cur_file_line++;
			lines++;
		}
		free(line);
	}
}

void	check_and_set_texttr_and_col_lines(t_data *data, t_check *check)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(data, ERR_OPEN);
	check_file_lines(data, check);
	data->scene.col_ceiling = get_colour(data->scene.ceiling_rgb);
	data->scene.col_floor = get_colour(data->scene.floor_rgb);
}
