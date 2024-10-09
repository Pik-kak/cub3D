/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fille_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 07:56:31 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/09 09:19:49 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
void set_colour_line(t_data *data, char *temp, char *pointer, int **rgb)
{
	char *str;
	char **splitted;
	
	str = copy_str(pointer);
	splitted = ft_split (str, ',');
	if (!splitted)
		return (ft_free_data_and_error(data, "malloc error"), 1);
	free(str);
	rgb[0] = ft_atoi(splitted[0]);
	rgb[1] = ft_atoi(splitted[1]);
	rgb[2] = ft_atoi(splitted[2]);
	ft_free_double_array(splitted);
}


int	check_colour_line(t_data *data, char *line)
{
	char	*pointer;
	char	*temp;

	pointer = skip_spaces(line);// pointer at the beginning of the text
	if (*pointer == '\n' || *pointer == '\0')//if we are in the end of the line	
		return (1);
	temp = pointer;
	if (ft_strncmp(pointer, "F", 1) == 0 || ft_strncmp(pointer, "C", 1) == 0 && pointer[1] == ' ')
	{
		pointer = pointer + 1;//skip element identifier
		pointer = skip_spaces(pointer);// skip spaces to the beginning of the path name
	}
	if (ft_strncmp(temp, "F", 1) == 0)
	{
		if (data->scene.floor_rgb)
			ft_free_data_and_error(data, "invalid file");
		return (set_colour_line(data, temp, pointer, data->scene.floor_rgb), 0);
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		if (data->scene.ceiling_rgb)
			ft_free_data_and_error(data, "invalid file");
		return (set_colour_line(data, temp, pointer, data->scene.ceiling_rgb), 0);
	}
	return (1);
}

int set_texture_line(t_data *data, char *temp, char *pointer)
{
	if (ft_strncmp(temp, "NO", 2) == 0)
	{
		if (data->scene.no)
			ft_free_data_and_error(data, "invalid file");
		return (data->scene.no = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "SO", 2) == 0)
	{
		if (data->scene.so)
			ft_free_data_and_error(data, "invalid file");
		return (data->scene.so = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "EA", 2) == 0)
	{
		if (data->scene.ea)
			ft_free_data_and_error(data, "invalid file");
		return (data->scene.ea = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "WE", 2) == 0)
	{
		if (data->scene.we)
			ft_free_data_and_error(data, "invalid file");
		return (data->scene.we = copy_str(pointer), 0);
	}
	return (1);
}

int	check_texture_line(t_data *data, char *line)
{
	char	*pointer;
	char	*temp;

	pointer = skip_spaces(line);// pointer at the beginning of the text
	if (*pointer == '\n' || *pointer == '\0')//if we are in the end of the line	
		return ;
	temp = pointer;
	if ((ft_strncmp(pointer, "NO", 2) == 0 || ft_strncmp(pointer, "SO", 2) == 0 
		|| ft_strncmp(pointer, "EA", 2) == 0 || ft_strncmp(pointer, "WE", 2) == 0) 
		&& pointer[2] == ' ')
	{
		pointer = pointer + 2;//skip element identifier
		pointer = skip_spaces(pointer);// skip spaces to the beginning of the path name
	}
	if (set_texture_line(data, temp, pointer) == 0)
		return (0);
	return (1);
}

int check_invalid_line(t_data *data, char *line)
{
	if (check_texture_line(data, line)  == 0)
		return (0);
	if (check_colour_line(data, line) == 0)
		return (0);
}

int check_map_lines(t_data *data, t_check *check)
{
	char	*line;
	int lines;
	int i; 
	
	i = 0;
	lines = 0;
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
			continue ;
		}
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && line[i] != 'W' && line[i] != '\n')
				return (1);
			i++;
		}
		free(line);
	}
	return (0);
}

/*
Reads the file line by line and calls check line to check that the lines contain the elements needed. Doesn't yet check floor/ceiling or stop at map
*/
void check_file_lines(t_data *data)
{
	char	*line;
	int lines;

	lines = 0;
	line = NULL;
	while (lines < 7)
	{
		line = get_next_line(data->fd);
		if (!line)
		{
			break;
		}
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		else if (check_invalid_line == 0)
			lines++;
		free(line);
	}
}

void	check_and_set_texttr_and_col_lines(t_data *data, t_check *check)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(ERR_OPEN);
	check_file_lines(data);
	close(data->fd);
}