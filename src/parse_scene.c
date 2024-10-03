/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:08:05 by kkauhane          #+#    #+#             */
/*   Updated: 2024/10/03 14:52:30 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
- Check the file type
- Read the file until you find all the elements before the map.
  If you reach the map(1) and all the elements are not found, or if there are extra elements/map doesnt start with 1 return error.
- Check that the elements are correct (the paths are real paths and the rgb values are between 0-255)
- Read the map, checking that there are no extra symbols and count the size of the map(lengt/width) by finding the longest line.
- Change the spaces to '2's
- Check that the map is surrounded by walls on all sides and if there are spaces around them as well
*/


void allocate_map(t_data *data, t_check *check)
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


/*
Opens ffile several times and runs parsing aand check functions
*/
void	check_and_parse_file(t_data *data, t_check *check)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(ERR_OPEN);
	parse_file_for_walls_and_colours(data, check);
	close(data->fd);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(ERR_OPEN);
	read_file_for_longest_map_line(data, check);
	close(data->fd);
	data->scene.rows = check->map_lines + 2;
	data->scene.cols = check->longest_line + 2;
	allocate_map(data, check);
	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		ft_error(ERR_OPEN);
	fill_map(data, check);
	close(data->fd);
}

/*
Checks that the file type ends with .cub
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


void set_player_position(t_player *player, char dir, int i, int ii)
{
	player->px = ii * BLOCK_SIZE;
	player->py = i * BLOCK_SIZE;
	if (dir == 'N')
		player->direction = 3 / 2 * PI;
	if (dir == 'E')
		player->direction = 0;
	if (dir == 'S')
		player->direction = PI / 2;
	if (dir == 'W')
		player->direction = PI;
}

void	check_map(t_data *data)
{
	int	i;
	int	ii;
	int player_found;

	player_found = 0;
	i = -1;
	while (data->scene.map[i++] != NULL)
	{
		ii = 0;
		while (data->scene.map[i][ii] != '\0')
		{
			if (data->scene.map[i][ii] == 'N' || data->scene.map[i][ii] == 'S' 
                 || data->scene.map[i][ii] == 'E' || data->scene.map[i][ii] == 'W')
			{
				set_player_position(&data->scene.player, data->scene.map[i][ii], i, ii);
				player_found++;
			}
			else if (data->scene.map[i][ii] != '0' && data->scene.map[i][ii] != '1' && data->scene.map[i][ii] != ' ')
				ft_free_data_and_error(data, "map not valid");
			ii++;
		}
	}
	if (player_found != 1)
		ft_free_data_and_error(data, "map not valid");
}
