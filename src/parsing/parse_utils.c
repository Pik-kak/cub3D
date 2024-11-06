/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
/*   Updated: 2024/11/06 14:13:01 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

//helper function to check that there is no illegal char's in map
int	check_map_line(char *line, t_check *check)
{
	int	i;

	i = 0;
	if ((line[i] != ' ' && line[i] != '1') || line[i] == '\n')
		return (1);
	while (line[i] != '\0')
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

/*
Checks that the file type ends with .cub
*/
int	check_filetype(char *filepath, char *filetype)
{
	char			*file_end;
	char			*filename;
	unsigned int	i;

	i = 0;
	filename = ft_strrchr(filepath, '/');
	if (filename)
	{
		filename++;
		if (ft_isalnum(*filename) == 0)
			return (1);
	}
	file_end = ft_strrchr(filepath, '.');
	if (!file_end)
		return (1);
	while (file_end[i] != '\0' && filetype[i] == file_end[i])
		i++;
	return (file_end[i] - filetype[i]);
}

/*
Skips spaces 
*/
char	*skip_spaces(char *line)
{
	int		i;
	char	*pointer;

	i = 0;
	while (line[i] == ' ')
		i++;
	pointer = &line[i];
	return (pointer);
}

void	allocate_map(t_data *data)
{
	int	row;

	row = 0;
	data->scene.map = malloc(data->scene.rows * sizeof(int *));
	if (!data->scene.map)
	{
		ft_free_data_and_error(data, ERR_MALLOC);
	}
	while (row < data->scene.rows)
	{
		data->scene.map[row] = malloc(data->scene.cols * sizeof(int));
		if (!data->scene.map[row])
		{
			ft_free_data_and_error(data, ERR_MALLOC);
		}
		row++;
	}
}
