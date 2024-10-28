/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textr_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:27:23 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/25 20:38:22 by pikkak           ###   ########.fr       */
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
		ft_error(data, ERR_MALLOC);
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
		ft_error(data, "element not valid, extra characters");
	}
	return (ret);
}

/*
Skips the spaces in the beginning.
If there is some content, checks if it corresponds with the element identifiers.
Sets the variable value if it is valid.
*/

void	check_colour_line(t_data *data, char *line)
{
	char	*pointer;
	char	*temp;
	char	*str;
	char	**splitted;

	pointer = skip_spaces(line);// pointer at the beginning of the text
	if (*pointer == '\n' || *pointer == '\0')//if we are in the end of the line	
		return ;
	temp = pointer;
	if (ft_strncmp(pointer, "F", 1) == 0 || ft_strncmp(pointer, "C", 1) == 0 && pointer[1] == ' ')
	{
		pointer = pointer + 1;//skip element identifier
		pointer = skip_spaces(pointer);// skip spaces to the beginning of the path name
	}
	if (ft_strncmp(temp, "F", 1) == 0)
	{
		str = copy_str(pointer);
		splitted = ft_split (str, ',');
		if (!splitted)
			return (ft_free_data_and_error(data, "malloc error"));
		free(str);
		data->scene.floor_rgb[0] = ft_atoi(splitted[0]);
		data->scene.floor_rgb[1] = ft_atoi(splitted[1]);
		data->scene.floor_rgb[2] = ft_atoi(splitted[2]);
		ft_free_double_array(splitted);
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		str = copy_str(pointer);
		splitted = ft_split (str, ',');
		if (!splitted)
			return (ft_free_data_and_error(data, "malloc error"));
		free(str);
		data->scene.ceiling = rgb_to_hex(ft_atoi(splitted[0]), ft_atoi(splitted[1]), ft_atoi(splitted[2]), 255);
		data->scene.ceiling_rgb[0] = ft_atoi(splitted[0]);
		data->scene.ceiling_rgb[1] = ft_atoi(splitted[1]);
		data->scene.ceiling_rgb[2] = ft_atoi(splitted[2]);
		ft_free_double_array(splitted);
	}
	// add check that if the variable in question already has a value we give error
}

void	check_texture_line(t_data *data, char *line)
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
	// add check that if the variable in question already has a value we give error
	if (ft_strncmp(temp, "NO", 2) == 0)
		data->scene.no = copy_str(pointer);
	else if (ft_strncmp(temp, "SO", 2) == 0)
		data->scene.so = copy_str(pointer);
	else if (ft_strncmp(temp, "EA", 2) == 0)
		data->scene.ea = copy_str(pointer);
	else if (ft_strncmp(temp, "WE", 2) == 0)
		data->scene.we = copy_str(pointer);
}

/*
Reads the file line by line and calls check line to check that the lines contain the elements needed. Doesn't yet check floor/ceiling or stop at map
*/
void parse_file_for_walls_and_colours(t_data *data, t_check *check)
{
	char	*line;

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
		check_texture_line(data, line);
		check_colour_line(data, line);
		free(line);
	}
	free(line);
}

