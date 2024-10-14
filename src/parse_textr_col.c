/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textr_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:27:23 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/14 13:16:36 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
Mallocs a copy and copies the string until ' ', ' \n' or '\0' and returns the copy
if there is content after the path returns error
*/
char	*copy_str(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while(line[i] && line[i] != ' ' && line[i] != '\n')//while there is content other than ' ', ' \n' or '\0'
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc((i + 1) * sizeof(char));//mallocs the path string
	if (!ret)
		ft_error(ERR_MALLOC);
	i = 0;
	while(line[i] != ' ' && line[i] != '\n' && line[i])//copies the path
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '\0';
	line = skip_spaces(&line[i]);//skips the spaces after the path
	if (*line != '\n' && *line!= '\0')// if there is something else in the end returns 
	{
		free(ret);
		ft_error("element not valid, extra characters");
	}
	return (ret);
}

/*
Skips the spaces in the beginning.
If there is some content, checks if it corresponds with the element identifiers.
Sets the variable value if it is valid.
*/

void set_colour_line(t_data *data, char *temp, char *pointer, int *rgb)
{
	char *str;
	char **splitted;
	
	str = copy_str(pointer);
	splitted = ft_split (str, ',');
	if (!splitted)
		ft_free_data_and_error(data, "malloc error");
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
		if (data->scene.floor_rgb[0] != -1 && data->scene.floor_rgb[1] != -1 && data->scene.floor_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, floor color allready set");
		return (set_colour_line(data, temp, pointer, data->scene.floor_rgb), 0);
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		if (data->scene.ceiling_rgb[0] != -1 && data->scene.ceiling_rgb[1] != -1 && data->scene.ceiling_rgb[2] != -1)
			ft_free_data_and_error(data, "invalid file, ceiling color allready set");
		return (set_colour_line(data, temp, pointer, data->scene.ceiling_rgb), 0);
	}
	return (1);
}

int set_texture_line(t_data *data, char *temp, char *pointer)
{
	if (ft_strncmp(temp, "NO", 2) == 0)
	{
		if (data->scene.no)
			ft_free_data_and_error(data, "invalid file, double north texture path");
		return (data->scene.no = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "SO", 2) == 0)
	{
		if (data->scene.so)
			ft_free_data_and_error(data, "invalid file, double south texture path");
		return (data->scene.so = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "EA", 2) == 0)
	{
		if (data->scene.ea)
			ft_free_data_and_error(data, "invalid file, double east texture path");
		return (data->scene.ea = copy_str(pointer), 0);
	}
	else if (ft_strncmp(temp, "WE", 2) == 0)
	{
		if (data->scene.we)
			ft_free_data_and_error(data, "invalid file, double west texture path");
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
		return (1);
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

int check_valid_line(t_data *data, char *line)
{
	if (check_texture_line(data, line)  == 0)
		return (0);
	else if (check_colour_line(data, line) == 0)
		return (0);
	else
	{
		return (ft_free_data_and_error(data, "invalid file"), 1);
	}
	return (1);
}



/*
Reads the file line by line and calls check line to check that the lines contain the elements needed. Doesn't yet check floor/ceiling or stop at map
*/
void check_file_lines(t_data *data, t_check *check)
{
	char	*line;
	int lines;

	lines = 0;
	line = NULL;
	while (lines < 6)
	{
		line = get_next_line(data->fd);
		if (!line)
		{
			ft_free_data_and_error(data, "malloc error");
		}
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
		ft_error(ERR_OPEN);
	check_file_lines(data, check);
}

