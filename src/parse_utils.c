/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:19 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/09 12:44:05 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
rgb to hexadecimal 
*/

int	check_file_type(t_data *data, t_check *check)
{
	char			*file_name;
	char			*file_type;
	unsigned int	i;

	i = 0;
	file_type = ".cub";
	file_name = ft_strrchr(data->file, '.');
	if (!file_name)
		return (ERROR);
	while (file_name[i] != '\0' && file_type[i] == file_name[i])
		i++;
	return (file_name[i] - file_type[i]);
}

unsigned int rgb_to_hex(int r, int g, int b, int alpha)
{
	return (alpha << 24) | (r << 16) | (g << 8) | b;
}


/*
Skips spaces 
*/


char *skip_spaces(char *line)
{
	int		i;
	char	*pointer;

	i  = 0;
	while (line[i] == ' ')
		i++;
	pointer = &line[i];
	return (pointer);
}

void allocate_map(t_data *data)
{
	int row;

	row = 0;
	data->scene.map = malloc(data->scene.rows * sizeof(int*));
	if (!data->scene.map)
	{
		ft_free_data_and_error(data, "malloc error");
	}
	while (row < data->scene.rows)
	{
		data->scene.map[row] = malloc(data->scene.cols * sizeof(int));
		if (!data->scene.map[row])
		{
			ft_free_data_and_error(data, "malloc error");
		}
		row++;
	}
}