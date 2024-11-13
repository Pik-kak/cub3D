/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textr_col_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:27:23 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/13 14:23:48 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	set_colour_to_rgb(t_data *data, int *rgb, char **spl, char *line)
{
	rgb[0] = ft_atoi(spl[0]);
	rgb[1] = ft_atoi(spl[1]);
	rgb[2] = ft_atoi(spl[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
	{
		ft_free_double_array(spl);
		ft_free_data_and_error(data,
			"invalid file, colour value out of range", line);
	}
}

static void	set_col_line(t_data *data, char *pointer, int *rgb, char *line)
{
	char	*str;
	char	**splitted;
	int		i;

	i = 0;
	str = copy_str(data, pointer, line);
	check_amount_of_commas(data, str, line);
	splitted = ft_split (str, ',');
	free(str);
	if (!splitted)
	{
		ft_free_double_array(splitted);
		ft_free_data_and_error(data, "malloc error", line);
	}
	while (splitted[i] != 0)
		check_valid_color_value(data, splitted[i++], line);
	if (i != 3)
	{
		ft_free_double_array(splitted);
		ft_free_data_and_error(data,
			"invalid file, invalid amount color parameters", line);
	}
	set_colour_to_rgb(data, rgb, splitted, line);
	ft_free_double_array(splitted);
}

int	check_colour_line(t_data *data, char *line)
{
	char	*pointer;
	char	*temp;

	pointer = skip_spaces(line);
	if (*pointer == '\n' || *pointer == '\0')
		return (1);
	temp = pointer;
	if (ft_strncmp(pointer, "F", 1) == 0 \
		|| ft_strncmp(pointer, "C", 1) == 0 && pointer[1] == ' ')
		pointer = skip_spaces(pointer + 1);
	if (ft_strncmp(temp, "F", 1) == 0)
	{
		if (data->scene.floor_rgb[0] != -1
			&& data->scene.floor_rgb[1] != -1 && data->scene.floor_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, double F-color", line);
		return (set_col_line(data, pointer, data->scene.floor_rgb, line), 0);
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		if (data->scene.ceiling_rgb[0] != -1 \
		&& data->scene.ceiling_rgb[1] != -1 && data->scene.ceiling_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, double C-color", line);
		return (set_col_line(data, pointer, data->scene.ceiling_rgb, line), 0);
	}
	return (1);
}

static int	set_texture_line(t_data *data, char *temp, char *ptr, char *line)
{
	if (ft_strncmp(temp, "NO", 2) == 0)
	{
		if (data->scene.no)
			ft_free_data_and_error(data, "invalid file, double NO path", line);
		return (data->scene.no = copy_str(data, ptr, line), 0);
	}
	else if (ft_strncmp(temp, "SO", 2) == 0)
	{
		if (data->scene.so)
			ft_free_data_and_error(data, "invalid file, double SO path", line);
		return (data->scene.so = copy_str(data, ptr, line), 0);
	}
	else if (ft_strncmp(temp, "EA", 2) == 0)
	{
		if (data->scene.ea)
			ft_free_data_and_error(data, "invalid file, double EA path", line);
		return (data->scene.ea = copy_str(data, ptr, line), 0);
	}
	else if (ft_strncmp(temp, "WE", 2) == 0)
	{
		if (data->scene.we)
			ft_free_data_and_error(data, "invalid file, double WE path", line);
		return (data->scene.we = copy_str(data, ptr, line), 0);
	}
	return (1);
}

int	check_texture_line(t_data *data, char *line)
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
	if (set_texture_line(data, temp, pointer, line) == 0)
		return (0);
	return (1);
}
